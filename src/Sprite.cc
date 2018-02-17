/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Sprite.hh"
#include <vector>
#include <Entropy/Theia/GL/Bind.hh>

using namespace Entropy::Asteria;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;
using namespace std;

Sprite::Sprite(const shared_ptr<Texture> &t) :
	SharedData<detail::sprite_data>(),
	Object(),
	_texture(t),
	_position(0, 0, 0),
	_is_flipped(false)
{
	// 2018-01-08 AMR TODO: is this always necessary?
	// 2018-01-08 AMR TODO: is this where we want to do this?
	_texture->generateMipmaps();
}

Sprite::Sprite(const Sprite &) = default;
Sprite::Sprite(Sprite &&) = default;
Sprite::~Sprite() = default;

void Sprite::setTexture(const shared_ptr<Texture> &t)
{
	// 2018-01-16 AMR TODO: avoid doing this here
	t->generateMipmaps();
	_texture = t;
}

const shared_ptr<Texture> &Sprite::getTexture() const
{
	return _texture;
}

void Sprite::Translate(const Vertex &offset)
{
	_position += offset;

	Vertex v = offset;
	if(_is_flipped) {
		v.x = -v.x;
	}

	Object::Translate(v);
}

const Vertex &Sprite::Position() const
{
	return _position;
}

void Sprite::Flip()
{
	_is_flipped = !_is_flipped;
	Rotate(180, Vertex(0, 1, 0));
}

bool Sprite::isFlipped() const
{
	return _is_flipped;
}

void Sprite::Draw()
{
	Bind
		p(shared()->program),
		a(shared()->array),
		e(shared()->elements),
		t(*_texture)
	;

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void Sprite::UpdateModel()
{
	shared()->program.SetUniform("model"s, Model());
}

void Sprite::UpdateScreen(const Screen &s)
{
	shared()->program.SetUniform("projection"s, s.Perspective());
}

void Sprite::UpdateCamera(const Camera &c)
{
	shared()->program.SetUniform("view"s, c.View());
}

using namespace Entropy::Asteria::detail;

sprite_data::sprite_data()
	: program(), array(), elements(Buffer::Element)
{
	// 2018-01-08 AMR TODO: is this always necessary?
	// 2018-01-08 AMR TODO: is this where we want to do this?
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 2018-01-08 AMR TODO: move to external file and load w/ Mnemosyne
	string vert_code =
		"#version 130\n"

		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"

		"in vec2 in_position;"
		"in vec2 in_texture_pos;"

		"out vec2 texture_pos;"

		"void main() {"
			"texture_pos = in_texture_pos;"
			"gl_Position = projection * view * model * vec4(in_position, 0.0, 1.0);"
		"}"
	;

	string frag_code =
		"#version 130\n"

		"uniform sampler2D uni_texture;"

		"in vec2 texture_pos;"

		"out vec4 out_color;"

		"void main() {"
			"out_color = texture(uni_texture, texture_pos);"
		"}"
	;

	Shader vert(Shader::Vertex, vert_code);
	Shader frag(Shader::Fragment, frag_code);

	program.Attach(vert);
	program.Attach(frag);
	program.Link();

	struct vertex {
		struct {
			Dimension x;
			Dimension y;
		} position;
		struct {
			Dimension x;
			Dimension y;
		} texture;
	};

	vector<vertex> vertices = {
		{		// top right
			{
				0.5f, 0.5f
			}, {
				1.0f, 0.0f
			},
		}, {	// bottom right
			{
				0.5f, -0.5f
			}, {
				1.0f, 1.0f
			},
		}, {	// bottom left
			{
				-0.5f, -0.5f
			}, {
				0.0f, 1.0f
			},
		}, {	// top left
			{
				-0.5f, 0.5f
			}, {
				0.0f, 0.0f
			},
		},
	};

	vector<unsigned short> element_data = {
		0, 1, 3,
		1, 2, 3
	};

	Buffer vbo(Buffer::Vertex);
	vbo.Data(vertices, Buffer::Static);
	elements.Data(element_data, Buffer::Static);

	array.Bind(program, vbo, "in_position"s, 2, GL_FLOAT, sizeof(vertex), offsetof(vertex, position));
	array.Bind(program, vbo, "in_texture_pos"s, 2, GL_FLOAT, sizeof(vertex), offsetof(vertex, texture));
}

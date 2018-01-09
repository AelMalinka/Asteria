/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "World.hh"
#include "../Application.hh"
#include <Entropy/Mnemosyne/Resources/Texture.hh>

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Asteria;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;
using namespace Entropy::Mnemosyne;
using namespace Entropy;
using namespace std;

World::World(Mnemosyne::Application &app)
	: Mode(app), _player(), _floor(), _wall()
{
	auto player = App().load("Character.png", Resources::Texture(Texture::Texture2D));
	auto floor = App().load("Grass.png", Resources::Texture(Texture::Texture2D));
	auto wall = App().load("Mountain.png", Resources::Texture(Texture::Texture2D));

	auto height = 7;
	auto width = 13;
	for(auto x = -width; x <= width; x++) {
		for(auto y = -height; y <= height; y++) {
			auto t = make_shared<Tile>(floor.shared());

			t->Translate(Vertex(x, y, 0));
			_floor.push_back(t);
		}
	}

	for(auto x = -width - 1; x <= width + 1; x++) {
		{
			auto t = make_shared<Tile>(wall.shared(), true);

			t->Translate(Vertex(x, height + 1, 0));
			_wall.push_back(t);
		}
		{
			auto t = make_shared<Tile>(wall.shared(), true);

			t->Translate(Vertex(x, -height - 1, 0));
			_wall.push_back(t);
		}
	}

	for(auto y = -height - 1; y <= height + 1; y++) {
		{
			auto t = make_shared<Tile>(wall.shared(), true);

			t->Translate(Vertex(width + 1, y, 0));
			_wall.push_back(t);
		}
		{
			auto t = make_shared<Tile>(wall.shared(), true);

			t->Translate(Vertex(-width - 1, y, 0));
			_wall.push_back(t);
		}
	}

	_player = make_shared<Character>(player.shared(), 0, 0, 0, 0, 0, 0);

	for(auto &t : _floor) {
		Current().addDrawable(t);
	}
	for(auto &t : _wall) {
		Current().addDrawable(t);
	}

	Current().addDrawable(_player);
	Current().getCamera().setPosition(Vertex(0, 0, 5));
}

void World::onEvent(const Entropy::Event &ev)
{
	if(ev.Id() == Theia::Events::Key::Id) {
		const Theia::Events::Key &k = dynamic_cast<const Theia::Events::Key &>(ev);
		if(k.Action() == GLFW_PRESS || k.Action() == GLFW_REPEAT) {
			if(k.Code() == GLFW_KEY_ESCAPE) {
				dynamic_cast<Application &>(App()).Menu();
			} else if(k.Code() == GLFW_KEY_LEFT) {
				_player->Translate(Vertex(-1.0, 0.0, 0.0));
			} else if(k.Code() == GLFW_KEY_RIGHT) {
				_player->Translate(Vertex(1.0, 0.0, 0.0));
			} else if(k.Code() == GLFW_KEY_DOWN) {
				_player->Translate(Vertex(0.0, -1.0, 0.0));
			} else if(k.Code() == GLFW_KEY_UP) {
				_player->Translate(Vertex(0.0, 1.0, 0.0));
			}
		}
	}
}

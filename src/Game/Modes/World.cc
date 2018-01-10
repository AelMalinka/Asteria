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
	: Mode(app), _player(), _map()
{
	auto player = App().load("Character.png", Resources::Texture(Texture::Texture2D));
	auto floor = App().load("Grass.png", Resources::Texture(Texture::Texture2D));
	auto wall = App().load("Mountain.png", Resources::Texture(Texture::Texture2D));

	auto height = 16;
	auto width = 28;

	const Tile Wall(wall.shared(), true);
	const Tile Floor(floor.shared());

	vector<vector<Tile>> v;

	for(auto x = 0; x <= width; x++) {
		vector<Tile> t;
		for(auto y = 0; y <= height; y++) {
			if(x == 0 || x == width || y == 0 || y == height)
				t.push_back(Wall);
			else
				t.push_back(Floor);
		}
		v.push_back(t);
	}

	_map = make_shared<Map>(move(v));
	_player = make_shared<Character>(player.shared(), 0, 0, 0, 0, 0, 0);

	_player->Translate(Vertex(width / 2, height / 2, 0));

	Current().addDrawable(_map);
	Current().addDrawable(_player);
	Current().getCamera().setPosition(Vertex(width / 2, height / 2, 5));
	Current().getCamera().setLookAt(Vertex(width / 2, height / 2, 0));
}

void World::onEvent(const Entropy::Event &ev)
{
	if(ev.Id() == Theia::Events::Key::Id) {
		const Theia::Events::Key &k = dynamic_cast<const Theia::Events::Key &>(ev);
		if(k.Action() == GLFW_PRESS || k.Action() == GLFW_REPEAT) {
			if(k.Code() == GLFW_KEY_ESCAPE) {
				dynamic_cast<Application &>(App()).Menu();
			} else if(k.Code() == GLFW_KEY_LEFT) {
				if(!(*_map)[_player->Position().x - 1][_player->Position().y].isWall())
					_player->Translate(Vertex(-1.0, 0.0, 0.0));
			} else if(k.Code() == GLFW_KEY_RIGHT) {
				if(!(*_map)[_player->Position().x + 1][_player->Position().y].isWall())
					_player->Translate(Vertex(1.0, 0.0, 0.0));
			} else if(k.Code() == GLFW_KEY_DOWN) {
				if(!(*_map)[_player->Position().x][_player->Position().y - 1].isWall())
					_player->Translate(Vertex(0.0, -1.0, 0.0));
			} else if(k.Code() == GLFW_KEY_UP) {
				if(!(*_map)[_player->Position().x][_player->Position().y + 1].isWall())
					_player->Translate(Vertex(0.0, 1.0, 0.0));
			}
		}
	}
}

/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "World.hh"
#include <Entropy/Mnemosyne/Resources/Texture.hh>

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Asteria;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;
using namespace Entropy::Theia::Events;
using namespace Entropy::Mnemosyne;
using namespace Entropy;
using namespace std;

World::World(Application &app, const shared_ptr<Character> &p, const shared_ptr<Map> &m)
	: Mode(app), _player(p), _map(m), _camera(Current().getCamera(), p, m)
{
	Current().addDrawable(_map);
	Current().addDrawable(_player);
}

void World::onEvent(const Event &ev)
{
	Mode<Application>::onEvent(ev);

	// 2018-01-27 AMR TODO: why?
	dynamic_cast<EventHandler &>(_camera).onEvent(ev);
}

void World::onEvent(const Key &k)
{
	if(k.Action() == GLFW_PRESS || k.Action() == GLFW_REPEAT) {
		if(k.Code() == GLFW_KEY_ESCAPE) {
			App().Menu();
		} else if(k.Code() == GLFW_KEY_LEFT) {
			if(!(*_map)[_player->Position().x - 1][_player->Position().y].isWall()) {
				if(_player->isFlipped()) {
					_player->Flip();
				}
				_player->Translate(Vertex(-1.0, 0.0, 0.0));
				auto &t = (*_map)[_player->Position().x][_player->Position().y];
				if(t.hasActor()) {
					App().Fight(_player, t.Actor(), _map);
				}
			}
		} else if(k.Code() == GLFW_KEY_RIGHT) {
			if(!(*_map)[_player->Position().x + 1][_player->Position().y].isWall()) {
				if(!_player->isFlipped()) {
					_player->Flip();
				}
				_player->Translate(Vertex(1.0, 0.0, 0.0));
				auto &t = (*_map)[_player->Position().x][_player->Position().y];
				if(t.hasActor()) {
					App().Fight(_player, t.Actor(), _map);
				}
			}
		} else if(k.Code() == GLFW_KEY_DOWN) {
			if(!(*_map)[_player->Position().x][_player->Position().y - 1].isWall()) {
				_player->Translate(Vertex(0.0, -1.0, 0.0));
				auto &t = (*_map)[_player->Position().x][_player->Position().y];
				if(t.hasActor()) {
					App().Fight(_player, t.Actor(), _map);
				}
			}
		} else if(k.Code() == GLFW_KEY_UP) {
			if(!(*_map)[_player->Position().x][_player->Position().y + 1].isWall()) {
				_player->Translate(Vertex(0.0, 1.0, 0.0));
				auto &t = (*_map)[_player->Position().x][_player->Position().y];
				if(t.hasActor()) {
					App().Fight(_player, t.Actor(), _map);
				}
			}
		}
	}
}

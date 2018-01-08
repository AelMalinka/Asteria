/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "World.hh"
#include "../Application.hh"

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Asteria;
using namespace Entropy::Theia;
using namespace Entropy;
using namespace std;

World::World(Mnemosyne::Application &app)
	: Mode(app)
{}

void World::onEvent(const Entropy::Event &ev)
{
	if(ev.Id() == Theia::Events::Key::Id) {
		const Theia::Events::Key &k = dynamic_cast<const Theia::Events::Key &>(ev);
		if(k.Action() == GLFW_PRESS) {
			if(k.Code() == GLFW_KEY_ESCAPE) {
				dynamic_cast<Application &>(App()).Menu();
			}
		}
	}
}

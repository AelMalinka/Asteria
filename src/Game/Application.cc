/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

#include "Modes/Fight.hh"
#include "Modes/Menu.hh"
#include "Modes/World.hh"

#include <Entropy/Mnemosyne/Resources/Json.hh>

using namespace std;
using namespace Entropy::Asteria;
using namespace Entropy::Mnemosyne::Resources;

Application::Application() :
	Entropy::Mnemosyne::Application(),
	_menu(end()),
	_world(end()),
	_fight(end())
{
	addSearchPath("data"s);

	_menu = addMode(make_shared<Modes::Menu>(*this));
	_world = addMode(make_shared<Modes::World>(*this));
	_fight = addMode(make_shared<Modes::Fight>(*this));

	setMode(_menu);
}

Application::Application(const int ArgC, char *ArgV[]) :
	Entropy::Mnemosyne::Application(ArgC, ArgV),
	_menu(end()),
	_world(end()),
	_fight(end())
{
	addSearchPath("data"s);

	_menu = addMode(make_shared<Modes::Menu>(*this));
	_world = addMode(make_shared<Modes::World>(*this));
	_fight = addMode(make_shared<Modes::Fight>(*this));

	setMode(_menu);
}

void Application::Start()
{
	setMode(_world);
}

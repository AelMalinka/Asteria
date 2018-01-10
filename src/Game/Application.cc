/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

#include "Modes/Fight.hh"
#include "Modes/Menu.hh"
#include "Modes/World.hh"
#include "Modes/Options.hh"

#include <Entropy/Mnemosyne/Resources/Json.hh>

using namespace std;
using namespace Entropy::Asteria;
using namespace Json;

using Conf = Entropy::Mnemosyne::Resources::Json;

Application::Application() :
	Entropy::Mnemosyne::Application(),
	_menu(end()),
	_world(end()),
	_fight(end()),
	_options(end()),
	_settings()
{
	addSearchPath(DATADIR);
	addSearchPath(SYSCONFDIR);
	addSearchPath(getenv("HOME") + "/.asteria"s);
	addSearchPath("data"s);

	_settings = load("settings", Conf());

	_menu = addMode(make_shared<Modes::Menu>(*this));
	_world = addMode(make_shared<Modes::World>(*this));
	_fight = addMode(make_shared<Modes::Fight>(*this));
	_options = addMode(make_shared<Modes::Options>(*this));

	setMode(_menu);
}

Application::Application(const int ArgC, char *ArgV[]) :
	Entropy::Mnemosyne::Application(ArgC, ArgV),
	_menu(end()),
	_world(end()),
	_fight(end()),
	_options(end()),
	_settings()
{
	addSearchPath(DATADIR);
	addSearchPath(SYSCONFDIR);
	addSearchPath(getenv("HOME") + "/.asteria"s);
	addSearchPath("data"s);

	_settings = load("settings", Conf());

	_menu = addMode(make_shared<Modes::Menu>(*this));
	_world = addMode(make_shared<Modes::World>(*this));
	_fight = addMode(make_shared<Modes::Fight>(*this));
	_options = addMode(make_shared<Modes::Options>(*this));

	setMode(_menu);
}

Application::~Application()
{
	write("settings", _settings, Conf());
}

void Application::Menu()
{
	setMode(_menu);
}

void Application::Start()
{
	setMode(_world);
}

void Application::Options()
{
	setMode(_options);
}

Value &Application::Settings()
{
	return *_settings;
}

const Value &Application::Settings() const
{
	return *_settings;
}

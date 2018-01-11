/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

#include "Modes/Fight.hh"
#include "Modes/Menu.hh"
#include "Modes/World.hh"
#include "Modes/Options.hh"
#include "Modes/Death.hh"

#include <Entropy/Mnemosyne/Resources/Texture.hh>
#include <Entropy/Mnemosyne/Resources/Json.hh>

using namespace std;
using namespace Entropy::Asteria;
using namespace Json;

using Entropy::Mnemosyne::Resources::Texture;
using Conf = Entropy::Mnemosyne::Resources::Json;

namespace GL = Entropy::Theia::GL;

Application::Application() :
	Entropy::Mnemosyne::Application(),
	_player(),
	_menu(end()),
	_world(end()),
	_fight(end()),
	_options(end()),
	_death(end()),
	_settings()
{
	addSearchPath(DATADIR);
	addSearchPath(SYSCONFDIR);
	addSearchPath("data"s);
	addSearchPath(getenv("HOME") + "/.asteria"s);

	_settings = load("settings", Conf());

	Restart();
}

Application::Application(const int ArgC, char *ArgV[]) :
	Entropy::Mnemosyne::Application(ArgC, ArgV),
	_menu(end()),
	_world(end()),
	_fight(end()),
	_options(end()),
	_death(end()),
	_settings()
{
	addSearchPath(DATADIR);
	addSearchPath(SYSCONFDIR);
	addSearchPath("data"s);
	addSearchPath(getenv("HOME") + "/.asteria"s);

	_settings = load("settings", Conf());

	Restart();
}

Application::~Application()
{
	write(getenv("HOME") + "/.asteria/settings"s, _settings, Conf());
}

void Application::Menu()
{
	setMode(_menu);
}

void Application::World()
{
	setMode(_world);
}

void Application::Options()
{
	setMode(_options);
}

void Application::Restart()
{
	auto player = load("Character.png", Texture(GL::Texture::Texture2D));

	_player = make_shared<Character>(player.shared(), 1, 1, 1, 1, 1, 1);

	_menu = addMode(make_shared<Modes::Menu>(*this));
	_world = addMode(make_shared<Modes::World>(*this, _player));
	_fight = addMode(make_shared<Modes::Fight>(*this));
	_options = addMode(make_shared<Modes::Options>(*this));
	_death = addMode(make_shared<Modes::Death>(*this));

	setMode(_menu);
}

void Application::Fight(const shared_ptr<Character> &a, const shared_ptr<Character> &b, const shared_ptr<Map> &m)
{
	dynamic_pointer_cast<Modes::Fight>(_fight.shared())->setMap(m);
	dynamic_pointer_cast<Modes::Fight>(_fight.shared())->setCombatants(a, b);

	setMode(_fight);
}

void Application::Win(const shared_ptr<Character> &w)
{
	if(w != _player) {
		setMode(_death);
	}
}

Value &Application::Settings()
{
	return *_settings;
}

const Value &Application::Settings() const
{
	return *_settings;
}

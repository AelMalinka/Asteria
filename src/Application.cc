/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

#include "Modes/Fight.hh"
#include "Modes/Menu.hh"
#include "Modes/World.hh"
#include "Modes/Options.hh"
#include "Modes/Message.hh"

#include "Map/Cave.hh"

#include <Entropy/Mnemosyne/Resources/Texture.hh>
#include <Entropy/Mnemosyne/Resources/Json.hh>
#include <cassert>

using namespace std;
using namespace Entropy::Asteria;
using namespace Json;

using Conf = Entropy::Mnemosyne::Resources::Json;
namespace GL = Entropy::Theia::GL;

using Entropy::Mnemosyne::Resources::Texture;
using Entropy::Theia::Vertex;

Application::Application() :
	Entropy::Mnemosyne::Application(),
	_player(),
	_map(),
	_weapon(),
	_armor(),
	_menu(end()),
	_world(end()),
	_fight(end()),
	_options(end()),
	_death(end()),
	_enemy(),
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
	_player(),
	_map(),
	_menu(end()),
	_world(end()),
	_fight(end()),
	_options(end()),
	_death(end()),
	_enemy(),
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
	_enemy = load("Monster.png"s, Texture(GL::Texture::Texture2D));

	auto player = load("Character.png"s, Texture(GL::Texture::Texture2D));
	auto floor = load("Grass.png"s, Texture(GL::Texture::Texture2D));
	auto wall = load("Mountain.png"s, Texture(GL::Texture::Texture2D));
	auto sword = load("Sword.png"s, Texture(GL::Texture::Texture2D));
	auto armor = load("Armor.png"s, Texture(GL::Texture::Texture2D));

	Template None("Empty Template", {});

	_weapon = make_shared<Weapon>("Basic Sword"s, sword.shared(), Weapon::Type::Sword, None);
	_armor = make_shared<Armor>("Basic Light Armor"s, armor.shared(), Armor::Type::Light, None);

	Cave c(100, 100, floor.shared(), wall.shared());
	c();

	auto height = c.Height();
	auto width = c.Width();

	_map = c.getMap();
	_player = make_shared<Character>(player.shared(), 10, 10, 10, 10, 10, 10);

	auto px = width / 2;
	auto py = height / 2;

	auto ex = width / 2 - width / 4;
	auto ey = height / 2;

	while((*_map)[px][py].isWall()) {
		++px;
	}

	while((*_map)[ex][ey].isWall()) {
		++ex;
	}

	assert(px < width);
	assert(ex < width);

	_player->Translate(Vertex(px, py, 0));
	(*_map)[ex][ey].setActor(make_shared<Character>(_enemy.shared(), 0, 0, 1, 0, 0, 0));

	_menu = addMode(make_shared<Modes::Menu>(*this));
	_world = addMode(make_shared<Modes::World>(*this, _player, _map));
	_fight = addMode(make_shared<Modes::Fight>(*this));
	_options = addMode(make_shared<Modes::Options>(*this));
	_death = addMode(make_shared<Modes::Message>(*this, "You Died!", Vertex(1, 0, 0)));

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
	auto height = _map->Height();
	auto width = _map->Width();

	if(w != _player) {
		setMode(_death);
	} else {
		auto p = (*_map)[_player->Position().x][_player->Position().y].Actor()->Cost();

		_player->giveXp((p > 0) ? p : 1);

		if(_player->Xp() >= 10 && !_player->hasWeapon()) {
			_player->Equip(*_weapon);
		} else if(_player->Xp() >= 20 && !_player->hasArmor()) {
			_player->Equip(*_armor);
		}

		(*_map)[_player->Position().x][_player->Position().y].setActor(shared_ptr<Character>());

		auto ex1 = width / 2 - width / 4;
		auto ey1 = height / 2;

		auto ex2 = width / 2 + width / 4;
		auto ey2 = height / 2;

		while((*_map)[ex1][ey1].isWall()) {
			++ex1;
		}

		while((*_map)[ex2][ey2].isWall()) {
			++ex2;
		}

		assert(ex1 < _map->Width());
		assert(ex2 < _map->Width());

		if(_player->Position().x == ex1 && _player->Position().y == ey1) {
			(*_map)[ex2][ey2].setActor(make_shared<Character>(_enemy.shared(), 0, 0, 1, 0, 0, 0));
		} else {
			(*_map)[ex1][ey1].setActor(make_shared<Character>(_enemy.shared(), 0, 0, 1, 0, 0, 0));
		}

		setMode(_world);
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

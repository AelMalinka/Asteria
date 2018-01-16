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

	// 2018-01-11 AMR NOTE: calculated with the super scientific method of trial and error
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
	_player = make_shared<Character>(player.shared(), 10, 10, 10, 10, 10, 10);

	_player->Translate(Vertex(width / 2, height / 2, 0));
	(*_map)[width / 2 - width / 4][height / 2].setActor(make_shared<Character>(_enemy.shared(), 0, 0, 1, 0, 0, 0));

	_menu = addMode(make_shared<Modes::Menu>(*this));
	_world = addMode(make_shared<Modes::World>(*this, _player, _map));
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

		if(_player->Position().x == width / 2 - width / 4 && _player->Position().y == height / 2) {
			(*_map)[width / 2 + width / 4][height / 2].setActor(make_shared<Character>(_enemy.shared(), 0, 0, 1, 0, 0, 0));
		} else {
			(*_map)[width / 2 - width / 4][height / 2].setActor(make_shared<Character>(_enemy.shared(), 0, 0, 1, 0, 0, 0));
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

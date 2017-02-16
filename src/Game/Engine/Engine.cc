/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Engine.hh"
#include <Entropy/Exception.hh>

ENTROPY_EXCEPTION_BASE(YouHaveDied, "You Have Died");
ENTROPY_EXCEPTION_BASE(YouHaveWon, "You Have Won");

using namespace Entropy::Asteria;
using namespace std;

Engine::Engine()
	: _done(false), _main(), _new(), _expl(), _rend(&_main), _ch()
{}

void Engine::operator () ()
{
	while(!_done)
		_rend(*this);
}

void Engine::Done()
{
	_done = true;
}

void Engine::New()
{
	_rend.changeMenu(&_new);
}

void Engine::Main()
{
	_rend.changeMenu(&_main);
}

void Engine::NewGame(const shared_ptr<Character> &ch, const shared_ptr<Character> &mob)
{
	_ch = ch;
	_mob = mob;
	_generate_map();

	_map[1][2].Actor() = _ch;
	_map[3][2].Actor() = _mob;
	_pos = make_tuple(1, 2);

	_rend.changeMenu(&_expl);
}

void Engine::Fight(const shared_ptr<Character> &o)
{
	Menus::Fight f(o);
	_rend.changeMenu(&f);

	while(o->isAlive() && _ch->isAlive() && !_done)
		_rend(*this);

	if(!_ch->isAlive()) {
		ENTROPY_THROW(YouHaveDied());
	}
	else {
		ENTROPY_THROW(YouHaveWon());
	}
}

Map &Engine::map()
{
	return _map;
}

tuple<size_t, size_t> &Engine::Position()
{
	return _pos;
}

shared_ptr<Character> &Engine::Player()
{
	return _ch;
}

void Engine::_generate_map()
{
	_map = {
		{
			Wall,
			Wall,
			Wall,
			Wall,
			Wall
		},
		{
			Wall,
			Tile(),
			Tile(),
			Tile(),
			Wall
		},
		{
			Wall,
			Tile(),
			Tile(),
			Tile(),
			Wall
		},
		{
			Wall,
			Tile(),
			Tile(),
			Tile(),
			Wall
		},
		{
			Wall,
			Wall,
			Wall,
			Wall,
			Wall
		}
	};
}

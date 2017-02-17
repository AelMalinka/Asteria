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
	: _done(false), _main(), _new(), _expl(), _current(_main), _ch()
{}

void Engine::operator () ()
{
	while(!_done)
	{
		if(!_current)
			ENTROPY_THROW(Exception("No current context"));

		_current(*this);
	}
}

void Engine::Done()
{
	_done = true;
}

void Engine::StartNewGame()
{
	_current = _new;
}

void Engine::Main()
{
	_current = _main;
}

void Engine::NewGame(const shared_ptr<Character> &ch, const shared_ptr<Character> &mob)
{
	_ch = ch;
	_mob = mob;
	_generate_map();

	_map[1][2].Actor() = _ch;
	_map[3][2].Actor() = _mob;
	_pos = make_tuple(1, 2);

	_current = _expl;
}

void Engine::StartFight(const shared_ptr<Character> &o)
{
	Fight f(o);
	_current = f;

	while(o->isAlive() && _ch->isAlive() && !_done)
		_current(*this);

	if(!_ch->isAlive()) {
		ENTROPY_THROW(YouHaveDied());
	}
	else if(!o->isAlive()) {
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

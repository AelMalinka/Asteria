/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Engine.hh"

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

void Engine::NewGame(const shared_ptr<Character> &ch)
{
	_ch = ch;
	_rend.changeMenu(&_expl);
}

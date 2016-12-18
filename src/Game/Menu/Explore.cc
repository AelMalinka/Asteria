/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Explore.hh"
#include "../Engine/Engine.hh"

#include <iostream>

using namespace Entropy::Asteria;
using namespace Entropy::Asteria::Menus;
using namespace std;

void Explore::operator () (Engine &engine)
{
	_map(engine);
	_menu(engine);
}

void Explore::_map(Engine &engine)
{
	cout << endl;
	auto ch = engine.Player();
	for(auto &&r : engine.map()) {
		for(auto &&t : r) {
			if(t.isWall()) cout << "#";
			else if(t.hasActor() && t.Actor() == ch) cout << "C";
			else if(t.hasActor()) cout << "X";
			else if(t.hasObject()) cout << "!";
			else cout << " ";
		}
		cout << endl;
	}
}

void Explore::_menu(Engine &engine)
{
	cout << endl
		<< "----------------" << endl
		<< "1) Move Left" << endl
		<< "2) Move Right" << endl
		<< "3) Move Up" << endl
		<< "4) Move Down" << endl
		<< "q) Quit" << endl;

	string line;
	getline(cin, line);

	auto x = get<1>(engine.Position());
	auto y = get<0>(engine.Position());

	if(line == "1")
		--x;
	else if(line == "2")
		++x;
	else if(line == "3")
		--y;
	else if(line == "4")
		++y;
	else if(line == "q")
		engine.Done();
	else
		cout << "Invalid Response" << endl;

	_move(engine, x, y);
}

void Explore::_move(Engine &engine, const size_t x, const size_t y)
{
	if((get<0>(engine.Position()) != y || get<1>(engine.Position()) != x) && !engine.map()[y][x].isWall())
	{
		if(engine.map()[y][x].hasActor()) {
			engine.Fight(engine.map()[y][x].Actor());
		}

		engine.map()[get<0>(engine.Position())][get<1>(engine.Position())].Actor() = nullptr;
		engine.map()[y][x].Actor() = engine.Player();
		engine.Position() = make_tuple(y, x);
	}
}

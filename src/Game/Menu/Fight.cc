/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Fight.hh"
#include "../Engine/Engine.hh"

using namespace Entropy::Asteria;
using namespace Entropy::Asteria::Menus;
using namespace std;

Fight::Fight(const shared_ptr<Character> &c)
	: _enemy(c)
{}

void Fight::operator () (Engine &engine)
{
	cout << endl
		<< "Unimplemented" << endl
		<< "q) Quit" << endl;

	string line;
	getline(cin, line);

	if(line == "q")
		engine.Done();
}

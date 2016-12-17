/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "New.hh"
#include "../Engine/Engine.hh"
#include <iostream>

using namespace Entropy::Asteria;
using namespace Entropy::Asteria::Menus;
using namespace std;

void New::operator () (Engine &engine)
{
	Strength str;
	Agility agi;
	Endurance end;
	Perception per;
	Magic mag;
	Willpower wil;

	// 2016-12-17 AMR TODO: stream into Stat/Skill/etc
	int temp;

	cout << endl
		<< "New Game" << endl
		<< endl;

	cout << "Strength: " << flush;
	cin >> temp;
	str = temp;
	temp = 0;

	cout << "Agility: " << flush;
	cin >> temp;
	agi = temp;
	temp = 0;

	cout << "Endurance: " << flush;
	cin >> temp;
	end = temp;
	temp = 0;

	cout << "Perception: " << flush;
	cin >> temp;
	per = temp;
	temp = 0;

	cout << "Magic: " << flush;
	cin >> temp;
	mag = temp;
	temp = 0;

	cout << "Willpower: " << flush;
	cin >> temp;
	wil = temp;
	temp = 0;

	auto ch = make_shared<Character>(str, agi, end, per, mag, wil);
	engine.NewGame(ch);

	string t;
	getline(cin, t);
}

/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "New.hh"
#include "../Engine.hh"
#include <iostream>

using namespace Entropy::Asteria;
using namespace std;

void New::operator () (Engine &engine)
{
	shared_ptr<Character> ch;
	shared_ptr<Character> mb;

	cout << endl
		<< "New Game" << endl
		<< endl;

	{
		Strength str;
		Agility agi;
		Endurance end;
		Perception per;
		Magic mag;
		Willpower wil;
		{
			int temp = 0;
			cout << "Your Strength: " << flush;
			cin >> temp;
			str = temp;
		}
		{
			int temp = 0;
			cout << "Your Agility: " << flush;
			cin >> temp;
			agi = temp;
		}
		{
			int temp = 0;
			cout << "Your Endurance: " << flush;
			cin >> temp;
			end = temp;
		}
		{
			int temp = 0;
			cout << "Your Perception: " << flush;
			cin >> temp;
			per = temp;
		}
		{
			int temp = 0;
			cout << "Your Magic: " << flush;
			cin >> temp;
			mag = temp;
		}
		{
			int temp = 0;
			cout << "Your Willpower: " << flush;
			cin >> temp;
			wil = temp;
		}
		ch = make_shared<Character>(str, agi, end, per, mag, wil);
	}
	cout << endl;
	{
		Strength str;
		Agility agi;
		Endurance end;
		Perception per;
		Magic mag;
		Willpower wil;
		{
			int temp = 0;
			cout << "Their Strength: " << flush;
			cin >> temp;
			str = temp;
		}
		{
			int temp = 0;
			cout << "Their Agility: " << flush;
			cin >> temp;
			agi = temp;
		}
		{
			int temp = 0;
			cout << "Their Endurance: " << flush;
			cin >> temp;
			end = temp;
		}
		{
			int temp = 0;
			cout << "Their Perception: " << flush;
			cin >> temp;
			per = temp;
		}
		{
			int temp = 0;
			cout << "Their Magic: " << flush;
			cin >> temp;
			mag = temp;
		}
		{
			int temp = 0;
			cout << "Their Willpower: " << flush;
			cin >> temp;
			wil = temp;
		}
		mb = make_shared<Character>(str, agi, end, per, mag, wil);
	}
	engine.NewGame(ch, mb);
	{
		string t;
		getline(cin, t);
	}
}

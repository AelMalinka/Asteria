/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Fight.hh"
#include "../Engine/Engine.hh"

using namespace Entropy::Asteria;
using namespace Entropy::Asteria::Menus;
using namespace std;

struct Output
{
	explicit Output(bool);
	void operator () (const Check::Result &) const;
private:
	bool _is_me;
};

Fight::Fight(const shared_ptr<Character> &c)
	: _enemy(c), _me(), _them()
{}

void Fight::operator () (Engine &engine)
{
	using Entropy::Hecate::onSuccess;
	using Entropy::Hecate::onFailure;
	using Entropy::Hecate::onCritical;

	cout << "Health: " << engine.Player()->Hp().Current() << endl
		<< "Enemy Health: " << _enemy->Hp().Current() << endl
		<< endl;

	cout << "---------------------------------" << endl
		<< "1) Attack" << endl
		<< "q) Quit" << endl;

	string line;
	getline(cin, line);

	if(line == "q")
		engine.Done();
	else if (line == "1") {
		if (!_me) {
			_me = make_shared<Check>(engine.Player()->Attack(*_enemy));

			_me->Add(Output(true));
		}

		if (!_them) {
			_them = make_shared<Check>(_enemy->Attack(*engine.Player()));

			_them->Add(Output(false));
		}

		cout << endl;
		(*_me)();
		(*_them)();
	}
	else {
		cout << "Invalid Choice" << endl;
	}

	cout << endl;
}

Output::Output(bool isMe)
	: _is_me(isMe)
{}

void Output::operator () (const Check::Result &res) const
{
	cout << (_is_me ? "You " : "They ") << "Attack: " << (res.isCritical() ? "Critical " : "") << (res ? "Hit" : "Miss");
	if (res)
		cout << " for " << res.Value() * ENTROPY_ASTERIA_DEFAULT_MAX_DAMAGE / res.Chance() << " damage";
	cout << endl;
}

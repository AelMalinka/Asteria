/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Map/Object.hh"
#include "Character/Weapon.hh"
#include <Entropy/Mnemosyne/Resources/Texture.hh>
#include <Entropy/Mnemosyne/Application.hh>

using namespace Entropy::Asteria;
using namespace testing;
using namespace std;
using namespace Entropy::Mnemosyne;
using namespace Entropy::Mnemosyne::Resources;

using Tex = Entropy::Theia::GL::Texture;

namespace {
	Template None("Empty Template", {});
	Item Ring("Useless Ring", None);

	TEST(Object, Create) {
		Application app;
		auto t = app.load("data/Sword.png"s, Texture(Tex::Texture2D)).shared();
		Weapon BasicSword("Basic Sword", t, Weapon::Type::Sword, None);

		Object empty;
		Object basic({
			make_shared<Item>(Ring),
			make_shared<Weapon>(BasicSword)
		});
		Object multiple({
			make_shared<Item>(Ring),
			make_shared<Item>(Ring),
			make_shared<Item>(Ring),
			make_shared<Weapon>(BasicSword),
			make_shared<Weapon>(BasicSword),
			make_shared<Weapon>(BasicSword)
		});


		EXPECT_EQ(empty.size(), 0ul);
		EXPECT_EQ(basic.size(), 2ul);
		EXPECT_EQ(multiple.size(), 6ul);
	}

	TEST(Object, Iterate) {
		Application app;
		auto t = app.load("data/Sword.png"s, Texture(Tex::Texture2D)).shared();
		Weapon BasicSword("Basic Sword", t, Weapon::Type::Sword, None);

		Object empty;
		Object rings({
			make_shared<Item>(Ring),
			make_shared<Item>(Ring),
			make_shared<Item>(Ring)
		});
		Object swords({
			make_shared<Weapon>(BasicSword),
			make_shared<Weapon>(BasicSword),
			make_shared<Weapon>(BasicSword)
		});

		for(auto &&i : empty) {
			(void)i;

			FAIL() << "Empty is iterating";
		}

		for(auto &&r : rings) {
			EXPECT_EQ(r->Name(), "Useless Ring"s);
		}

		for(auto &&s : swords) {
			EXPECT_EQ(s->Name(), "Basic Sword"s);
		}
	}
}

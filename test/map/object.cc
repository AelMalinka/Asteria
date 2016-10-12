/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Map/Object.hh"
#include "Character/Weapon.hh"
#include <gtest/gtest.h>

using namespace Entropy::Asteria;
using namespace testing;
using namespace std;

namespace {
	Template None("Empty Template", {});
	Item Ring("Useless Ring", None);
	Weapon BasicSword("Basic Sword", Weapon::Type::Sword, None);

	TEST(Object, Create) {
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


		EXPECT_EQ(empty.size(), 0);
		EXPECT_EQ(basic.size(), 2);
		EXPECT_EQ(multiple.size(), 6);
	}

	TEST(Object, Iterate) {
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

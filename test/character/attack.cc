/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Character.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Asteria;

namespace {
	TEST(CharacterAttack, Basic) {
		Character a(10, 10, 10, 10, 10, 10);
		Character b(10, 10, 10, 10, 10, 10);
		Check ab = a.Attack(b);

		EXPECT_EQ(a.Hp().Current(), 100);
		EXPECT_EQ(b.Hp().Current(), 100);

		auto res = ab();
		while(!res) {
			EXPECT_EQ(a.Hp().Current(), 100);
			EXPECT_EQ(b.Hp().Current(), 100);
			EXPECT_LE(res, 0);
			res = ab();
		}

		EXPECT_GT(res, 0);
		EXPECT_EQ(a.Hp().Current(), 100);
		EXPECT_NE(b.Hp().Current(), 100);
	}

	TEST(CharacterAttack, Damage) {
		for(auto x = 0; x < 10; x++) {
			Character a(10, 10, 10, 10, 10, 10);
			Character b(10, 10, 10, 10, 10, 10);
			Check attack = a.Attack(b);

			while(b.Hp().Current() > 0) {
				auto last = b.Hp().Current();
				auto res = attack();
				auto dmg = last - b.Hp().Current();

				if(res) {
					EXPECT_LE(dmg, ENTROPY_ASTERIA_DEFAULT_MAX_DAMAGE);
					EXPECT_GT(dmg, 0);
				} else {
					EXPECT_EQ(dmg, 0);
				}
			}
		}
	}
}

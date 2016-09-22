/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Character.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Asteria;

#define TEST_BEGIN try {
#define TEST_END } catch(exception &e) { FAIL() << e << endl; }

namespace {
	TEST(CharacterBasic, Stats) {
		TEST_BEGIN
			Character test(5, 10, 15, 20, 25, 30);

			EXPECT_EQ(test.strength().Value(), 5);
			EXPECT_EQ(test.agility().Value(), 10);
			EXPECT_EQ(test.endurance().Value(), 15);
			EXPECT_EQ(test.perception().Value(), 20);
			EXPECT_EQ(test.magic().Value(), 25);
			EXPECT_EQ(test.willpower().Value(), 30);
		TEST_END
	}

	Template None("Empty Template", {});
	Weapon BasicSword("Basic Sword", Weapon::Type::Sword, None);
	Armor BasicLight("Basic Light Armor", Armor::Type::Light, None);

	TEST(CharacterBasic, Unarmed) {
		TEST_BEGIN
			Character alice(0, 0, 0, 0, 0, 0);
			Character bob(0, 0, 0, 0, 0, 0);

			Melee melee(bob.Stats());
			Unarmed unarmed(0, bob.get(melee));
			bob.get(unarmed).Raw() = 10;

			auto a = alice.Attack(bob);
			auto b = bob.Attack(alice);

			EXPECT_EQ(a.size(), 2);
			EXPECT_EQ(b.size(), 2);

			auto i = a.begin();
			auto j = b.begin();
			i++; j++;

			ASSERT_NE(i, a.end());
			ASSERT_NE(j, b.end());

			EXPECT_EQ((*i)->Reason(), "Unarmed Skill"s);
			EXPECT_EQ((*j)->Reason(), "Unarmed Skill"s);
			EXPECT_EQ((*i)->Value(), 0);
			EXPECT_EQ((*j)->Value(), 10);
		TEST_END
	}

	TEST(CharacterBasic, Weapon) {
		TEST_BEGIN
			Character alice(0, 0, 0, 0, 0, 0);
			Character bob(0, 0, 0, 0, 0, 0);

			Melee melee(bob.Stats());
			Sword sword(0, bob.get(melee));
			bob.get(sword).Raw() = 10;
			bob.Equip(BasicSword);

			auto a = alice.Attack(bob);
			auto b = bob.Attack(alice);

			EXPECT_EQ(a.size(), 2);
			EXPECT_EQ(b.size(), 2);

			auto i = a.begin();
			auto j = b.begin();
			i++; j++;

			ASSERT_NE(i, a.end());
			ASSERT_NE(j, b.end());

			EXPECT_EQ((*i)->Reason(), "Unarmed Skill"s);
			EXPECT_EQ((*j)->Reason(), "Sword Skill"s);
			EXPECT_EQ((*i)->Value(), 0);
			EXPECT_EQ((*j)->Value(), 10);
		TEST_END
	}

	TEST(CharacterBasic, Armor) {
		TEST_BEGIN
			Character alice(0, 0, 0, 0, 0, 0);
			Character bob(0, 0, 0, 0, 0, 0);

			Unarmored unarmored(bob.Stats());
			LightArmor armor(0, bob.get(unarmored), bob.strength());
			bob.get(armor).Raw() = 10;
			bob.Equip(BasicLight);

			auto a = alice.Attack(bob);
			auto b = bob.Attack(alice);

			EXPECT_EQ(a.size(), 2);
			EXPECT_EQ(b.size(), 2);

			auto i = a.begin();
			auto j = b.begin();

			ASSERT_NE(i, a.end());
			ASSERT_NE(j, b.end());

			EXPECT_EQ((*i)->Reason(), "Opponent's Defense"s);
			EXPECT_EQ((*j)->Reason(), "Opponent's Defense"s);
			EXPECT_EQ((*i)->Raw(), 10);
			EXPECT_EQ((*j)->Raw(), 0);
		TEST_END
	}
}

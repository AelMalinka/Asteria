/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Character.hh"
#include <Entropy/Mnemosyne/Resources/Texture.hh>
#include <Entropy/Mnemosyne/Application.hh>

using namespace std;
using namespace testing;
using namespace Entropy::Asteria;
using namespace Entropy::Mnemosyne;
using namespace Entropy::Mnemosyne::Resources;

using Tex = Entropy::Theia::GL::Texture;

#define TEST_BEGIN try {
#define TEST_END } catch(exception &e) { FAIL() << e << endl; }

namespace {
	TEST(CharacterBasic, Stats) {
		TEST_BEGIN
			Application app;
			auto t = app.load("data/Character.png"s, Texture(Tex::Texture2D)).shared();
			Character test(t, 5, 10, 15, 20, 25, 30);

			Strength str;
			Agility agi;
			Endurance end;
			Perception per;
			Magic mag;
			Willpower wil;

			EXPECT_EQ(test.get(str).Value(), 5);
			EXPECT_EQ(test.get(agi).Value(), 10);
			EXPECT_EQ(test.get(end).Value(), 15);
			EXPECT_EQ(test.get(per).Value(), 20);
			EXPECT_EQ(test.get(mag).Value(), 25);
			EXPECT_EQ(test.get(wil).Value(), 30);
		TEST_END
	}

	Template None("Empty Template", {});

	TEST(CharacterBasic, Unarmed) {
		TEST_BEGIN
			Application app;
			auto t = app.load("data/Character.png"s, Texture(Tex::Texture2D)).shared();
			Character alice(t, 0, 0, 0, 0, 0, 0);
			Character bob(t, 0, 0, 0, 0, 0, 0);

			Melee melee(bob.Stats());
			Unarmed unarmed(0, bob.get(melee));
			bob.get(unarmed).Raw() = 10;

			auto a = alice.Attack(bob);
			auto b = bob.Attack(alice);

			EXPECT_EQ(a.Modifiers()[Untyped].size(), 2ul);
			EXPECT_EQ(b.Modifiers()[Untyped].size(), 2ul);

			auto i = a.Modifiers()[Untyped].begin();
			auto j = b.Modifiers()[Untyped].begin();
			i++; j++;

			ASSERT_NE(i, a.Modifiers()[Untyped].end());
			ASSERT_NE(j, b.Modifiers()[Untyped].end());

			EXPECT_EQ(i->Value(), 0);
			EXPECT_EQ(j->Value(), 10);
		TEST_END
	}

	TEST(CharacterBasic, Weapon) {
		TEST_BEGIN
			Application app;
			auto t = app.load("data/Character.png"s, Texture(Tex::Texture2D)).shared();
			auto s = app.load("data/Sword.png"s, Texture(Tex::Texture2D)).shared();
			Character alice(t, 0, 0, 0, 0, 0, 0);
			Character bob(t, 0, 0, 0, 0, 0, 0);
			Weapon BasicSword("Basic Sword", s, Weapon::Type::Sword, None);

			Melee melee(bob.Stats());
			Sword sword(0, bob.get(melee));
			bob.get(sword).Raw() = 10;
			bob.Equip(BasicSword);

			auto a = alice.Attack(bob);
			auto b = bob.Attack(alice);

			EXPECT_EQ(a.Modifiers()[Untyped].size(), 2ul);
			EXPECT_EQ(b.Modifiers()[Untyped].size(), 2ul);

			auto i = a.Modifiers()[Untyped].begin();
			auto j = b.Modifiers()[Untyped].begin();
			i++; j++;

			ASSERT_NE(i, a.Modifiers()[Untyped].end());
			ASSERT_NE(j, b.Modifiers()[Untyped].end());

			EXPECT_EQ(i->Value(), 0);
			EXPECT_EQ(j->Value(), 10);
		TEST_END
	}

	TEST(CharacterBasic, Armor) {
		TEST_BEGIN
			Application app;
			auto t = app.load("data/Character.png"s, Texture(Tex::Texture2D)).shared();
			auto r = app.load("data/Armor.png"s, Texture(Tex::Texture2D)).shared();
			Character alice(t, 0, 0, 0, 0, 0, 0);
			Character bob(t, 0, 0, 0, 0, 0, 0);
			Armor BasicLight("Basic Light Armor", r, Armor::Type::Light, None);

			Strength str;
			Unarmored unarmored(bob.Stats());
			LightArmor armor(0, bob.get(unarmored), bob.get(str));
			bob.get(armor).Raw() = 10;
			bob.Equip(BasicLight);

			auto a = alice.Attack(bob);
			auto b = bob.Attack(alice);

			EXPECT_EQ(a.Modifiers()[Untyped].size(), 2ul);
			EXPECT_EQ(b.Modifiers()[Untyped].size(), 2ul);

			auto i = a.Modifiers()[Untyped].begin();
			auto j = b.Modifiers()[Untyped].begin();

			ASSERT_NE(i, a.Modifiers()[Untyped].end());
			ASSERT_NE(j, b.Modifiers()[Untyped].end());

			EXPECT_EQ(i->Raw(), 10);
			EXPECT_EQ(j->Raw(), 0);
		TEST_END
	}
}

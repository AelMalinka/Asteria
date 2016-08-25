/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Character.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Asteria;

namespace {
	TEST(CharacterBasic, Stats) {
		Character test(5, 10, 15, 20, 25, 30);

		EXPECT_EQ(test.strength().Value(), 5);
		EXPECT_EQ(test.agility().Value(), 10);
		EXPECT_EQ(test.endurance().Value(), 15);
		EXPECT_EQ(test.perception().Value(), 20);
		EXPECT_EQ(test.magic().Value(), 25);
		EXPECT_EQ(test.willpower().Value(), 30);
	}
}

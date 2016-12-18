/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Map.hh"
#include <gtest/gtest.h>

using namespace Entropy::Asteria;
using namespace testing;
using namespace std;

namespace {
	TEST(Map, Create) {
		Map map;

		EXPECT_EQ(map.Height(), 0);
		EXPECT_EQ(map.Width(), 0);
	}

	TEST(Map, Room) {
		Map map = {
			{
				Wall,
				Wall,
				Wall
			},
			{
				Wall,
				Tile(),
				Wall
			},
			{
				Wall,
				Wall,
				Wall
			}
		};

		EXPECT_EQ(map.Height(), 3);
		EXPECT_EQ(map.Width(), 3);
		EXPECT_TRUE(map[0][0].isWall());
		EXPECT_TRUE(map[0][1].isWall());
		EXPECT_TRUE(map[0][2].isWall());
		EXPECT_TRUE(map[1][0].isWall());
		EXPECT_FALSE(map[1][1].isWall());
		EXPECT_TRUE(map[1][2].isWall());
		EXPECT_TRUE(map[2][0].isWall());
		EXPECT_TRUE(map[2][1].isWall());
		EXPECT_TRUE(map[2][2].isWall());

		for(auto &&r: map) {
			for(auto &&t : r) {
				EXPECT_FALSE(t.hasActor());
				EXPECT_FALSE(t.hasObject());
			}
		}
	}
}

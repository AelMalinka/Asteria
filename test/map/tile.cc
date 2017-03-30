/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Map/Tile.hh"
#include <gtest/gtest.h>

using namespace Entropy::Asteria;
using namespace testing;
using namespace std;

namespace {
	Template None("Blank Template", {});
	Item Ring("Useless Ring", None);

	TEST(Tile, Create) {
		Tile blank;
		Tile wall(true);
		Tile ch(make_shared<Character>(5, 0, 0, 0, 0, 0));
		Tile junk(make_shared<Object>());
		Tile stuff(make_shared<Object>(Object{
			make_shared<Item>(Ring)
		}));
		Tile stuff_ch(make_shared<Object>(Object{
			make_shared<Item>(Ring)
		}), make_shared<Character>(5, 0, 0, 0, 0, 0));

		EXPECT_FALSE(blank.isWall());
		EXPECT_TRUE(wall.isWall());
		EXPECT_FALSE(ch.isWall());
		EXPECT_FALSE(junk.isWall());
		EXPECT_FALSE(stuff.isWall());
		EXPECT_FALSE(stuff_ch.isWall());

		EXPECT_FALSE(blank.hasObject());
		EXPECT_FALSE(wall.hasObject());
		EXPECT_FALSE(ch.hasObject());
		EXPECT_TRUE(junk.hasObject());
		EXPECT_TRUE(stuff.hasObject());
		EXPECT_TRUE(stuff_ch.hasObject());

		EXPECT_FALSE(blank.hasActor());
		EXPECT_FALSE(wall.hasActor());
		EXPECT_TRUE(ch.hasActor());
		EXPECT_FALSE(junk.hasActor());
		EXPECT_FALSE(stuff.hasActor());
		EXPECT_TRUE(stuff_ch.hasActor());

		Strength st;
		EXPECT_EQ(ch.Actor()->get(st).Value(), 5);
		EXPECT_EQ(stuff_ch.Actor()->get(st).Value(), 5);

		EXPECT_EQ(stuff.Loot()->size(), 1ul);
		EXPECT_EQ(stuff_ch.Loot()->size(), 1ul);
	}
}

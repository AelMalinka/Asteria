/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Cave.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Asteria;

namespace {
	TEST(Cave, Create) {
		Cave cave(100, 100);

		EXPECT_EQ(cave.Tiles().size(), 100);
		EXPECT_EQ(cave.Tiles().front().size(), 100);
	}
}

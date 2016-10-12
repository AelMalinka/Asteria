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
}

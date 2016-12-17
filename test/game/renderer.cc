/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Game/Engine/Renderer.hh"
#include "Game/Engine/Engine.hh"
#include <gtest/gtest.h>

using namespace Entropy::Asteria;
using namespace testing;
using namespace std;

namespace {
	struct TestMenu :
		Menu
	{
		TestMenu();
		void operator () (Engine &);
		bool ran;
	};

	TEST(Renderer, Construct) {
		TestMenu t;
		Renderer r(&t);
	}

	TEST(Renderer, Run) {
		TestMenu t;
		Renderer r(&t);
		Engine e;

		EXPECT_FALSE(t.ran);
		r(e);
		EXPECT_TRUE(t.ran);
	}

	TEST(Renderer, Switch) {
		TestMenu t1;
		TestMenu t2;
		Renderer r(&t1);
		Engine e;

		EXPECT_FALSE(t1.ran);
		EXPECT_FALSE(t2.ran);
		r(e);
		EXPECT_TRUE(t1.ran);
		EXPECT_FALSE(t2.ran);
		r.changeMenu(&t2);
		EXPECT_TRUE(t1.ran);
		EXPECT_FALSE(t2.ran);
		r(e);
		EXPECT_TRUE(t1.ran);
		EXPECT_TRUE(t2.ran);
	}

	TestMenu::TestMenu()
		: ran(false)
	{}

	void TestMenu::operator () (Engine &)
	{
		ran = true;
	}
}

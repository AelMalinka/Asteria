/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Map/Cave.hh"
#include <Entropy/Mnemosyne/Resources/Texture.hh>
#include <Entropy/Mnemosyne/Application.hh>

using namespace std;
using namespace testing;
using namespace Entropy::Asteria;
using namespace Entropy::Mnemosyne;
using namespace Entropy::Theia::GL;

namespace {
	TEST(Cave, Create) {
		Application app;
		auto f = app.load("data/Grass.png", Resources::Texture(Texture::Texture2D));
		auto w = app.load("data/Mountain.png", Resources::Texture(Texture::Texture2D));

		Cave cave(100, 100, f.shared(), w.shared());

		cave();

		EXPECT_EQ(cave.Height(), 100ul);
		EXPECT_EQ(cave.Width(), 100ul);
	}
}

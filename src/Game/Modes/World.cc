/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "World.hh"

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Mnemosyne;

World::World(Mnemosyne::Application &app)
	: Mode(app)
{}

World::~World() = default;

void World::onEvent(const Entropy::Event &)
{}

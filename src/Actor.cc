/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Actor.hh"

using namespace Entropy::Asteria;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;
using namespace std;

Actor::Actor(const shared_ptr<Texture> &t)
	: Sprite(t)
{}

Actor::~Actor() = default;

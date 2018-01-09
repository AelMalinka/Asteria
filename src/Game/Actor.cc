/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Actor.hh"

using namespace Entropy::Asteria;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;
using namespace std;

Actor::Actor(const shared_ptr<Texture> &t)
	: Sprite(t), _position(0, 0, 0)
{}

Actor::~Actor() = default;

void Actor::Flip()
{
	Rotate(180.0, Vertex(0.0, 1.0, 0.0));
}

const Vertex &Actor::Position() const
{
	return _position;
}

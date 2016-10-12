/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Tile.hh"

using namespace Entropy::Asteria;
using namespace std;

Tile Entropy::Asteria::Wall(true);

Tile::Tile(const bool isWall)
	: _is_wall(isWall), _actor(), _object()
{}

Tile::Tile(const shared_ptr<Object> &obj)
	: _is_wall(false), _actor(), _object(obj)
{}

Tile::Tile(const shared_ptr<Character> &ch)
	: _is_wall(false), _actor(ch), _object()
{}

Tile::Tile(const shared_ptr<Object> &obj, const shared_ptr<Character> &ch)
	: _is_wall(false), _actor(ch), _object(obj)
{}

Tile::Tile(const Tile &) = default;
Tile::~Tile() = default;

bool Tile::isWall() const
{
	return _is_wall;
}

bool Tile::hasActor() const
{
	return static_cast<bool>(_actor);
}

bool Tile::hasObject() const
{
	return static_cast<bool>(_object);
}

shared_ptr<Character> &Tile::Actor()
{
	return _actor;
}

shared_ptr<Object> &Tile::Loot()
{
	return _object;
}

const shared_ptr<Character> &Tile::Actor() const
{
	return _actor;
}

const shared_ptr<Object> &Tile::Loot() const
{
	return _object;
}

/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Tile.hh"

using namespace Entropy::Asteria;
using namespace std;

using Entropy::Theia::GL::Texture;
using Entropy::Theia::Vertex;

Tile::Tile(const shared_ptr<Texture> &t, const bool isWall)
	: Sprite(t), _is_wall(isWall), _actor(), _object()
{}

Tile::Tile(const shared_ptr<Texture> &t, const shared_ptr<Asteria::Object> &obj)
	: Sprite(t), _is_wall(false), _actor(), _object(obj)
{}

Tile::Tile(const shared_ptr<Texture> &t, const shared_ptr<Character> &ch)
	: Sprite(t), _is_wall(false), _actor(ch), _object()
{}

Tile::Tile(const shared_ptr<Texture> &t, const shared_ptr<Asteria::Object> &obj, const shared_ptr<Character> &ch)
	: Sprite(t), _is_wall(false), _actor(ch), _object(obj)
{}

Tile::Tile(const Tile &) = default;
Tile::~Tile() = default;

void Tile::Translate(const Vertex &v)
{
	if(hasActor())
		Actor()->Translate(v);

	Sprite::Translate(v);
}

void Tile::Draw()
{
	Sprite::Draw();

	if(hasActor())
		_actor->Draw();
}

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

void Tile::setWall(const bool v)
{
	_is_wall = v;
}

void Tile::setActor(const shared_ptr<Character> &v)
{
	_actor = v;
	_actor->Translate(Position());
}

void Tile::setLoot(const shared_ptr<Asteria::Object> &v)
{
	_object = v;
}

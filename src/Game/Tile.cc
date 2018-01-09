/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Tile.hh"

using namespace Entropy::Asteria;
using namespace Entropy::Theia::GL;
using namespace std;

Tile::Tile(const shared_ptr<Texture> &t)
	: Sprite(t)
{}

Tile::Tile(const Tile &) = default;
Tile::Tile(Tile &&) = default;
Tile::~Tile() = default;

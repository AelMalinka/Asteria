/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Map.hh"

using namespace Entropy::Asteria;
using namespace std;

size_t Map::Height() const
{
	return _tiles.size();
}

size_t Map::Width() const
{
	if(_tiles.begin() == _tiles.end())
		return 0;

	return _tiles.front().size();
}

vector<vector<Tile>>::reference Map::operator [] (const size_t off)
{
	return _tiles[off];
}

vector<vector<Tile>>::iterator Map::begin()
{
	return _tiles.begin();
}

vector<vector<Tile>>::iterator Map::end()
{
	return _tiles.end();
}

vector<vector<Tile>>::const_reference Map::operator [] (const size_t off) const
{
	return _tiles[off];
}

vector<vector<Tile>>::const_iterator Map::begin() const
{
	return _tiles.begin();
}

vector<vector<Tile>>::const_iterator Map::end() const
{
	return _tiles.end();
}

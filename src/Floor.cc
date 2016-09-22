/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Floor.hh"

using namespace Entropy::Asteria;
using namespace std;

Floor::Floor(const size_t height, const size_t width)
	: _tiles(height, vector<bool>(width, false))
{}

Floor::~Floor() = default;

size_t Floor::Height() const
{
	return _tiles.size();
}

size_t Floor::Width() const
{
	return _tiles.front().size();
}

const vector<vector<bool>> &Floor::Tiles() const
{
	return _tiles;
}

vector<vector<bool>> &Floor::tiles()
{
	return _tiles;
}

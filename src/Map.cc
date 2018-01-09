/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Map.hh"

#include <utility>

using namespace Entropy::Asteria;
using namespace std;
using namespace Entropy::Theia;

Map::Map() = default;

Map::Map(const vector<vector<Tile>> &o)
	: _tiles(o)
{
	auto x = 0.0;
	auto y = 0.0;

	for(auto &i : _tiles) {
		for(auto &t : i) {
			t.Translate(Vertex(x, y++, 0.0));
		}
		x++; y = 0.0;
	}
}

Map::Map(vector<vector<Tile>> &&o)
	: _tiles(move(o))
{
	auto x = 0.0;
	auto y = 0.0;

	for(auto &i : _tiles) {
		for(auto &t : i) {
			t.Translate(Vertex(x, y++, 0.0));
		}
		x++; y = 0.0;
	}
}

Map::Map(initializer_list<vector<Tile>> o)
	: _tiles(o)
{}

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

void Map::Update(const chrono::duration<double> &dt)
{
	for(auto &i : _tiles) {
		for(auto &t : i) {
			dynamic_cast<Drawable &>(t).Update(dt);
		}
	}
}

void Map::UpdateScreen(const Screen &s)
{
	for(auto &i : _tiles) {
		for(auto &t : i) {
			dynamic_cast<Drawable &>(t).UpdateScreen(s);
		}
	}
}

void Map::UpdateCamera(const Camera &c)
{
	for(auto &i : _tiles) {
		for(auto &t : i) {
			dynamic_cast<Drawable &>(t).UpdateCamera(c);
		}
	}
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

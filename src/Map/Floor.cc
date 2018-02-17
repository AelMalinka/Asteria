/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Floor.hh"

using namespace Entropy::Asteria;
using namespace std;
using namespace Entropy::Theia::GL;

Floor::Floor(
	const size_t height,
	const size_t width,
	const shared_ptr<Texture> &f,
	const shared_ptr<Texture> &w
) :
	_floor(f),
	_wall(w),
	_map(make_shared<Map>(
		vector<vector<Tile>>(
			width,
			vector<Tile>(
				height,
				Tile(_floor)
			)
		)
	))
{}

Floor::~Floor() = default;

size_t Floor::Height() const
{
	return _map->Height();
}

size_t Floor::Width() const
{
	return _map->Width();
}

const Map &Floor::Tiles() const
{
	return *_map;
}

const shared_ptr<Map> &Floor::getMap() const
{
	return _map;
}

const shared_ptr<Texture> &Floor::Blank() const
{
	return _floor;
}

const shared_ptr<Texture> &Floor::Wall() const
{
	return _wall;
}

Map &Floor::tiles()
{
	return *_map;
}

/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Cave.hh"

using namespace Entropy::Asteria;
using namespace std;

using Entropy::Hecate::Roll;
using Entropy::Theia::GL::Texture;

Cave::Cave(
	const size_t height,
	const size_t width,
	const shared_ptr<Texture> &floor,
	const shared_ptr<Texture> &wall
) :
	Cellular(height, width, floor, wall),
	_open_areas(),
	_largest(_open_areas.end())
{}

Cave::~Cave() = default;

void Cave::operator () ()
{
	while(!checkOpenness()) {
		ENTROPY_LOG(Log, Severity::Info) << "Generating Cave floor";
		generateFloor();
		fillGaps();
	}
}

void Cave::generateFloor()
{
	_open_areas.clear();

	ENTROPY_LOG(Log, Severity::Debug) << "Generating base floor";
	init(_first_fill);

	ENTROPY_LOG(Log, Severity::Debug) << "Walling in";
	for(size_t x = 0; x < Width(); x++) {
		for(size_t y = 0; y < Height(); y++) {
			if(x == 0 || y == 0 || x == Width() - 1 || y == Height() - 1) {
				tiles()[x][y].setWall(true);
				tiles()[x][y].setTexture(Wall());
			}
		}
	}

	ENTROPY_LOG(Log, Severity::Debug) << "Aging cellular Automata";
	for(size_t x = 0; x < _openness_passes; x++) {
		step([this](auto &tile, auto count) {
			if(count[0] >= _smoothing_threshold || count[1] <= _openness_threshold) {
				tile.setWall(true);
				tile.setTexture(Wall());
			} else {
				tile.setWall(false);
				tile.setTexture(Blank());
			}
		}, {_smoothing_distance, _openness_distance});
	}

	for(size_t x = 0; x < _smoothing_passes; x++) {
		step([this](auto &tile, auto count) {
			if(count[0] >= _smoothing_threshold) {
				tile.setWall(true);
				tile.setTexture(Wall());
			} else {
				tile.setWall(false);
				tile.setTexture(Blank());
			}
		}, {_smoothing_distance});
	}

	ENTROPY_LOG(Log, Severity::Debug) << "Reaffirming wallin";
	for(size_t x = 0; x < Width(); x++) {
		for(size_t y = 0; y < Height(); y++) {
			if(x == 0 || y == 0 || x == Width() - 1 || y == Height() - 1) {
				tiles()[x][y].setWall(true);
				tiles()[x][y].setTexture(Wall());
			}
		}
	}
}

void Cave::fillGaps()
{
	_open_areas.emplace_back();
	auto next = _open_areas.begin();
	_largest = next;

	bool swapped = false;

	for(size_t x = 0; x < Width(); x++) {
		for(size_t y = 0; y < Height(); y++) {
			if(!swapped && tiles()[x][y].isWall())
				swapped = true;

			if(swapped && !tiles()[x][y].isWall()) {
				flood(*next, x, y);
				ENTROPY_LOG(Log, Severity::Debug) << next->size() << " entires in this block " << _largest->size() << " entries in largest block";
				if(next->size() > _largest->size()) {
					ENTROPY_LOG(Log, Severity::Debug) << "Swapping Largest: " << _largest->size() << " and " << next->size();
					_largest = next;
				}
				_open_areas.emplace_back();
				next = --_open_areas.end();
				swapped = false;
			}
		}
	}

	for(auto &q : _open_areas) {
		if(q.size() < _largest->size()) {
			ENTROPY_LOG(Log, Severity::Debug) << "filling in " << q.size() << " tiles";
			for(auto &&t : q) {
				t->setWall(true);
				t->setTexture(Wall());
				q.erase(t);
			}
		}
	}
}

bool Cave::checkOpenness()
{
	if(_open_areas.size() == 0 || Height() * Width() == 0)
		return false;

	auto area = Height() * Width();
	auto filled = _largest->size() * _required_openness_digits;

	ENTROPY_LOG(Log, Severity::Debug) << "Height: " << Height() << " Width: " << Width() << " area: " << Height() * Width() << " filled: " << _largest->size() << " " << filled / area << "%";
	ENTROPY_LOG(Log, Severity::Info) << "Generated cave floor with " << filled / area << "% openness";

	return filled / area >= _required_openness;
}

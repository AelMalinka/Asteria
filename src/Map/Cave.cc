/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Cave.hh"

using namespace Entropy::Asteria;
using namespace std;

Cave::Cave(const size_t height, const size_t width)
	: Floor(height, width)
{}

Cave::~Cave() = default;

void Cave::operator () ()
{
	for(auto &&j : Tiles()) {
		for(auto &&i : j) {
			if(Roll() < _first_fill) {
				i = true;
			}
		}
	}

	for(size_t x = 0; x < _openness_passes; x++) {
		step([](auto tile, auto count) {
			if(count[0] >= _smoothing_threshold || count[1] <= _openness_threshold)
				tile = true;
			else
				tile = false;
		}, {_smoothing_distance, _openness_distance});
	}

	for(size_t x = 0; x < _smoothing_passes; x++) {
		step([](auto tile, auto count) {
			if(count[0] >= _smoothing_threshold)
				tile = true;
			else
				tile = false;
		}, {_smoothing_distance});
	}
}

void Cave::step(const function<void(vector<bool>::reference, const vector<size_t> &)> &f, const std::vector<size_t> &distances)
{
	for(size_t i = 0; i < Height(); i++) {
		for(size_t j = 0; j < Width(); j++) {
			vector<size_t> counts;

			for(auto &&x : distances) {
				size_t count = 0;

				for(int ii = i - x; ii <= static_cast<int>(i) + static_cast<int>(x); ii++) {
					if(ii < 0 || ii >= static_cast<int>(Height())) {
						count += 3 * x * (0 - ii);
						continue;
					}

					for(int jj = j - x; jj <= static_cast<int>(j) + static_cast<int>(x); jj++) {
						if(jj < 0 || jj >= static_cast<int>(Width())) {
							count += 3 * x * (0 - jj);
							continue;
						}
						if(tiles()[ii][jj])
							++count;
					}
				}

				counts.push_back(count);
			}

			f(tiles()[i][j], counts);
		}
	}
}

/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Cellular.hh"

using namespace Entropy::Asteria;
using namespace std;
using namespace Entropy::Hecate;

using Entropy::Theia::GL::Texture;

Cellular::Cellular(
	const size_t height,
	const size_t width,
	const shared_ptr<Texture> &f,
	const shared_ptr<Texture> &w
) :
	Floor(height, width, f, w)
{}

Cellular::~Cellular() = default;

void Cellular::init(const PercentType first_fill)
{
	for(auto &&j : tiles()) {
		for(auto &&i : j) {
			if(Roll() < first_fill) {
				i.setWall(true);
				i.setTexture(Wall());
			} else {
				i.setWall(false);
				i.setTexture(Blank());
			}
		}
	}
}

// 2018-01-30 AMR TODO: is there a better interface for this
void Cellular::step(
	const function<void(Tile &, const vector<size_t> &)> &f,
	const vector<size_t> &distances
) {
	for(size_t i = 0; i < Width(); i++) {
		for(size_t j = 0; j < Height(); j++) {
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
						if(tiles()[ii][jj].isWall())
							++count;
					}
				}

				counts.push_back(count);
			}

			f(tiles()[i][j], counts);
		}
	}
}

// 2018-01-30 AMR FIXME: implementation does not correctly return whole area
void Cellular::flood(
	set<Tile *> &ret,
	const size_t x,
	const size_t y,
	const bool wall
) {
	if(tiles()[x][y].isWall() == wall && ret.find(&tiles()[x][y]) == ret.end()) {
		ret.insert(&tiles()[x][y]);
		if(x + 1 < Width() && tiles()[x + 1][y].isWall() == wall) {
			flood(ret, x + 1, y, wall);
		}
		if(static_cast<long long>(x) - 1 >= 0 && tiles()[x - 1][y].isWall() == wall) {
			flood(ret, x - 1, y, wall);
		}
		if(y + 1 < Height() && tiles()[x][y + 1].isWall() == wall) {
			flood(ret, x, y + 1, wall);
		}
		if(static_cast<long long>(y) - 1 >= 0 && tiles()[x][y - 1].isWall() == wall) {
			flood(ret, x, y - 1, wall);
		}
	}
}

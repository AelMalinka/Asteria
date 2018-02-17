/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Cellular.hh"
#include <queue>

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

set<Tile *> Cellular::flood(
	const size_t x,
	const size_t y,
	const bool wall
) {
	set<Tile *> ret;
	if(tiles()[x][y].isWall() == wall) {
		queue<Tile *> q;

		q.push(&tiles()[x][y]);
		while(!q.empty()) {
			Tile *t = q.front();
			q.pop();

			if(ret.find(t) == ret.end()) {
				ret.insert(t);

				auto i = static_cast<long long>(t->Position().x);
				auto j = static_cast<long long>(t->Position().y);
				auto w = static_cast<long long>(t->Position().x) - 1;
				auto e = static_cast<long long>(t->Position().x) + 1;
				auto s = static_cast<long long>(t->Position().y) - 1;
				auto n = static_cast<long long>(t->Position().y) + 1;

				if(w >= 0 && tiles()[w][j].isWall() == wall)
					q.push(&tiles()[w][j]);
				if(e <= static_cast<long long>(Width()) && tiles()[e][j].isWall() == wall)
					q.push(&tiles()[e][j]);
				if(s >= 0 && tiles()[i][s].isWall() == wall)
					q.push(&tiles()[i][s]);
				if(n <= static_cast<long long>(Height()) && tiles()[i][n].isWall() == wall)
					q.push(&tiles()[i][n]);
			}
		}
	}

	return ret;
}

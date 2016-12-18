/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_MAP
#	define ENTROPY_ASTERIA_MAP

#	include <vector>
#	include "Exception.hh"
#	include "Map/Tile.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Map
			{
				public:
					Map();
					explicit Map(const std::vector<std::vector<Tile>> &);
					explicit Map(std::vector<std::vector<Tile>> &&);
					Map(std::initializer_list<std::vector<Tile>>);
					std::size_t Height() const;
					std::size_t Width() const;
				public:
					std::vector<std::vector<Tile>>::reference operator [] (const std::size_t);
					std::vector<std::vector<Tile>>::iterator begin();
					std::vector<std::vector<Tile>>::iterator end();
					std::vector<std::vector<Tile>>::const_reference operator [] (const std::size_t) const;
					std::vector<std::vector<Tile>>::const_iterator begin() const;
					std::vector<std::vector<Tile>>::const_iterator end() const;
				private:
					std::vector<std::vector<Tile>> _tiles;
			};
		}
	}

#endif

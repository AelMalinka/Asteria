/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_FLOOR_INC
#	define ENTROPY_ASTERIA_FLOOR_INC

#	include "../Exception.hh"

#	include <vector>

	namespace Entropy
	{
		namespace Asteria
		{
			class Floor
			{
				public:
					Floor(const std::size_t, const std::size_t);
					virtual ~Floor();
					virtual void operator () () = 0;
					std::size_t Height() const;
					std::size_t Width() const;
					const std::vector<std::vector<bool>> &Tiles() const;
				protected:
					std::vector<std::vector<bool>> &tiles();
				private:
					std::vector<std::vector<bool>> _tiles;
			};
		}
	}

#endif

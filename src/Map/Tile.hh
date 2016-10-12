/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_TILE_INC
#	define ENTROPY_ASTERIA_TILE_INC

#	include <memory>
#	include "Object.hh"
#	include "../Character.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Tile
			{
				public:
					explicit Tile(const bool = false);
					Tile(const std::shared_ptr<Object> &);
					Tile(const std::shared_ptr<Character> &);
					Tile(const std::shared_ptr<Object> &, const std::shared_ptr<Character> &);
					Tile(const Tile &);
					~Tile();
					bool isWall() const;
					bool hasActor() const;
					bool hasObject() const;
					std::shared_ptr<Character> &Actor();
					std::shared_ptr<Object> &Loot();
					const std::shared_ptr<Character> &Actor() const;
					const std::shared_ptr<Object> &Loot() const;
				private:
					bool _is_wall;
					std::shared_ptr<Character> _actor;
					std::shared_ptr<Object> _object;
			};

			extern Tile Wall;
		}
	}

#endif

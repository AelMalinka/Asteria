/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_TILE_INC
#	define ENTROPY_ASTERIA_GAME_TILE_INC

#	include "Sprite.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Tile :
				public Sprite
			{
				public:
					explicit Tile(const std::shared_ptr<Theia::GL::Texture> &, const bool = false);
					Tile(const Tile &);
					Tile(Tile &&);
					virtual ~Tile();
				private:
					bool _is_wall;
					std::shared_ptr<Character> _actor;
					std::shared_ptr<Object> _object;
			};
		}
	}

#endif

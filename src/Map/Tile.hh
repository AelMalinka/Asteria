/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_TILE_INC
#	define ENTROPY_ASTERIA_TILE_INC

#	include <memory>
#	include "Object.hh"
#	include "../Character.hh"
#	include "../Game/Sprite.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Tile :
				public Sprite
			{
				public:
					explicit Tile(const std::shared_ptr<Theia::GL::Texture> &, const bool = false);
					Tile(const std::shared_ptr<Theia::GL::Texture> &, const std::shared_ptr<Asteria::Object> &);
					Tile(const std::shared_ptr<Theia::GL::Texture> &, const std::shared_ptr<Character> &);
					Tile(const std::shared_ptr<Theia::GL::Texture> &, const std::shared_ptr<Asteria::Object> &, const std::shared_ptr<Character> &);
					Tile(const Tile &);
					Tile(Tile &&);
					~Tile();
					bool isWall() const;
					bool hasActor() const;
					bool hasObject() const;
					std::shared_ptr<Character> &Actor();
					std::shared_ptr<Asteria::Object> &Loot();
					const std::shared_ptr<Character> &Actor() const;
					const std::shared_ptr<Asteria::Object> &Loot() const;
					void setWall(const bool);
					void setActor(const std::shared_ptr<Character> &);
					void setLoot(const std::shared_ptr<Asteria::Object> &);
					void Translate(const Theia::Vertex &);
					void Draw();
				private:
					bool _is_wall;
					std::shared_ptr<Character> _actor;
					std::shared_ptr<Asteria::Object> _object;
			};
		}
	}

#endif

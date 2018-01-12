/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_ACTOR_INC
#	define ENTROPY_ASTERIA_GAME_ACTOR_INC

#	include "Sprite.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			// 2018-01-11 AMR TODO: with moving everything to sprite, do we really want actor still?
			class Actor :
				public Sprite
			{
				public:
					Actor(const std::shared_ptr<Theia::GL::Texture> &);
					Actor(const Actor &);
					Actor(Actor &&);
					virtual ~Actor();
			};
		}
	}

#endif

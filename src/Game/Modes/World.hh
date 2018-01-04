/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MODES_WORLD_INC
#	define ENTROPY_ASTERIA_GAME_MODES_WORLD_INC

#	include <Entropy/Mnemosyne/Mode.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace Modes
			{
				class World :
					public Entropy::Mnemosyne::Mode
				{
					public:
						World(Mnemosyne::Application &);
						~World();
						void onEvent(const Event &);
				};
			}
		}
	}

#endif

/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MODES_WORLD_INC
#	define ENTROPY_ASTERIA_GAME_MODES_WORLD_INC

#	include "../Exception.hh"
#	include "../Character.hh"
#	include "../Map.hh"
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
						World(Mnemosyne::Application &, const std::shared_ptr<Character> &, const std::shared_ptr<Map> &);
						void onEvent(const Event &);
					private:
						std::shared_ptr<Character> _player;
						std::shared_ptr<Map> _map;
				};
			}
		}
	}

#endif

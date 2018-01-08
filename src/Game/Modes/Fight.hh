/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MODES_FIGHT_INC
#	define ENTROPY_ASTERIA_GAME_MODES_FIGHT_INC

#	include "../../Exception.hh"
#	include <Entropy/Mnemosyne/Mode.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace Modes
			{
				class Fight :
					public Entropy::Mnemosyne::Mode
				{
					public:
						Fight(Mnemosyne::Application &);
						void onEvent(const Event &);
				};
			}
		}
	}

#endif

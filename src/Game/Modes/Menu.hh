/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MODES_MENU_INC
#	define ENTROPY_ASTERIA_GAME_MODES_MENU_INC

#	include "../../Exception.hh"
#	include "../UI/Button.hh"
#	include <Entropy/Mnemosyne/Mode.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace Modes
			{
				class Menu :
					public Entropy::Mnemosyne::Mode
				{
					public:
						Menu(Mnemosyne::Application &);
						~Menu();
						void onEvent(const Event &);
					private:
						std::shared_ptr<UI::Button> _play;
						std::shared_ptr<UI::Button> _quit;
				};
			}
		}
	}

#endif

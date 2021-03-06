/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MODES_MENU_INC
#	define ENTROPY_ASTERIA_GAME_MODES_MENU_INC

#	include "../Application.hh"
#	include "../UI/Menu.hh"
#	include <Entropy/Mnemosyne/Mode.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace Modes
			{
				class Menu :
					public Entropy::Mnemosyne::Mode<Application>
				{
					public:
						Menu(Application &);
						void onEvent(const Entropy::Event &);
						void onEvent(const Mnemosyne::Events::ModeChange &);
						void onEvent(const Theia::Events::Show &);
						void onEvent(const Theia::Events::Resize &);
					private:
						std::shared_ptr<UI::Menu> _menu;
				};
			}
		}
	}

#endif

/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MENU_FIGHT_INC
#	define ENTROPY_ASTERIA_GAME_MENU_FIGHT_INC

#	include "../Engine/Menu.hh"
#	include "../../Character.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			namespace Menus
			{
				class Fight :
					public Menu
				{
					public:
						Fight(const std::shared_ptr<Character> &);
						void operator () (Engine &);
					private:
						std::shared_ptr<Character> _enemy;
				};
			}
		}
	}

#endif

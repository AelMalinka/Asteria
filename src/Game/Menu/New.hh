/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MENU_NEW_INC
#	define ENTROPY_ASTERIA_GAME_MENU_NEW_INC

#	include "../Engine/Menu.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			namespace Menus
			{
				class New :
					public Menu
				{
					public:
						void operator () (Engine &);
				};
			}
		}
	}

#endif

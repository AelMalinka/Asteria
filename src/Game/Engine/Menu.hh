/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MENU_INC
#	define ENTROPY_ASTERIA_GAME_MENU_INC

	namespace Entropy
	{
		namespace Asteria
		{
			class Engine;

			class Menu
			{
				public:
					virtual void operator () (Engine &) = 0;
			};
		}
	}

#endif

/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MENU_EXPLORE_INC
#	define ENTROPY_ASTERIA_GAME_MENU_EXPLORE_INC

#	include <cstddef>

	namespace Entropy
	{
		namespace Asteria
		{
			class Engine;

			class Explore
			{
				public:
					void operator () (Engine &);
				private:
					void _map(Engine &);
					void _menu(Engine &);
					void _move(Engine &, const std::size_t, const std::size_t);
			};
		}
	}

#endif

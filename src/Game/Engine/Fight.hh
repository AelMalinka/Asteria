/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MENU_FIGHT_INC
#	define ENTROPY_ASTERIA_GAME_MENU_FIGHT_INC

#	include "../../Character.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Engine;

			class Fight
			{
				public:
					Fight(const std::shared_ptr<Character> &);
					void operator () (Engine &);
				private:
					std::shared_ptr<Character> _enemy;
					std::shared_ptr<Check> _me;
					std::shared_ptr<Check> _them;
			};
		}
	}

#endif

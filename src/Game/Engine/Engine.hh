/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_ENGINE_INC
#	define ENTROPY_ASTERIA_GAME_ENGINE_INC

#	include "Renderer.hh"

#	include "../../Character.hh"
#	include "../../Map.hh"

#	include "../Menu/Main.hh"
#	include "../Menu/New.hh"
#	include "../Menu/Explore.hh"
#	include "../Menu/Fight.hh"

#	include <memory>
#	include <tuple>

	namespace Entropy
	{
		namespace Asteria
		{
			class Engine
			{
				public:
					Engine();
					void operator () ();
					void Done();
					void Main();
					void New();
					void NewGame(const std::shared_ptr<Character> &, const std::shared_ptr<Character> &);
					void Fight(const std::shared_ptr<Character> &);
					Map &map();
					std::tuple<std::size_t, std::size_t> &Position();
					std::shared_ptr<Character> &Player();
				private:
					void _generate_map();
				private:
					bool _done;
					Menus::Main _main;
					Menus::New _new;
					Menus::Explore _expl;
					Renderer _rend;
					std::shared_ptr<Character> _ch;
					std::shared_ptr<Character> _mob;
					Map _map;
					std::tuple<std::size_t, std::size_t> _pos;
			};
		}
	}

#endif

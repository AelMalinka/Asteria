/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_ENGINE_INC
#	define ENTROPY_ASTERIA_GAME_ENGINE_INC

#	include "../Character.hh"
#	include "../Map.hh"

#	include "Engine/Title.hh"
#	include "Engine/New.hh"
#	include "Engine/Explore.hh"
#	include "Engine/Fight.hh"

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
					void StartNewGame();
					void NewGame(const std::shared_ptr<Character> &, const std::shared_ptr<Character> &);
					void StartFight(const std::shared_ptr<Character> &);
					Map &map();
					std::tuple<std::size_t, std::size_t> &Position();
					std::shared_ptr<Character> &Player();
				private:
					void _generate_map();
				private:
					bool _done;
					Title _main;
					New _new;
					Explore _expl;
					std::function<void(Engine &)> _current;
					std::shared_ptr<Character> _ch;
					std::shared_ptr<Character> _mob;
					Map _map;
					std::tuple<std::size_t, std::size_t> _pos;
			};
		}
	}

#endif

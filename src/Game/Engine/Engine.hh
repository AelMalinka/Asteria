/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_ENGINE_INC
#	define ENTROPY_ASTERIA_GAME_ENGINE_INC

#	include "Renderer.hh"

#	include "../Menu/Main.hh"
#	include "../Menu/New.hh"

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
				private:
					bool _done;
					Menus::Main _main;
					Menus::New _new;
					Renderer _rend;
			};
		}
	}

#endif

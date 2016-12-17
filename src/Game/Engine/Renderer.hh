/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_RENDERER_INC
#	define ENTROPY_ASTERIA_GAME_RENDERER_INC

#	include "Menu.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Engine;

			class Renderer
			{
				public:
					Renderer(Menu *);
					void operator () (Engine &);
					void changeMenu(Menu *);
				private:
					Menu *_current;
			};
		}
	}

#endif

/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MAIN_INC
#	define ENTROPY_ASTERIA_GAME_MAIN_INC

#	include <Entropy/Application.hh>
#	include "Engine.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Application :
				public Entropy::Application
			{
				public:
					Application();
					Application(const int, char *[]);
					void operator () ();
				private:
					Engine _engine;
			};
		}
	}

#endif

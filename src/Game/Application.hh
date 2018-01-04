/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MAIN_INC
#	define ENTROPY_ASTERIA_GAME_MAIN_INC

#	include <Entropy/Mnemosyne/Application.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			class Application :
				public Entropy::Mnemosyne::Application
			{
				public:
					Application();
					Application(const int, char *[]);
				private:
					PolymorphicList<Mnemosyne::Mode>::iterator _menu;
					PolymorphicList<Mnemosyne::Mode>::iterator _world;
					PolymorphicList<Mnemosyne::Mode>::iterator _fight;
			};
		}
	}

#endif

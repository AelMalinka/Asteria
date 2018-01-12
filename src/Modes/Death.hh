/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MODES_DEATH_INC
#	define ENTROPY_ASTERIA_GAME_MODES_DEATH_INC

#	include "../Application.hh"
#	include <Entropy/Mnemosyne/Mode.hh>
#	include <Entropy/Theia/UI/Text.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace Modes
			{
				class Death :
					public Entropy::Mnemosyne::Mode<Application>
				{
					public:
						Death(Application &);
						void onEvent(const Mnemosyne::Events::ModeChange &);
						void onEvent(const Theia::Events::Resize &);
						void onEvent(const Theia::Events::Key &);
					private:
						std::shared_ptr<Theia::UI::Text> _message;
				};
			}
		}
	}

#endif

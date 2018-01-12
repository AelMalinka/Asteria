/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MODES_FIGHT_INC
#	define ENTROPY_ASTERIA_GAME_MODES_FIGHT_INC

#	include "../Application.hh"
#	include "../Character.hh"
#	include "../Map.hh"
#	include "../UI/Menu.hh"
#	include <Entropy/Mnemosyne/Mode.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace Modes
			{
				ENTROPY_ERROR_INFO(APositionInfo, Theia::Vertex);
				ENTROPY_ERROR_INFO(BPositionInfo, Theia::Vertex);

				class Fight :
					public Entropy::Mnemosyne::Mode<Application>
				{
					public:
						Fight(Application &);
						void onEvent(const Event &);
						void setMap(const std::shared_ptr<Map> &);
						// 2018-01-10 AMR TODO: how should we handle multiple enemies?
						void setCombatants(const std::shared_ptr<Character> &, const std::shared_ptr<Character> &);
					private:
						std::shared_ptr<UI::Menu> _menu;
						std::shared_ptr<Theia::UI::Text> _info;
						std::shared_ptr<Sprite> _bg;
						std::shared_ptr<Map> _map;
						std::shared_ptr<Character> _a;
						std::shared_ptr<Character> _b;
				};
			}
		}
	}

#endif

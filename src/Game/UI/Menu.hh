/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_UI_MENU_INC
#	define ENTROPY_ASTERIA_GAME_UI_MENU_INC

#	include <vector>
#	include <utility>
#	include <functional>
#	include <Entropy/Event.hh>
#	include "Button.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			namespace UI
			{
				class Menu :
					public Theia::UI::Element
				{
					public:
						typedef std::function<void(const Event &)> callback;
						typedef std::vector<std::pair<Button, callback>> container;
						typedef container::iterator iterator;
					public:
						Menu(const std::vector<std::pair<std::string, callback>> &, const std::shared_ptr<Theia::UI::FT::Font> &);
						void setPosition(const Theia::ScreenVertex &);
						void setColor(const Theia::Vertex &);
						void setScale(const Theia::Dimension &);
						void setTransparency(const Theia::Dimension &);
						Theia::ScreenVertex Size() const;
						void setSelected(const iterator &);
						void onEvent(const Event &);
						std::size_t size();
						iterator begin();
						iterator end();
						iterator selected();
					protected:
						void Draw();
						void UpdateScreen(const Theia::Screen &);
					protected:
						void Update();
					private:
						container _menus;
				};
			}
		}
	}

#endif

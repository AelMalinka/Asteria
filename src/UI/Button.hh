/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_UI_BUTTON_INC
#	define ENTROPY_ASTERIA_GAME_UI_BUTTON_INC

#	include "../Exception.hh"
#	include <Entropy/Theia/UI/Box.hh>
#	include <Entropy/Theia/UI/Text.hh>

#	ifndef ENTROPY_ASTERIA_BUTTON_SELECTED_TRANSPARENCY
#		define ENTROPY_ASTERIA_BUTTON_SELECTED_TRANSPARENCY 0.5
#	endif

	namespace Entropy
	{
		namespace Asteria
		{
			namespace UI
			{
				class Button :
					public Theia::UI::Element
				{
					public:
						Button(const std::string &, const std::shared_ptr<Theia::UI::FT::Font> &);
						void setPosition(const Theia::ScreenVertex &);
						void setScale(const Theia::Dimension &);
						void setTextColor(const Theia::Vertex &);
						void setSelectColor(const Theia::Vertex &);
						void setTransparency(const Theia::Dimension &);
						void setValue(const std::string &);
						void setValue(std::string &&);
						void setSelected(const bool);
						void toggleSelected();
						Theia::ScreenVertex Position() const;
						Theia::Dimension Scale() const;
						Theia::Vertex TextColor() const;
						Theia::Vertex SelectColor() const;
						Theia::Dimension Transparency() const;
						const std::string &Value() const;
						bool isSelected() const;
						Theia::ScreenVertex Size() const;
						void Draw();
						void UpdateScreen(const Theia::Screen &);
					private:
						Theia::UI::Text _text;
						Theia::UI::Box _selected;
						static constexpr Theia::Dimension _selected_transparency = ENTROPY_ASTERIA_BUTTON_SELECTED_TRANSPARENCY;
				};
			}
		}
	}

#endif

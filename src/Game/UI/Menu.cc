/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Menu.hh"
#include <Entropy/Theia/Events.hh>

using namespace Entropy::Asteria::UI;
using namespace Entropy::Theia::UI;
using namespace Entropy::Theia::UI::FT;
using namespace Entropy::Theia;
using namespace Entropy::Theia::Events;
using namespace std;

Menu::Menu(const std::vector<std::pair<std::string, Menu::callback>> &items, const shared_ptr<Font> &font)
	: Element(), _menus()
{
	for(auto &i : items) {
		Button &&t = Button(i.first, font);
		_menus.push_back(make_pair(move(t), i.second));
	}

	setSelected(begin());
	Update();
}

ScreenVertex Menu::Size() const
{
	ScreenVertex r;

	for(auto &b : _menus) {
		r.y += b.first.Size().y;

		if(b.first.Size().x > r.x)
			r.x = b.first.Size().x;
	}

	return r;
}

void Menu::Update()
{
	// 2018-01-06 AMR NOTE: top-left
	ScreenDimension y = Position().y + Size().y;

	for(auto &b : _menus) {
		b.first.setTextColor(Color());
		b.first.setTransparency(Transparency());
		b.first.setScale(Scale());

		b.first.setPosition(ScreenVertex(Position().x, y));
		y -= b.first.Size().y;
	}
}

void Menu::onEvent(const Entropy::Event &ev)
{
	if(ev.Id() == Key::Id) {
		const Key &k = dynamic_cast<const Key &>(ev);

		if(k.Action() == GLFW_PRESS || k.Action() == GLFW_REPEAT) {
			if(k.Code() == GLFW_KEY_UP) {
				if(selected() == begin()) {
					setSelected(--end());
				} else {
					setSelected(--selected());
				}
			} else if(k.Code() == GLFW_KEY_DOWN) {
				if(selected() == --end()) {
					setSelected(begin());
				} else {
					setSelected(++selected());
				}
			} else {
				if(selected() != end())
					selected()->second(ev);
			}
		} else {
			if(selected() != end())
				selected()->second(ev);
		}
	} else {
		if(selected() != end())
			selected()->second(ev);
	}
}

void Menu::setSelected(const Menu::iterator &i)
{
	for(auto &b : _menus) {
		b.first.setSelected(false);
	}

	i->first.setSelected(true);
}

Menu::iterator Menu::selected()
{
	for(auto ret = begin(); ret != end(); ++ret) {
		if(ret->first.isSelected()) {
			return ret;
		}
	}

	return end();
}

void Menu::Draw()
{
	for(auto &b : _menus) {
		b.first.Draw();
	}
}

void Menu::UpdateScreen(const Screen &s)
{
	for(auto &b : _menus) {
		b.first.UpdateScreen(s);
	}
}

void Menu::setPosition(const ScreenVertex &v)
{
	Element::setPosition(v);

	Update();
}

void Menu::setColor(const Vertex &v)
{
	Element::setColor(v);

	Update();
}

void Menu::setScale(const Dimension &v)
{
	Element::setScale(v);

	Update();
}

void Menu::setTransparency(const Dimension &v)
{
	Element::setTransparency(v);

	Update();
}

size_t Menu::size()
{
	return _menus.size();
}

Menu::iterator Menu::begin()
{
	return _menus.begin();
}

Menu::iterator Menu::end()
{
	return _menus.end();
}

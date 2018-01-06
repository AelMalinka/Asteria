/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Button.hh"


using namespace Entropy::Asteria::UI;
using namespace Entropy::Theia;
using namespace Entropy::Theia::UI;
using namespace Entropy::Theia::UI::FT;
using namespace std;

constexpr Dimension Button::_selected_transparency;

Button::Button(const string &text, const shared_ptr<Font> &font) :
	_text(text, font),
	_selected(_text.Size().x, _text.Size().y)
{
	_selected.setTransparency(0.0);
}

Button::~Button() = default;

void Button::setPosition(const ScreenVertex &v)
{
	_text.setPosition(v);
	_selected.setPosition(v);
}

void Button::setTextColor(const Vertex &v)
{
	_text.setColor(v);
}

void Button::setSelectColor(const Vertex &v)
{
	_selected.setColor(v);
}

void Button::setScale(const Dimension &v)
{
	_text.setScale(v);
	_selected.setScale(v);
}

void Button::setTransparency(const Dimension &v)
{
	_text.setTransparency(v);
}

void Button::setSelected(const bool sel)
{
	_selected.setTransparency((sel) ? _selected_transparency : 0.0);
}

void Button::toggleSelected()
{
	setSelected(!isSelected());
}

const ScreenVertex &Button::Position() const
{
	return _text.Position();
}

const Dimension &Button::Scale() const
{
	return _text.Scale();
}

Vertex Button::TextColor() const
{
	return _text.Color();
}

Vertex Button::SelectColor() const
{
	return _selected.Color();
}

Dimension Button::Transparency() const
{
	return _text.Transparency();
}

bool Button::isSelected() const
{
	return _selected.Transparency() != 0.0;
}

void Button::Draw()
{
	Theia::Drawable &t = dynamic_cast<Theia::Drawable &>(_text);
	Theia::Drawable &b = dynamic_cast<Theia::Drawable &>(_selected);

	t.Update(chrono::duration<double>());
	b.Update(chrono::duration<double>());
}

void Button::UpdateScreen(const Theia::Screen &s)
{
	Theia::Drawable &t = dynamic_cast<Theia::Drawable &>(_text);
	Theia::Drawable &b = dynamic_cast<Theia::Drawable &>(_selected);

	t.UpdateScreen(s);
	b.UpdateScreen(s);
}

const ScreenVertex Button::Size() const
{
	return _text.Size();
}

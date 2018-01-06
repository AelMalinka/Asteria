/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Menu.hh"

#include <Entropy/Mnemosyne/Resources/Font.hh>

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Asteria;
using namespace Entropy::Asteria::UI;
using namespace Entropy::Mnemosyne::Resources;
using namespace Entropy::Theia;
using namespace std;

Menu::Menu(Mnemosyne::Application &app)
	: Mode(app), _play(), _quit()
{
	auto f = App().load("NotoSansUI-Regular.ttf"s, Font());

	_play = make_shared<Button>("Play"s, f.shared());
	_quit = make_shared<Button>("Quit"s, f.shared());

	_play->setTextColor(Vertex(1.0, 1.0, 1.0));
	_quit->setTextColor(Vertex(1.0, 1.0, 1.0));

	Current().addDrawable(_play);
	Current().addDrawable(_quit);
}

Menu::~Menu() = default;

void Menu::onEvent(const Entropy::Event &ev)
{
	if(ev.Id() == Theia::Events::Show::Id) {
		dynamic_cast<const Theia::Events::Show &>(ev).Window().Fullscreen();
	} else if(ev.Id() == Theia::Events::Tick::Id) {
		_play->setPosition(ScreenVertex(App().Windows()->getScreen().Width() / 2 - _play->Size().x / 2, App().Windows()->getScreen().Height() / 2 + 5));
		_quit->setPosition(ScreenVertex(App().Windows()->getScreen().Width() / 2 - _quit->Size().x / 2, App().Windows()->getScreen().Height() / 2 - _quit->Size().y + 5));
	}
}

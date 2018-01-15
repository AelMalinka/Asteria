/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Menu.hh"
#include <Entropy/Mnemosyne/Resources/Font.hh>
#include <Entropy/Mnemosyne/Events.hh>

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Asteria;
using namespace Entropy::Mnemosyne::Resources;
using namespace Entropy::Mnemosyne::Events;
using namespace Entropy::Theia;
using namespace Entropy::Theia::Events;
using namespace Entropy;
using namespace std;

using Entropy::Event;

Menu::Menu(Application &a)
	: Mode(a), _menu()
{
	vector<pair<string, UI::Menu::callback>> v = {
		make_pair("Play"s, Mnemosyne::onEvent(
			[this](const Key &k) {
				if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ENTER) {
					App().World();
				}
			}
		)),
		make_pair("Options"s, Mnemosyne::onEvent(
			[this](const Key &k) {
				if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ENTER) {
					App().Options();
				}
			}
		)),
		make_pair("Quit"s, Mnemosyne::onEvent(
			[this](const Key &k) {
				if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ENTER) {
					App().Windows()->Close();
				}
			}
		))
	};

	_menu = make_shared<UI::Menu>(v, App().load("NotoSansUI-Regular.ttf"s, Font()).shared());

	Current().addDrawable(_menu);
}

void Menu::onEvent(const Event &ev)
{
	_menu->onEvent(ev);

	Mode<Asteria::Application>::onEvent(ev);
}

void Menu::onEvent(const ModeChange &)
{
	_menu->setPosition(ScreenVertex(App().Windows()->getScreen().Width() / 2 - _menu->Size().x, App().Windows()->getScreen().Height() / 2 - _menu->Size().y));
}

void Menu::onEvent(const Show &)
{
	if(dynamic_cast<const Application &>(App()).Settings()["fullscreen"].asBool()) {
		App().Windows()->Fullscreen();
	}
}

void Menu::onEvent(const Resize &rz)
{
	_menu->setPosition(ScreenVertex(rz.Width() / 2 - _menu->Size().x, rz.Height() / 2 - _menu->Size().y));
}

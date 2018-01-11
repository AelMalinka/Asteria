/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Menu.hh"
#include "../Application.hh"
#include <Entropy/Mnemosyne/Resources/Font.hh>
#include <Entropy/Mnemosyne/Events.hh>

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Asteria;
using namespace Entropy::Mnemosyne::Resources;
using namespace Entropy::Theia;
using namespace Entropy;
using namespace std;

using Entropy::Event;

Menu::Menu(Mnemosyne::Application &a)
	: Mode(a), _menu()
{
	Application &app = dynamic_cast<Application &>(App());

	vector<pair<string, UI::Menu::callback>> v = {
		make_pair("Play"s, [&app](const Event &ev) {
			if(ev.Id() == Events::Key::Id) {
				const Events::Key &k = dynamic_cast<const Events::Key &>(ev);
				if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ENTER) {
					app.World();
				}
			}
		}),
		make_pair("Options"s, [&app](const Event &ev) {
			if(ev.Id() == Events::Key::Id) {
				const Events::Key &k = dynamic_cast<const Events::Key &>(ev);
				if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ENTER) {
					app.Options();
				}
			}
		}),
		make_pair("Quit"s, [&app](const Event &ev) {
			if(ev.Id() == Events::Key::Id) {
				const Events::Key &k = dynamic_cast<const Events::Key &>(ev);
				if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ENTER) {
					app.Windows()->Close();
				}
			}
		})
	};

	_menu = make_shared<UI::Menu>(v, App().load("NotoSansUI-Regular.ttf"s, Font()).shared());

	Current().addDrawable(_menu);
}

void Menu::onEvent(const Event &ev)
{
	if(ev.Id() == Theia::Events::Show::Id) {
		if(dynamic_cast<const Application &>(App()).Settings()["fullscreen"].asBool()) {
			App().Windows()->Fullscreen();
		}
	} else if(ev.Id() == Mnemosyne::Events::ModeChange::Id) {
		_menu->setPosition(ScreenVertex(App().Windows()->getScreen().Width() / 2 - _menu->Size().x, App().Windows()->getScreen().Height() / 2 - _menu->Size().y));
	} else if(ev.Id() == Theia::Events::Resize::Id) {
		const Theia::Events::Resize &rz = dynamic_cast<const Theia::Events::Resize &>(ev);
		_menu->setPosition(ScreenVertex(rz.Width() / 2 - _menu->Size().x, rz.Height() / 2 - _menu->Size().y));
	}

	_menu->onEvent(ev);
}

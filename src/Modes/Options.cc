/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Options.hh"
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

Options::Options(Application &a)
	: Mode(a), _menu()
{
	vector<pair<string, UI::Menu::callback>> v = {
		make_pair("Fullscreen: "s + App().Settings()["fullscreen"].asString(), Mnemosyne::onEvent(
			[this](const Key &k) {
				if(k.Action() == GLFW_PRESS || k.Action() == GLFW_REPEAT) {
					if(k.Code() == GLFW_KEY_ENTER || k.Code() == GLFW_KEY_RIGHT || k.Code() == GLFW_KEY_LEFT) {
						App().Windows()->Fullscreen();
						App().Settings()["fullscreen"] = !App().Settings()["fullscreen"].asBool();

						_menu->selected()->first.setValue("Fullscreen: "s + App().Settings()["fullscreen"].asString());
					}
				}
			}
		)),
		make_pair("Back"s, Mnemosyne::onEvent(
			[this](const Key &k) {
				if(k.Action() == GLFW_PRESS || k.Action() == GLFW_REPEAT) {
					if(k.Code() == GLFW_KEY_ENTER) {
						App().Menu();
					}
				}
			}
		))
	};

	_menu = make_shared<UI::Menu>(v, App().load("NotoSansUI-Regular.ttf"s, Font()).shared());

	Current().addDrawable(_menu);
}

void Options::onEvent(const Entropy::Event &ev)
{
	_menu->onEvent(ev);

	Mode<Asteria::Application>::onEvent(ev);
}

void Options::onEvent(const ModeChange &)
{
	_menu->setPosition(ScreenVertex(App().Windows()->getScreen().Width() / 2 - _menu->Size().x, App().Windows()->getScreen().Height() / 2 - _menu->Size().y));
}

void Options::onEvent(const Resize &rz)
{
	_menu->setPosition(ScreenVertex(rz.Width() / 2 - _menu->Size().x, rz.Height() / 2 - _menu->Size().y));
}

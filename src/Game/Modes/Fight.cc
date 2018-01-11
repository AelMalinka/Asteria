/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Fight.hh"
#include "../Application.hh"
#include <Entropy/Mnemosyne/Resources/Font.hh>
#include <Entropy/Mnemosyne/Resources/Texture.hh>
#include <Entropy/Mnemosyne/Events.hh>
#include <boost/lexical_cast.hpp>

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Asteria;
using namespace Entropy::Asteria::UI;
using namespace Entropy::Mnemosyne;
using namespace Entropy::Mnemosyne::Resources;
using namespace Entropy::Theia;
using namespace Entropy::Theia::UI;
using namespace std;

using boost::lexical_cast;

Fight::Fight(Mnemosyne::Application &a)
	: Mode(a), _menu(), _info(), _bg(), _map(), _a(), _b()
{
	Application &app = dynamic_cast<Application &>(a);

	auto font = App().load("NotoSansUI-Regular.ttf"s, Font());
	auto bg = App().load("Grass.png"s, Texture(GL::Texture::Texture2D));

	vector<pair<string, UI::Menu::callback>> v = {
		make_pair("Run!"s, [&app, this](const Event &ev) {
			if(ev.Id() == Theia::Events::Key::Id) {
				const Theia::Events::Key &k = dynamic_cast<const Theia::Events::Key &>(ev);
				Check flee = _a->Flee(*_b);

				if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ENTER) {
					Vertex to = Vertex(0, 0, 0);
					if((*_map)[_a->Position().x + 1][_a->Position().y].isWall()) {
						if((*_map)[_a->Position().x][_a->Position().y - 1].isWall()) {
							if((*_map)[_a->Position().x - 1][_a->Position().y].isWall()) {
								if((*_map)[_a->Position().x][_a->Position().y + 1].isWall()) {
									_info->setValue("Can't Run!");
									return;
								} else {
									to.y++;
								}
							} else {
								to.x--;
							}
						} else {
							to.y--;
						}
					} else {
						to.x++;
					}

					auto res = flee();
					if(res) {
						_info->setValue("Encounter!"s);
						_a->Translate(to);
						app.World();
					} else {
						auto s = "Failed to run"s;
#						ifdef DEBUG
							 s +=  " rolled: "s + lexical_cast<string>(res.Value()) + " chance: "s + lexical_cast<string>(res.Chance());
#						endif
						_info->setValue(s);
					}
				}
			}
		})
	};

	// 2018-01-10 AMR TODO: cleanup interface
	// 2018-01-10 AMR TODO: fix ugly ass background
	_menu = make_shared<Menu>(v, font.shared());
	_info = make_shared<Text>("Encounter!"s, font.shared());
	_bg = make_shared<Sprite>(bg.shared());

	_info->setScale(.5);
	_info->setColor(Vertex(1, 1, 1));
	_bg->Scale(Vertex(100, 100, 1));

	Current().getCamera().setPosition(Vertex(0, 0, 0.1));

	Current().addDrawable(_bg);
	Current().addDrawable(_menu);
	Current().addDrawable(_info);
}

void Fight::setCombatants(const shared_ptr<Character> &a, const shared_ptr<Character> &b)
{
	_a = a;
	_b = b;
}

void Fight::setMap(const shared_ptr<Map> &m)
{
	_map = m;
}

void Fight::onEvent(const Entropy::Event &ev)
{
	if(ev.Id() == Mnemosyne::Events::ModeChange::Id) {
		_menu->setPosition(ScreenVertex(App().Windows()->getScreen().Width() / 2 - _menu->Size().x, App().Windows()->getScreen().Height() / 2 - _menu->Size().y - App().Windows()->getScreen().Height() / 4));
		_info->setPosition(ScreenVertex(App().Windows()->getScreen().Width() / 2 - _info->Size().x, App().Windows()->getScreen().Height() / 2 - _info->Size().y + App().Windows()->getScreen().Height() / 4));

		// 2018-01-10 AMR TODO: should we verify we're the new mode?
		if(!_map) {
			ENTROPY_THROW(Exception("Failed to set field of batlle"));
		} else if(!_a || !_b) {
			// 2018-01-10 AMR TODO: should we really crash on this condition?
			ENTROPY_THROW(Exception("Failed to set combantants"));
		} else if(_a->Position() != _b->Position()) {
			// 2018-01-10 AMR TODO: should we really crash on this condition?
			ENTROPY_THROW(Exception("Combantants are not in position to fight") <<
				APositionInfo(_a->Position()) <<
				BPositionInfo(_b->Position())
			);
		}
	} else if(ev.Id() == Theia::Events::Resize::Id) {
		const Theia::Events::Resize &rz = dynamic_cast<const Theia::Events::Resize &>(ev);
		_menu->setPosition(ScreenVertex(rz.Width() / 2 - _menu->Size().x, rz.Height() / 2 - _menu->Size().y - rz.Height() / 4));
		_info->setPosition(ScreenVertex(rz.Width() / 2 - _info->Size().x, rz.Height() / 2 - _info->Size().y + rz.Height() / 4));
	}

	_menu->onEvent(ev);
}

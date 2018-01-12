/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Death.hh"
#include <Entropy/Mnemosyne/Resources/Font.hh>
#include <Entropy/Mnemosyne/Events.hh>

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Asteria;
using namespace Entropy::Mnemosyne::Resources;
using namespace Entropy::Theia;
using namespace Entropy::Theia::UI;
using namespace Entropy;
using namespace Entropy::Mnemosyne::Events;
using namespace Entropy::Theia::Events;
using namespace std;

Death::Death(Application &a)
	: Mode(a), _message()
{
	_message = make_shared<Text>("You Died"s, App().load("NotoSansUI-Regular.ttf"s, Font()).shared());
	_message->setColor(Vertex(1, 0, 0));
	_message->setScale(3);

	Current().addDrawable(_message);
}

void Death::onEvent(const Event &ev)
{
	if(ev.Id() == ModeChange::Id) {
		_message->setPosition(ScreenVertex(App().Windows()->getScreen().Width() / 2 - _message->Size().x / 2, App().Windows()->getScreen().Height() / 2));
	} else if(ev.Id() == Resize::Id) {
		const Resize &rz = dynamic_cast<const Resize &>(ev);
		_message->setPosition(ScreenVertex(rz.Width() / 2 - _message->Size().x / 2, rz.Height() / 2));
	} else if(ev.Id() == Key::Id) {
		const Key &k = dynamic_cast<const Key &>(ev);
		if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ENTER) {
			App().Restart();
		}
	}
}

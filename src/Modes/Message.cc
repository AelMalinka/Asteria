/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Message.hh"
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

Message::Message(Application &a, const string &t, const Vertex &c)
	: Mode(a), _message()
{
	_message = make_shared<Text>(t, App().load("NotoSansUI-Regular.ttf"s, Font()).shared());
	_message->setColor(c);
	_message->setScale(3);

	Current().addDrawable(_message);
}

void Message::onEvent(const ModeChange &)
{
	_message->setPosition(ScreenVertex(App().Windows()->getScreen().Width() / 2 - _message->Size().x / 2, App().Windows()->getScreen().Height() / 2));
}

void Message::onEvent(const Resize &rz)
{
	_message->setPosition(ScreenVertex(rz.Width() / 2 - _message->Size().x / 2, rz.Height() / 2));
}

void Message::onEvent(const Key &k)
{
	if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ENTER) {
		App().Restart();
	}
}

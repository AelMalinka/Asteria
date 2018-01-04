/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Menu.hh"

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Mnemosyne;

Menu::Menu(Mnemosyne::Application &app)
	: Mode(app)
{}

Menu::~Menu() = default;

void Menu::onEvent(const Entropy::Event &)
{}

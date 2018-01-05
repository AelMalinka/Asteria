/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Fight.hh"

using namespace Entropy::Asteria::Modes;
using namespace Entropy::Mnemosyne;

Fight::Fight(Mnemosyne::Application &app)
	: Mode(app)
{}

Fight::~Fight() = default;

void Fight::onEvent(const Entropy::Event &)
{}

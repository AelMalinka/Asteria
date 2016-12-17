/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Renderer.hh"
#include "Engine.hh"

using namespace Entropy::Asteria;

#include <iostream>
using namespace std;

Renderer::Renderer(Menu *menu)
	: _current(menu)
{}

void Renderer::operator () (Engine &engine)
{
	(*_current)(engine);
}

void Renderer::changeMenu(Menu *menu)
{
	_current = menu;
}

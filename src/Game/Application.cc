/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

using namespace Entropy::Asteria;

Application::Application() = default;

Application::Application(const int ArgC, char *ArgV[])
	: Entropy::Application(ArgC, ArgV)
{}

void Application::operator () ()
{
	_engine();
}

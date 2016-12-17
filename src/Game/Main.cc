/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Main.hh"

using namespace Entropy::Asteria;
using namespace Entropy;

Main::Main() = default;

Main::Main(const int ArgC, char *ArgV[])
	: Application(ArgC, ArgV)
{}

void Main::operator () ()
{
	_engine();
}

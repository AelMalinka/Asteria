/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include "Application.hh"

using namespace std;
using namespace Entropy::Asteria;

int main(int ArgC, char *ArgV[])
{
	try
	{
		Application app(ArgC, ArgV);
		app();
	}
	catch(exception &e)
	{
		cerr << e << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Armor.hh"

using namespace Entropy::Asteria;
using namespace std;
using namespace Entropy::Theia::GL;

Armor::Armor(const string &name, const shared_ptr<Texture> &t, const Armor::Type &type, const Template &templ)
	: Equipment(name, t, Equipment::Slot::Armor, templ), _type(type)
{}

Armor::Armor(const Armor &) = default;
Armor::Armor(Armor &&) = default;
Armor::~Armor() = default;

const Armor::Type &Armor::Which() const
{
	return _type;
}

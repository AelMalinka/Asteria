/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Weapon.hh"

using namespace Entropy::Asteria;
using namespace std;

Weapon::Weapon(const string &name, const Type &type, const Template &templ)
	: Equipment(name, Equipment::Slot::Weapon, templ), _type(type)
{}

Weapon::Weapon(const Weapon &) = default;
Weapon::Weapon(Weapon &&) = default;
Weapon::~Weapon() = default;

const Weapon::Type &Weapon::Which() const
{
	return _type;
}

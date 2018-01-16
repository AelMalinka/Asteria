/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Equipment.hh"

using namespace Entropy::Asteria;
using namespace Entropy::Theia::GL;
using namespace std;

Equipment::Equipment(const string &name, const shared_ptr<Texture> &t, const Equipment::Slot &where, const Template &templ)
	: Item(name, templ), Sprite(t), _where(where)
{}

Equipment::Equipment(const Equipment &) = default;
Equipment::Equipment(Equipment &&) = default;
Equipment::~Equipment() = default;

const Equipment::Slot &Equipment::Where() const
{
	return _where;
}

/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Item.hh"

using namespace Entropy::Asteria;
using namespace std;

Item::Item(const string &name, const Template &templ)
	: _name(name), _templ(templ)
{}

Item::Item(const Item &) = default;
Item::Item(Item &&) = default;
Item::~Item() = default;

const string &Item::Name() const
{
	return _name;
}

Template &Item::Value()
{
	return _templ;
}

const Template &Item::Value() const
{
	return _templ;
}

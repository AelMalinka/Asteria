/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Object.hh"

using namespace Entropy::Asteria;
using namespace std;

Object::Object()
	: _loot()
{}

Object::Object(initializer_list<shared_ptr<Item>> il)
	: _loot(il)
{}

Object::Object(const Object &) = default;
Object::Object(Object &&) = default;
Object::~Object() = default;

size_t Object::size() const
{
	return _loot.size();
}

vector<shared_ptr<Item>>::iterator Object::begin()
{
	return _loot.begin();
}

vector<shared_ptr<Item>>::iterator Object::end()
{
	return _loot.end();
}

/*	Copyright 2016 (c) Michael Thovas (valinka) <valinka@entropy-developvent.cov>
	Distributed under the tervs of the GNU Affero General Public License v3
*/

#include "Character.hh"

using namespace Entropy::Asteria;
using namespace std;

Character::Character(const Strength &s, const Agility &a, const Endurance &e, const Perception &p, const Magic &v, const Willpower &w)
	: BaseCharacter(s, a, e, p, v, w)
{}

/*	Copyright 2016 (c) Michael Thovas (valinka) <valinka@entropy-developvent.cov>
	Distributed under the tervs of the GNU Affero General Public License v3
*/

#include "Character.hh"

using namespace Entropy::Asteria;
using namespace std;

Character::Character(const Strength &s, const Agility &a, const Endurance &e, const Perception &p, const Magic &v, const Willpower &w)
	: BaseCharacter(s, a, e, p, v, w), _weapon(), _armor(Armor::Type::None)
{}

Check Character::Attack(Character &target)
{
	Check ret;
	Melee melee(Stats());
	Ranged ranged(Stats());

	Unarmed unarmed(0, get(melee));
	Sword sword(0, get(melee));
	Blunt blunt(0, get(melee));

	Bow bow(0, get(ranged));
	Thrown thrown(0, get(ranged));

	Weapon::Type type = Weapon::Type::None;

	if(_weapon)
		type = _weapon->Which();

	switch(type)
	{
		case Weapon::Type::None:
			return _check(
				Modifier(target.Defend(), "Opponent's Defense", negative),
				Modifier(get(unarmed), "Unarmed Skill")
			);
		case Weapon::Type::Sword:
			return _check(
				Modifier(target.Defend(), "Opponent's Defense", negative),
				Modifier(get(sword), "Sword Skill")
			);
		case Weapon::Type::Blunt:
			return _check(
				Modifier(target.Defend(), "Opponent's Defense", negative),
				Modifier(get(blunt), "Blunt Skill")
			);
		case Weapon::Type::Bow:
			return _check(
				Modifier(target.Defend(), "Opponent's Defense", negative),
				Modifier(get(bow), "Bow Skill")
			);
		case Weapon::Type::Thrown:
			return _check(
				Modifier(target.Defend(), "Opponent's Defense", negative),
				Modifier(get(thrown), "Thrown Skill")
			);
		default:
			ENTROPY_THROW(Exception("Unknown Weapon Type") <<
				WeaponTypeInfo(_weapon->Which())
			);
	}
}

Check Character::Defend()
{
	Unarmored unarmored(Stats());
	LightArmor lightarmor(0, get(unarmored), strength());
	HeavyArmor heavyarmor(0, get(unarmored), strength(), endurance());

	switch(_armor)
	{
		case Armor::Type::None:
			return _check(Modifier(get(unarmored), "Unarmored"));
		break;
		case Armor::Type::Light:
			return _check(Modifier(get(lightarmor), "Light Armor"));
		break;
		case Armor::Type::Heavy:
			return _check(Modifier(get(heavyarmor), "Heavy Armor"));
		break;
		default:
			ENTROPY_THROW(Exception("Unknown Armor Type") <<
				ArmorTypeInfo(_armor)
			);
	}
}

void Character::Equip(const Weapon &weapon)
{
	Unequip(weapon.Where());

	_equipment[weapon.Where()] = make_shared<Weapon>(weapon);
	_equipment[weapon.Where()]->Value().Add(*this);
	_weapon = dynamic_pointer_cast<Weapon>(_equipment[weapon.Where()]);
}

void Character::Equip(const Armor &armor)
{
	Unequip(armor.Where());

	_equipment[armor.Where()] = make_shared<Armor>(armor);
	_equipment[armor.Where()]->Value().Add(*this);
	_armor = armor.Which();
}

void Character::Equip(const Equipment &equip)
{
	Unequip(equip.Where());

	_equipment[equip.Where()] = make_shared<Equipment>(equip);
	_equipment[equip.Where()]->Value().Add(*this);
}

void Character::Unequip(const Equipment::Slot &where)
{
	if(_equipment.find(where) != _equipment.end())
		_equipment[where]->Value().Remove(*this);

	_equipment.erase(where);
}

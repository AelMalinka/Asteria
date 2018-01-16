/*	Copyright 2016 (c) Michael Thovas (valinka) <valinka@entropy-developvent.cov>
	Distributed under the tervs of the GNU Affero General Public License v3
*/

#include "Character.hh"

using namespace Entropy::Asteria;
using namespace Entropy::Theia::GL;
using namespace std;

Character::Character(const shared_ptr<Texture> &t, const Strength &s, const Agility &a, const Endurance &e, const Perception &p, const Magic &v, const Willpower &w) :
	BaseCharacter(s, a, e, p, v, w),
	Actor(t),
	_health(Stats()),
	_weapon(),
	_armor(Armor::Type::None)
{}

Health &Character::Hp()
{
	return _health;
}

const Health &Character::Hp() const
{
	return _health;
}

bool Character::isAlive() const
{
	return _health.Current() > 0;
}

Check Character::Attack(Character &target)
{
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

	Check ret(_check(Modifier(target.Defend(), negative)));

	switch(type)
	{
		case Weapon::Type::None:
			ret.Add(Modifier(get(unarmed)));
		break;
		case Weapon::Type::Sword:
			ret.Add(Modifier(get(sword)));
		break;
		case Weapon::Type::Blunt:
			ret.Add(Modifier(get(blunt)));
		break;
		case Weapon::Type::Bow:
			ret.Add(Modifier(get(bow)));
		break;
		case Weapon::Type::Thrown:
			ret.Add(Modifier(get(thrown)));
		break;
		default:
			ENTROPY_THROW(Exception("Unknown Weapon Type") <<
				WeaponTypeInfo(type)
			);
	}

	// 2017-02-10 AMR TODO: various weapon damages
	// 2017-02-10 AMR TODO: armor effects?
	// 2017-02-10 AMR TODO: cleanup
	ret.Add(Hecate::onSuccess([this, &target](const Check::Result &res) {
		PercentType dmg = 0;

		if (res.isCritical())
			dmg = _default_damage;
		else
			dmg = res.Value() * _default_damage / res.Chance();

		if(dmg == 0)
			dmg = 1;

		target.Hp().Current() -= dmg;
	}));

	return ret;
}

Check Character::Defend()
{
	Strength strength;
	Endurance endurance;
	Unarmored unarmored(Stats());
	LightArmor lightarmor(0, get(unarmored), get(strength));
	HeavyArmor heavyarmor(0, get(unarmored), get(strength), get(endurance));

	switch(_armor)
	{
		case Armor::Type::None:
			return _check(Modifier(get(unarmored)));
		break;
		case Armor::Type::Light:
			return _check(Modifier(get(lightarmor)));
		break;
		case Armor::Type::Heavy:
			return _check(Modifier(get(heavyarmor)));
		break;
		default:
			ENTROPY_THROW(Exception("Unknown Armor Type") <<
				ArmorTypeInfo(_armor)
			);
	}
}

Check Character::Flee(Character &other)
{
	Agility agi;

	return _check(
		Modifier(get(agi)),
		Modifier(other.Chase(), negative)
	);
}

Check Character::Chase()
{
	Agility agi;

	return _check(Modifier(get(agi)));
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

void Character::Draw()
{
	Actor::Draw();

	// 2018-01-16 AMR NOTE: draw them in this order for stacking purposes
	if(_equipment[Equipment::Slot::Accessory]) _equipment[Equipment::Slot::Accessory]->Draw();
	if(_equipment[Equipment::Slot::Armor]) _equipment[Equipment::Slot::Armor]->Draw();
	if(_equipment[Equipment::Slot::Weapon]) _equipment[Equipment::Slot::Weapon]->Draw();
}

void Character::UpdateCamera(const Theia::Camera &c)
{
	Actor::UpdateCamera(c);

	for(auto &&p : _equipment) {
		if(p.second)
			p.second->UpdateCamera(c);
	}
}

void Character::UpdateScreen(const Theia::Screen &s)
{
	Actor::UpdateScreen(s);

	for(auto &&p : _equipment) {
		if(p.second)
			p.second->UpdateScreen(s);
	}
}

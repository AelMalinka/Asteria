/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_CHARACTER_INC
#	define ENTROPY_ASTERIA_CHARACTER_INC

#	include <Entropy/Hecate/Character.hh>

#	include "Exception.hh"

#	include "Stats.hh"
#	include "Skills.hh"

#	include "Weapon.hh"
#	include "Armor.hh"

#	include <map>
#	include <memory>

	namespace Entropy
	{
		namespace Asteria
		{
			using BaseCharacter = Entropy::Hecate::Character<Entropy::Hecate::tuple<Strength, Agility, Endurance, Perception, Magic, Willpower>>;

			using Entropy::Hecate::Check;
			using Entropy::Hecate::Modifier;
			using Entropy::Hecate::negative;

			class Character :
				public BaseCharacter
			{
				public:
					Character(const Strength &, const Agility &, const Endurance &, const Perception &, const Magic &, const Willpower &);
					Check Attack(Character &);
					Check Defend();
					void Equip(const Weapon &);
					void Equip(const Armor &);
					void Equip(const Equipment &);
					void Unequip(const Equipment::Slot &);
				private:
					std::shared_ptr<Weapon> _weapon;
					Armor::Type _armor;
					std::map<Equipment::Slot, std::shared_ptr<Equipment>> _equipment;
			};
		}
	}

#endif

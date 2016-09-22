/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_CHARACTER_INC
#	define ENTROPY_ASTERIA_CHARACTER_INC

#	include <Entropy/Hecate/Character.hh>

#	include "Exception.hh"
#	include "Weapon.hh"
#	include "Armor.hh"

#	include <map>
#	include <memory>

	namespace Entropy
	{
		namespace Asteria
		{
			// 2016-09-10 AMR TODO: balance stats, skills
			ENTROPY_HECATE_DEFINE_STAT(Strength, 11);
			ENTROPY_HECATE_DEFINE_STAT(Agility, 11);
			ENTROPY_HECATE_DEFINE_STAT(Endurance, 5);
			ENTROPY_HECATE_DEFINE_STAT(Perception, 3);
			ENTROPY_HECATE_DEFINE_STAT(Magic, 5);
			ENTROPY_HECATE_DEFINE_STAT(Willpower, 2);

			ENTROPY_HECATE_DEFINE_SKILL(Melee, 3, Strength, Strength, Agility);
			ENTROPY_HECATE_DEFINE_SKILL(Sword, 1, Melee);
			ENTROPY_HECATE_DEFINE_SKILL(Blunt, 1, Melee);
			ENTROPY_HECATE_DEFINE_SKILL(Unarmed, 1, Melee);

			ENTROPY_HECATE_DEFINE_SKILL(Ranged, 2, Strength, Agility, Agility);
			ENTROPY_HECATE_DEFINE_SKILL(Bow, 1, Ranged);
			ENTROPY_HECATE_DEFINE_SKILL(Thrown, 1, Ranged);

			ENTROPY_HECATE_DEFINE_SKILL(Find, 1, Perception);

			ENTROPY_HECATE_DEFINE_SKILL(Unarmored, 3, Agility, Agility, Endurance);
			ENTROPY_HECATE_DEFINE_SKILL(LightArmor, 1, Unarmored, Strength);
			ENTROPY_HECATE_DEFINE_SKILL(HeavyArmor, 1, Unarmored, Strength, Endurance);

			ENTROPY_HECATE_DEFINE_SKILL(Divination, 1, Magic, Perception);
			ENTROPY_HECATE_DEFINE_SKILL(Alteration, 1, Magic, Willpower);
			ENTROPY_HECATE_DEFINE_SKILL(Healing, 1, Magic, Endurance);
			ENTROPY_HECATE_DEFINE_SKILL(Destruction, 1, Magic, Strength);

			ENTROPY_HECATE_DEFINE_CHARACTER(Strength, Agility, Endurance, Perception, Magic, Willpower);

			using Entropy::Hecate::Check;
			using Entropy::Hecate::Modifier;
			using Entropy::Hecate::negative;

			class Character :
				public BaseCharacter
			{
				public:
					Character(const Strength &, const Agility &, const Endurance &, const Perception &, const Magic &, const Willpower &);
					ENTROPY_HECATE_STAT_ACCESSOR(strength, Strength);
					ENTROPY_HECATE_STAT_ACCESSOR(agility, Agility);
					ENTROPY_HECATE_STAT_ACCESSOR(endurance, Endurance);
					ENTROPY_HECATE_STAT_ACCESSOR(perception, Perception);
					ENTROPY_HECATE_STAT_ACCESSOR(magic, Magic);
					ENTROPY_HECATE_STAT_ACCESSOR(willpower, Willpower);
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

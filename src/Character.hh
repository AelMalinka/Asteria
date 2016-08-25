/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_CHARACTER_INC
#	define ENTROPY_ASTERIA_CHARACTER_INC

#	include <Entropy/Hecate/Character.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			ENTROPY_HECATE_DEFINE_STAT(Strength);
			ENTROPY_HECATE_DEFINE_STAT(Agility);
			ENTROPY_HECATE_DEFINE_STAT(Endurance);
			ENTROPY_HECATE_DEFINE_STAT(Perception);
			ENTROPY_HECATE_DEFINE_STAT(Magic);
			ENTROPY_HECATE_DEFINE_STAT(Willpower);

			ENTROPY_HECATE_DEFINE_SKILL(Melee, Strength, Strength, Agility);
			ENTROPY_HECATE_DEFINE_SKILL(Sword, Melee);
			ENTROPY_HECATE_DEFINE_SKILL(Blunt, Melee);
			ENTROPY_HECATE_DEFINE_SKILL(Unarmed, Melee);

			ENTROPY_HECATE_DEFINE_SKILL(Ranged, Strength, Agility, Agility);
			ENTROPY_HECATE_DEFINE_SKILL(Bow, Ranged);
			ENTROPY_HECATE_DEFINE_SKILL(Thrown, Ranged);

			ENTROPY_HECATE_DEFINE_SKILL(Unarmored, Agility, Agility, Endurance);
			ENTROPY_HECATE_DEFINE_SKILL(LightArmor, Unarmored, Strength);
			ENTROPY_HECATE_DEFINE_SKILL(HeavyArmor, Unarmored, Strength, Endurance);

			ENTROPY_HECATE_DEFINE_SKILL(Divination, Magic, Perception);
			ENTROPY_HECATE_DEFINE_SKILL(Alteration, Magic, Willpower);
			ENTROPY_HECATE_DEFINE_SKILL(Healing, Magic, Endurance);
			ENTROPY_HECATE_DEFINE_SKILL(Destruction, Magic, Strength);

			ENTROPY_HECATE_DEFINE_CHARACTER(Strength, Agility, Endurance, Perception, Magic, Willpower);

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
			};
		}
	}

#endif

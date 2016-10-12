/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_SKILLS_INC
#	define ENTROPY_ASTERIA_SKILLS_INC

#	include "Stats.hh"

#	include <Entropy/Hecate/Skill.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace detail
			{
				struct melee {};
				struct sword {};
				struct blunt {};
				struct unarmed {};

				struct ranged {};
				struct bow {};
				struct thrown {};

				struct find {};

				struct unarmored {};
				struct light {};
				struct heavy {};

				struct divination {};
				struct alteration {};
				struct healing {};
				struct destruction {};
			}

			using Melee = Entropy::Hecate::Skill<detail::melee, 4, Strength, Strength, Agility>;
			using Sword = Entropy::Hecate::Skill<detail::sword, 1, Melee>;
			using Blunt = Entropy::Hecate::Skill<detail::blunt, 1, Melee>;
			using Unarmed = Entropy::Hecate::Skill<detail::unarmed, 1, Melee>;

			using Ranged = Entropy::Hecate::Skill<detail::ranged, 3, Strength, Agility, Agility>;
			using Bow = Entropy::Hecate::Skill<detail::bow, 1, Ranged>;
			using Thrown = Entropy::Hecate::Skill<detail::thrown, 1, Ranged>;

			using Find = Entropy::Hecate::Skill<detail::find, 1, Perception>;

			using Unarmored = Entropy::Hecate::Skill<detail::unarmed, 3, Agility, Agility, Endurance>;
			using LightArmor = Entropy::Hecate::Skill<detail::light, 1, Unarmored, Strength>;
			using HeavyArmor = Entropy::Hecate::Skill<detail::heavy, 1, Unarmored, Strength, Endurance>;

			using Divination = Entropy::Hecate::Skill<detail::divination, 1, Magic, Perception>;
			using Alteration = Entropy::Hecate::Skill<detail::alteration, 1, Magic, Willpower>;
			using Healing = Entropy::Hecate::Skill<detail::healing, 1, Magic, Endurance>;
			using Destruction = Entropy::Hecate::Skill<detail::destruction, 1, Magic, Strength>;
		}
	}

#endif

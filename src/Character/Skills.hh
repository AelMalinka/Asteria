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

				struct unarmored {};
				struct light {};
				struct heavy {};

				struct divination {};
				struct alteration {};
				struct healing {};
				struct destruction {};

				struct find {};
			}

			using Melee = Entropy::Hecate::Skill<detail::melee, Entropy::Hecate::Linear<4>, Strength, Strength, Agility>;
			using Sword = Entropy::Hecate::Skill<detail::sword, Entropy::Hecate::Linear<1>, Melee>;
			using Blunt = Entropy::Hecate::Skill<detail::blunt, Entropy::Hecate::Linear<1>, Melee>;
			using Unarmed = Entropy::Hecate::Skill<detail::unarmed, Entropy::Hecate::Linear<1>, Melee>;

			using Ranged = Entropy::Hecate::Skill<detail::ranged, Entropy::Hecate::Linear<3>, Strength, Agility, Agility>;
			using Bow = Entropy::Hecate::Skill<detail::bow, Entropy::Hecate::Linear<1>, Ranged>;
			using Thrown = Entropy::Hecate::Skill<detail::thrown, Entropy::Hecate::Linear<1>, Ranged>;

			using Unarmored = Entropy::Hecate::Skill<detail::unarmed, Entropy::Hecate::Linear<3>, Agility, Agility, Endurance>;
			using LightArmor = Entropy::Hecate::Skill<detail::light, Entropy::Hecate::Linear<1>, Unarmored, Strength>;
			using HeavyArmor = Entropy::Hecate::Skill<detail::heavy, Entropy::Hecate::Linear<1>, Unarmored, Strength, Endurance>;

			using Divination = Entropy::Hecate::Skill<detail::divination, Entropy::Hecate::Linear<1>, Magic, Perception>;
			using Alteration = Entropy::Hecate::Skill<detail::alteration, Entropy::Hecate::Linear<1>, Magic, Willpower>;
			using Healing = Entropy::Hecate::Skill<detail::healing, Entropy::Hecate::Linear<1>, Magic, Endurance>;
			using Destruction = Entropy::Hecate::Skill<detail::destruction, Entropy::Hecate::Linear<1>, Magic, Strength>;

			using Find = Entropy::Hecate::Skill<detail::find, Entropy::Hecate::Linear<1>, Perception, Perception, Divination>;
		}
	}

#endif

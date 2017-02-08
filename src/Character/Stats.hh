/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_STATS_INC
#	define ENTROPY_ASTERIA_STATS_INC

#	include <Entropy/Hecate/Stat.hh>
#	include <Entropy/Hecate/Algorithms/Linear.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace detail
			{
				struct strength {};
				struct agility {};
				struct endurance {};
				struct perception {};
				struct magic {};
				struct willpower {};
			}

			// 2016-09-22 AMR TODO: balance stats
			using Strength = Entropy::Hecate::Stat<detail::strength, Entropy::Hecate::Linear<11>>;
			using Agility = Entropy::Hecate::Stat<detail::agility, Entropy::Hecate::Linear<11>>;
			using Endurance = Entropy::Hecate::Stat<detail::endurance, Entropy::Hecate::Linear<6>>;
			using Perception = Entropy::Hecate::Stat<detail::perception, Entropy::Hecate::Linear<3>>;
			using Magic = Entropy::Hecate::Stat<detail::magic, Entropy::Hecate::Linear<5>>;
			using Willpower = Entropy::Hecate::Stat<detail::willpower, Entropy::Hecate::Linear<2>>;
		}
	}

#endif

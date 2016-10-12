/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_STATS_INC
#	define ENTROPY_ASTERIA_STATS_INC

#	include <Entropy/Hecate/Stat.hh>

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
			using Strength = Entropy::Hecate::Stat<detail::strength, 11>;
			using Agility = Entropy::Hecate::Stat<detail::agility, 11>;
			using Endurance = Entropy::Hecate::Stat<detail::endurance, 5>;
			using Perception = Entropy::Hecate::Stat<detail::perception, 3>;
			using Magic = Entropy::Hecate::Stat<detail::magic, 5>;
			using Willpower = Entropy::Hecate::Stat<detail::willpower, 2>;
		}
	}

#endif

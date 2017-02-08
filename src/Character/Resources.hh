/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_RESOURCES_INC
#	define ENTROPY_ASTERIA_RESOURCES_INC

#	include "Skills.hh"

#	include <Entropy/Hecate/Resource.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace detail
			{
				struct health {};
			}

			using Health = Entropy::Hecate::Resource<detail::health, Entropy::Hecate::Linear<10>, Entropy::Hecate::Linear<1>, Endurance>;
		}
	}

#endif

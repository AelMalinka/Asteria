/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_CAVE_INC
#	define ENTROPY_ASTERIA_CAVE_INC

#	include "Floor.hh"

#	include <Entropy/Hecate/Random.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			using Entropy::Hecate::PercentType;

			class Cave :
				public Floor
			{
				public:
					Cave(const std::size_t, const std::size_t);
					virtual ~Cave();
					virtual void operator () ();
				protected:
					void step(const std::function<void(std::vector<bool>::reference, const std::vector<std::size_t> &)> &, const std::vector<std::size_t> &);
				private:
					// 2016-09-22 AMR TODO: abstract some, cleanup interface, make runtime parameters
					static constexpr PercentType _first_fill = 45;
					static constexpr std::size_t _openness_threshold = 2;
					static constexpr std::size_t _openness_distance = 2;
					static constexpr std::size_t _openness_passes = 4;
					static constexpr std::size_t _smoothing_threshold = 5;
					static constexpr std::size_t _smoothing_distance = 1;
					static constexpr std::size_t _smoothing_passes = 3;
			};
		}
	}

#endif

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
					// 2018-01-16 AMR TODO: cleanup
					Cave(const std::size_t, const std::size_t, const std::shared_ptr<Theia::GL::Texture> &, const std::shared_ptr<Theia::GL::Texture> &);
					virtual ~Cave();
					virtual void operator () ();
				protected:
					virtual void generateFloor();
					virtual void step(const std::function<void(Tile &, const std::vector<std::size_t> &)> &, const std::vector<std::size_t> &);
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

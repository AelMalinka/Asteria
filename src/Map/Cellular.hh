/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_CELLULAR_INC
#	define ENTROPY_ASTERIA_CELLULAR_INC

#	include "Floor.hh"
#	include <Entropy/Hecate/Random.hh>
#	include <set>

	namespace Entropy
	{
		namespace Asteria
		{
			// 2018-01-30 AMR TODO: add to testing
			class Cellular :
				public Floor
			{
				public:
					Cellular(const std::size_t, const std::size_t, const std::shared_ptr<Theia::GL::Texture> &, const std::shared_ptr<Theia::GL::Texture> &);
					virtual ~Cellular();
				protected:
					virtual void init(const PercentType);
					virtual void step(const std::function<void(Tile &, const std::vector<std::size_t> &)> &, const std::vector<std::size_t> &);
					virtual void flood(std::set<Tile *> &, const std::size_t, const std::size_t, const bool = false);
			};
		}
	}

#endif

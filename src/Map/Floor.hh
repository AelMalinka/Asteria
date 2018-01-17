/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_FLOOR_INC
#	define ENTROPY_ASTERIA_FLOOR_INC

#	include "../Exception.hh"
#	include "../Map.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Floor
			{
				public:
					Floor(const std::size_t, const std::size_t, const std::shared_ptr<Theia::GL::Texture> &, const std::shared_ptr<Theia::GL::Texture> &);
					virtual ~Floor();
					virtual void operator () () = 0;
					std::size_t Height() const;
					std::size_t Width() const;
					const Map &Tiles() const;
				protected:
					Map &tiles();
					const std::shared_ptr<Theia::GL::Texture> &Blank() const;
					const std::shared_ptr<Theia::GL::Texture> &Wall() const;
				private:
					std::shared_ptr<Theia::GL::Texture> _floor;
					std::shared_ptr<Theia::GL::Texture> _wall;
					Map _map;
			};
		}
	}

#endif

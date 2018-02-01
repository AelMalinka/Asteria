/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_CAMERA_INC
#	define ENTROPY_ASTERIA_CAMERA_INC

#	include "Exception.hh"
#	include <Entropy/Mnemosyne/EventHandler.hh>
#	include <Entropy/Theia/Camera.hh>
#	include "Map.hh"

	// 2018-02-01 AMR NOTE: currently only works well near 5
#	ifndef ENTROPY_ASTERIA_ZOOM_LEVEL
#		define ENTROPY_ASTERIA_ZOOM_LEVEL 5
#	endif

	namespace Entropy
	{
		namespace Asteria
		{
			// 2018-01-31 AMR TODO: this being drawable feels horribly counter intuitive 
			class Camera :
				public Mnemosyne::EventHandler,
				public Theia::Drawable
			{
				public:
					Camera(Theia::Camera &, const std::shared_ptr<Character> &, const std::shared_ptr<Map> &);
					void Update(const std::chrono::duration<double> &);
					void UpdateScreen(const Theia::Screen &);
					void UpdateCamera(const Theia::Camera &);
					constexpr Theia::Dimension Height() const;
					constexpr Theia::Dimension Width() const;
				protected:
					void Update();
					void onEvent(const Theia::Events::Key &);
				private:
					Theia::Camera &_camera;
					std::shared_ptr<Character> _player;
					std::shared_ptr<Map> _map;
					static constexpr std::size_t _zoom_level = ENTROPY_ASTERIA_ZOOM_LEVEL;
			};
		}
	}

#endif

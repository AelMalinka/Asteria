/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_SPRITE_INC
#	define ENTROPY_ASTERIA_GAME_SPRITE_INC

#	include <Entropy/SharedData.hh>
#	include <Entropy/Theia/Object.hh>
#	include <Entropy/Theia/GL/Texture.hh>
#	include <Entropy/Theia/GL/Program.hh>
#	include <Entropy/Theia/GL/Array.hh>
#	include <Entropy/Theia/GL/Buffer.hh>
#	include <Entropy/Mnemosyne/Handle.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			namespace detail
			{
				struct sprite_data
				{
					sprite_data();
					Theia::GL::Program program;
					Theia::GL::Array array;
					Theia::GL::Buffer elements;
				};
			}

			class Sprite :
				private SharedData<detail::sprite_data>,
				public Theia::Object
			{
				public:
					explicit Sprite(const std::shared_ptr<Theia::GL::Texture> &);
					Sprite(const Sprite &);
					Sprite(Sprite &&);
					virtual ~Sprite();
					virtual void Draw();
					virtual void UpdateModel();
					virtual void UpdateScreen(const Theia::Screen &);
					virtual void UpdateCamera(const Theia::Camera &);
					virtual void Translate(const Theia::Vertex &);
					const Theia::Vertex &Position() const;
					virtual void Flip();
					virtual bool isFlipped() const;
				private:
					std::shared_ptr<Theia::GL::Texture> _texture;
					Theia::Vertex _position;
					bool _is_flipped;
			};
		}
	}

#endif

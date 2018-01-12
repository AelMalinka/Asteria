/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_GAME_MAIN_INC
#	define ENTROPY_ASTERIA_GAME_MAIN_INC

#	include "Exception.hh"
#	include "Character.hh"
#	include "Map.hh"

#	include <Entropy/Mnemosyne/Application.hh>
#	include <Entropy/Mnemosyne/Handle.hh>
#	include <Entropy/Theia/GL/Texture.hh>
#	include <json/json.h>

	namespace Entropy
	{
		namespace Asteria
		{
			class Application :
				public Entropy::Mnemosyne::Application
			{
				public:
					Application();
					Application(const int, char *[]);
					~Application();
					void Menu();
					void World();
					void Options();
					void Restart();
					void Fight(const std::shared_ptr<Character> &, const std::shared_ptr<Character> &, const std::shared_ptr<Map> &);
					void Win(const std::shared_ptr<Character> &);
					Json::Value &Settings();
					const Json::Value &Settings() const;
				private:
					std::shared_ptr<Character> _player;
					std::shared_ptr<Map> _map;
					PolymorphicList<Mnemosyne::ModeBase>::iterator _menu;
					PolymorphicList<Mnemosyne::ModeBase>::iterator _world;
					PolymorphicList<Mnemosyne::ModeBase>::iterator _fight;
					PolymorphicList<Mnemosyne::ModeBase>::iterator _options;
					PolymorphicList<Mnemosyne::ModeBase>::iterator _death;
					Mnemosyne::Handle<Theia::GL::Texture> _enemy;
					Mnemosyne::Handle<Json::Value> _settings;
			};
		}
	}

#endif

/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <Entropy/Mnemosyne/Application.hh>
#include <Entropy/Mnemosyne/Resources/Texture.hh>
#include "Map.hh"
#include "Map/Cave.hh"

using namespace std;
using namespace Entropy::Asteria;
using namespace Entropy::Mnemosyne;
using namespace Entropy::Mnemosyne::Events;
using namespace Entropy::Theia::Events;
using namespace Entropy::Theia::GL;

// 2018-01-30 AMR TODO: probably should using these in Asteria
using Entropy::PolymorphicList;
using Entropy::Theia::Vertex;

// 2018-01-30 AMR TODO: runtime specify
constexpr size_t HEIGHT = 100;
constexpr size_t WIDTH = 100;
// 2018-01-30 AMR TODO: auto-caluclate
constexpr size_t ZOOM = 40;

// 2018-01-30 AMR TODO: use Astera::Application as a base
class MyApp :
	public Application
{
	public:
		MyApp(const int, char *[]);
		~MyApp() = default;
		void Done();
	private:
		PolymorphicList<ModeBase>::iterator _mode;
};

class MyMode :
	public Mode<MyApp>
{
	public:
		MyMode(MyApp &);
		void Reset();
		void onEvent(const Key &);
	private:
		Handle<Texture> _floor;
		Handle<Texture> _wall;
		shared_ptr<Map> _map;
};

int main(int argc, char *argv[])
{
	try
	{
		MyApp app(argc, argv);
		app();

		return EXIT_SUCCESS;
	}
	catch(exception &e)
	{
		cerr << e << endl;
	}

	return EXIT_FAILURE;
}

void MyMode::onEvent(const Key &k)
{
	if(k.Action() == GLFW_PRESS || k.Action() == GLFW_REPEAT) {
		if(k.Code() == GLFW_KEY_ESCAPE) {
			App().Done();
		} else if(k.Code() == GLFW_KEY_ENTER) {
			Reset();
		}
	}
}

void MyMode::Reset()
{
	Current().clearDrawables();
	Cave c(WIDTH, HEIGHT, _floor.shared(), _wall.shared());

	c();

	_map = make_shared<Map>(c.Tiles());
	Current().addDrawable(_map);
}

MyMode::MyMode(MyApp &a)
	: Mode<MyApp>(a), _map()
{
	Current().getCamera().setPosition(Vertex(WIDTH / 2, HEIGHT / 2, ZOOM));
	Current().getCamera().setLookAt(Vertex(WIDTH / 2, HEIGHT / 2, 0));

	_floor = App().load("Grass.png", Resources::Texture(Texture::Texture2D));
	_wall = App().load("Mountain.png", Resources::Texture(Texture::Texture2D));

	Reset();
}

MyApp::MyApp(const int argc, char *argv[]) :
	Application(argc, argv),
	_mode(end())
{
	addSearchPath(DATADIR);
	addSearchPath(SYSCONFDIR);
	addSearchPath("data"s);
	addSearchPath(getenv("HOME") + "/.asteria"s);

	_mode = addMode(make_shared<MyMode>(*this));

	setMode(_mode);
}

void MyApp::Done()
{
	Windows()->Close();
}

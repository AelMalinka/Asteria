/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Camera.hh"

using namespace Entropy::Asteria;
using namespace std;
using namespace Entropy;

using Entropy::Theia::Events::Key;
using Entropy::Theia::Vertex;
using Entropy::Theia::Dimension;

constexpr size_t Camera::_zoom_level;

Camera::Camera(Theia::Camera &camera, const shared_ptr<Character> &player, const shared_ptr<Map> &map)
	: _camera(camera), _player(player), _map(map)
{
	Update();
}

void Camera::Update()
{
	// 2018-01-27 AMR TODO: currently locks character into center unless edge of map
	Dimension w = _map->Width();
	Dimension h = _map->Height();

	Dimension x = _player->Position().x;
	Dimension y = _player->Position().y;

	// 2018-01-27 AMR FIXME:
	static_assert(_zoom_level == 5, "Currently only functions at zoom level 5");
	Dimension magic_width = 30 / 2;
	Dimension magic_height = 18 / 2;

	if(x < magic_width) {
		x = magic_width - 1;
	} else if(x > w - magic_width) {
		x = w - magic_width;
	}

	if(y < magic_height) {
		y = magic_height - 1;
	} else if(y > h - magic_height) {
		y = h - magic_height;
	}

	_camera.setPosition(Vertex(x, y, _zoom_level));
	_camera.setLookAt(Vertex(x, y, 0));
}

void Camera::onEvent(const Key &k)
{
	if(k.Action() == GLFW_PRESS || k.Action() == GLFW_REPEAT) {
		if(k.Code() == GLFW_KEY_LEFT || k.Code() == GLFW_KEY_RIGHT || k.Code() == GLFW_KEY_UP || k.Code() == GLFW_KEY_DOWN) {
			Update();
		}
	}
}

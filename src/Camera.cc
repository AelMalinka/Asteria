/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Camera.hh"

using namespace Entropy::Asteria;
using namespace std;
using namespace Entropy;

using Entropy::Mnemosyne::Events::ModeChange;
using Entropy::Theia::Events::Key;
using Entropy::Theia::Vertex;
using Entropy::Theia::Dimension;

constexpr size_t Camera::_zoom_level;

Camera::Camera(Theia::Camera &camera, const shared_ptr<Character> &player, const shared_ptr<Map> &map)
	: _camera(camera), _player(player), _map(map)
{
	Update();
}

constexpr Dimension Camera::Height() const
{
	// 2018-02-01 AMR TODO: actually calculate these correctly
	return _zoom_level * 4 - 2;
}

constexpr Dimension Camera::Width() const
{
	// 2018-02-01 AMR TODO: actually calculate these correctly
	return _zoom_level * 6;
}

void Camera::Update()
{
	// 2018-01-27 AMR TODO: currently locks character into center unless edge of map
	Dimension w = _map->Width();
	Dimension h = _map->Height();

	Dimension x = _player->Position().x;
	Dimension y = _player->Position().y;

	if(x < Width() / 2) {
		x = Width() / 2 - 1;
	} else if(x > w - Width() / 2) {
		x = w - Width() / 2;
	}

	if(y < Height() / 2) {
		y = Height() / 2 - 1;
	} else if(y > h - Height() / 2) {
		y = h - Height() / 2;
	}

	_camera.setPosition(Vertex(x, y, _zoom_level));
	_camera.setLookAt(Vertex(x, y, 0));
}

void Camera::Update(const chrono::duration<double> &dt)
{
	for(
		auto x = _camera.Position().x - Width() / 2 + 1;
		x < _camera.Position().x + Width() / 2;
		x++
	) {
		for(
			auto y = _camera.Position().y - Height() / 2 + 1;
			y < _camera.Position().y + Height() / 2;
			y++
		) {
			(*_map)[x][y].Update(dt);
		}
	}
}

void Camera::onEvent(const ModeChange &)
{
	Update();
}

void Camera::onEvent(const Key &k)
{
	if(k.Action() == GLFW_PRESS || k.Action() == GLFW_REPEAT) {
		if(k.Code() == GLFW_KEY_LEFT || k.Code() == GLFW_KEY_RIGHT || k.Code() == GLFW_KEY_UP || k.Code() == GLFW_KEY_DOWN) {
			Update();
		}
	}
}

void Camera::UpdateScreen(const Theia::Screen &s)
{
	_map->UpdateScreen(s);
}

void Camera::UpdateCamera(const Theia::Camera &c)
{
	_map->UpdateCamera(c);
}

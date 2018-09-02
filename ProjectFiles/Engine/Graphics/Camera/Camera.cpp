//============================================================================
// # VOYAGER ENGINE #
// Name: Camera.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 2, 2018
// Description: Camera for right-handed OpenGL coordinate system
//============================================================================

#include <Graphics/Camera/Camera.h>
#include <gtx/transform.hpp>

namespace Graphics
{
	Camera::Camera(): _position(1.0f, 0.0f, 0.0f), _view_dir(0.0f, 0.0f, -1.0f), _up(0.0f, 1.0f, 0.0f)
	{

	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return glm::lookAt(_position, _position + _view_dir, _up);
	}

	void Camera::mouseUpdate(const glm::vec2& new_mouse_pos)
	{
		glm::vec2 mouse_delta = new_mouse_pos - _old_mouse_pos;
		if (glm::length(mouse_delta) > 50.0f)
		{
			_old_mouse_pos = new_mouse_pos;
		}
		else
		{
			_view_dir = glm::mat3(glm::rotate(glm::radians(-mouse_delta.x) * 0.5f, _up)) * _view_dir;
			_old_mouse_pos = new_mouse_pos;
		}
	}
}
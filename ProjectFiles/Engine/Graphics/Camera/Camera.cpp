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
	Camera::Camera(): _position(0.0f, 3.0f, 0.0f), _view_dir(0.0f, 0.0f, -1.0f), _up(0.0f, 1.0f, 0.0f)
	{
		_right = glm::cross(_view_dir, _up);
		_movement_speed = 0.1f;
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
			const float ROTATIONAL_SPEED = 0.5f;
			_right = glm::cross(_view_dir, _up);

			glm::mat4 x_y_rotation = glm::rotate(glm::radians(-mouse_delta.x) * ROTATIONAL_SPEED, _up) * 
								glm::rotate(glm::radians(-mouse_delta.y) * ROTATIONAL_SPEED, _right);

			_view_dir = glm::mat3(x_y_rotation) * _view_dir;

			_old_mouse_pos = new_mouse_pos;
		}
	}

	void Camera::moveForward()
	{
		_position += _movement_speed * _view_dir;
	}

	void Camera::moveBackward()
	{
		_position -= _movement_speed * _view_dir;
	}

	void Camera::strafeLeft()
	{
		_position -= _movement_speed * _right;
	}

	void Camera::strafeRight()
	{
		_position += _movement_speed * _right;
	}

	void Camera::moveUp()
	{
		_position += _movement_speed * _up;
	}

	void Camera::moveDown()
	{
		_position -= _movement_speed * _up;
	}
}
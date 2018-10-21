//============================================================================
// # VOYAGER ENGINE #
// Name: Camera.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 2, 2018
// Description: Camera for right-handed OpenGL coordinate system
//============================================================================

#ifndef VE_GRAPHICS_CAMERA_H
#define VE_GRAPHICS_CAMERA_H

#include <glm.hpp>

namespace Graphics
{
	class Camera
	{
	public:
		Camera();

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;
		glm::vec3 getPosition() const;

		void setAspectRatio(const float ratio);

		void mouseUpdate(const glm::vec2& new_mouse_pos);

		void moveForward();
		void moveBackward();
		void strafeLeft();
		void strafeRight();
		void moveUp();
		void moveDown();

	private:
		glm::vec3 _position;
		glm::vec3 _view_dir;
		glm::vec3 _up;
		glm::vec3 _right;

		glm::vec2 _old_mouse_pos;
		float _movement_speed;
		float _aspect_ratio;
	};
}

#endif

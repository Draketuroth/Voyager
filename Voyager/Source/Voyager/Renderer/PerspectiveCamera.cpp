
#include "Voyager/Renderer/PerspectiveCamera.h"
#include "Voyager/Math/Matrix/Matrix3x3.h"
#include "Voyager/Math/Vector/Vector4.h"

#include "Voyager/Math/Utils.h"

#include <iostream>

float yaw = 0.0f;
float pitch = 0.0f;

namespace VE 
{
	namespace Rendering 
	{
		PerspectiveCamera::PerspectiveCamera() :
			_movement_speed(2.0f),
			_aspect_ratio(1.0f),
			_rotation(0.0f),
			_position(0.0f, 0.0f, 15.0f),
			_view_dir(0.0f, 0.0f, -1.0f),
			_right(1.0f, 0.0f, 0.0f),
			_up(0.0f, 1.0f, 0.0f),
			_old_mouse_pos(0.0f, 0.0f),
			_viewMatrix(Math::lookAtRH(_position, _position + _view_dir, _up)),
			_projectionMatrix(Math::perspectiveFovRH(Math::toRadians(90.0f), _aspect_ratio, 0.0f, 100.f)),
			_viewProjectionMatrix(_viewMatrix* _projectionMatrix)
		{

		}

		void PerspectiveCamera::setAspectRatio(const float ratio)
		{
			_aspect_ratio = ratio;
		}

		void PerspectiveCamera::setPosition(const Math::Vector3 position)
		{
			_position = position;
			recalculateViewMatrix();
		}

		void PerspectiveCamera::setRotation(float rotation)
		{
			_rotation = rotation;
			recalculateViewMatrix();
		}

		void PerspectiveCamera::moveForward(const Core::Timestep ts)
		{
			_position += (_movement_speed * ts) * _view_dir;
		}

		void PerspectiveCamera::moveBackward(const Core::Timestep ts)
		{
			_position -= (_movement_speed * ts) * _view_dir;
		}

		void PerspectiveCamera::moveLeft(const Core::Timestep ts)
		{
			_position -= (_movement_speed * ts) * _right;
		}

		void PerspectiveCamera::moveRight(const Core::Timestep ts)
		{
			_position += (_movement_speed * ts) * _right;
		}

		void PerspectiveCamera::moveUp(const Core::Timestep ts)
		{
			_position += (_movement_speed * ts) * _up;
		}

		void PerspectiveCamera::moveDown(const Core::Timestep ts)
		{
			_position -= (_movement_speed * ts) * _up;
		}

		void PerspectiveCamera::rotateCW(const Core::Timestep ts)
		{
			// Empty.
		}

		void PerspectiveCamera::rotateCCW(const Core::Timestep ts)
		{
			// Empty.
		}

		void PerspectiveCamera::update()
		{
			recalculateViewMatrix();
		}

		void PerspectiveCamera::mouseUpdate(const Math::Vector2& new_mouse_pos)
		{
			Math::Vector2 mouse_delta = new_mouse_pos - _old_mouse_pos;
			if (mouse_delta.magnitude() > 50.0f)
			{
				_old_mouse_pos = new_mouse_pos;
			}
			else
			{
				const float ROTATIONAL_SPEED = 0.5f;
				_right = Math::cross(_view_dir, _up);

				_right = Math::Vector::normalize(_right);

				Math::Matrix4x4 x_y_rotation = Math::rotateAxis(Math::toRadians(-mouse_delta.x) * ROTATIONAL_SPEED, _up) *
					Math::rotateAxis(Math::toRadians(-mouse_delta.y) * ROTATIONAL_SPEED, _right);

				_view_dir = _view_dir * VE::Math::Matrix3x3(x_y_rotation.m);

				_old_mouse_pos = new_mouse_pos;

				recalculateViewMatrix();
			}
		}

		const Math::Matrix4x4 PerspectiveCamera::getViewMatrix() const
		{
			return _viewMatrix;
		}

		const  Math::Matrix4x4 PerspectiveCamera::getProjectionMatrix() const
		{
			return _projectionMatrix;
		}

		const  Math::Matrix4x4 PerspectiveCamera::getViewProjectionMatrix() const
		{
			return _viewProjectionMatrix;
		}

		const VE::Math::Vector4 PerspectiveCamera::getDirection() const
		{
			return VE::Math::Vector4(_view_dir.x, _view_dir.y, _view_dir.z);
		}

		const Math::Vector4 PerspectiveCamera::getPosition() const
		{
			return VE::Math::Vector4(_position.x, _position.y, _position.z);
		}

		float PerspectiveCamera::getRotation() const
		{
			return _rotation;
		}

		void PerspectiveCamera::recalculateViewMatrix()
		{
			_viewMatrix = Math::lookAtRH(_position, _position + _view_dir, _up);

			_viewProjectionMatrix = _viewMatrix * _projectionMatrix;
		}
	}
}
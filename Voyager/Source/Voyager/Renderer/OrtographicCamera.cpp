
#include "Voyager/Renderer/OrtographicCamera.h"
#include "Voyager/Math/Utils.h"

#include "Voyager/Core/Log.h"

namespace VE 
{
	namespace Rendering 
	{
		// -1.6f, 1.6f, -0.9f, 0.9f
		OrtographicCamera::OrtographicCamera(float left, float right, float bottom, float top) :
			_movement_speed(2.0f),
			_rotation_speed(4.0f),
			_rotation(0.0f),
			_aspect_ratio(1.0f),
			_position(0.0f, 1.5f, 0.0f),
			_view_dir(0.0f, 0.0f, -1.0f),
			_up(0.0f, 1.0f, 0.0f),
			_right(1.0f, 0.0f, 0.0f),
			_viewMatrix(),
			_projectionMatrix(Math::orthoRH(left, right, bottom, top, -1.0f, 100.0f)),
			_viewProjectionMatrix(_viewMatrix* _projectionMatrix)
		{

		}

		void OrtographicCamera::setAspectRatio(const float ratio)
		{
			_aspect_ratio = ratio;
		}

		void OrtographicCamera::setPosition(const VE::Math::Vector3 position)
		{
			_position = position;
			recalculateViewMatrix();
		}

		void OrtographicCamera::setRotation(float rotation)
		{
			_rotation = rotation;
			recalculateViewMatrix();
		}

		void OrtographicCamera::moveForward(const Core::Timestep ts)
		{
			// Empty due to ortographic projection.
		}

		void OrtographicCamera::moveBackward(const Core::Timestep ts)
		{
			// Empty due to ortographic projection.
		}

		void OrtographicCamera::moveLeft(const Core::Timestep ts)
		{
			_position -= (_movement_speed * ts) * _right;
		}

		void OrtographicCamera::moveRight(const Core::Timestep ts)
		{
			_position += (_movement_speed * ts) * _right;
		}

		void OrtographicCamera::moveUp(const Core::Timestep ts)
		{
			_position += (_movement_speed * ts) * _up;
		}

		void OrtographicCamera::moveDown(const Core::Timestep ts)
		{
			_position -= (_movement_speed * ts) * _up;
		}

		void OrtographicCamera::rotateCW(const Core::Timestep ts)
		{
			_rotation -= _rotation_speed * ts;
		}

		void OrtographicCamera::rotateCCW(const Core::Timestep ts)
		{
			_rotation += _rotation_speed * ts;
		}

		void OrtographicCamera::update()
		{
			recalculateViewMatrix();
		}

		void OrtographicCamera::mouseUpdate(const VE::Math::Vector2& _mouse_pos)
		{
			recalculateViewMatrix();
		}

		const VE::Math::Matrix4D OrtographicCamera::getViewMatrix() const
		{
			return _viewMatrix;
		}
		const VE::Math::Matrix4D OrtographicCamera::getProjectionMatrix() const
		{
			return _projectionMatrix;
		}
		const VE::Math::Matrix4D OrtographicCamera::getViewProjectionMatrix() const
		{
			return _viewProjectionMatrix;
		}
		const VE::Math::Vector4 OrtographicCamera::getDirection() const
		{
			return VE::Math::Vector4(_view_dir.x, _view_dir.y, _view_dir.z);
		}

		const Math::Vector4 OrtographicCamera::getPosition() const
		{
			return VE::Math::Vector4(_position.x, _position.y, _position.z);
		}
		float OrtographicCamera::getRotation() const
		{
			return _rotation;
		}
		void OrtographicCamera::recalculateViewMatrix()
		{
			Math::Matrix4D transform = Math::rotateAxis(Math::toRadians(_rotation), Math::Vector3(0, 0, 1)) * Math::translate(_position);

			if (!Math::inverse(transform.m, _viewMatrix.m))
			{
				VE_CORE_WARN("Matrix not invertible, determinant was zero!");
			}

			_viewProjectionMatrix = _viewMatrix * _projectionMatrix;
		}
	}
}
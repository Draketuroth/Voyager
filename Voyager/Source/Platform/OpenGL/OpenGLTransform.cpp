
#include "Platform/OpenGL/OpenGLTransform.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			void OpenGLTransform::update()
			{
				VE::Math::Matrix4D scale = VE::Math::scale(_scale);
				VE::Math::Matrix4D rotation = VE::Math::rotate(_rotation.yaw, _rotation.pitch, _rotation.roll);
				VE::Math::Matrix4D translation = VE::Math::translate(_position);

				// Translation order: normally you first scale, rotate and finally translate.
				_matrix = scale * rotation * translation;
			}
			Math::Matrix4D OpenGLTransform::getTransformMatrix() const
			{
				return _matrix;
			}
			Math::Vector3 OpenGLTransform::getPosition() const
			{
				return _position;
			}
			Math::Vector3 OpenGLTransform::getScale() const
			{
				return _scale;
			}
			Math::YawPitchRoll OpenGLTransform::getYawPitchRoll() const
			{
				return _rotation;
			}
			void OpenGLTransform::setPosition(Math::Vector3& pos)
			{
				_position = pos;
			}
			void OpenGLTransform::setScale(Math::Vector3& scale)
			{
				_scale = scale;
			}
			void OpenGLTransform::setRotation(Math::YawPitchRoll& rot)
			{
				_rotation = rot;
			}
		}
	}
}
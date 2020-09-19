#ifndef VE_OPENGL_TRANSFORM_H
#define VE_OPENGL_TRANSFORM_H

#include "Voyager/Renderer/Transform.h"
#include "Voyager/Math/Matrix/Matrix4D.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			class OpenGLTransform : public Rendering::Transform
			{
			public:
				OpenGLTransform() : _position(0.0, 0.0, 0.0), _scale(1.0, 1.0, 1.0), _rotation(0.0, 0.0, 0.0) {}
				virtual ~OpenGLTransform() {};

				virtual void update() override;
				virtual Math::Matrix4D getTransformMatrix() const override;

				virtual Math::Vector3D getPosition() const override;
				virtual Math::Vector3D getScale() const override;
				virtual Math::YawPitchRoll getYawPitchRoll() const override;

				virtual void setPosition(Math::Vector3D& pos) override;
				virtual void setScale(Math::Vector3D& scale) override;
				virtual void setRotation(Math::YawPitchRoll& rot) override;

			private:

				Math::Matrix4D _matrix;
				Math::Vector3D _position;
				Math::Vector3D _scale;
				Math::YawPitchRoll _rotation;
			};
		}
	}
}

#endif
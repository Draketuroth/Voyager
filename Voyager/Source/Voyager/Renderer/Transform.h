#ifndef VE_TRANSFORM_H
#define VE_TRANSFORM_H

#include "Voyager/Core/Core.h"
#include "Voyager/Math/Vector/Vector3D.h"
#include "Voyager/Math/Vector/Rotation.h"
#include "Voyager/Math/Matrix/Matrix4D.h"

namespace VE 
{
	namespace Rendering 
	{
		class VOYAGER_API Transform
		{
		public:
			

		public:
			virtual ~Transform() = default;

			virtual void update() = 0;
			virtual Math::Matrix4D getTransformMatrix() const = 0;

			virtual void setPosition(Math::Vector3D& pos) = 0;
			virtual void setScale(Math::Vector3D& scale) = 0;
			virtual void setRotation(Math::YawPitchRoll& rot) = 0;

			virtual Math::Vector3D getPosition() const = 0;
			virtual Math::Vector3D getScale() const = 0;
			virtual Math::YawPitchRoll getYawPitchRoll() const = 0;

			static Transform* create();
		};
	}
}

#endif
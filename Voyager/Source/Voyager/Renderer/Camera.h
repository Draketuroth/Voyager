#ifndef VE_CAMERA_H
#define VE_CAMERA_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Timestep.h"

#include "Voyager/Math/Vector/Vector2.h"
#include "Voyager/Math/Vector/Vector3.h"
#include "Voyager/Math/Matrix/Matrix4x4.h"

namespace VE
{
	namespace Core 
	{
		class VOYAGER_API Camera
		{
		public:
			virtual ~Camera() {}

			// Will trigger recalculate of each corresponding matrix.
			virtual void setAspectRatio(const float ratio) = 0;
			virtual void setPosition(const Math::Vector3 position) = 0;
			virtual void setRotation(float rotation) = 0;

			virtual void moveForward(const Timestep ts) = 0;
			virtual void moveBackward(const Timestep ts) = 0;
			virtual void moveLeft(const Timestep ts) = 0;
			virtual void moveRight(const Timestep ts) = 0;
			virtual void moveUp(const Timestep ts) = 0;
			virtual void moveDown(const Timestep ts) = 0;

			virtual void rotateCW(const Timestep ts) = 0;
			virtual void rotateCCW(const Timestep ts) = 0;

			virtual void update() = 0;
			virtual void mouseUpdate(const Math::Vector2& _mouse_pos) = 0;

			virtual const Math::Matrix4x4 getViewMatrix() const = 0;
			virtual const Math::Matrix4x4 getProjectionMatrix() const = 0;
			virtual const Math::Matrix4x4 getViewProjectionMatrix() const = 0;
			virtual const Math::Vector4 getPosition() const = 0;
			virtual const Math::Vector4 getDirection() const = 0;
			virtual float getRotation() const = 0;
		};
	}
}

#endif

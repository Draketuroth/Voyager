#ifndef VE_COMPONENT_TRANSFORM_H
#define VE_COMPONENT_TRANSFORM_H

#include "Voyager/Core/Core.h"

#include "Voyager/Renderer/Transform.h"

namespace VE
{
	namespace Components 
	{
		struct Transform
		{
			Transform()
			{
				_transform = VE::Rendering::Transform::create();
			}

			VE::Rendering::Transform* getTransform() 
			{
				return _transform;
			}

			void update()
			{
				_transform->update();
			}

			VE::Math::Matrix4D getTransformMatrix() const 
			{
				return _transform->getTransformMatrix();
			}

			VE::Math::Vector3D getPosition() const 
			{
				return _transform->getPosition();
			}

			VE::Math::Vector3D getScale() const 
			{
				return _transform->getScale();
			}

			VE::Math::YawPitchRoll getYawPitchRoll() const
			{
				return _transform->getYawPitchRoll();
			}

			void setPosition(VE::Math::Vector3D& pos) 
			{
				_transform->setPosition(pos);
			}

			void setScale(VE::Math::Vector3D& scale) 
			{
				_transform->setScale(scale);
			}

			void setRotation(VE::Math::YawPitchRoll& rotation) 
			{
				_transform->setRotation(rotation);
			}
			
		private:
			VE::Rendering::Transform* _transform;
		};
	}
}

#endif
#ifndef VE_PERSPECTIVE_CAMERA_H
#define VE_PERSPECTIVE_CAMERA_H

#include "Voyager/Renderer/Camera.h"

#include "Voyager/Math/Vector/Vector2.h"
#include "Voyager/Math/Vector/Vector4.h"

namespace VE 
{
	namespace Rendering 
	{
		class VOYAGER_API PerspectiveCamera : public Core::Camera
		{
		public:
			PerspectiveCamera();
			virtual ~PerspectiveCamera() {}

			virtual void setAspectRatio(const float ratio) override;
			virtual void setPosition(const VE::Math::Vector3) override;
			virtual void setRotation(float rotation) override;

			virtual void moveForward(const Core::Timestep ts) override;
			virtual void moveBackward(const Core::Timestep ts) override;
			virtual void moveLeft(const Core::Timestep ts) override;
			virtual void moveRight(const Core::Timestep ts) override;
			virtual void moveUp(const Core::Timestep ts) override;
			virtual void moveDown(const Core::Timestep ts) override;

			virtual void rotateCW(const Core::Timestep ts) override;
			virtual void rotateCCW(const Core::Timestep ts) override;

			virtual void update() override;
			virtual void mouseUpdate(const VE::Math::Vector2& _mouse_pos) override;

			virtual const VE::Math::Matrix4x4 getViewMatrix() const override;
			virtual const VE::Math::Matrix4x4 getProjectionMatrix() const override;
			virtual const VE::Math::Matrix4x4 getViewProjectionMatrix() const override;
			virtual const VE::Math::Vector4 getDirection() const override;
			virtual const VE::Math::Vector4 getPosition() const override;
			virtual float getRotation() const override;
		private:
			void recalculateViewMatrix();

			float _movement_speed;
			float _aspect_ratio;
			float _rotation;

			VE::Math::Vector3 _position;
			VE::Math::Vector3 _view_dir;
			VE::Math::Vector3 _right;
			VE::Math::Vector3 _up;

			VE::Math::Vector2 _old_mouse_pos;

			VE::Math::Matrix4x4 _viewMatrix;
			VE::Math::Matrix4x4 _projectionMatrix;
			VE::Math::Matrix4x4 _viewProjectionMatrix;
		};
	}
}

#endif

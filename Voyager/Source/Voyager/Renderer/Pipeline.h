#ifndef VE_PIPELINE_H
#define VE_PIPELINE_H

#include "Voyager/Core/Core.h"

#include "Voyager/Math/Matrix/Matrix4x4.h"
#include "Voyager/Math/Vector/Vector4.h"
#include "Voyager/Math/Vector/Vector2.h"

#include "Voyager/Renderer/Shaderset.h"

namespace VE 
{
	namespace Rendering
	{
		class VOYAGER_API Pipeline 
		{
		public:
			virtual ~Pipeline() {}

			virtual bool attachShaderset(unsigned int shadersetId, VE::Rendering::ShaderSet* shaderset) = 0;

			virtual bool createRenderTarget(unsigned int targetId, unsigned int width, unsigned height) = 0;
			virtual void createSharedBuffer(unsigned int bufferId, unsigned int bytes) = 0;
			
			virtual bool registerToBuffer(unsigned int shadersetId, unsigned int bufferId, unsigned int slot) = 0;
			virtual bool updateSharedBuffer(unsigned int bufferId, unsigned int bytes, void* data) = 0;

			virtual bool setActiveShader(unsigned int shadersetId) = 0;
			virtual bool setActiveRenderTarget(unsigned int renderTargetId) = 0;
			virtual bool setColorAttachment(unsigned int renderTargetId) = 0;

			virtual void resetRenderTarget() = 0;

			virtual bool resizeRenderTarget(unsigned int targetId, unsigned int width, unsigned height) = 0;

			virtual void updateConstantMatrix4x4(const std::string& name, const VE::Math::Matrix4x4& value, bool transpose) = 0;
			virtual void updateConstantVector4(const std::string& name, const VE::Math::Vector4& value) = 0;
			virtual void updateConstantVector3(const std::string& name, const VE::Math::Vector3& value) = 0;
			virtual void updateConstantVector2D(const std::string& name, const VE::Math::Vector2& value) = 0;
			virtual void updateConstantInt(const std::string& name, int value) = 0;

			static Pipeline* create();
		};
	}
}

#endif
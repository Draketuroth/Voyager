#ifndef VE_OPENGL_PIPELINE_H
#define VE_OPENGL_PIPELINE_H

#include "Voyager/Renderer/Pipeline.h"

#include "Platform/OpenGL/OpenGLShaderset.h"

#include <string>
#include <unordered_map>

namespace VE
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			class OpenGLPipeline : public Rendering::Pipeline
			{
			public:
				class RenderTarget 
				{
				public:
					RenderTarget() : bufferId(0), colorTextureId(0), depthTextureId(0),  _width(256), _height(256) {}
					unsigned int bufferId;
					unsigned int colorTextureId;
					unsigned int depthTextureId;

					void setWidth(unsigned int width) { _width = width; };
					void setHeight(unsigned int height) { _height = height; };

				private:
					unsigned int _width;
					unsigned int _height;
				};

				OpenGLPipeline();
				virtual ~OpenGLPipeline();

				virtual bool attachShaderset(unsigned int shadersetId, VE::Rendering::ShaderSet* shaderSet) override;

				virtual bool createRenderTarget(unsigned int targetId, unsigned int width, unsigned int height) override;
				virtual void createSharedBuffer(unsigned int bufferId, unsigned int bytes) override;

				virtual bool registerToBuffer(unsigned int shadersetlId, unsigned int bufferId, unsigned int slot) override;
				virtual bool updateSharedBuffer(unsigned int bufferId, unsigned int bytes, void* data) override;

				virtual bool setActiveShader(unsigned int shadersetId) override;
				virtual bool setActiveRenderTarget(unsigned int renderTargetId) override;
				virtual bool setColorAttachment(unsigned int renderTargetId) override;

				virtual void resetRenderTarget() override;

				virtual bool resizeRenderTarget(unsigned int targetId, unsigned int width, unsigned height) override;

				virtual void updateConstantMatrix4D(const std::string& name, const VE::Math::Matrix4D& value, bool transpose) override;
				virtual void updateConstantVector4D(const std::string& name, const VE::Math::Vector4D& value) override;
				virtual void updateConstantVector3D(const std::string& name, const VE::Math::Vector3D& value) override;
				virtual void updateConstantVector2D(const std::string& name, const VE::Math::Vector2D& value) override;
				virtual void updateConstantInt(const std::string& name, int value) override;

			private:
				unsigned int _activeProgram;
				unsigned int _activeTarget;

				std::unordered_map<unsigned int, unsigned int> _ubos;
				std::unordered_map<unsigned int, unsigned int*> _programs;
				std::unordered_map<unsigned int, RenderTarget> _targets;
			};
		}
	}
}

#endif
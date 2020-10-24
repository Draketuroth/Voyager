
#include "Voyager/Renderer/Pipeline.h"
#include "OpenGLPipeline.h"
#include <glad/glad.h>

#include "Voyager/Math/Utils.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			OpenGLPipeline::OpenGLPipeline()
			{

			}
			OpenGLPipeline::~OpenGLPipeline()
			{

			}

			bool OpenGLPipeline::attachShaderset(unsigned int shadersetId, VE::Rendering::ShaderSet* shaderSet)
			{
				auto glShaderSet = static_cast<OpenGLShaderSet*>(shaderSet);
				if (glShaderSet) 
				{
					auto it = _programs.find(shadersetId);
					if (it != _programs.end()) 
					{
						it->second = glShaderSet->addProgramFromShaders();
						return true;
					}
					_programs.insert(std::make_pair(shadersetId, glShaderSet->addProgramFromShaders()));
					return true;
				}
				return false;
			}

			bool OpenGLPipeline::createRenderTarget(unsigned int targetId, unsigned int width, unsigned int height)
			{
				RenderTarget target;
				
				glGenFramebuffers(1, &target.bufferId);
				glBindFramebuffer(GL_FRAMEBUFFER, target.bufferId);

				glGenTextures(1, &target.colorTextureId);
				glBindTexture(GL_TEXTURE_2D, target.colorTextureId);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glBindTexture(GL_TEXTURE_2D, 0);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, target.colorTextureId, 0);

				glGenRenderbuffers(1, &target.depthTextureId);
				glBindRenderbuffer(GL_RENDERBUFFER, target.depthTextureId);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);

				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, target.depthTextureId);

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
				{
					return false;
				}
				glBindFramebuffer(GL_FRAMEBUFFER, 0);

				_targets.insert(std::make_pair(targetId, target));

				return true;
			}

			void OpenGLPipeline::createSharedBuffer(unsigned int bufferId, unsigned int bytes)
			{
				unsigned int ubo;
				glGenBuffers(1, &ubo);
				glBindBuffer(GL_UNIFORM_BUFFER, ubo);
				glBufferData(GL_UNIFORM_BUFFER, bytes, NULL, GL_DYNAMIC_DRAW);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);

				glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, bytes);

				_ubos.insert(std::make_pair(bufferId, ubo));
			}

			bool OpenGLPipeline::registerToBuffer(unsigned int shadersetId, unsigned int bufferId, unsigned int slot)
			{
				auto uboIt = _ubos.find(bufferId);
				auto matIt = _programs.find(shadersetId);
				if (matIt != _programs.end() && uboIt != _ubos.end())
				{
					glBindBufferBase(GL_UNIFORM_BUFFER, slot, uboIt->second);
					return true;
				}
				// Log...
				return false;
			}

			bool OpenGLPipeline::updateSharedBuffer(unsigned int bufferId, unsigned int bytes, void* data)
			{
				auto uboIt = _ubos.find(bufferId);
				if (uboIt != _ubos.end())
				{
					glBindBuffer(GL_UNIFORM_BUFFER, uboIt->second);
					glBufferSubData(GL_UNIFORM_BUFFER, 0, bytes, data);
					glBindBuffer(GL_UNIFORM_BUFFER, 0);
					return true;
				}
				// Log...
				return false;
			}

			bool OpenGLPipeline::setActiveShader(unsigned int shadersetId)
			{
				auto it = _programs.find(shadersetId);
				if (it != _programs.end())
				{
					_activeProgram = *it->second;
					glUseProgram(_activeProgram);
					return true;
				}
				// Log...
				return false;
			}

			bool OpenGLPipeline::setActiveRenderTarget(unsigned int renderTargetId)
			{
				auto it = _targets.find(renderTargetId);
				if (it != _targets.end())
				{
					_activeTarget = it->second.bufferId;
					glBindFramebuffer(GL_FRAMEBUFFER, _activeTarget);
					return true;
				}
				// Log...
				return false;
			}

			bool OpenGLPipeline::setColorAttachment(unsigned int renderTargetId)
			{
				auto it = _targets.find(renderTargetId);
				if (it != _targets.end())
				{
					glBindTexture(GL_TEXTURE_2D, it->second.colorTextureId);
					return true;
				}
				// Log...
				return false;
			}

			void OpenGLPipeline::resetRenderTarget()
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			bool OpenGLPipeline::resizeRenderTarget(unsigned int targetId, unsigned int width, unsigned height)
			{
				auto it = _targets.find(targetId);
				if (it != _targets.end()) 
				{
					glBindFramebuffer(GL_FRAMEBUFFER, it->second.bufferId);

					glBindTexture(GL_TEXTURE_2D, it->second.colorTextureId);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
					glBindTexture(GL_TEXTURE_2D, 0);

					glBindRenderbuffer(GL_RENDERBUFFER, it->second.depthTextureId);
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
					glBindRenderbuffer(GL_RENDERBUFFER, 0);

					glBindFramebuffer(GL_FRAMEBUFFER, 0);
				}
				// Log...
				return false;
			}

			void OpenGLPipeline::updateConstantMatrix4D(const std::string& name, const VE::Math::Matrix4D& value, bool transpose)
			{
				GLint location = glGetUniformLocation(_activeProgram, name.c_str());
				glUniformMatrix4fv(location, 1, GL_FALSE, &value.m[0][0]);
			}

			void OpenGLPipeline::updateConstantVector4(const std::string& name, const VE::Math::Vector4& value)
			{
				GLint location = glGetUniformLocation(_activeProgram, name.c_str());
				glUniform4f(location, value.x, value.y, value.z, value.w);
			}

			void OpenGLPipeline::updateConstantVector3(const std::string& name, const VE::Math::Vector3& value)
			{
				GLint location = glGetUniformLocation(_activeProgram, name.c_str());
				glUniform3f(location, value.x, value.y, value.z);
			}

			void OpenGLPipeline::updateConstantVector2D(const std::string& name, const VE::Math::Vector2& value)
			{
				GLint location = glGetUniformLocation(_activeProgram, name.c_str());
				glUniform2f(location, value.x, value.y);
			}

			void OpenGLPipeline::updateConstantInt(const std::string& name, int value)
			{
				GLint location = glGetUniformLocation(_activeProgram, name.c_str());
				glUniform1i(location, value);
			}
		}
	}
}

#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>

#include "Platform/OpenGL/OpenGLShaderSet.h"
#include "Platform/OpenGL/OpenGLStatus.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			OpenGLShaderSet::OpenGLShaderSet(std::vector<Rendering::Shader*> shaders)
			{
				for (auto shader : shaders)
				{
					VE::Rendering::TypePair tmp(shader->getShaderHandle()._name, shader->getShaderHandle()._type);
					_shaders.emplace(tmp, static_cast<OpenGLShader*>(shader));
				}
			}

			OpenGLShaderSet::~OpenGLShaderSet()
			{

			}

			GLuint* OpenGLShaderSet::addProgramFromShaders()
			{
				std::vector<const VE::Rendering::TypePair*> shaderHandles;

				// Find references to existing shaders and create ones that did not previously exist.
				for (const auto& shader : _shaders)
				{
					shaderHandles.push_back(&shader.first);
				}

				// Make sure the programs comes in a canonical order.
				std::sort(std::begin(shaderHandles), std::end(shaderHandles));
				shaderHandles.erase(std::unique(begin(shaderHandles), end(shaderHandles)), end(shaderHandles));

				// Find the program associated with these shaders, or create.
				auto foundProgram = _programs.emplace(std::vector<const VE::Rendering::TypePair*>(shaderHandles), OpenGLProgramHandle{}).first;
				if (!foundProgram->second._internalID)
				{
					foundProgram->second = OpenGLProgram::initialize();
					for (const VE::Rendering::TypePair* key : shaderHandles)
					{
						glAttachShader(foundProgram->second._internalID, _shaders[*key]->getShaderHandle()._id);
					}
					if (!OpenGLProgram::link(foundProgram->second))
					{
						std::cout << "Program could not be linked" << std::endl;
					}
				}

				return &foundProgram->second._publicID;
			}

			/*
			void OpenGLShaderSet::update(Publisher* pub, void* msg)
			{
				std::string* fileStr = static_cast<std::string*>(msg);

				// Construct key.
				VE::Rendering::TypePair key;
				if (OpenGLShader::getNameTypePair(key, *fileStr))
				{
					// If shader is present in the shaderset, set it as dirty.
					const auto foundShader = _shaders.find(key);
					if (foundShader != _shaders.end())
					{
						_updatedShaders.emplace_back(key);
					}
				}
				else
				{
					std::cout << "GLShaderSet::update could not reconstruct type pair" << std::endl;
				}
			}
			*/

			/*
			void OpenGLShaderSet::updatePrograms(bool& refreshFlag)
			{
				if (_updatedShaders.size() > 0)
				{
					// Recompile all updated shaders.
					for (VE::Rendering::TypePair key : _updatedShaders)
					{
						auto shader = _shaders.at(key);
						OpenGLShaderUtility::compile(shader);
					}

					// Relink all programs that had their shaders updated.
					for (std::pair<const std::vector<const VE::Rendering::TypePair*>, OpenGLProgramHandle>& program : _programs)
					{
						bool programNeedsRelink = false;
						for (const VE::Rendering::TypePair* programShader : program.first)
						{
							for (const VE::Rendering::TypePair key : _updatedShaders)
							{
								if (key._name == programShader->_name && key._type == programShader->_type)
								{
									programNeedsRelink = true;
									break;
								}
							}
							if (programNeedsRelink)
							{
								break;
							}
						}

						// Clear.
						_updatedShaders.clear();

						// Do not attempt to link shaders that did not compile successfully.
						bool canRelink = true;
						if (programNeedsRelink)
						{
							for (const VE::Rendering::TypePair* programShader : program.first)
							{
								if (!OpenGLStatus::status(_shaders[*programShader]._id, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS))
								{
									canRelink = false;
									break;
								}
							}
						}

						if (programNeedsRelink && canRelink)
						{
							OpenGLProgram::link(program.second);
							refreshFlag = true;
						}
					}
				}
			}
			*/
		}
	}
}

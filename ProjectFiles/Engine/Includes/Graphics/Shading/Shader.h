//============================================================================
// # VOYAGER ENGINE #
// Name: Shader.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 30, 2018
// Description: OpenGL shader wrapper.
//============================================================================

#ifndef VE_GRAPHICS_SHADER_H
#define VE_GRAPHICS_SHADER_H

#include <gl/glew.h>
#include <string>

namespace Graphics
{
	class Shader
	{
	public:

		Shader();
		~Shader();

		GLuint getID() const;
		GLenum getType() const;

		bool initialize(const char* file_name, const GLenum type);

	private:
		std::string readShaderCode(const char* file_name);
		bool checkShaderStatus(GLuint shader_id);

		GLuint _id;
		GLenum _type;
	};
}
#endif

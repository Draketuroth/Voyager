//============================================================================
// # VOYAGER ENGINE #
// Name: ShaderProgram.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: OpenGL shader program container.
//============================================================================

#ifndef VE_GRAPHICS_SHADERPROGRAM_H
#define VE_GRAPHICS_SHADERPROGRAM_H

#include <gl/glew.h>
#include <Graphics/Shading/Shader.h>

namespace Graphics
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		bool initialize();
		void initializeUniforms();
		bool shutdown();

		bool link();
		void use();

		GLuint getID() const;
		void setShader(Shader* shader);

		GLuint _mvp_uniform_location;
		GLuint _world_uniform_location;
		GLuint _ambient_uniform_location;
		GLuint _light_uniform_location;
		GLuint _camera_position_uniform_location;

	private:

		bool checkProgramStatus(GLuint program_id);

		Shader* _vertex_shader;
		Shader* _geometry_shader;
		Shader* _fragment_shader;

		GLuint _id;
	};
}

#endif

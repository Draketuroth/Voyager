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
		bool setVertexShader(const std::shared_ptr<Shader> &shader);
		bool setGeometryShader(const std::shared_ptr<Shader> &shader);
		bool setFragmentShader(const std::shared_ptr<Shader> &shader);

		GLuint _mvp_uniform_location;
		GLuint _world_uniform_location;
		GLuint _ambient_uniform_location;
		GLuint _light_uniform_location;
		GLuint _camera_position_uniform_location;
		GLuint _diffuse_color_uniform_location;

	private:

		bool checkProgramStatus(GLuint program_id);

		std::shared_ptr<Shader> _vertex_shader;
		std::shared_ptr<Shader> _geometry_shader;
		std::shared_ptr<Shader> _fragment_shader;

		GLuint _id;
	};
}

#endif

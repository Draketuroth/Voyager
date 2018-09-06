//============================================================================
// # VOYAGER ENGINE #
// Name: GLWindow.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 30, 2018
// Description: Qt-based OpenGL window
//============================================================================

#ifndef VE_GRAPHICS_GLWINDOW_H
#define VE_GRAPHICS_GLWINDOW_H
#include <QtWidgets/qopenglwidget.h>
#include <Graphics/Shading/Shader.h>
#include <Graphics/Camera/Camera.h>


#if defined DLL_EXPORT_GRAPHICS
#define DECLDIR_R __declspec(dllexport)
#else
#define DECLDIR_R __declspec(dllimport)
#endif

namespace Graphics
{
	class DECLDIR_R GLWindow: public QOpenGLWidget
	{
	public:
		GLWindow();
		~GLWindow();

		bool initialize();
		bool shutdown();

		void sendDataToOpenGL();

		void initializeShaders();

		bool checkShaderStatus(GLuint shader_id);
		bool checkProgramStatus(GLuint program_id);
		bool checkStatus(
			GLuint object_id,
			PFNGLGETSHADERIVPROC object_property_getter,
			PFNGLGETSHADERINFOLOGPROC info_log_func,
			GLenum status_type);


	protected:
		void initializeGL();
		void paintGL();
		void mouseMoveEvent(QMouseEvent *e);
		void closeEvent(QCloseEvent *e);
		void keyPressEvent(QKeyEvent *e);
	private:

		// Vertex Array objects.
		GLuint _cube_vao_ID;
		GLuint _cube_normal_vao_ID;

		GLuint _plane_vao_ID;
		GLuint _plane_normal_vao_ID;

		// Buffer byte offset.
		GLuint _cube_index_byte_offset;
		GLuint _cube_normal_byte_offset;

		GLuint _plane_index_byte_offset;
		GLuint _plane_normal_byte_offset;

		// Buffer objects.
		GLuint _buffer_ID;

		// Shader objects.
		Shader _shader;
		GLuint _vertex_shader_ID;
		GLuint _fragment_shader_ID;

		// Shader program objects.
		GLuint _program_ID;

		// Uniform locations.
		GLuint _mvp_uniform_location;
		GLuint _world_uniform_location;
		GLuint _ambient_uniform_location;
		GLuint _light_uniform_location;
		GLuint _camera_position_uniform_location;

		// Indices.
		GLuint _plane_num_indices;
		GLuint _plane_num_normal_indices;

		GLuint _cube_num_indices;
		GLuint _cube_num_normal_indices;

		Camera _camera;
	};
}

#endif

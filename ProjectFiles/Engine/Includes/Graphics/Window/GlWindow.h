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

		GLuint _cube_vao_ID;
		GLuint _arrow_vao_ID;
		GLuint _cube_index_buffer_offset;
		GLuint _arrow_index_buffer_offset;

		GLuint _buffer_ID;

		GLuint _vertex_shader_ID;
		GLuint _fragment_shader_ID;

		GLuint _program_ID;
		Shader _shader;

		GLuint _mvp_uniform_location;

		Camera _camera;
	};
}

#endif

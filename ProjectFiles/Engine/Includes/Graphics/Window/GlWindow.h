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
#include <Graphics/Shading/Shader.h>
#include <Graphics/Shading/ShaderProgram.h>
#include <QtWidgets/qopenglwidget.h>
#include <Graphics/Camera/Camera.h>
#include <Graphics/Rendering/GLRenderer.h>

#if defined DLL_EXPORT_GRAPHICS
#define DECLDIR_R __declspec(dllexport)
#else
#define DECLDIR_R __declspec(dllimport)
#endif

namespace Graphics
{
	struct Model;

	class DECLDIR_R GLWindow: public QOpenGLWidget
	{
	public:
		GLWindow(Model* model);
		~GLWindow();

		bool initialize();
		bool shutdown();

		void sendDataToOpenGL();

		void initializeShaders();

	protected:
		void initializeGL();
		void paintGL();
		void mouseMoveEvent(QMouseEvent *e);
		void closeEvent(QCloseEvent *e);
		void keyPressEvent(QKeyEvent *e);

	private:

		Model* _model;

		// Shader objects.
		Shader* _vertex_shader;
		Shader* _fragment_shader;

		// Shader program objects.
		ShaderProgram* _program;

		GLRenderer* _renderer;

		// Indices.
		GLuint _plane_num_indices;
		GLuint _plane_num_normal_indices;

		GLuint _cube_num_indices;
		GLuint _cube_num_normal_indices;

		Camera _camera;
	};
}

#endif

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
#include <Graphics/Camera/Camera.h>

#include <memory.h>

#if defined DLL_EXPORT
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

namespace Graphics { class ShaderProgram; class IRenderBackend; }

namespace Graphics
{
	struct Model;

	class EXPORT GLWindow: public QOpenGLWidget
	{
	public:
		GLWindow(Model* model);
		~GLWindow();

		void sendDataToOpenGL();

		void initializeShaders();

	protected:
		void initializeGL();
		void paintGL();
		void mouseMoveEvent(QMouseEvent *e);
		void closeEvent(QCloseEvent *e);
		void keyPressEvent(QKeyEvent *e);

	private:

		IRenderBackend* _renderer;

		// Indices.
		GLuint _plane_num_indices;
		GLuint _plane_num_normal_indices;

		GLuint _cube_num_indices;
		GLuint _cube_num_normal_indices;

		Camera _camera;
	};
}

#endif

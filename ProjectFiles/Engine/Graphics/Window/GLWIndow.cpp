//============================================================================
// # VOYAGER ENGINE #
// Name: GLWindow.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 30, 2018
// Description: Qt-based OpenGL window
//============================================================================

#include <gl/glew.h>

#include <Qt3DInput/qmouseevent.h>
#include <Qt3DInput/qkeyevent.h>
#include <QtCore/qdebug.h>

#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

#include <Graphics/GL/glassert.h>
#include <Graphics/Window/GLWindow.h>
#include <Graphics/Primitives/Vertex.h>
#include <Graphics/Primitives/GeometryGenerator.h>
#include <Graphics/Datatypes/Model.h>

#include <Graphics/Interfaces/IRenderBackend.h>

#include <Graphics/Shading/ShaderProgram.h>
#include <Graphics/Shading/Shader.h>

#include <cassert>

using Math::Vector3D;
using glm::vec3;
using glm::vec4;
using glm::mat4;

namespace Graphics
{
	static void infoGL()
	{
		glCheckError();
		const GLubyte *str;
		std::cout << "OpenGL Status" << std::endl;
		str = glGetString(GL_RENDERER);
		std::cout << "Renderer : " << str << std::endl;
		str = glGetString(GL_VENDOR);
		std::cout << "Vendor : " << str << std::endl;
		str = glGetString(GL_VERSION);
		std::cout << "OpenGL Version : " << str << std::endl;
		str = glGetString(GL_SHADING_LANGUAGE_VERSION);
		std::cout << "GLSL Version : " << str << std::endl;
		glCheckError();
	}

	GLWindow::GLWindow(Model* model)
	{
		_renderer = Graphics::CreateGLRenderer();
		_renderer->setModelView(model);
		_renderer->setActiveCamera(&_camera);

		qDebug() << "Created GLWindow";
	}

	GLWindow::~GLWindow()
	{
		qDebug() << "Destroyed GLWindow";
	}

	void GLWindow::sendDataToOpenGL()
	{
		// Generate cube geometry.
		Geometry cube = GeometryGenerator::makeCube();
		Transform cube_1_model_to_world =
		{ 
			-3.0f, 1.0f, -2.0f,
			1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 0.0f
		};
			// glm::translate(vec3(-3.0f, 1.0f, -2.0f)) *
			// glm::rotate(0.0f, vec3(1.0f, 0.0f, 0.0f));
		Geometry cube_normals = GeometryGenerator::generateNormals(cube);

		// Generate plane geometry.
		Geometry plane = GeometryGenerator::makePlane();
		Transform plane_model_to_world = 
		{
			0.5f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 0.0f
		};
			
			//glm::translate(vec3(0.5f, 0.0f, 0.0f));
		Geometry plane_normals = GeometryGenerator::generateNormals(plane);

		_renderer->initialize();

		_renderer->addRenderable(cube, cube_1_model_to_world);
		_renderer->addRenderable(plane, plane_model_to_world);

		cube.release();
		plane.release();
	}

	void GLWindow::initializeShaders()
	{
		std::unique_ptr<Shader> _vertex_shader = std::make_unique<Shader>();
		_vertex_shader->initialize("Shaders\\vertex.glsl", GL_VERTEX_SHADER);

		std::unique_ptr<Shader> _fragment_shader = std::make_unique<Shader>();
		_fragment_shader->initialize("Shaders\\fragment.glsl", GL_FRAGMENT_SHADER);

		std::unique_ptr<ShaderProgram> _program = std::make_unique<ShaderProgram>();
		_program->initialize();
		_program->setVertexShader(std::move(_vertex_shader));
		_program->setFragmentShader(std::move(_fragment_shader));

		// Explicitly bind the vertex attributes.
		// layout(location = N) is not necessary in shader.
		// glBindAttribLocation(_program_ID, 1, "position");

		// Or let the linker handle the binding automatically.
		// layout(location = N) is required in shader.
		_program->link();

		_program->initializeUniforms();

		GLuint _program_ID = _program->getID();

		// If the linker binds the attributes, make sure to query and verify their location!
		GLint position_location = glGetAttribLocation(_program_ID, "vertex_position_model");
		GLint transform_location = glGetAttribLocation(_program_ID, "vertex_normal_model");
		GLint uv_location = glGetAttribLocation(_program_ID, "vertex_uv");

		_program->use();
		_renderer->setProgram(std::move(_program));
	}

	void GLWindow::initializeGL()
	{
		GLenum error_code = glewInit();
		assert(error_code == 0);

		infoGL();

		setMouseTracking(false);

		glEnable(GL_DEPTH_TEST);
		sendDataToOpenGL();
		initializeShaders();
	}

	void GLWindow::paintGL()
	{
		_renderer->updateViewport(width(), height());
		_renderer->updateView();
		_renderer->render();
	}

	void GLWindow::mouseMoveEvent(QMouseEvent* e)
	{
		setFocus();
		_camera.mouseUpdate(glm::vec2(e->x(), e->y()));
		repaint();
	}

	void GLWindow::closeEvent(QCloseEvent *e)
	{
		delete _renderer;
	}

	void GLWindow::keyPressEvent(QKeyEvent *e)
	{
		switch (e->key())
		{
		case Qt::Key::Key_W:
			_camera.moveForward();
			break;
		case Qt::Key::Key_S:
			_camera.moveBackward();
			break;
		case Qt::Key::Key_A:
			_camera.strafeLeft();
			break;
		case Qt::Key::Key_D:
			_camera.strafeRight();
			break;
		case Qt::Key::Key_R:
			_camera.moveUp();
			break;
		case Qt::Key::Key_F:
			_camera.moveDown();
			break;
		}
		repaint();
	}
}
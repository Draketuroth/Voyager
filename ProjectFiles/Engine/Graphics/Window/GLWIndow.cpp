#include <gl/glew.h>
#include <Graphics/GL/glassert.h>
#include <Graphics/Window/GLWindow.h>
#include <QtCore/qdebug.h>

namespace Graphics
{
	const float X_DELTA = 0.1f;
	const uint NUM_VERTICES_PER_TRI = 3;
	const uint NUM_FLOATS_PER_VERTICE = 6;
	const uint TRIANGLE_BYTE_SIZE = NUM_VERTICES_PER_TRI * NUM_FLOATS_PER_VERTICE * sizeof(float);
	const uint MAX_TRIANGLES = 20;

	uint num_tris = 0;

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

	void GLWindow::sendDataToOpenGL()
	{
		
		GLuint vertex_buffer_ID;
		glGenBuffers(1, &vertex_buffer_ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_ID);
		glBufferData(GL_ARRAY_BUFFER, MAX_TRIANGLES * TRIANGLE_BYTE_SIZE, NULL, GL_STATIC_DRAW);

		// Stride is the distance from the beginning of the first attribute to the next occurence of it. 
		// Stride = 0 means that data is tightly packed.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

		GLushort indices[] = { 0, 1, 2,  3, 4, 5 };
		GLuint index_buffer_ID;
		glGenBuffers(1, &index_buffer_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void GLWindow::initializeShaders()
	{
		GLuint vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);	// VSO
		GLuint fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);	// FSO

		const char* adapter[1];
		std::string temp = shader.readShaderCode("Shaders\\vertex.glsl").c_str();
		adapter[0] = temp.c_str();
		glShaderSource(vertex_shader_ID, 1, adapter, 0);
		temp = shader.readShaderCode("Shaders\\fragment.glsl").c_str();
		adapter[0] = temp.c_str();
		glShaderSource(fragment_shader_ID, 1, adapter, 0);

		glCompileShader(vertex_shader_ID);
		glCompileShader(fragment_shader_ID);

		if (!checkShaderStatus(vertex_shader_ID) || !checkShaderStatus(fragment_shader_ID))
		{
			return;
		}

		GLuint program_ID = glCreateProgram();
		glAttachShader(program_ID, vertex_shader_ID);
		glAttachShader(program_ID, fragment_shader_ID);
		glLinkProgram(program_ID);

		if (!checkProgramStatus(program_ID))
		{
			return;
		}

		glUseProgram(program_ID);
	}

	bool GLWindow::checkShaderStatus(GLuint shader_id)
	{
		return checkStatus(shader_id, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
	}

	bool GLWindow::checkProgramStatus(GLuint program_id)
	{
		return checkStatus(program_id, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
	}

	bool GLWindow::checkStatus(
		GLuint object_id,
		PFNGLGETSHADERIVPROC object_property_getter,
		PFNGLGETSHADERINFOLOGPROC info_log_func,
		GLenum status_type)
	{
		// iv = integer vector. We are just passing one.
		GLint status;
		object_property_getter(object_id, status_type, &status);
		if (status != GL_TRUE)
		{
			GLint info_log_length;
			object_property_getter(object_id, GL_INFO_LOG_LENGTH, &info_log_length);
			GLchar* buffer = new GLchar[info_log_length];

			GLsizei buffer_size;
			info_log_func(object_id, info_log_length, &buffer_size, buffer);
			qDebug() << buffer;

			delete[] buffer;
			return false;
		}
		return true;
	}

	void GLWindow::sendAnotherTriangle()
	{
		if (num_tris == MAX_TRIANGLES)
		{
			return;
		}
		const GLfloat THIS_TRI_X = -1 + num_tris * X_DELTA;
		GLfloat this_tri[] = {
			THIS_TRI_X , 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			THIS_TRI_X + X_DELTA , 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			THIS_TRI_X, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
		};
		glBufferSubData(
			GL_ARRAY_BUFFER,
			num_tris * TRIANGLE_BYTE_SIZE,
			TRIANGLE_BYTE_SIZE,
			this_tri);
		num_tris++;
	}

	void GLWindow::initializeGL()
	{
		glewInit();
		glEnable(GL_DEPTH_TEST);
		infoGL();
		sendDataToOpenGL();
		initializeShaders();
	}

	void GLWindow::paintGL()
	{
		glClearColor(0, 0, 0, 1);

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width(), height());
		sendAnotherTriangle();
		glDrawArrays(GL_TRIANGLES, (num_tris - 1) * NUM_VERTICES_PER_TRI, NUM_VERTICES_PER_TRI);
	}
}
//============================================================================
// # VOYAGER ENGINE #
// Name: GLRenderer.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: OpenGL based renderer.
//============================================================================

#ifndef VE_GRAPHICS_GLRENDERER_H
#define VE_GRAPHICS_GLRENDERER_H

#include <gl/glew.h>
#include <QtOpenGL/qgl.h>
#include <QtGui/qopenglvertexarrayobject.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglbuffer.h>

#include <Graphics/Rendering/Geometry.h>
#include <Graphics/Rendering/Renderable.h>
#include <Graphics/Shading/ShaderProgram.h>
#include <Graphics/Camera/Camera.h>

namespace Math { struct Vector3D; }

#if defined DLL_EXPORT_GRAPHICS
#define DECLDIR_R __declspec(dllexport)
#else
#define DECLDIR_R __declspec(dllimport)
#endif

namespace Graphics
{
	struct Model;
	class DECLDIR_R GLRenderer
	{

	public:
		GLRenderer();

		bool initialize();
		bool shutdown();
		void update(float t);
		void render(const Camera camera, Model* model);
		void resize(int width, int height);

		void setProgram(ShaderProgram* program);
		void updateViewport(const int width, const int height);

		Geometry* addGeometry(
			Vertex* vertices, uint num_vertices,
			GLushort* indices, uint num_indices, GLenum render_mode = GL_TRIANGLES);

		void addRenderable(Geometry geometry, glm::mat4 transform);

	private:

		// Helper functions.
		void setupBuffer(GLuint &buffer_id, Geometry g);
		void setupGeometryVAO(GLuint &vao_id, GLuint buffer_id);
		void setupNormalVAO(GLuint &vao_id, GLuint buffer_id);

		// Cache coherent. 
		static const uint NUM_MAX_GEOMETRIES = 10;
		static const uint NUM_MAX_RENDERABLES = 10;
		static const uint MAX_BUFFER_SIZE = 1024;
		static const uint MAX_VERTICES = 10;

		int _width;
		int _height;

		uint _num_geometries;
		uint _num_renderables;

		Geometry _geometries[NUM_MAX_GEOMETRIES];
		Renderable _renderables[NUM_MAX_RENDERABLES];

		ShaderProgram* _program;
	};

}

#endif

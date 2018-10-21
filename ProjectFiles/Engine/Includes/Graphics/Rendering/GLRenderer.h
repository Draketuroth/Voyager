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

#include <Graphics/Interfaces/IRenderBackend.h>

#include <memory.h>

#if defined DLL_EXPORT
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

namespace Math { struct Vector3D; }

namespace Graphics { struct Model; class Camera; class Texture; }

namespace Graphics
{
	class EXPORT GLRenderer : public IRenderBackend
	{

	public:
		GLRenderer();
		~GLRenderer();

		int initialize() override;

		void update(float t) override;
		int render() override;
		void resize(int width, int height) override;

		void setProgram(std::unique_ptr<ShaderProgram> program) override;
		void setModelView(Model* model) override;
		void setActiveCamera(Camera* camera) override;

		void updateViewport(const int width, const int height) override;
		void updateView() override;

		Geometry* addGeometry(
			Vertex* vertices, uint num_vertices,
			ushort* indices, uint num_indices, GLenum render_mode = GL_TRIANGLES);

		void addRenderable(Geometry g, Transform t) override;

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

		glm::mat4 view_to_proj;
		glm::mat4 world_to_view;
		glm::mat4 world_to_proj;

		uint _num_geometries;
		uint _num_renderables;

		Geometry _geometries[NUM_MAX_GEOMETRIES];
		Renderable _renderables[NUM_MAX_RENDERABLES];

		std::shared_ptr<Texture> _texture;
		bool switch_color;

		Camera* _active_camera;
		Model* _model;
		std::unique_ptr<ShaderProgram> _program;
	};

}

#endif

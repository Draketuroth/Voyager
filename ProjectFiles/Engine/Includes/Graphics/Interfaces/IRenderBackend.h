#ifndef IRENDERBACKEND_H
#define IRENDERBACKEND_H

#include <Graphics/Rendering/Geometry.h>
#include <Graphics/Rendering/Renderable.h>
#include <Graphics/Shading/ShaderProgram.h>
#include <Graphics/Datatypes/Transform.h>

namespace Graphics { struct Model; class Camera; }

#if defined DLL_EXPORT
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

namespace Graphics
{
	class EXPORT IRenderBackend
	{
	public:

		virtual ~IRenderBackend() {};

		virtual int initialize() = 0;

		virtual void update(float t) = 0;

		virtual int render() = 0;

		virtual void resize(int width, int height) = 0;

		virtual void setProgram(std::unique_ptr<ShaderProgram> program) = 0;
		virtual void setModelView(Model* model) = 0;
		virtual void setActiveCamera(Camera* camera) = 0;

		virtual void updateViewport(const int width, const int height) = 0;
		virtual void updateView() = 0;

		virtual void addRenderable(Geometry g, Transform t) = 0;

	protected:
		IRenderBackend() {};
		IRenderBackend(const IRenderBackend& copy) = delete;
		IRenderBackend(const IRenderBackend&& copy) = delete;
		IRenderBackend& operator=(const IRenderBackend& rhs) = delete;
	};

	EXPORT IRenderBackend* CreateGLRenderer();
}

#endif

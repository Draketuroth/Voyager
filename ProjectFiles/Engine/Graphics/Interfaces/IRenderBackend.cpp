#include <Graphics/Interfaces/IRenderBackend.h>
#include <Graphics/Rendering/GLRenderer.h>

Graphics::IRenderBackend* Graphics::CreateGLRenderer()
{
	return new GLRenderer;
}

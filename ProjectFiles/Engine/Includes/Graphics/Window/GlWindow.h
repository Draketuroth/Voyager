#ifndef VE_GRAPHICS_GLWINDOW_H
#define VE_GRAPHICS_GLWINDOW_H
#include <QtWidgets/qopenglwidget.h>
#include <Graphics/Shading/Shader.h>

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

		void sendDataToOpenGL();

		void initializeShaders();

		bool checkShaderStatus(GLuint shader_id);
		bool checkProgramStatus(GLuint program_id);
		bool checkStatus(
			GLuint object_id,
			PFNGLGETSHADERIVPROC object_property_getter,
			PFNGLGETSHADERINFOLOGPROC info_log_func,
			GLenum status_type);

		void sendAnotherTriangle();


	protected:
		void initializeGL();
		void paintGL();

	private:
		Shader shader;
	};
}

#endif

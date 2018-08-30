
#include <Graphics/Shading/Shader.h>
#include <fstream>
#include <QtCore/qdebug.h>

namespace Graphics
{
	Shader::Shader()
	{

	}

	Shader::~Shader()
	{

	}

	std::string Shader::readShaderCode(const char* file_name)
	{
		std::ifstream shader_input(file_name);
		if (!shader_input.good())
		{
			qDebug() << "File failed to load..." << file_name;
			exit(1);
		}
		return std::string(
			std::istreambuf_iterator<char>(shader_input),
			std::istreambuf_iterator<char>());
	}

}
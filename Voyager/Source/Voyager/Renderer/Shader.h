#ifndef VE_SHADER_H
#define VE_SHADER_H

#include "Voyager/Core/Core.h"

#include "Voyager/Core/Resource.h"
#include "Voyager/IO/ImportSettings.h"

#include <tuple>
#include <string>

namespace VE 
{
	namespace Rendering
	{
		enum class ShaderType 
		{
			NONE = 0,
			VERTEX,
			GEOMETRY,
			FRAGMENT
		};

		struct TypePair
		{
			TypePair() : _name(""), _type(ShaderType::NONE) {}
			TypePair(const std::string name, ShaderType type) : _name(name), _type(type) {}
			bool operator<(const TypePair& rhs) const
			{
				return std::tie(_name, _type) < std::tie(rhs._name, rhs._type);
			}
			std::string _name;
			ShaderType _type;
		};

		struct ShaderHandle
		{
			ShaderHandle() :
				_name(""),
				_path(""),
				_type(ShaderType::NONE),
				_id(0),
				_hash(0) {}

			std::string _name;
			std::string _path;
			ShaderType _type;

			int32_t _hash;
			unsigned int _id;
		};

		class VOYAGER_API Shader : Core::Resource
		{
		public:
			virtual ~Shader() = default;

			virtual bool status() const = 0;

			virtual ShaderHandle& getShaderHandle() = 0;

			static void createResource(Shader** resource, const std::string path, VE::IO::Setting flags);
			static Shader* create(const std::string& filepath);

			static bool getNameTypePair(TypePair& tp, std::string path);
		};
	}
}

#endif


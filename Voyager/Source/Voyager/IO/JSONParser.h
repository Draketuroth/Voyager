#ifndef VOYAGER_JSONPARSER_H
#define VOYAGER_JSONPARSER_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Log.h"

#include <typeinfo>

#include <fstream>
#include <vector>
#include <map>

namespace VE
{
	namespace IO
	{
		namespace JSON 
		{
			enum JSONParseStrategy 
			{
				STANDARD, COMMENTS
			};

			class JSONValue;

			class VOYAGER_API JSONNode final
			{
			public:
				enum class JSONType : char
				{
					NONE, NUMBER, BOOL, STRING, ARRAY, OBJECT
				};

				// Convenient typedefs for json terminology. 
				typedef std::vector<JSONNode> array;
				typedef std::map<std::string, JSONNode> object;

				JSONNode() noexcept;
				JSONNode(std::nullptr_t) noexcept;

				JSONNode(int value);
				JSONNode(double value);
				JSONNode(bool value);
				JSONNode(const std::string& value);
				JSONNode(std::string&& value);
				JSONNode(const char* value);
				JSONNode(const array& values);
				JSONNode(array&& values);
				JSONNode(const object& values);
				JSONNode(object&& values);

				JSONType getType() const;

				bool isNull() const { return getType() == JSONType::NONE; }
				bool isNumber() const { return getType() == JSONType::NUMBER; }
				bool isBool() const { return getType() == JSONType::BOOL; }
				bool isString() const { return getType() == JSONType::STRING; }
				bool isArray() const { return getType() == JSONType::ARRAY; }
				bool isObject() const { return getType() == JSONType::OBJECT; }

				int asInteger() const;
				double asNumber() const;
				bool asBoolean() const;
				const std::string& asString() const;
				const array& asArray() const;
				const object& asObject() const;


				static JSONNode parse(const std::string& in´, std::string& err, JSONParseStrategy strategy = JSONParseStrategy::STANDARD);
				static JSONNode parse(const char* in, std::string& err, JSONParseStrategy strategy = JSONParseStrategy::STANDARD) 
				{
					if (in) 
					{
						return parse(std::string(in), err, strategy);
					}
					else 
					{
						err = "null input";
						return nullptr;
					}
				}

				// Parse multiple objects, concatenated or seperated by whitespace.
				static std::vector<JSONNode> parseMulti(const std::string& in, std::string::size_type& parserStopPos, std::string& err, JSONParseStrategy strategy = JSONParseStrategy::STANDARD);
				static inline std::vector<JSONNode> parseMulti(const std::string& in, std::string& err, JSONParseStrategy strategy = JSONParseStrategy::STANDARD)
				{
					std::string::size_type parserStopPos;
					return parseMulti(in, parserStopPos, err, strategy);
				}

				const JSONNode& operator[](size_t index) const;
				const JSONNode& operator[](const std::string& key) const;

				bool operator == (const JSONNode& rhs) const;
				bool operator < (const JSONNode& rhs) const;
				bool operator > (const JSONNode& rhs) const { return (rhs < *this); }
				bool operator != (const JSONNode& rhs) const { return !(*this == rhs); }
				bool operator >= (const JSONNode& rhs) const { return !(*this < rhs); }
				bool operator <= (const JSONNode& rhs) const { return !(rhs < *this); }

				private:
					VE::Core::Ref<JSONValue> _ptr;
			};

			// Internal class hierarchy - not exposed to the users of the parser.
			class JSONValue 
			{
			protected:
				friend class JSONNode;
				friend class JSONInt;
				friend class JSONDouble;
				virtual JSONNode::JSONType getType() const = 0;
				virtual bool equals(const JSONValue* other) const = 0;
				virtual bool less(const JSONValue* other) const = 0;

				virtual int asInteger() const;
				virtual double asNumber() const;
				virtual bool asBoolean() const;
				virtual const std::string& asString() const;
				virtual const JSONNode::array& asArray() const;
				virtual const JSONNode::object& asObject() const;

				virtual const JSONNode& operator[](size_t index) const;
				virtual const JSONNode& operator[](const std::string& key) const;

				virtual ~JSONValue() {}
			};
		}
	}
}

#endif
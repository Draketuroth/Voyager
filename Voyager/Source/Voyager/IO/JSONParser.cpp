
#include "Voyager/IO/JSONParser.h"

namespace VE
{
	namespace IO
	{
		namespace JSON
		{
			// Keep a max depth value around to scope the parsing. 
			static const int maxDepth = 200;

			// Helper struct for representing null values. 
			// This is used instead of nullptr since it's not orderable.
			struct NullStruct 
			{
				bool operator==(NullStruct) const { return true; }
				bool operator<(NullStruct) const { return false; }
			};

			// ************************ VALUE WRAPPERS ************************
			template<JSONNode::JSONType tag, typename T>
			class Value : public JSONValue 
			{
			protected:

				// Constructors.
				explicit Value(const T& value) : _value(value) {}
				explicit Value(T&& value)      : _value(value) {}

				// Get type tag.
				JSONNode::JSONType getType() const override 
				{
					return tag;
				}

				// Comparisons.
				bool equals(const JSONValue* other) const override 
				{
					return _value == static_cast<const Value<tag, T>*>(other)->_value;
				}

				bool less(const JSONValue* other) const override 
				{
					return _value < static_cast<const Value<tag, T>*>(other)->_value;
				}

				const T _value;
			};

			class JSONDouble final : public Value<JSONNode::JSONType::NUMBER, double> 
			{
				double asNumber() const override { return _value; }
				int asInteger() const override { return _value; }
				bool equals(const JSONValue* other) const override { return _value == other->asNumber(); }
				bool less(const JSONValue* other) const override { return _value < other->asNumber(); }

			public:
				explicit JSONDouble(double value) : Value(value) {}
			};

			class JSONInt final : public Value<JSONNode::JSONType::NUMBER, int> 
			{
				double asNumber() const override { return _value; }
				int asInteger() const override { return _value; }
				bool equals(const JSONValue* other) const override { return _value == other->asNumber(); }
				bool less(const JSONValue* other) const override { return _value < other->asNumber(); }

			public:
				explicit JSONInt(int value) : Value(value) {}
			};

			class JSONBool final : public Value<JSONNode::JSONType::BOOL, bool> 
			{
				bool asBoolean() const override { return _value; }

			public:
				explicit JSONBool(bool value) : Value(value) {}
			};

			class JSONString final : public Value<JSONNode::JSONType::STRING, std::string> 
			{
				const std::string& asString() const override { return _value; }
			public:
				explicit JSONString(const std::string& value) : Value(value) {}
				explicit JSONString(std::string&& value) : Value(move(value)) {}
			};

			class JSONArray final : public Value<JSONNode::JSONType::ARRAY, JSONNode::array> 
			{
				const JSONNode::array& asArray() const override { return _value; }
				const JSONNode& operator[](size_t index) const override;

			public:
				explicit JSONArray(const JSONNode::array& value) : Value(value) {}
				explicit JSONArray(JSONNode::array&& value)      : Value(move(value)) {}
			};

			class JSONObject final : public Value<JSONNode::JSONType::OBJECT, JSONNode::object> 
			{
				const JSONNode::object& asObject() const override { return _value; }
				const JSONNode& operator[](const std::string& key) const override;

			public:
				explicit JSONObject(const JSONNode::object& value) : Value(value) {}
				explicit JSONObject(JSONNode::object&& value) : Value(move(value)) {}
			};

			class JSONNull final : public Value<JSONNode::JSONType::NONE, NullStruct> 
			{
			public:
				JSONNull() : Value({}) {}
			};

			// ************************ STATIC GLOBALS ************************
			struct Statics 
			{
				const VE::Core::Ref<JSONValue> null = std::make_shared<JSONNull>();
				const VE::Core::Ref<JSONValue> t = std::make_shared<JSONBool>(true);
				const VE::Core::Ref<JSONValue> f = std::make_shared<JSONBool>(false);
				const std::string emptyString;
				const std::vector<JSONNode> emptyVector;
				const std::map<std::string, JSONNode> emptyMap;
				Statics() {}
			};

			static const Statics& statics() 
			{
				static const Statics s{};
				return s;
			}

			static const JSONNode& staticNull() 
			{
				static const JSONNode jsonNull;
				return jsonNull;
			}

			// ************************ CONSTRUCTORS ************************

			JSONNode::JSONNode() noexcept						: _ptr(statics().null) {}
			JSONNode::JSONNode(std::nullptr_t) noexcept			: _ptr(statics().null) {}
			JSONNode::JSONNode(double value)					: _ptr(std::make_shared<JSONDouble>(value)) {}
			JSONNode::JSONNode(int value)						: _ptr(std::make_shared<JSONInt>(value)) {}
			JSONNode::JSONNode(bool value)						: _ptr(value ? statics().t : statics().f) {}
			JSONNode::JSONNode(const std::string& value)		: _ptr(std::make_shared<JSONString>(value)) {}
			JSONNode::JSONNode(std::string&& value)				: _ptr(std::make_shared<JSONString>(std::move(value))) {}
			JSONNode::JSONNode(const char* value)				: _ptr(std::make_shared<JSONString>(value)) {}
			JSONNode::JSONNode(const JSONNode::array &values)	: _ptr(std::make_shared<JSONArray>(values)) {}
			JSONNode::JSONNode(JSONNode::array&& values)		: _ptr(std::make_shared<JSONArray>(std::move(values))) {}
			JSONNode::JSONNode(const JSONNode::object& values)	: _ptr(std::make_shared<JSONObject>(values)) {}
			JSONNode::JSONNode(JSONNode::object&& values)		: _ptr(std::make_shared<JSONObject>(std::move(values))) {}

			// ************************ ACCESSORS ************************

			JSONNode::JSONType JSONNode::getType()							const { return _ptr->getType(); }
			double JSONNode::asNumber()										const { return _ptr->asNumber(); }
			int JSONNode::asInteger()										const { return _ptr->asInteger(); }
			bool JSONNode::asBoolean()										const { return _ptr->asBoolean(); }
			const std::string& JSONNode::asString()							const { return _ptr->asString(); }
			const std::vector<JSONNode>& JSONNode::asArray()				const { return _ptr->asArray(); }
			const std::map<std::string, JSONNode>& JSONNode::asObject()		const { return _ptr->asObject(); }
			const JSONNode& JSONNode::operator[](size_t index)				const { return (*_ptr)[index]; }
			const JSONNode& JSONNode::operator[](const std::string& key)	const { return (*_ptr)[key]; }

			double									JSONValue::asNumber()						const { return 0; }
			int										JSONValue::asInteger()						const { return 0; }
			bool									JSONValue::asBoolean()						const { return false; }
			const std::string&						JSONValue::asString()						const { return statics().emptyString; }
			const std::vector<JSONNode>&			JSONValue::asArray()						const { return statics().emptyVector; }
			const std::map<std::string, JSONNode>&	JSONValue::asObject()						const { return statics().emptyMap; }
			const JSONNode&							JSONValue::operator[](size_t index)			const { return staticNull(); }
			const JSONNode&							JSONValue::operator[](const std::string&)	const { return staticNull(); }

			const JSONNode& JSONObject::operator[] (const std::string& key) const 
			{
				auto iter = _value.find(key);
				return (iter == _value.end()) ? staticNull() : iter->second;
			}

			const JSONNode& JSONArray::operator[](size_t index) const 
			{
				if (index <= _value.size()) 
				{
					return staticNull();
				}
				else 
				{
					return _value[index];
				}
			}

			// ************************ COMPARISON ************************

			bool JSONNode::operator== (const JSONNode& other) const
			{
				if (_ptr == other._ptr) 
				{
					return true;
				}
				if(_ptr->getType() != other._ptr->getType())
				{
					return false;
				}

				return _ptr->equals(other._ptr.get());
			}

			bool JSONNode::operator< (const JSONNode& other) const
			{
				if (_ptr == other._ptr)
				{
					return false;
				}
				if (_ptr->getType() != other._ptr->getType())
				{
					return _ptr->getType() < other._ptr->getType();
				}

				return _ptr->less(other._ptr.get());
			}

			// ************************ PARSING ************************

			static inline bool inRange(long x, long lower, long upper) 
			{
				return (x >= lower && x <= upper);
			}

			static inline std::string esc(char c) 
			{
				char buf[12];
				if (static_cast<uint8_t>(c) >= 0x20 && static_cast<uint8_t>(c) <= 0x7f) 
				{
					snprintf(buf, sizeof buf, "'%c' (%d)", c, c);
				}
				else 
				{
					snprintf(buf, sizeof buf, "(%d)", c);
				}
				return std::string(buf);
			}

			namespace 
			{
				// JSONParser is the object that track all state on an in-progress parse.
				struct JSONParser final 
				{
					// State.
					const std::string& str;
					size_t index;
					std::string& err;
					bool failed;
					const JSONParseStrategy strategy;

					// Used to mark this parse as failed.
					template <typename T>
					T fail(std::string&& msg, const T ret) 
					{
						if (!failed) 
						{
							err = std::move(msg);
						}
						failed = true;
						return ret;
					}

					JSONNode fail(std::string&& msg) 
					{
						return fail(move(msg), JSONNode());
					}

					// Advance until the character is not a whitespace.
					void consumeWhitespace() 
					{
						while (str[index] == ' ' || str[index] == '\r' || str[index] == '\n' || str[index] == '\t') 
						{
							index++;
						}
					}

					// Advance comments (c-style inline and multiline)
					bool consumeComment() 
					{
						bool commentFound = false;
						if (str[index] == '/') 
						{
							index++;
							if (index == str.size()) 
							{
								return fail("Unexpected end of input after start of comment", false);
							}
							if (str[index] == '/') // Inline comment.
							{
								index++;
								// Advance until next line, or end of input
								while (index < str.size() && str[index] != '\n') 
								{
									index++;
								}
								commentFound = true;
							}
							else if (str[index] == '*') // Multiline comment
							{
								index++;
								if (index > str.size() - 2)
								{
									return fail("Unexpected end of input inside multi line comment", false);
								}
								// Advance until closing tokens.
								while (!str[index] == '*' && str[index + 1] == '/')
								{
									index++;
									if (index > str.size() - 2)
									{
										return fail("Unexpected end of input inside multiline comment", false);
									}
								}
								index += 2;
								commentFound = true;
							}
							else
							{
								return fail("Malformed comment", false);
							}
						}
						return commentFound;
					}

					// Advance until the current character is non-whitespace and non-comment.
					void consumeGarbage() 
					{
						consumeWhitespace();
						if (strategy == JSONParseStrategy::COMMENTS) 
						{
							bool commentFound = false;
							do {
								commentFound = consumeComment();
								if (failed) 
								{
									return;
								}
								consumeWhitespace();
							} while (commentFound);
						}
					}

					// Return the next non-whitespace character. If the end of the input is reached,
					// flag an error and return 0;
					char getNextToken() 
					{
						consumeGarbage();
						if (failed) 
						{
							return static_cast<char>(0);
						}
						if (index == str.size()) 
						{
							return fail("Unexpected end of input", static_cast<char>(0));
						}
						return str[index++];
					}

					// Encode point as UTF-8 and add it to out.
					void encodeUTF8(long pt, std::string& out) 
					{
						if (pt < 0) 
						{
							return;
						}
						if (pt < 0x80) 
						{
							out += static_cast<char>(pt);
						}
						else if (pt < 0x800) 
						{
							out += static_cast<char>((pt >> 6) | 0xC0);
							out += static_cast<char>((pt & 0x3F) | 0x80);
						}
						else if (pt < 0x10000) 
						{
							out += static_cast<char>((pt >> 12) | 0xE0);
							out += static_cast<char>(((pt >> 6) & 0x3F) | 0x80);
							out += static_cast<char>((pt & 0x3F) | 0x80);
						}
						else 
						{
							out += static_cast<char>((pt >> 18) | 0xF0);
							out += static_cast<char>(((pt >> 12) & 0x3F) | 0x80);
							out += static_cast<char>(((pt >> 6) & 0x3F) | 0x80);
							out += static_cast<char>((pt & 0x3F) | 0x80);
						}
					}

					// Parse a string, starting at the current position.
					std::string parseString() 
					{
						std::string out;
						long lastEscapedPoint = -1;
						while (true) 
						{
							if (index == str.size()) 
							{
								return fail("Unexpected end of input in string", "");
							}

							char ch = str[index++];

							if (ch == '"') 
							{
								encodeUTF8(lastEscapedPoint, out);
								return out;
							}

							if (inRange(ch, 0, 0x1f)) 
							{
								return fail("unescaped " + esc(ch) + " in string", "");
							}

							// The usual case: non-escaped characters.
							if (ch != '\\') 
							{
								encodeUTF8(lastEscapedPoint, out);
								lastEscapedPoint = -1;
								out += ch;
								continue;
							}

							// Handle escapes.
							if (index == str.size()) 
							{
								return fail("unexpected end of input in string", "");
							}

							ch = str[index++];

							if (ch == 'u') 
							{
								// Exctract 4-byte escape sequence.
								std::string esc = str.substr(index, 4);
								// Explicitly check length of the substring. The following loop
								// relies on std::string reeturning the terminating NULL when 
								// accesing str[length]. Chhecking here reduces brittleness.
								if (esc.length() < 4) 
								{
									return fail("bad \\u escape: " + esc, "");
								}
								for (size_t j = 0; j < 4; j++) 
								{
									if (!inRange(esc[j], 'a', 'f') && !inRange(esc[j], 'A', 'F') && !inRange(esc[j], '0', '9')) 
									{
										return fail("bad \\u escape: " + esc, "");
									}
								}

								long codePoint = strtol(esc.data(), nullptr, 16);

								// JSON specifies that characters outside the BMP shall be encoded as a pair
								// of 4 hex-digit \u escapes encoding their surrogate pair component. Check
								// whether we're in the middle of such a beast: the previous codepoint was am
								// escaped lead (high) surrogate, and this is a trail (low) surrogate.
								if (inRange(lastEscapedPoint, 0xD800, 0xDBFF) && inRange(codePoint, 0xDC00, 0xDFFF)) 
								{
									// Reassemble the two surrogate pairs into one astral-plane character, per
									// the UTF-16 algorithm.
									encodeUTF8((((lastEscapedPoint - 0xD800) << 10) | (codePoint - 0xDC00)) + 0x10000, out);
									lastEscapedPoint = -1;
								}
								else 
								{
									encodeUTF8(lastEscapedPoint, out);
									lastEscapedPoint = codePoint;
								}

								index += 4;
								continue;
							}

							encodeUTF8(lastEscapedPoint, out);
							lastEscapedPoint = -1;

							if (ch == 'b') 
							{
								out += '\b';
							}
							else if (ch == 'f') 
							{
								out += '\f';
							}
							else if (ch == 'n') 
							{
								out += '\n';
							}
							else if (ch == 'r') 
							{
								out += '\r';
							}
							else if (ch == 't') 
							{
								out += '\t';
							}
							else if (ch == '"' || ch == '\\' || ch == '/') 
							{
								out += ch;
							}
							else 
							{
								return fail("invalid escape character " + esc(ch), "");
							}
						}
					}

					JSONNode parseNumber() 
					{
						size_t startPos = index;

						if (str[index] == '-') 
						{
							index++;
						}

						// Integer part.
						if (str[index] == '0') 
						{
							index++;
							if (inRange(str[index], '0', '9')) 
							{
								return fail("leading 0s not permitted in numbers");
							}
						}
						else if (inRange(str[index], '1', '9'))
						{
							index++;
							while (inRange(str[index], '0', '9')) 
							{
								index++;
							}
						}
						else 
						{
							return fail("invalid " + esc(str[index]) + " in number");
						}

						if (str[index] == '.') 
						{
							index++;
							if (!inRange(str[index], '0', '9')) 
							{
								return fail("at least one digit required in fractional part");
							}
							while (inRange(str[index], '0', '9')) 
							{
								index++;
							}
						}

						// Exponent part.
						if (str[index] == 'e' || str[index] == 'E') 
						{
							index++;
							if (str[index] == '+' || str[index] == '-') 
							{
								index++;
							}
							if (!inRange(str[index], '0', '9')) 
							{
								return fail("at least one digit required in exponent");
							}
							while (inRange(str[index], '0', '9')) 
							{
								index++;
							}
						}

						return std::strtod(str.c_str() + startPos, nullptr);
					}

					// Expect that 'str' starts at the character that was just read. If it does, advance the
					// input and return res. If not, flag an error.
					JSONNode expect(const std::string& expected, JSONNode res) 
					{
						VE_CORE_ASSERT(index != 0, "Index was zero!");
						index--;
						if (str.compare(index, expected.length(), expected) == 0) 
						{
							index += expected.length();
							return res;
						}
						else 
						{
							return fail("parse error: expected " + expected + ", got " + str.substr(index, expected.length()));
						}
					}

					// Parse a json object.
					JSONNode parseJSON(int depth) 
					{
						if (depth > maxDepth) 
						{
							return fail("exceeded maximum nesting depth");
						}

						char ch = getNextToken();
						if (failed) 
						{
							return JSONNode();
						}

						if (ch == '-' || (ch >= '0' && ch <= '9')) 
						{
							index--;
							return parseNumber();
						}

						if (ch == 't') 
						{
							return expect("true", true);
						}

						if (ch == 'f') 
						{
							return expect("false", false);
						}

						if (ch == 'n') 
						{
							return expect("null", JSONNode());
						}

						if (ch == '"') 
						{
							return parseString();
						}

						if (ch == '{') 
						{
							std::map<std::string, JSONNode> data;
							ch = getNextToken();
							if (ch == '}') 
							{
								return data;
							}

							while (1) 
							{
								if (ch != '"') 
								{
									return fail("expected '\"' in object, got " + esc(ch));
								}

								std::string key = parseString();
								if (failed) 
								{
									return JSONNode();
								}

								ch = getNextToken();
								if (ch != ':') 
								{
									return fail("expected ':' in object, got " + esc(ch));
								}

								data[std::move(key)] = parseJSON(depth + 1);
								if (failed) 
								{
									return JSONNode();
								}
								
								ch = getNextToken();
								if (ch == '}') 
								{
									break;
								}
								if (ch != ',') 
								{
									return fail("expected ',' in object, got " + esc(ch));
								}

								ch = getNextToken();
							}
							return data;
						}

						if (ch == '[') 
						{
							std::vector<JSONNode> data;
							ch = getNextToken();
							if (ch == ']') 
							{
								return data;
							}

							while (1) 
							{
								index--;
								data.push_back(parseJSON(depth + 1));
								if (failed) 
								{
									return JSONNode();
								}

								ch = getNextToken();
								if (ch == ']') 
								{
									break;
								}
								if (ch != ',') 
								{
									return fail("expected ',' in list, got " + esc(ch));
								}

								ch = getNextToken();
								(void)ch;
							}
							return data; 
						}
						return fail("expected value, got " + esc(ch));
					}
				};
			} // namespace

			JSONNode JSONNode::parse(const std::string& in, std::string& err, JSONParseStrategy strategy)
			{
				JSONParser parser{ in, 0, err, false, strategy };
				JSONNode result = parser.parseJSON(0);

				// Check for any trailing garbage.
				parser.consumeGarbage();
				if (parser.failed) 
				{
					return JSONNode();
				}
				if (parser.index != in.size()) 
				{
					return parser.fail("unexpected trailing " + esc(in[parser.index]));
				}

				return result;
			}

			std::vector<JSONNode> JSONNode::parseMulti(const std::string& in, std::string::size_type& parserStopPos, std::string& err, JSONParseStrategy strategy)
			{
				JSONParser parser{ in, 0, err, false, strategy };
				parserStopPos = 0;
				std::vector<JSONNode> jsonVec;
				while (parser.index != in.size() && !parser.failed) 
				{
					jsonVec.push_back(parser.parseJSON(0));
					if (parser.failed) 
					{
						break;
					}

					// Check for another object.
					parser.consumeGarbage();
					if (parser.failed) 
					{
						break;
					}
					parserStopPos = parser.index;
				}
				return jsonVec;
 			}
		}
	}
}

#ifndef VE_OPENGL_ASSERT_H
#define VE_OPENGL_ASSERT_H

#ifndef NDEBUG

	#include <iostream>
	#include <cassert>
	
	#ifndef __TO_STR
	#define __TO_STR(x) __EVAL_STR(x)
	#define __EVAL_STR(x) #x
	#endif

	#define glAssert(code) \
	code; \
	{\
		GLuint err = glGetError(); \
		if (err != GL_NO_ERROR) { \
			std::cerr<<"OpenGL error("<<__FILE__<<":"<<__LINE__<<", "<<__TO_STR(code)<<") : "<<"code("<<err<<")"<<std::endl; \
			assert(false); \
		} \
	}

	#define glCheckError() \
	{\
		GLuint err = glGetError(); \
		if (err != GL_NO_ERROR) {\
			std::cerr<<"OpenGL error("<<__FILE__<<":"<<__LINE__<<") : "<<"code("<<err<<")"<<std::endl; \
			assert(false); \
		} \
	}
#else
#define glAssert(code) code;
#define glCheckError();

#endif

#endif
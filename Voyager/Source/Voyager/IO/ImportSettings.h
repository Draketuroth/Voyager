#ifndef VE_IMPORTSETTINGS_H
#define VE_IMPORTSETTINGS_H

namespace VE 
{
	namespace IO 
	{
		enum Setting : char {
			None = 0,
			FlipTexture = 1 << 0, // 00001 == 1
		};
	}
}

#endif
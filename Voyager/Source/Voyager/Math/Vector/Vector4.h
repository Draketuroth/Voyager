#ifndef VE_MATH_VECTOR_4_H
#define VE_MATH_VECTOR_4_H

#include "Voyager/Math/Vector/Base.h"
#include "Voyager/Math/Vector/VectorLayout.h"

namespace VE
{
	namespace Math
	{
		struct Vector4 : public Vector::Base<Vector::LayoutXYZW>
		{
			inline explicit Vector4(float xIn = 0.0f, float yIn = 0.0f, float zIn = 0.0f, float wIn = 1.0f) 
			{
				x = xIn;
				y = yIn;
				z = zIn;
				w = wIn;
			}

			inline Vector4(const Vector::Base<Vector::LayoutXYZW>& other);
		};

		inline Vector4 splatX(const Vector4& in);
		inline Vector4 splatY(const Vector4& in);
		inline Vector4 splatZ(const Vector4& in);
		inline Vector4 mergeXY(const Vector4& a, const Vector4& b);
		inline Vector4 mergeZW(const Vector4& a, const Vector4& b);

#include "Voyager/Math/Vector/Vector4.inl"
	}
}

#endif
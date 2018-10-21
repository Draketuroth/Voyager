#ifndef TRANSFORM_H
#define TRANSFORM_H

namespace Graphics
{
	struct Transform
	{
		float p[3] = { 0.0f, 0.0f, 0.0f };
		float s[3] = { 1.0f, 1.0f, 1.0f };
		float r[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
	};
}

#endif


float lerp(float min, float max, float factor)
{
	return (min + factor * (max - min));
}

float clamp(float value, float lower, float upper)
{
	return std::max(lower, std::min(value, upper));
}
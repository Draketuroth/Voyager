
float lerp(float min, float max, float factor)
{
	return (min + factor * (max - min));
}

float clamp(float value, float lower, float upper)
{
	return std::max(lower, std::min(value, upper));
}

float toRadians(float angleDegrees)
{
	return angleDegrees * (PI / 180.0);
}

float toDegrees(float angleRadians)
{
	return angleRadians * (180.0 / PI);
}
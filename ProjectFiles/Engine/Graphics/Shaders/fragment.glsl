#version 420

out vec4 final_color;

in vec3 normal;
in vec3 position;

uniform vec3 light_position;

void main()
{
	vec3 light_vector = normalize(light_position - position);
	float brightness = dot(light_vector, normal);
	final_color = vec4(brightness, brightness, brightness, 1.0f);
}

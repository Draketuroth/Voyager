#version 420

out vec4 final_color;

in vec3 world_normal;
in vec3 world_position;

uniform vec3 light_position_world;
uniform vec4 ambient_light;
uniform vec3 eye_position_world;

void main()
{
	// Diffuse lighting.
	vec3 light_vector_world = normalize(light_position_world - world_position);
	float brightness = dot(light_vector_world, normalize(world_normal));
	vec4 diffuse_light = vec4(brightness, brightness, brightness, 1.0f);

	// Specular lighting.
	vec3 reflected_light_vector = reflect(-light_vector_world, world_normal);
	vec3 eye_vector_world = normalize(eye_position_world - world_position);
	float specularity = dot(reflected_light_vector, eye_vector_world);
	specularity = pow(specularity, 50);
	vec4 specular_light = vec4(specularity, specularity, specularity, 1.0f);

	final_color = ambient_light + clamp(diffuse_light, 0, 1) + clamp(specular_light, 0, 1);
}

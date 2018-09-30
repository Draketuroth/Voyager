#version 420

out vec4 final_color;

in vec3 surface_position_world;
in vec3 surface_normal_world;
in vec2 uv;

uniform vec3 light_position_world;
uniform vec4 ambient_light;
uniform vec3 eye_position_world;
uniform vec3 diffuse_color;

uniform sampler2D surface_texture;

void main()
{
	vec4 surface_color = texture(surface_texture, uv);

	float light_radius = 2.0f;
	float threshold = 0.1f;

	vec3 light_vector_world = light_position_world - surface_position_world;
	float distance_to_light = length(light_vector_world);
	float d = max(distance_to_light - light_radius, 0);
	vec3 light_vector_world_normalized = normalize(light_vector_world);

	float denominator = d / light_radius + 1;
	float attenuation = 1 / (denominator * denominator);

	attenuation = (attenuation - threshold) / (1 - threshold);
	attenuation = max(attenuation, 0);

	vec3 surface_normal_vector_normalized = normalize(surface_normal_world);

	// Diffuse lighting.
	float diffuse_coefficient = max(dot(light_vector_world_normalized, surface_normal_vector_normalized), 0);
	vec3 diffuse_light = vec3(1.0f, 1.0f, 1.0f) * diffuse_coefficient * attenuation;

	// Specular lighting.
	vec3 reflected_light_vector = reflect(-light_vector_world_normalized, surface_normal_vector_normalized);
	vec3 eye_vector_world = normalize(eye_position_world - surface_position_world);
	float specularity_coefficient = clamp(dot(reflected_light_vector, eye_vector_world), 0, 1);
	specularity_coefficient = pow(specularity_coefficient, 50);
	vec3 specular_light = vec3(1.0f, 1.0f, 1.0f) * specularity_coefficient * attenuation;

	final_color = (ambient_light + vec4(diffuse_light, 1.0f) + vec4(specular_light, 1.0f)) * diffuse_color;
	// final_color = surface_color;
}

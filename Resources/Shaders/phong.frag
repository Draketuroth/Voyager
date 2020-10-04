#version 460

out layout(location = 0) vec4 final_color;

layout(std140, binding = 0) uniform SceneData
{
    vec4 camera_position_world;
	vec4 camera_center_world;
	mat4 camera_view;
	mat4 camera_projection;
	mat4 camera_view_projection;
};

layout(std140, binding = 1) uniform DisplayData
{
    vec2 resolution;
};

layout(std140, binding = 2) uniform TimeData
{
    float timeSec;
};

uniform int wireframe;

in vec3 surface_position_world;
in vec3 surface_normal_world;
in vec3 surface_barycentric;
in vec2 uv;

uniform sampler2D surface_texture;

float edgeFactor(vec3 vBC){
    vec3 d = fwidth(vBC);
    vec3 a3 = smoothstep(vec3(0.0), d*1.5, vBC);
    return min(min(a3.x, a3.y), a3.z);
}

void main()
{
    vec4 ambient_light = vec4(0.1f, 0.1f, 0.1f, 0.1f);
	vec4 diffuse_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec3 light_position_world = vec3(-3.0f, 3.0f, 0.0f);
	
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
	vec3 camera_vector_world = normalize(vec3(camera_position_world.xy, 1.0f) - surface_position_world);
	float specularity_coefficient = clamp(dot(reflected_light_vector, camera_vector_world), 0, 1);
	specularity_coefficient = pow(specularity_coefficient, 50);
	vec3 specular_light = vec3(1.0f, 1.0f, 1.0f) * specularity_coefficient * attenuation;

	final_color = (ambient_light + vec4(diffuse_light, 1.0f) + vec4(specular_light, 1.0f)) * surface_color;
	
	if(wireframe == 1)
	{
		final_color.rgb = mix(vec3(0.0), final_color.rgb, edgeFactor(surface_barycentric));
	}
}

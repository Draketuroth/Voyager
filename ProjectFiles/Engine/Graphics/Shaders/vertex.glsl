#version 420

in layout(location = 0) vec4 vertex_position_model;
in layout(location = 1) vec3 vertex_normal_model;
in layout(location = 2) vec2 vertex_uv;

uniform mat4 model_to_projection_matrix;
uniform mat4 model_to_world_matrix;

out vec3 surface_position_world;
out vec3 surface_normal_world;
out vec2 uv;

void main()
{
	gl_Position = model_to_projection_matrix * vertex_position_model;
	
	surface_position_world = vec3(model_to_world_matrix * vertex_position_model);
	surface_normal_world = mat3(model_to_world_matrix) * vertex_normal_model;

	uv = vertex_uv;
}

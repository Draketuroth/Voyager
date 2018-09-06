#version 420

in layout(location = 0) vec4 vertex_position_model;
in layout(location = 1) vec3 vertex_color;
in layout(location = 2) vec3 vertex_normal_model;

uniform mat4 model_to_projection_matrix;
uniform mat4 model_to_world_matrix;

out vec3 world_normal;
out vec3 world_position;

void main()
{
	gl_Position = model_to_projection_matrix * vertex_position_model;
	
	world_normal = mat3(model_to_world_matrix) * vertex_normal_model;
	world_position = vec3(model_to_world_matrix * vertex_position_model);
}

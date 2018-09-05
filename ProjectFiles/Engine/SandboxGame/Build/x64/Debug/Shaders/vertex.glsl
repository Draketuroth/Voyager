#version 420

in layout(location = 0) vec3 vertex_position;
in layout(location = 1) vec3 vertex_color;
in layout(location = 2) vec3 vertex_normal;

uniform vec3 ambient_light;

uniform mat4 mvp_matrix;
uniform mat4 world_matrix;

out vec3 normal;
out vec3 position;

void main()
{
	vec4 v = vec4(vertex_position, 1.0f);
	gl_Position = mvp_matrix * v;
	
	normal = mat3(world_matrix) * vertex_normal;
	position = vec3(world_matrix * v);
}

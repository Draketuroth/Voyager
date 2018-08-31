#version 420

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 vertex_color;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

out vec3 color;

void main()
{
	vec4 v = vec4(position, 1.0f);
	vec4 new_pos = model_matrix * v;
	vec4 projected_pos = projection_matrix * new_pos;
	gl_Position = projected_pos;

	color = vertex_color;
}

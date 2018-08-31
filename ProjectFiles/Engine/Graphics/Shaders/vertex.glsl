#version 420

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 vertex_color;

uniform mat4 mvp_matrix;

out vec3 color;

void main()
{
	vec4 v = vec4(position, 1.0f);
	gl_Position = mvp_matrix * v;

	color = vertex_color;
}

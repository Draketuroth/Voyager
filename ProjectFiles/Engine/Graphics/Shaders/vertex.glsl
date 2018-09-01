#version 420

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 vertex_color;
in layout(location = 2) mat4 transform;

out vec3 color;

void main()
{
	vec4 v = vec4(position, 1.0f);
	gl_Position = transform * v;

	color = vertex_color;
}

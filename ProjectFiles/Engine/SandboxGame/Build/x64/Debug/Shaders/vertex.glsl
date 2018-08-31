#version 420

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 vertex_color;

uniform vec3 main_color;
uniform float y_flip;

out vec3 color;

void main()
{
	gl_Position = vec4(position, 1.0f);
	gl_Position.y = gl_Position.y * y_flip;
	color = main_color;
}

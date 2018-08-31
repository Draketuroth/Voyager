#version 420

out vec4 final_color;
in vec3 color;

void main()
{
	final_color = vec4(color, 1.0f);
}

#version 460

in layout(location=0) vec3 vertex_position;
in layout(location=1) vec3 vertex_normal;
in layout(location=2) vec3 vertex_barycentric;
in layout(location=3) vec2 vertex_texcoord;

layout(std140, binding = 0) uniform SceneData
{
    vec4 camera_position_world;
	vec4 camera_center_world;
	mat4 camera_view;
	mat4 camera_projection;
	mat4 camera_view_projection;
};

uniform mat4 model_to_world;

out vec3 surface_position_world;
out vec3 surface_normal_world;
out vec3 surface_barycentric;
out vec2 uv;

void main()
{
	gl_Position = camera_view_projection * model_to_world * vec4(vertex_position, 1.0);	
	
	surface_position_world = vec3(model_to_world * vec4(vertex_position, 1.0));
	surface_normal_world = mat3(model_to_world) * vertex_normal;
	
	surface_barycentric = vertex_barycentric;

	uv = vertex_texcoord;
}
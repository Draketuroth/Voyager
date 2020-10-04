#version 460

out layout(location = 0) vec4 color;

layout(std140, binding = 1) uniform DisplayData
{
    vec2 resolution;
};

layout(std140, binding = 2) uniform TimeData
{
    float timeSec;
};

in vec2 uv;

vec3 palette(in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d)
{
  return a + b * cos(6.28318 * (c * t + d));
}

void main()
{
  vec2 position = gl_FragCoord.xy / resolution.xy;
  vec3 col = palette(position.y, vec3(0.82, 0.25, 0.36), vec3(0.39, 0.1, 0.12), vec3(0.37, 0.22, 0.36), vec3(0.22, 0.09, 0.63));
  color = vec4( col, 1.0 );
}
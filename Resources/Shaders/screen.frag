#version 460

out vec4 FragColor;

layout(std140, binding = 1) uniform DisplayData
{
    vec2 resolution;
};

layout(std140, binding = 2) uniform TimeData
{
    float timeSec;
};
  
in vec2 uv;

uniform sampler2D screenTexture;

uniform float radius = 400.0;
uniform float angle = 0.4;

vec4 twirl(sampler2D tex, vec2 uv)
{
  vec2 texSize = vec2(resolution.x, resolution.y);
  vec2 center =  vec2(texSize.x / 2.0, texSize.y / 2.0);
  
  vec2 tc = uv * texSize;
  tc -= center;
  float dist = length(tc);
  if (dist < radius) 
  {
    float percent = (radius - dist) / radius;
    float theta = percent * percent * angle * 8.0;
    float s = sin(theta);
    float c = cos(theta);
    tc = vec2(dot(tc, vec2(c, -s)), dot(tc, vec2(s, c)));
  }
  tc += center;
  vec3 color = texture2D(tex, tc / texSize).rgb;
  return vec4(color, 1.0);
}

void main()
{ 
    // FragColor = texture(screenTexture, uv);
	FragColor = twirl(screenTexture, uv);
}
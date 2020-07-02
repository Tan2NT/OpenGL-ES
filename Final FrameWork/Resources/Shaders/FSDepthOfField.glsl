precision mediump float;
uniform sampler2D u_texture2D0;
uniform sampler2D u_texture2D1;
uniform sampler2D u_texture2D2;
uniform float u_near;
uniform float u_far;
uniform float u_fade;
uniform float u_clarity;
uniform vec4 u_step; 
varying vec2 v_textcoordL;

float CalculateMixFactor(vec2 uv)
{
      float depth = texture2D(u_texture2D2, uv).x;
      float z = -u_far * u_near / (depth * (u_far - u_near) + (-u_far));
      float k = clamp(abs(z - u_clarity) / u_fade, 0.0, 1.0);
      return k;
}

void main()
{
	vec2 uv2 = v_textcoordL + vec2(u_step.x,0.0);
    vec2 uv3 = v_textcoordL + vec2(u_step.z, u_step.w);
    vec2 uv4 = v_textcoordL + vec2(0.0, u_step.y);
    vec2 uv5 = v_textcoordL + vec2(-u_step.z, u_step.w);
    vec2 uv6 = v_textcoordL + vec2(-u_step.x, 0.0);
	vec2 uv7 = v_textcoordL + vec2(-u_step.z, -u_step.w);
    vec2 uv8 = v_textcoordL + vec2(0.0, -u_step.y);
    vec2 uv9 = v_textcoordL + vec2(u_step.z, -u_step.w);
	
	vec4 color1 = texture2D(u_texture2D1, v_textcoordL);
	vec4 color2 = texture2D(u_texture2D1, uv2);
	vec4 color3 = texture2D(u_texture2D1, uv3);
	vec4 color4 = texture2D(u_texture2D1, uv4);
	vec4 color5 = texture2D(u_texture2D1, uv5);
	vec4 color6 = texture2D(u_texture2D1, uv6);
	vec4 color7 = texture2D(u_texture2D1, uv7);
	vec4 color8 = texture2D(u_texture2D1, uv8);
	vec4 color9 = texture2D(u_texture2D1, uv9);

	float d1 = CalculateMixFactor(v_textcoordL);
	float d2 = CalculateMixFactor(uv2);
	float d3 = CalculateMixFactor(uv3);
    float d4 = CalculateMixFactor(uv4);
    float d5 = CalculateMixFactor(uv5);
    float d6 = CalculateMixFactor(uv6);
    float d7 = CalculateMixFactor(uv7);
    float d8 = CalculateMixFactor(uv8);
    float d9 = CalculateMixFactor(uv9);
    float total = 2.0 + d2 + d3 + d4 + d5 + d6 + d7 + d8 + d9;
 
    vec4 colorOriginal = texture2D(u_texture2D0, v_textcoordL);
    vec4 colorBlur = (2.0 * color1 + color2 * d2 + color3 * d3 + color4 * d4 + color5 * d5 + color6 * d6 + color7 * d7 + color8 * d8 + color9 * d9) / total;
    gl_FragColor = mix(colorOriginal, colorBlur, d1);
}
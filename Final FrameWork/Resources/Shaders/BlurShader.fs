precision mediump float;

uniform sampler2D u_texture2D0;

uniform vec4 u_step; 

varying vec2 v_textcoordL;

void main(void)

{
	vec3 color1 = texture2D(u_texture2D0, v_textcoordL).rgb;

	vec3 color2 = texture2D(u_texture2D0, vec2(v_textcoordL.x + u_step.x, v_textcoordL.y)).rgb;

	vec3 color3 = texture2D(u_texture2D0, v_textcoordL + vec2(-u_step.x, 0.0)).rgb;
	
	vec3 color4 = texture2D(u_texture2D0, v_textcoordL + vec2(0.0, u_step.y)).rgb;

	vec3 color5 = texture2D(u_texture2D0, v_textcoordL + vec2(0.0, -u_step.y)).rgb;

	vec3 color6 = texture2D(u_texture2D0, v_textcoordL + vec2(u_step.z, u_step.w)).rgb;

	vec3 color7 = texture2D(u_texture2D0, v_textcoordL + vec2(-u_step.z, u_step.w)).rgb;

	vec3 color8 = texture2D(u_texture2D0, v_textcoordL + vec2(-u_step.z, -u_step.w)).rgb;

	vec3 color9 = texture2D(u_texture2D0, v_textcoordL + vec2(u_step.z, -u_step.w)).rgb;

	vec4 color = vec4((color1 * 2.0 + color2 + color3 + color4 + color5 + color6 + color7 + color8 + color9) * 0.1, 1.0);

	float briness = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
	
	gl_FragColor = color;
	//gl_FragColor = vec4(briness, briness, briness, 1.0);
}
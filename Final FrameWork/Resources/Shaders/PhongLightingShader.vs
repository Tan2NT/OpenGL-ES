attribute	vec3 a_posL;
attribute	vec2 a_textcoordL;
varying		vec2 v_textcoordL;
attribute	vec3 a_normalL;
uniform mat4 u_WVP;
uniform mat4 u_worldW;
varying vec3 v_posW;
varying vec3 v_normalW;
void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);
	
	v_textcoordL = a_textcoordL;
	
	v_posW = normalize(u_worldW * vec4(a_posL, 1.0)).xyz;
	
	v_normalW = (u_worldW * vec4(a_normalL, 0.0)).xyz;
	//v_normalW = a_normalL;
}
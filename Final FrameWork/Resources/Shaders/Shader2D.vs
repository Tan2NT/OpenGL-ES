attribute	vec3 a_posL;
attribute	vec2 a_textcoordL;
varying		vec2 v_textcoordL;
uniform mat4 u_WVP;
uniform mat4 u_worldW;
varying vec3 v_posW;
void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);
	
	v_textcoordL = a_textcoordL;
	
	v_posW = (u_worldW * vec4(a_posL, 1.0)).xyz;
}
   
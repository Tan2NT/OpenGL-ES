attribute	vec3 a_posL;
attribute	vec2 a_textcoordL;
varying		vec2 v_textcoordL;
uniform		mat4 u_WVP;

void main()
{
	vec4 posL = u_WVP * vec4(a_posL, 1.0);
	v_textcoordL = a_textcoordL;
	gl_Position = posL;
}
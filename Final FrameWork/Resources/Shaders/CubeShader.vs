attribute	vec3 a_posL;

uniform		mat4 u_WVP;

varying vec3 v_posW;

void main(void)
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);
	gl_Position.z = gl_Position.w * ( 1.0 - 0.0001 );
	v_posW = a_posL;
}
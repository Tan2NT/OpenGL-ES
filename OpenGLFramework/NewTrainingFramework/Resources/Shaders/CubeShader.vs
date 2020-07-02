attribute	vec3 a_posL;
uniform mat4 u_mvpMat;

varying vec3 v_pos;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_mvpMat * posL;
v_pos = a_posL;
} 
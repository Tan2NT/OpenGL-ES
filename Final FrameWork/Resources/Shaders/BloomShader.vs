attribute vec3 a_posL;
attribute vec2 a_textcoordL;
varying vec2 v_textcoordL;
uniform mat4 u_WVP;
void main(void)
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);
	vec2 textcoord = vec2(a_posL.x, a_posL.y);
	v_textcoordL = a_textcoordL;
}
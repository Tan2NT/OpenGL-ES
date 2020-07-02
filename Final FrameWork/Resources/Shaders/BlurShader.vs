attribute vec3 a_posL;
attribute vec2 a_textcoordL;
varying vec2 v_textcoordL;

void main(void)
{
	gl_Position = vec4(a_posL, 1.0);
	v_textcoordL = a_textcoordL;
}

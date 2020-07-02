attribute vec3 a_posL;
attribute vec2 a_textcoordL;
varying vec2 v_texCoords;
uniform mat4 u_WVP;
void main(void)
{
	gl_Position = vec4(a_posL, 1.0);
	vec2 texcoord = vec2(a_posL.x, a_posL.y);
	v_texCoords = texcoord * 0.5 + 0.5;
	//v_texCoords = a_textcoordL;
}
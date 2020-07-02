attribute vec3 a_posL;
attribute vec3 a_normalL;
attribute vec2 a_textcoord;
uniform mat4 u_WVP;
uniform mat4 u_W;
varying vec3 v_normalW;
varying vec2 v_textcoord;
void main()
{
    gl_Position = u_WVP * vec4(a_posL, 1.0);
    v_normalW = normalize((u_W * vec4(a_normalL, 0.0)).xyz);
    v_textcoord = a_textcoord;
}
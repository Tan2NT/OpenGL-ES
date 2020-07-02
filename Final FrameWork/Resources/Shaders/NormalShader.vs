attribute vec3 a_posL;
attribute vec3 a_tangentL;
attribute vec3 a_bitangentL;
attribute vec3 a_normalL;
attribute vec2 a_textcoordL;
uniform mat4 u_WVP;
uniform mat4 u_worldW;
varying vec3 v_posW;
varying vec3 v_tangentW;
varying vec3 v_bitangentW;
varying vec3 v_normalW;
varying vec2 v_textcoordL;
void main()
{
    gl_Position = u_WVP * vec4(a_posL, 1.0);
    v_normalW = normalize((u_worldW * vec4(a_normalL, 0.0)).xyz);
    v_tangentW = normalize((u_worldW * vec4(a_tangentL, 0.0)).xyz);
    v_bitangentW = normalize((u_worldW * vec4(a_bitangentL, 0.0)).xyz);
    v_posW = normalize(u_worldW * vec4(a_posL, 1.0)).xyz;
    v_textcoordL = a_textcoordL;
}
attribute vec3 a_posL;
attribute vec3 a_normalL;
uniform mat4 u_WVP;
uniform mat4 u_worldW;
varying vec3 v_normalW;
varying vec3 v_posW;
void main()
{
    gl_Position  = u_WVP * vec4(a_posL.x, -a_posL.y, a_posL.z, 1.0);
    v_posW = (u_worldW * vec4(a_posL.x, a_posL.y, a_posL.z, 1.0)).xyz;
    v_normalW = normalize((u_worldW * vec4(a_normalL, 0.0)).xyz);
}
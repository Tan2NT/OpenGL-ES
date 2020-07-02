precision mediump float;
varying vec3 v_normalW;
varying vec2 v_textcoord;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform sampler2D u_texture4;
void main()
{
    vec3 normal1 = texture2D(u_texture0, v_textcoord).xyz;
    vec3 normal2 = texture2D(u_texture1, v_textcoord).xyz;
    vec3 normal3 = texture2D(u_texture2, v_textcoord).xyz;
    vec3 normal4 = texture2D(u_texture3, v_textcoord).xyz;
    vec3 normal5 = texture2D(u_texture4, v_textcoord).xyz;
    vec3 color = (normal1 + normal2 + normal3 + normal4 + normal5) * 0.25;
    gl_FragColor = vec4(color, texture2D(u_texture0,v_textcoord).w);
    //gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
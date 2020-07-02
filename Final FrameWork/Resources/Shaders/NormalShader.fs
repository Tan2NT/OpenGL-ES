precision mediump float;
varying vec3 v_tangentW;
varying vec3 v_bitangentW;
varying vec3 v_normalW;
varying vec3 v_posW;
varying vec2 v_textcoordL;
uniform vec3 u_LightPos0;
uniform sampler2D u_texture2D0;
uniform sampler2D u_texture2D1;
void main()
{
	vec3 LightDirection0 = v_posW - u_LightPos0;
    vec3 normal = texture2D(u_texture2D0, v_textcoordL).xyz;
    mat3 TBN = mat3(normalize(v_tangentW), normalize(v_bitangentW), normalize(v_normalW));
    vec3 normalW = normalize(TBN * (2.0 * normal - 1.0));
    float diffuse = max(0.0, dot(-LightDirection0, normalW));
    vec4 color = texture2D(u_texture2D1, v_textcoordL);
    gl_FragColor = vec4(diffuse * color.xyz, color.a);
}
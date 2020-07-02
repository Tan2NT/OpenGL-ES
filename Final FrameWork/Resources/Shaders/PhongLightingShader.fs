precision mediump float;
varying	vec2 v_textcoordL;
uniform sampler2D u_texture2D0;
uniform vec3 u_posCameraW;

uniform vec3 u_LightPos0;
uniform vec3 u_LightDiffuse0;
uniform vec3 u_LightSpecular0;

uniform vec3 u_LightPos1;
uniform vec3 u_LightDiffuse1;
uniform vec3 u_LightSpecular1;

uniform vec3 u_LightPos2;
uniform vec3 u_LightDiffuse2;
uniform vec3 u_LightSpecular2;

uniform vec3 u_AmbientColor;
uniform float u_weight;
uniform float u_specPower0;
uniform float u_specPower1;
uniform float u_specPower2;
varying vec3 v_posW;
varying vec3 v_normalW;

void main()
{
	vec4 ObjColor = texture2D(u_texture2D0, v_textcoordL );
	vec3 normalW = 	normalize(v_normalW);
	vec3 LightDirection0 = normalize(u_LightPos0);
	vec3 LightDirection1 = normalize(v_posW - u_LightPos1);
	vec3 LightDirection2 = normalize(v_posW - u_LightPos2);
	
	vec4 AmbientComponent = vec4(u_AmbientColor, 1.0);
	
	vec4 DiffuseComponent = max(dot(v_normalW, -LightDirection0), 0.0) * vec4(u_LightDiffuse0, 0.0);
	vec3 reflectVector = normalize((reflect(LightDirection0, normalW)));
	vec3 toEye = normalize(u_posCameraW - v_posW);
	vec4 SpecularComponent = pow(max(dot(reflectVector,toEye), 0.0), u_specPower0)* vec4(u_LightSpecular0, 0.0);
	
	vec4 DiffuseComponent1 = max(dot(v_normalW, -LightDirection1), 0.0) * vec4(u_LightDiffuse1, 0.0);
	vec3 reflectVector1 = normalize((reflect(LightDirection1, normalW)));
	vec3 toEye1 = normalize(u_posCameraW - v_posW);
	vec4 SpecularComponent1 = pow(max(dot(reflectVector1,toEye1), 0.0), u_specPower1)* vec4(u_LightSpecular1, 0.0);

	vec4 DiffuseComponent2 = max(dot(v_normalW, -LightDirection2), 0.0) * vec4(u_LightDiffuse2, 0.0);
	vec3 reflectVector2 = normalize((reflect(LightDirection2, normalW)));
	vec3 toEye2 = normalize(u_posCameraW - v_posW);
	vec4 SpecularComponent2 = pow(max(dot(reflectVector2,toEye2), 0.0), u_specPower2)* vec4(u_LightSpecular2, 0.0);
	
	vec4 totalDiffuse = DiffuseComponent + DiffuseComponent1 + DiffuseComponent2;
	vec4 totalSpecular = SpecularComponent + SpecularComponent1 + SpecularComponent2;
	
	gl_FragColor = vec4(((u_weight * AmbientComponent + (1.0 - u_weight) * totalDiffuse) * ObjColor + totalSpecular).xyz, ObjColor.w);
}
precision mediump float;
varying		vec2 v_textcoordL;
uniform sampler2D u_texture2D0;
uniform vec3 u_posCameraW;
varying vec3 v_posW;
uniform float u_fogStart;
uniform float u_fogLength;

void main()
{
	vec4 texelColor = texture2D(u_texture2D0, v_textcoordL);
	
	vec3 distanceToCamera = vec3( v_posW - u_posCameraW);
	
	vec4 fogColor = vec4(1.0, 1.0, 1.0, 1.0);
	
	float leftValue = clamp( (length(distanceToCamera) - u_fogStart)/ u_fogLength , 0.0, 1.0); 
	
	gl_FragColor = leftValue * fogColor + (1.0 - leftValue) * texelColor;
	//gl_FragColor = texelColor;
}
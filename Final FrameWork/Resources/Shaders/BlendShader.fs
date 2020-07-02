precision mediump float;
varying		vec2 v_textcoordL;
uniform sampler2D u_texture2D0;
uniform sampler2D u_texture2D1;
uniform sampler2D u_texture2D2;
uniform sampler2D u_texture2D3;
uniform vec3 u_posCameraW;
varying vec3 v_posW;
uniform float u_fogStart;
uniform float u_fogLength;

void main()
{
	vec2 atlasCoord = vec2(1.0, -1.0);
	
	vec2 atlasSize = vec2(50.0, 50.0);
	
	vec4 color0 = texture2D(u_texture2D0, atlasCoord + fract(v_textcoordL) );
	vec4 color1 = texture2D(u_texture2D1, atlasCoord + fract(v_textcoordL) * atlasSize);
	vec4 color2 = texture2D(u_texture2D2, atlasCoord + fract(v_textcoordL) * atlasSize);
	vec4 color3 = texture2D(u_texture2D3, atlasCoord + fract(v_textcoordL) * atlasSize);
	
	vec4 color = (color0.r * color1 + color0.g * color2 + color0.b * color3) / (color0.r + color0.g + color0.b);
	
	vec3 distanceToCamera = vec3( v_posW - u_posCameraW);
	
	vec4 fogColor = vec4(1.0, 1.0, 1.0, 1.0);
	
	float leftValue = clamp((length(distanceToCamera) - u_fogStart)/ u_fogLength , 0.0, 1.0); 
	
	gl_FragColor = leftValue * fogColor + (1.0 - leftValue) * color;
	
	gl_FragColor = color;
	
}
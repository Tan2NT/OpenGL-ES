precision mediump float;
varying	vec2 v_textcoordL;
uniform	sampler2D u_texture2D0;
uniform	sampler2D	u_texture2D1;
uniform	sampler2D	u_texture2D2;
uniform	float	u_Time;
uniform vec3	u_posCameraW;
varying vec3	v_posW;
uniform float	u_fogStart;
uniform float	u_fogLength;

void main()
{
	vec2 disp = texture2D(u_texture2D0, vec2(v_textcoordL.x, v_textcoordL.y + u_Time)).rg;
	
	vec2 offset = (disp * 2.0 - 1.0) * 0.2;
	
	vec2 Tex_coords_displaced = v_textcoordL + offset;
	
	vec4 fire_color = texture2D(u_texture2D1, Tex_coords_displaced);

	vec4 AlphaValue = texture2D(u_texture2D2, v_textcoordL);
	
	gl_FragColor = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);

	if( gl_FragColor.a < 0.2 )
	{ 
		discard;
	}
}
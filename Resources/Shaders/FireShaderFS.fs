precision mediump float;

uniform sampler2D FireTexture;
uniform sampler2D FireMask;
uniform sampler2D Displ_tex;

uniform float u_Time;

varying vec2 v_uv;

void main()
{
 float dMax = 0.08;
 vec2 disp = texture2D(Displ_tex, vec2(v_uv.x, v_uv.y )).rg;
 vec2 offset = (2.0 *disp - 1.0)*dMax;
 vec2 Tex_coords_displaced = v_uv + offset;
 vec4 fire_color = texture2D (FireTexture, Tex_coords_displaced);
 vec4 alphaValue = texture2D(FireMask, v_uv);
 
 gl_FragColor = fire_color * vec4(1.0, 1.0, 1.0, alphaValue.r);

}
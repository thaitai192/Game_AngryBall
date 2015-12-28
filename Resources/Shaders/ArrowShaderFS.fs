precision mediump float;

uniform sampler2D u_mask;
uniform sampler2D u_texture;
uniform float u_Time;

varying vec2 v_uv;

void main()
{
 vec2 newuv = vec2(u_Time,0.0);
 vec4 texture_color = texture2D (u_texture, newuv+v_uv);
 vec4 alpha_Value = texture2D(u_mask, v_uv);
 
 gl_FragColor = texture_color*(1.0,1.0,1.0,alpha_Value.r);
}
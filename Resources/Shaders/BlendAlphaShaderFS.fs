precision mediump float;

uniform sampler2D u_mask;
uniform sampler2D u_texture;

varying vec2 v_uv;

void main()
{
 vec4 texture_color = texture2D (u_texture, v_uv);
 vec4 alpha_Value = texture2D(u_mask, v_uv);
 
 gl_FragColor = texture_color*(1.0,1.0,1.0,alpha_Value.r);
}
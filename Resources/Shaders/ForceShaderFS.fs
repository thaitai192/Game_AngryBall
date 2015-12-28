precision mediump float;

uniform sampler2D u_mask;
uniform sampler2D u_texture;
uniform float u_force;

varying vec2 v_uv;

void main()
{
 vec4 texture_color = texture2D (u_texture, v_uv);
 float alpha_Value = 1.0;
 if(v_uv.x>=u_force) alpha_Value=0.7;
	gl_FragColor = texture_color*(1.0,1.0,1.0,alpha_Value);
}
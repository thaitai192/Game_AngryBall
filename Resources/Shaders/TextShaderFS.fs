precision mediump float;
varying vec2 v_uv;
uniform vec4 u_color;
uniform sampler2D u_texture;
void main()
{
	gl_FragColor = vec4(u_color.r, u_color.g, u_color.b, texture2D(u_texture, v_uv).a * u_color.a);
}
attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec4 v_pos;

attribute float a_force;
varying float v_force;
uniform mediump mat4 u_MVP;//Model * View * Projection
void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_MVP*posL;
	v_uv = a_uv;
	v_pos=posL;
	v_force= a_force;
}
   
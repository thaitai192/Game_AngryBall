uniform mediump mat4 u_MVP;
uniform mat4 u_M;
attribute vec3 a_posL;
attribute vec2 a_uv;

varying vec2 v_uv;
varying vec2 v_uvScale;
varying vec3 v_posW;

void main(){
	vec4 posL=vec4(a_posL,1.0);
	gl_Position = u_MVP*posL;
	
	v_uv=a_uv;
	v_uvScale=a_uv*60.0;
	
	v_posW = gl_Position.xyz;
	
}
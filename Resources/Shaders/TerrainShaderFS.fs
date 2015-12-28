precision mediump float;
uniform sampler2D u_BlendMap;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;

varying vec2 v_uv;
varying vec2 v_uvScale;

varying vec3 v_posW;
uniform vec3 u_camPosition;
uniform float u_fogStart;
uniform float u_fogLength;
uniform vec3 u_fogColor;

void main(){
	vec4 BT	=	texture2D(u_BlendMap,v_uv);
	vec4 Tex1 = texture2D(u_Texture1, v_uvScale);
	vec4 Tex2 = texture2D(u_Texture2, v_uvScale);
	vec4 Tex3 = texture2D(u_Texture3, v_uvScale);
	gl_FragColor =(BT.r*Tex1 + BT.g*Tex2 +BT.b*Tex3)/(BT.r+BT.g+BT.b);
	

	float dis= distance(u_camPosition, v_posW);
	float lerpValue= clamp(((dis-u_fogStart)/u_fogLength), 0.0, 1.0);
	vec3 FinalColor = lerpValue*u_fogColor + (1.0-lerpValue)*gl_FragColor.xyz;
	gl_FragColor= vec4(FinalColor,1.0);
}
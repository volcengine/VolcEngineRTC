attribute vec3 attPosition;
attribute vec2 attUV;

attribute vec3 attPositionOffset;

uniform mat4 g_unif_ModelViewProjMat;
varying vec2 g_vary_Texcoord;
void main ()
{
  vec4 tmpvar_1;
  tmpvar_1.w = 1.0;
  tmpvar_1.xyz = attPosition+attPositionOffset;
  g_vary_Texcoord = attUV;
  gl_Position = (g_unif_ModelViewProjMat * tmpvar_1);
}


attribute vec3 attPosition;
attribute vec3 attNormal;
attribute vec3 attTangent;
attribute vec3 attBigTangent;
attribute vec2 attUV;
uniform mat4 g_unif_ModelMat;
uniform mat4 g_unif_ModelViewProjMat;
uniform mat3 g_unif_NormalWorldMat;
varying vec3 g_vary_WorldPosition;
varying vec3 g_vary_WorldNormal;
varying vec3 g_vary_WorldTangent;
varying vec3 g_vary_WorldBitangent;
varying vec2 g_vary_Texcoord;
void main ()
{
  vec4 tmpvar_1;
  tmpvar_1.w = 1.0;
  tmpvar_1.xyz = attPosition;
  g_vary_WorldPosition = (g_unif_ModelMat * tmpvar_1).xyz;
  g_vary_WorldNormal = (g_unif_NormalWorldMat * attNormal);
  g_vary_WorldTangent = (g_unif_NormalWorldMat * attTangent);
  g_vary_WorldBitangent = (g_unif_NormalWorldMat * attBigTangent);
  g_vary_Texcoord = attUV;
  gl_Position = (g_unif_ModelViewProjMat * tmpvar_1);
}


precision highp sampler2D;
precision highp float;
attribute vec3 attPosition;
attribute vec3 attNormal;
attribute vec4 attBoneIds;
attribute vec4 attWeights;
attribute vec2 attUV;
uniform mat4 g_unif_ModelMat;
uniform mat4 g_unif_ModelViewProjMat;
uniform mat3 g_unif_NormalWorldMat;
uniform mat4 g_unif_BoneMatArr[48];
varying vec3 g_vary_WorldPosition;
varying vec3 g_vary_WorldNormal;
varying vec2 g_vary_Texcoord;
void main ()
{
  mat4 bone_mat_1;
  bone_mat_1 = ((g_unif_BoneMatArr[int(attBoneIds.x)] * attWeights.x) + (g_unif_BoneMatArr[int(attBoneIds.y)] * attWeights.y));
  bone_mat_1 = (bone_mat_1 + (g_unif_BoneMatArr[int(attBoneIds.z)] * attWeights.z));
  bone_mat_1 = (bone_mat_1 + (g_unif_BoneMatArr[int(attBoneIds.w)] * attWeights.w));
  vec4 tmpvar_2;
  tmpvar_2.w = 1.0;
  tmpvar_2.xyz = attPosition;
  vec4 tmpvar_3;
  tmpvar_3.w = 0.0;
  tmpvar_3.xyz = attNormal;
  vec4 tmpvar_4;
  tmpvar_4.w = 1.0;
  tmpvar_4.xyz = (bone_mat_1 * tmpvar_2).xyz;
  g_vary_WorldPosition = (g_unif_ModelMat * tmpvar_4).xyz;
  g_vary_WorldNormal = (g_unif_NormalWorldMat * (bone_mat_1 * tmpvar_3).xyz);
  g_vary_Texcoord = attUV;
  gl_Position = (g_unif_ModelViewProjMat * tmpvar_4);
}


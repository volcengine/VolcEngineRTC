precision highp sampler2D;
precision highp float;
attribute vec3 attPosition;
attribute vec3 attNormal;
attribute vec2 attUV;

attribute vec3 attPositionOffset;
attribute vec3 attNormalOffset;

uniform mat4 g_unif_ModelMat;
uniform mat4 g_unif_ModelViewProjMat;
uniform mat3 g_unif_NormalWorldMat;
varying vec3 g_vary_WorldPosition;
varying vec3 g_vary_WorldNormal;
varying vec2 g_vary_Texcoord;
void main ()
{
    vec4 tmpvar_1;
    tmpvar_1.w = 1.0;
    tmpvar_1.xyz = attPosition + attPositionOffset;
    g_vary_WorldPosition = (g_unif_ModelMat * tmpvar_1).xyz;
    vec3 normal = normalize(attNormalOffset + attNormal);
    g_vary_WorldNormal = (g_unif_NormalWorldMat * normal);
    g_vary_Texcoord = attUV;
    gl_Position = (g_unif_ModelViewProjMat * tmpvar_1);
}

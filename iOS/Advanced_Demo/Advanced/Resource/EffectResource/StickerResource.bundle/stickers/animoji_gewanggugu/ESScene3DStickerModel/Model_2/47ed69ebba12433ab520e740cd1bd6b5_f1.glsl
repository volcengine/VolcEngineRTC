
    precision highp float;
    precision highp sampler2D;
precision highp sampler2D;
precision highp float;
uniform vec3 _AE_DIRECTIONAL_LIGHTS_DIRECTION_[1];
uniform vec3 _AE_DIRECTIONAL_LIGHTS_COLOR_[1];
uniform float _AE_DIRECTIONAL_LIGHTS_INTENSITY_[1];
uniform mat4 _AE_DIRECTIONAL_LIGHT0_SHADOW_MATRIX_;
uniform float _AE_DIRECTIONAL_LIGHT0_SHADOW_ENABLED_;
uniform float _AE_DIRECTIONAL_LIGHT0_SHADOW_BIAS_;
uniform float _AE_DIRECTIONAL_LIGHT0_SHADOW_STRENGTH_;
uniform float _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFT_;
uniform float _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFTNESS_;
uniform sampler2D _AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_;
uniform vec2 _AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_SIZE_;
uniform sampler2D u_RadianceTex;
uniform sampler2D u_IrradianceTex;
uniform vec3 u_BaseColor;
uniform float u_Metallic;
uniform float u_Roughness;
uniform float u_AmbientOcclusion;
uniform sampler2D u_MRAOTex;
uniform float u_Specular;
uniform vec3 u_EmissiveColor;
uniform float u_Translucency;
uniform sampler2D u_NormalTex;
uniform float u_Culloff;
uniform float u_IBLOffset;
uniform float u_IBLIntensity;
uniform vec3 g_unif_CameraWorldPos;
varying vec3 g_vary_WorldPosition;
varying vec3 g_vary_WorldNormal;
varying vec3 g_vary_WorldTangent;
varying vec3 g_vary_WorldBitangent;
varying vec2 g_vary_Texcoord;
void main ()
{
  vec3 final_color_1;
  vec3 tmpvar_2[1];
  vec3 tmpvar_3[1];
  float tmpvar_4[1];
  vec2 tmpvar_5;
  mat3 tmpvar_6;
  tmpvar_6[0] = normalize(g_vary_WorldTangent);
  tmpvar_6[1] = normalize(g_vary_WorldBitangent);
  tmpvar_6[2] = normalize(g_vary_WorldNormal);
  vec3 tmpvar_7;
  tmpvar_7 = normalize((g_unif_CameraWorldPos - g_vary_WorldPosition));
  tmpvar_5.x = g_vary_Texcoord.x;
  tmpvar_5.y = (1.0 - g_vary_Texcoord.y);
  vec3 tmpvar_8;
  float tmpvar_9;
  float tmpvar_10;
  float tmpvar_11;
  float tmpvar_12;
  vec3 tmpvar_13;
  tmpvar_13 = normalize((tmpvar_6 * (
    (texture2D (u_NormalTex, tmpvar_5).xyz * 2.0)
   - 1.0)));
  if ((1.0 < u_Culloff)) {
    discard;
  };
  tmpvar_8 = pow (u_BaseColor, vec3(2.2, 2.2, 2.2));
  tmpvar_11 = u_Translucency;
  vec4 tmpvar_14;
  tmpvar_14 = texture2D (u_MRAOTex, tmpvar_5);
  tmpvar_10 = (u_Metallic * tmpvar_14.x);
  tmpvar_9 = (u_Roughness * tmpvar_14.y);
  tmpvar_12 = pow (min (1.0, (tmpvar_14.z + 0.001)), u_AmbientOcclusion);
  vec3 tmpvar_15[1];
  vec3 tmpvar_16[1];
  float tmpvar_17[1];
  tmpvar_15[0]=tmpvar_2[0];
  tmpvar_16[0]=tmpvar_3[0];
  tmpvar_17[0]=tmpvar_4[0];
  tmpvar_15[0] = normalize(-(_AE_DIRECTIONAL_LIGHTS_DIRECTION_[0]));
  tmpvar_16[0] = _AE_DIRECTIONAL_LIGHTS_COLOR_[0];
  tmpvar_17[0] = _AE_DIRECTIONAL_LIGHTS_INTENSITY_[0];
  vec3 l_18;
  l_18 = tmpvar_15[0];
  float tmpvar_19;
  float shadow_factor_20;
  float bias_21;
  vec3 shadow_coord_22;
  if ((_AE_DIRECTIONAL_LIGHT0_SHADOW_ENABLED_ < 1.0)) {
    tmpvar_19 = 1.0;
  } else {
    float tmpvar_23;
    tmpvar_23 = max (dot (tmpvar_13, l_18), 0.0);
    vec4 tmpvar_24;
    tmpvar_24.w = 1.0;
    tmpvar_24.xyz = g_vary_WorldPosition;
    vec4 tmpvar_25;
    tmpvar_25 = (_AE_DIRECTIONAL_LIGHT0_SHADOW_MATRIX_ * tmpvar_24);
    vec3 tmpvar_26;
    tmpvar_26 = (tmpvar_25.xyz / tmpvar_25.w);
    shadow_coord_22 = tmpvar_26;
    if ((((
      (((tmpvar_26.x < 0.0) || (1.0 < tmpvar_26.x)) || (tmpvar_26.y < 0.0))
     || 
      (1.0 < tmpvar_26.y)
    ) || (tmpvar_26.z < 0.0)) || (1.0 < tmpvar_26.z))) {
      tmpvar_19 = 1.0;
    } else {
      float tmpvar_27;
      tmpvar_27 = (1.570796 - (sign(tmpvar_23) * (1.570796 - 
        (sqrt((1.0 - abs(tmpvar_23))) * (1.570796 + (abs(tmpvar_23) * (-0.2146018 + 
          (abs(tmpvar_23) * (0.08656672 + (abs(tmpvar_23) * -0.03102955)))
        ))))
      )));
      float tmpvar_28;
      tmpvar_28 = clamp ((_AE_DIRECTIONAL_LIGHT0_SHADOW_BIAS_ * (
        sin(tmpvar_27)
       / 
        cos(tmpvar_27)
      )), 0.0, 1.0);
      bias_21 = tmpvar_28;
      shadow_factor_20 = 0.0;
      if ((0.0 < _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFT_)) {
        vec2 inv_tex_size_30;
        float shadow_sum_31;
        vec2 sample_offsets_32[9];
        sample_offsets_32[0] = vec2(-1.0, -1.0);
        sample_offsets_32[1] = vec2(0.0, -1.0);
        sample_offsets_32[2] = vec2(1.0, -1.0);
        sample_offsets_32[3] = vec2(-1.0, 0.0);
        sample_offsets_32[4] = vec2(0.0, 0.0);
        sample_offsets_32[5] = vec2(1.0, 0.0);
        sample_offsets_32[6] = vec2(-1.0, 1.0);
        sample_offsets_32[7] = vec2(0.0, 1.0);
        sample_offsets_32[8] = vec2(1.0, 1.0);
        shadow_sum_31 = 0.0;
        inv_tex_size_30 = (1.0/(_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_SIZE_));
        for (highp int i_29 = 0; i_29 < 9; i_29++) {
          shadow_sum_31 = (shadow_sum_31 + float((shadow_coord_22.z < 
            (dot (texture2D (_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_, (shadow_coord_22.xy + (
              (sample_offsets_32[i_29] * _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFTNESS_)
             * inv_tex_size_30))), vec4(5.960464e-08, 1.525879e-05, 0.00390625, 1.0)) + bias_21)
          )));
        };
        shadow_factor_20 = (shadow_sum_31 / 9.0);
      } else {
        shadow_factor_20 = float((tmpvar_26.z < (
          dot (texture2D (_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_, tmpvar_26.xy), vec4(5.960464e-08, 1.525879e-05, 0.00390625, 1.0))
         + tmpvar_28)));
      };
      if ((shadow_factor_20 < 1.0)) {
        shadow_factor_20 = mix (1.0, shadow_factor_20, _AE_DIRECTIONAL_LIGHT0_SHADOW_STRENGTH_);
      };
      tmpvar_19 = shadow_factor_20;
    };
  };
  float tmpvar_33;
  float tmpvar_34;
  tmpvar_34 = (min (abs(
    (tmpvar_13.x / tmpvar_13.z)
  ), 1.0) / max (abs(
    (tmpvar_13.x / tmpvar_13.z)
  ), 1.0));
  float tmpvar_35;
  tmpvar_35 = (tmpvar_34 * tmpvar_34);
  tmpvar_35 = (((
    ((((
      ((((-0.01213232 * tmpvar_35) + 0.05368138) * tmpvar_35) - 0.1173503)
     * tmpvar_35) + 0.1938925) * tmpvar_35) - 0.3326756)
   * tmpvar_35) + 0.9999793) * tmpvar_34);
  tmpvar_35 = (tmpvar_35 + (float(
    (abs((tmpvar_13.x / tmpvar_13.z)) > 1.0)
  ) * (
    (tmpvar_35 * -2.0)
   + 1.570796)));
  tmpvar_33 = (tmpvar_35 * sign((tmpvar_13.x / tmpvar_13.z)));
  if ((abs(tmpvar_13.z) > (1e-08 * abs(tmpvar_13.x)))) {
    if ((tmpvar_13.z < 0.0)) {
      if ((tmpvar_13.x >= 0.0)) {
        tmpvar_33 += 3.141593;
      } else {
        tmpvar_33 = (tmpvar_33 - 3.141593);
      };
    };
  } else {
    tmpvar_33 = (sign(tmpvar_13.x) * 1.570796);
  };
  vec2 tmpvar_36;
  tmpvar_36.x = (((tmpvar_33 / 3.141593) + 1.0) * 0.5);
  tmpvar_36.y = ((1.570796 - (
    sign(tmpvar_13.y)
   * 
    (1.570796 - (sqrt((1.0 - 
      abs(tmpvar_13.y)
    )) * (1.570796 + (
      abs(tmpvar_13.y)
     * 
      (-0.2146018 + (abs(tmpvar_13.y) * (0.08656672 + (
        abs(tmpvar_13.y)
       * -0.03102955))))
    ))))
  )) / 3.141593);
  vec2 tmpvar_37;
  tmpvar_37.x = (float(mod ((tmpvar_36.x + u_IBLOffset), 1.0)));
  tmpvar_37.y = tmpvar_36.y;
  vec3 tmpvar_38;
  tmpvar_38 = pow (texture2D (u_IrradianceTex, tmpvar_37).xyz, vec3(2.2, 2.2, 2.2));
  vec2 rC_39;
  vec2 rC_40;
  vec4 color2_41;
  vec4 color1_42;
  vec3 I_43;
  I_43 = -(tmpvar_7);
  vec3 tmpvar_44;
  tmpvar_44 = normalize((I_43 - (2.0 * 
    (dot (tmpvar_13, I_43) * tmpvar_13)
  )));
  float tmpvar_45;
  float tmpvar_46;
  tmpvar_46 = (min (abs(
    (tmpvar_44.x / tmpvar_44.z)
  ), 1.0) / max (abs(
    (tmpvar_44.x / tmpvar_44.z)
  ), 1.0));
  float tmpvar_47;
  tmpvar_47 = (tmpvar_46 * tmpvar_46);
  tmpvar_47 = (((
    ((((
      ((((-0.01213232 * tmpvar_47) + 0.05368138) * tmpvar_47) - 0.1173503)
     * tmpvar_47) + 0.1938925) * tmpvar_47) - 0.3326756)
   * tmpvar_47) + 0.9999793) * tmpvar_46);
  tmpvar_47 = (tmpvar_47 + (float(
    (abs((tmpvar_44.x / tmpvar_44.z)) > 1.0)
  ) * (
    (tmpvar_47 * -2.0)
   + 1.570796)));
  tmpvar_45 = (tmpvar_47 * sign((tmpvar_44.x / tmpvar_44.z)));
  if ((abs(tmpvar_44.z) > (1e-08 * abs(tmpvar_44.x)))) {
    if ((tmpvar_44.z < 0.0)) {
      if ((tmpvar_44.x >= 0.0)) {
        tmpvar_45 += 3.141593;
      } else {
        tmpvar_45 = (tmpvar_45 - 3.141593);
      };
    };
  } else {
    tmpvar_45 = (sign(tmpvar_44.x) * 1.570796);
  };
  vec2 tmpvar_48;
  tmpvar_48.x = (((tmpvar_45 / 3.141593) + 1.0) * 0.5);
  tmpvar_48.y = ((1.570796 - (
    sign(tmpvar_44.y)
   * 
    (1.570796 - (sqrt((1.0 - 
      abs(tmpvar_44.y)
    )) * (1.570796 + (
      abs(tmpvar_44.y)
     * 
      (-0.2146018 + (abs(tmpvar_44.y) * (0.08656672 + (
        abs(tmpvar_44.y)
       * -0.03102955))))
    ))))
  )) / 3.141593);
  float tmpvar_49;
  tmpvar_49 = min (tmpvar_9, 0.99);
  float tmpvar_50;
  tmpvar_50 = min (7.0, (floor(
    (tmpvar_49 * 7.0)
  ) + 1.0));
  float tmpvar_51;
  tmpvar_51 = max (0.0, (tmpvar_50 - 1.0));
  float tmpvar_52;
  tmpvar_52 = exp2(tmpvar_50);
  float tmpvar_53;
  tmpvar_53 = (tmpvar_52 * 2.0);
  rC_40.x = ((float(mod ((tmpvar_48.x + u_IBLOffset), 1.0))) / tmpvar_52);
  rC_40.y = (((tmpvar_48.y / tmpvar_53) + 1.0) - (2.0 / tmpvar_53));
  vec4 tmpvar_54;
  tmpvar_54 = texture2D (u_RadianceTex, rC_40);
  color1_42.w = tmpvar_54.w;
  color1_42.xyz = (tmpvar_54.xyz / tmpvar_54.w);
  color1_42.xyz = (color1_42.xyz * (pow (
    mix (1.2, 1.5, tmpvar_54.w)
  , 
    (tmpvar_54.w * 32.0)
  ) - 1.2));
  float tmpvar_55;
  tmpvar_55 = exp2(tmpvar_51);
  float tmpvar_56;
  tmpvar_56 = (tmpvar_55 * 2.0);
  rC_39.x = ((float(mod ((tmpvar_48.x + u_IBLOffset), 1.0))) / tmpvar_55);
  rC_39.y = (((tmpvar_48.y / tmpvar_56) + 1.0) - (2.0 / tmpvar_56));
  vec4 tmpvar_57;
  tmpvar_57 = texture2D (u_RadianceTex, rC_39);
  color2_41.w = tmpvar_57.w;
  color2_41.xyz = (tmpvar_57.xyz / tmpvar_57.w);
  color2_41.xyz = (color2_41.xyz * (pow (
    mix (1.2, 1.5, tmpvar_57.w)
  , 
    (tmpvar_57.w * 32.0)
  ) - 1.2));
  tmpvar_2[0]=tmpvar_15[0];
  tmpvar_3[0]=tmpvar_16[0];
  tmpvar_4[0]=tmpvar_17[0];
  vec3 tmpvar_58;
  tmpvar_58 = mix (vec3((0.08 * u_Specular)), tmpvar_8, tmpvar_10);
  vec3 tmpvar_59;
  tmpvar_59 = tmpvar_15[0];
  float tmpvar_60;
  tmpvar_60 = dot (tmpvar_13, tmpvar_59);
  float tmpvar_61;
  tmpvar_61 = dot (tmpvar_13, tmpvar_7);
  float tmpvar_62;
  tmpvar_62 = dot (tmpvar_59, tmpvar_7);
  float tmpvar_63;
  tmpvar_63 = inversesqrt((2.0 + (2.0 * tmpvar_62)));
  float tmpvar_64;
  tmpvar_64 = clamp (((tmpvar_60 + tmpvar_61) * tmpvar_63), 0.0, 1.0);
  float tmpvar_65;
  tmpvar_65 = clamp (tmpvar_60, 0.0, 1.0);
  float tmpvar_66;
  tmpvar_66 = clamp (abs(tmpvar_61), 0.0, 1.0);
  float tmpvar_67;
  tmpvar_67 = (tmpvar_9 * tmpvar_9);
  float tmpvar_68;
  tmpvar_68 = (tmpvar_67 * tmpvar_67);
  float tmpvar_69;
  tmpvar_69 = (((
    (tmpvar_64 * tmpvar_68)
   - tmpvar_64) * tmpvar_64) + 1.0);
  float tmpvar_70;
  tmpvar_70 = (tmpvar_9 * tmpvar_9);
  float tmpvar_71;
  tmpvar_71 = pow ((1.0 - clamp (
    (tmpvar_63 + (tmpvar_63 * tmpvar_62))
  , 0.0, 1.0)), 5.0);
  final_color_1 = (((
    ((((
      (tmpvar_8 - (tmpvar_8 * vec3(tmpvar_10)))
     * 0.3183099) + (
      ((tmpvar_68 / ((3.141593 * tmpvar_69) * tmpvar_69)) * (0.5 / ((
        (tmpvar_65 * ((tmpvar_66 * (1.0 - tmpvar_70)) + tmpvar_70))
       + 
        (tmpvar_66 * ((tmpvar_65 * (1.0 - tmpvar_70)) + tmpvar_70))
      ) + 1e-05)))
     * 
      ((clamp ((50.0 * tmpvar_58.y), 0.0, 1.0) * tmpvar_71) + ((1.0 - tmpvar_71) * tmpvar_58))
    )) * tmpvar_65) * tmpvar_17[0])
   * tmpvar_16[0]) * vec3(tmpvar_19)) + u_EmissiveColor);
  vec3 result_72;
  float tmpvar_73;
  tmpvar_73 = min (max (dot (tmpvar_13, tmpvar_7), 0.0), 1.0);
  vec3 tmpvar_74;
  tmpvar_74 = mix (vec3(0.04, 0.04, 0.04), tmpvar_8, tmpvar_10);
  vec3 tmpvar_75;
  tmpvar_75 = (tmpvar_74 + ((
    max (vec3((0.99 - tmpvar_9)), tmpvar_74)
   - tmpvar_74) * pow (
    (1.0 - tmpvar_73)
  , 5.0)));
  float tmpvar_76;
  tmpvar_76 = (1.05 - tmpvar_73);
  result_72 = (((
    (((vec3(1.0, 1.0, 1.0) - tmpvar_75) * (1.0 - tmpvar_10)) * tmpvar_38)
   * tmpvar_8) + (
    (tmpvar_75 * pow ((mix (color2_41.xyz, color1_42.xyz, vec3(
      min (max (((tmpvar_49 * 7.0) - tmpvar_51), 0.0), 1.0)
    )) * vec3(1.57, 1.57, 1.57)), vec3(2.2, 2.2, 2.2)))
   * 
    mix (vec3(min (1.0, (tmpvar_76 * tmpvar_76))), tmpvar_58, tmpvar_10)
  )) * max (vec3(tmpvar_12), (
    ((((tmpvar_12 * 
      ((2.0404 * tmpvar_8) - 0.3324)
    ) + (
      (-4.7951 * tmpvar_8)
     + 0.6417)) * tmpvar_12) + ((2.7552 * tmpvar_8) + 0.6903))
   * tmpvar_12)));
  vec3 color_77;
  color_77 = (result_72 * u_IBLIntensity);
  color_77 = ((color_77 / (color_77 + 0.187)) * 1.035);
  result_72 = color_77;
  final_color_1 = (final_color_1 + color_77);
  vec4 tmpvar_78;
  tmpvar_78.xyz = final_color_1;
  tmpvar_78.w = tmpvar_11;
  vec4 tmpvar_79;
  vec4 color_80;
  color_80.w = tmpvar_78.w;
  color_80.xyz = pow (final_color_1, vec3(0.4545454, 0.4545454, 0.4545454));
  color_80.xyz = clamp (color_80.xyz, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));
  tmpvar_79 = color_80;
  gl_FragColor = tmpvar_79;
}



    precision highp float;
    precision highp sampler2D;
uniform vec3 _AE_DIRECTIONAL_LIGHTS_DIRECTION_[1];
uniform vec3 _AE_DIRECTIONAL_LIGHTS_COLOR_[1];
uniform float _AE_DIRECTIONAL_LIGHTS_INTENSITY_[1];
uniform highp mat4 _AE_DIRECTIONAL_LIGHT0_SHADOW_MATRIX_;
uniform highp float _AE_DIRECTIONAL_LIGHT0_SHADOW_ENABLED_;
uniform highp float _AE_DIRECTIONAL_LIGHT0_SHADOW_BIAS_;
uniform highp float _AE_DIRECTIONAL_LIGHT0_SHADOW_STRENGTH_;
uniform highp float _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFT_;
uniform highp float _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFTNESS_;
uniform sampler2D _AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_;
uniform highp vec2 _AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_SIZE_;
uniform sampler2D u_RadianceTex;
uniform sampler2D u_IrradianceTex;
uniform sampler2D u_MRAOTex;
uniform sampler2D u_NormalTex;
uniform highp vec3 u_InColor;
uniform highp vec3 u_OutColor;
uniform highp float u_Fresnel;
uniform highp float u_Roughness;
uniform highp float u_RoughnessOverride;
uniform highp float u_Metallic;
uniform highp float u_Opacity;
uniform highp float u_UVTilng;
uniform highp float u_IBLOffset;
uniform highp vec3 g_unif_CameraWorldPos;
varying highp vec3 g_vary_WorldPosition;
varying highp vec3 g_vary_WorldNormal;
varying highp vec3 g_vary_WorldTangent;
varying highp vec3 g_vary_WorldBitangent;
varying highp vec2 g_vary_Texcoord;
void main ()
{
  vec3 final_color_1;
  vec3 tmpvar_2[1];
  vec3 tmpvar_3[1];
  float tmpvar_4[1];
  highp vec2 tmpvar_5;
  mat3 tmpvar_6;
  tmpvar_6[0] = normalize(g_vary_WorldTangent);
  tmpvar_6[1] = normalize(g_vary_WorldBitangent);
  vec3 tmpvar_7;
  tmpvar_7 = normalize(g_vary_WorldNormal);
  tmpvar_6[2] = tmpvar_7;
  highp vec3 tmpvar_8;
  tmpvar_8 = normalize((g_unif_CameraWorldPos - g_vary_WorldPosition));
  tmpvar_5.x = g_vary_Texcoord.x;
  tmpvar_5.y = (1.0 - g_vary_Texcoord.y);
  vec3 tmpvar_9;
  float tmpvar_10;
  float tmpvar_11;
  float tmpvar_12;
  tmpvar_12 = (0.04 + (0.96 * pow (
    (1.0 - max (0.0, dot (tmpvar_7, tmpvar_8)))
  , u_Fresnel)));
  tmpvar_9 = mix (u_InColor, u_OutColor, tmpvar_12);
  tmpvar_10 = mix (u_Roughness, texture2D (u_MRAOTex, (tmpvar_5 * u_UVTilng)).y, u_RoughnessOverride);
  tmpvar_11 = mix (u_Opacity, 1.0, tmpvar_12);
  vec3 tmpvar_13;
  tmpvar_13 = normalize((tmpvar_6 * (
    (texture2D (u_NormalTex, tmpvar_5).xyz * 2.0)
   - 1.0)));
  vec3 tmpvar_14[1];
  vec3 tmpvar_15[1];
  float tmpvar_16[1];
  tmpvar_14[0]=tmpvar_2[0];
  tmpvar_15[0]=tmpvar_3[0];
  tmpvar_16[0]=tmpvar_4[0];
  tmpvar_14[0] = normalize(-(_AE_DIRECTIONAL_LIGHTS_DIRECTION_[0]));
  tmpvar_15[0] = _AE_DIRECTIONAL_LIGHTS_COLOR_[0];
  tmpvar_16[0] = _AE_DIRECTIONAL_LIGHTS_INTENSITY_[0];
  highp vec3 l_17;
  l_17 = tmpvar_14[0];
  float tmpvar_18;
  float shadow_factor_19;
  float bias_20;
  highp vec3 shadow_coord_21;
  if ((_AE_DIRECTIONAL_LIGHT0_SHADOW_ENABLED_ < 1.0)) {
    tmpvar_18 = 1.0;
  } else {
    float tmpvar_22;
    tmpvar_22 = max (dot (tmpvar_13, l_17), 0.0);
    highp vec4 tmpvar_23;
    tmpvar_23.w = 1.0;
    tmpvar_23.xyz = g_vary_WorldPosition;
    highp vec4 tmpvar_24;
    tmpvar_24 = (_AE_DIRECTIONAL_LIGHT0_SHADOW_MATRIX_ * tmpvar_23);
    highp vec3 tmpvar_25;
    tmpvar_25 = (tmpvar_24.xyz / tmpvar_24.w);
    shadow_coord_21 = tmpvar_25;
    if ((((
      (((tmpvar_25.x < 0.0) || (1.0 < tmpvar_25.x)) || (tmpvar_25.y < 0.0))
     || 
      (1.0 < tmpvar_25.y)
    ) || (tmpvar_25.z < 0.0)) || (1.0 < tmpvar_25.z))) {
      tmpvar_18 = 1.0;
    } else {
      float tmpvar_26;
      tmpvar_26 = (1.570796 - (sign(tmpvar_22) * (1.570796 - 
        (sqrt((1.0 - abs(tmpvar_22))) * (1.570796 + (abs(tmpvar_22) * (-0.2146018 + 
          (abs(tmpvar_22) * (0.08656672 + (abs(tmpvar_22) * -0.03102955)))
        ))))
      )));
      float tmpvar_27;
      tmpvar_27 = clamp ((_AE_DIRECTIONAL_LIGHT0_SHADOW_BIAS_ * (
        sin(tmpvar_26)
       / 
        cos(tmpvar_26)
      )), 0.0, 1.0);
      bias_20 = tmpvar_27;
      shadow_factor_19 = 0.0;
      if ((0.0 < _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFT_)) {
        highp vec2 inv_tex_size_29;
        float shadow_sum_30;
        vec2 sample_offsets_31[9];
        sample_offsets_31[0] = vec2(-1.0, -1.0);
        sample_offsets_31[1] = vec2(0.0, -1.0);
        sample_offsets_31[2] = vec2(1.0, -1.0);
        sample_offsets_31[3] = vec2(-1.0, 0.0);
        sample_offsets_31[4] = vec2(0.0, 0.0);
        sample_offsets_31[5] = vec2(1.0, 0.0);
        sample_offsets_31[6] = vec2(-1.0, 1.0);
        sample_offsets_31[7] = vec2(0.0, 1.0);
        sample_offsets_31[8] = vec2(1.0, 1.0);
        shadow_sum_30 = 0.0;
        inv_tex_size_29 = (1.0/(_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_SIZE_));
        for (highp int i_28 = 0; i_28 < 9; i_28++) {
          shadow_sum_30 = (shadow_sum_30 + float((shadow_coord_21.z < 
            (dot (texture2D (_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_, (shadow_coord_21.xy + (
              (sample_offsets_31[i_28] * _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFTNESS_)
             * inv_tex_size_29))), vec4(5.960464e-08, 1.525879e-05, 0.00390625, 1.0)) + bias_20)
          )));
        };
        shadow_factor_19 = (shadow_sum_30 / 9.0);
      } else {
        shadow_factor_19 = float((tmpvar_25.z < (
          dot (texture2D (_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_, tmpvar_25.xy), vec4(5.960464e-08, 1.525879e-05, 0.00390625, 1.0))
         + tmpvar_27)));
      };
      if ((shadow_factor_19 < 1.0)) {
        shadow_factor_19 = mix (1.0, shadow_factor_19, _AE_DIRECTIONAL_LIGHT0_SHADOW_STRENGTH_);
      };
      tmpvar_18 = shadow_factor_19;
    };
  };
  float tmpvar_32;
  float tmpvar_33;
  tmpvar_33 = (min (abs(
    (tmpvar_13.x / tmpvar_13.z)
  ), 1.0) / max (abs(
    (tmpvar_13.x / tmpvar_13.z)
  ), 1.0));
  float tmpvar_34;
  tmpvar_34 = (tmpvar_33 * tmpvar_33);
  tmpvar_34 = (((
    ((((
      ((((-0.01213232 * tmpvar_34) + 0.05368138) * tmpvar_34) - 0.1173503)
     * tmpvar_34) + 0.1938925) * tmpvar_34) - 0.3326756)
   * tmpvar_34) + 0.9999793) * tmpvar_33);
  tmpvar_34 = (tmpvar_34 + (float(
    (abs((tmpvar_13.x / tmpvar_13.z)) > 1.0)
  ) * (
    (tmpvar_34 * -2.0)
   + 1.570796)));
  tmpvar_32 = (tmpvar_34 * sign((tmpvar_13.x / tmpvar_13.z)));
  if ((abs(tmpvar_13.z) > (1e-08 * abs(tmpvar_13.x)))) {
    if ((tmpvar_13.z < 0.0)) {
      if ((tmpvar_13.x >= 0.0)) {
        tmpvar_32 += 3.141593;
      } else {
        tmpvar_32 = (tmpvar_32 - 3.141593);
      };
    };
  } else {
    tmpvar_32 = (sign(tmpvar_13.x) * 1.570796);
  };
  vec2 tmpvar_35;
  tmpvar_35.x = (((tmpvar_32 / 3.141593) + 1.0) * 0.5);
  tmpvar_35.y = ((1.570796 - (
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
  vec2 tmpvar_36;
  tmpvar_36.x = (float(mod ((tmpvar_35.x + u_IBLOffset), 1.0)));
  tmpvar_36.y = tmpvar_35.y;
  vec3 tmpvar_37;
  tmpvar_37 = pow (texture2D (u_IrradianceTex, tmpvar_36).xyz, vec3(2.2, 2.2, 2.2));
  vec2 rC_38;
  vec2 rC_39;
  vec4 color2_40;
  vec4 color1_41;
  highp vec3 I_42;
  I_42 = -(tmpvar_8);
  vec3 tmpvar_43;
  tmpvar_43 = normalize((I_42 - (2.0 * 
    (dot (tmpvar_13, I_42) * tmpvar_13)
  )));
  float tmpvar_44;
  float tmpvar_45;
  tmpvar_45 = (min (abs(
    (tmpvar_43.x / tmpvar_43.z)
  ), 1.0) / max (abs(
    (tmpvar_43.x / tmpvar_43.z)
  ), 1.0));
  float tmpvar_46;
  tmpvar_46 = (tmpvar_45 * tmpvar_45);
  tmpvar_46 = (((
    ((((
      ((((-0.01213232 * tmpvar_46) + 0.05368138) * tmpvar_46) - 0.1173503)
     * tmpvar_46) + 0.1938925) * tmpvar_46) - 0.3326756)
   * tmpvar_46) + 0.9999793) * tmpvar_45);
  tmpvar_46 = (tmpvar_46 + (float(
    (abs((tmpvar_43.x / tmpvar_43.z)) > 1.0)
  ) * (
    (tmpvar_46 * -2.0)
   + 1.570796)));
  tmpvar_44 = (tmpvar_46 * sign((tmpvar_43.x / tmpvar_43.z)));
  if ((abs(tmpvar_43.z) > (1e-08 * abs(tmpvar_43.x)))) {
    if ((tmpvar_43.z < 0.0)) {
      if ((tmpvar_43.x >= 0.0)) {
        tmpvar_44 += 3.141593;
      } else {
        tmpvar_44 = (tmpvar_44 - 3.141593);
      };
    };
  } else {
    tmpvar_44 = (sign(tmpvar_43.x) * 1.570796);
  };
  vec2 tmpvar_47;
  tmpvar_47.x = (((tmpvar_44 / 3.141593) + 1.0) * 0.5);
  tmpvar_47.y = ((1.570796 - (
    sign(tmpvar_43.y)
   * 
    (1.570796 - (sqrt((1.0 - 
      abs(tmpvar_43.y)
    )) * (1.570796 + (
      abs(tmpvar_43.y)
     * 
      (-0.2146018 + (abs(tmpvar_43.y) * (0.08656672 + (
        abs(tmpvar_43.y)
       * -0.03102955))))
    ))))
  )) / 3.141593);
  float tmpvar_48;
  tmpvar_48 = min (tmpvar_10, 0.99);
  float tmpvar_49;
  tmpvar_49 = min (7.0, (floor(
    (tmpvar_48 * 7.0)
  ) + 1.0));
  float tmpvar_50;
  tmpvar_50 = max (0.0, (tmpvar_49 - 1.0));
  float tmpvar_51;
  tmpvar_51 = exp2(tmpvar_49);
  float tmpvar_52;
  tmpvar_52 = (tmpvar_51 * 2.0);
  rC_39.x = ((float(mod ((tmpvar_47.x + u_IBLOffset), 1.0))) / tmpvar_51);
  rC_39.y = (((tmpvar_47.y / tmpvar_52) + 1.0) - (2.0 / tmpvar_52));
  vec4 tmpvar_53;
  tmpvar_53 = texture2D (u_RadianceTex, rC_39);
  color1_41.w = tmpvar_53.w;
  color1_41.xyz = (tmpvar_53.xyz / tmpvar_53.w);
  color1_41.xyz = (color1_41.xyz * (pow (
    mix (1.2, 1.5, tmpvar_53.w)
  , 
    (tmpvar_53.w * 32.0)
  ) - 1.2));
  float tmpvar_54;
  tmpvar_54 = exp2(tmpvar_50);
  float tmpvar_55;
  tmpvar_55 = (tmpvar_54 * 2.0);
  rC_38.x = ((float(mod ((tmpvar_47.x + u_IBLOffset), 1.0))) / tmpvar_54);
  rC_38.y = (((tmpvar_47.y / tmpvar_55) + 1.0) - (2.0 / tmpvar_55));
  vec4 tmpvar_56;
  tmpvar_56 = texture2D (u_RadianceTex, rC_38);
  color2_40.w = tmpvar_56.w;
  color2_40.xyz = (tmpvar_56.xyz / tmpvar_56.w);
  color2_40.xyz = (color2_40.xyz * (pow (
    mix (1.2, 1.5, tmpvar_56.w)
  , 
    (tmpvar_56.w * 32.0)
  ) - 1.2));
  tmpvar_2[0]=tmpvar_14[0];
  tmpvar_3[0]=tmpvar_15[0];
  tmpvar_4[0]=tmpvar_16[0];
  vec3 tmpvar_57;
  tmpvar_57 = mix (vec3(0.04, 0.04, 0.04), tmpvar_9, u_Metallic);
  highp vec3 tmpvar_58;
  tmpvar_58 = tmpvar_14[0];
  float tmpvar_59;
  tmpvar_59 = dot (tmpvar_13, tmpvar_58);
  float tmpvar_60;
  tmpvar_60 = dot (tmpvar_13, tmpvar_8);
  highp float tmpvar_61;
  tmpvar_61 = dot (tmpvar_58, tmpvar_8);
  highp float tmpvar_62;
  tmpvar_62 = inversesqrt((2.0 + (2.0 * tmpvar_61)));
  float tmpvar_63;
  tmpvar_63 = clamp (((tmpvar_59 + tmpvar_60) * tmpvar_62), 0.0, 1.0);
  float tmpvar_64;
  tmpvar_64 = clamp (tmpvar_59, 0.0, 1.0);
  float tmpvar_65;
  tmpvar_65 = clamp (abs(tmpvar_60), 0.0, 1.0);
  float tmpvar_66;
  tmpvar_66 = (tmpvar_10 * tmpvar_10);
  float tmpvar_67;
  tmpvar_67 = (tmpvar_66 * tmpvar_66);
  float tmpvar_68;
  tmpvar_68 = (((
    (tmpvar_63 * tmpvar_67)
   - tmpvar_63) * tmpvar_63) + 1.0);
  float tmpvar_69;
  tmpvar_69 = (tmpvar_10 * tmpvar_10);
  highp float tmpvar_70;
  tmpvar_70 = pow ((1.0 - clamp (
    (tmpvar_62 + (tmpvar_62 * tmpvar_61))
  , 0.0, 1.0)), 5.0);
  vec3 result_71;
  float tmpvar_72;
  tmpvar_72 = min (max (dot (tmpvar_13, tmpvar_8), 0.0), 1.0);
  vec3 tmpvar_73;
  tmpvar_73 = mix (vec3(0.04, 0.04, 0.04), tmpvar_9, u_Metallic);
  vec3 tmpvar_74;
  tmpvar_74 = (tmpvar_73 + ((
    max (vec3((0.99 - tmpvar_10)), tmpvar_73)
   - tmpvar_73) * pow (
    (1.0 - tmpvar_72)
  , 5.0)));
  float tmpvar_75;
  tmpvar_75 = (1.05 - tmpvar_72);
  result_71 = (((
    (((vec3(1.0, 1.0, 1.0) - tmpvar_74) * (1.0 - u_Metallic)) * tmpvar_37)
   * tmpvar_9) + (
    (tmpvar_74 * pow ((mix (color2_40.xyz, color1_41.xyz, vec3(
      min (max (((tmpvar_48 * 7.0) - tmpvar_50), 0.0), 1.0)
    )) * vec3(1.57, 1.57, 1.57)), vec3(2.2, 2.2, 2.2)))
   * 
    mix (vec3(min (1.0, (tmpvar_75 * tmpvar_75))), tmpvar_57, u_Metallic)
  )) * max (vec3(1.0, 1.0, 1.0), (
    (((2.0404 * tmpvar_9) - 0.3324) + ((-4.7951 * tmpvar_9) + 0.6417))
   + 
    ((2.7552 * tmpvar_9) + 0.6903)
  )));
  vec3 color_76;
  color_76 = ((result_71 / (result_71 + 0.187)) * 1.035);
  result_71 = color_76;
  final_color_1 = (((
    ((((
      (tmpvar_9 - (tmpvar_9 * vec3(u_Metallic)))
     * 0.3183099) + (
      ((tmpvar_67 / ((3.141593 * tmpvar_68) * tmpvar_68)) * (0.5 / ((
        (tmpvar_64 * ((tmpvar_65 * (1.0 - tmpvar_69)) + tmpvar_69))
       + 
        (tmpvar_65 * ((tmpvar_64 * (1.0 - tmpvar_69)) + tmpvar_69))
      ) + 1e-05)))
     * 
      ((clamp ((50.0 * tmpvar_57.y), 0.0, 1.0) * tmpvar_70) + ((1.0 - tmpvar_70) * tmpvar_57))
    )) * tmpvar_64) * tmpvar_16[0])
   * tmpvar_15[0]) * vec3(tmpvar_18)) + color_76);
  vec4 tmpvar_77;
  tmpvar_77.xyz = final_color_1;
  tmpvar_77.w = tmpvar_11;
  vec4 tmpvar_78;
  vec4 color_79;
  color_79.w = tmpvar_77.w;
  color_79.xyz = pow (final_color_1, vec3(0.4545454, 0.4545454, 0.4545454));
  color_79.xyz = clamp (color_79.xyz, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));
  tmpvar_78 = color_79;
  gl_FragColor = tmpvar_78;
}


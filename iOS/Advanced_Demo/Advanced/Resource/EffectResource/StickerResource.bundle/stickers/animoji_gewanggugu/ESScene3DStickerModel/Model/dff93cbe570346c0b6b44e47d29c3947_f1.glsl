
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
uniform sampler2D u_BaseColor;
uniform float u_Metallic;
uniform float u_Roughness;
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
  vec3 tmpvar_10;
  tmpvar_10 = normalize((tmpvar_6 * (
    (texture2D (u_NormalTex, tmpvar_5).xyz * 2.0)
   - 1.0)));
  vec4 tmpvar_11;
  tmpvar_11 = texture2D (u_BaseColor, tmpvar_5);
  if ((tmpvar_11.w < u_Culloff)) {
    discard;
  };
  tmpvar_8 = pow (tmpvar_11.xyz, vec3(2.2, 2.2, 2.2));
  tmpvar_9 = (u_Translucency * tmpvar_11.w);
  vec3 tmpvar_12[1];
  vec3 tmpvar_13[1];
  float tmpvar_14[1];
  tmpvar_12[0]=tmpvar_2[0];
  tmpvar_13[0]=tmpvar_3[0];
  tmpvar_14[0]=tmpvar_4[0];
  tmpvar_12[0] = normalize(-(_AE_DIRECTIONAL_LIGHTS_DIRECTION_[0]));
  tmpvar_13[0] = _AE_DIRECTIONAL_LIGHTS_COLOR_[0];
  tmpvar_14[0] = _AE_DIRECTIONAL_LIGHTS_INTENSITY_[0];
  vec3 l_15;
  l_15 = tmpvar_12[0];
  float tmpvar_16;
  float shadow_factor_17;
  float bias_18;
  vec3 shadow_coord_19;
  if ((_AE_DIRECTIONAL_LIGHT0_SHADOW_ENABLED_ < 1.0)) {
    tmpvar_16 = 1.0;
  } else {
    float tmpvar_20;
    tmpvar_20 = max (dot (tmpvar_10, l_15), 0.0);
    vec4 tmpvar_21;
    tmpvar_21.w = 1.0;
    tmpvar_21.xyz = g_vary_WorldPosition;
    vec4 tmpvar_22;
    tmpvar_22 = (_AE_DIRECTIONAL_LIGHT0_SHADOW_MATRIX_ * tmpvar_21);
    vec3 tmpvar_23;
    tmpvar_23 = (tmpvar_22.xyz / tmpvar_22.w);
    shadow_coord_19 = tmpvar_23;
    if ((((
      (((tmpvar_23.x < 0.0) || (1.0 < tmpvar_23.x)) || (tmpvar_23.y < 0.0))
     || 
      (1.0 < tmpvar_23.y)
    ) || (tmpvar_23.z < 0.0)) || (1.0 < tmpvar_23.z))) {
      tmpvar_16 = 1.0;
    } else {
      float tmpvar_24;
      tmpvar_24 = (1.570796 - (sign(tmpvar_20) * (1.570796 - 
        (sqrt((1.0 - abs(tmpvar_20))) * (1.570796 + (abs(tmpvar_20) * (-0.2146018 + 
          (abs(tmpvar_20) * (0.08656672 + (abs(tmpvar_20) * -0.03102955)))
        ))))
      )));
      float tmpvar_25;
      tmpvar_25 = clamp ((_AE_DIRECTIONAL_LIGHT0_SHADOW_BIAS_ * (
        sin(tmpvar_24)
       / 
        cos(tmpvar_24)
      )), 0.0, 1.0);
      bias_18 = tmpvar_25;
      shadow_factor_17 = 0.0;
      if ((0.0 < _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFT_)) {
        vec2 inv_tex_size_27;
        float shadow_sum_28;
        vec2 sample_offsets_29[9];
        sample_offsets_29[0] = vec2(-1.0, -1.0);
        sample_offsets_29[1] = vec2(0.0, -1.0);
        sample_offsets_29[2] = vec2(1.0, -1.0);
        sample_offsets_29[3] = vec2(-1.0, 0.0);
        sample_offsets_29[4] = vec2(0.0, 0.0);
        sample_offsets_29[5] = vec2(1.0, 0.0);
        sample_offsets_29[6] = vec2(-1.0, 1.0);
        sample_offsets_29[7] = vec2(0.0, 1.0);
        sample_offsets_29[8] = vec2(1.0, 1.0);
        shadow_sum_28 = 0.0;
        inv_tex_size_27 = (1.0/(_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_SIZE_));
        for (highp int i_26 = 0; i_26 < 9; i_26++) {
          shadow_sum_28 = (shadow_sum_28 + float((shadow_coord_19.z < 
            (dot (texture2D (_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_, (shadow_coord_19.xy + (
              (sample_offsets_29[i_26] * _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFTNESS_)
             * inv_tex_size_27))), vec4(5.960464e-08, 1.525879e-05, 0.00390625, 1.0)) + bias_18)
          )));
        };
        shadow_factor_17 = (shadow_sum_28 / 9.0);
      } else {
        shadow_factor_17 = float((tmpvar_23.z < (
          dot (texture2D (_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_, tmpvar_23.xy), vec4(5.960464e-08, 1.525879e-05, 0.00390625, 1.0))
         + tmpvar_25)));
      };
      if ((shadow_factor_17 < 1.0)) {
        shadow_factor_17 = mix (1.0, shadow_factor_17, _AE_DIRECTIONAL_LIGHT0_SHADOW_STRENGTH_);
      };
      tmpvar_16 = shadow_factor_17;
    };
  };
  float tmpvar_30;
  float tmpvar_31;
  tmpvar_31 = (min (abs(
    (tmpvar_10.x / tmpvar_10.z)
  ), 1.0) / max (abs(
    (tmpvar_10.x / tmpvar_10.z)
  ), 1.0));
  float tmpvar_32;
  tmpvar_32 = (tmpvar_31 * tmpvar_31);
  tmpvar_32 = (((
    ((((
      ((((-0.01213232 * tmpvar_32) + 0.05368138) * tmpvar_32) - 0.1173503)
     * tmpvar_32) + 0.1938925) * tmpvar_32) - 0.3326756)
   * tmpvar_32) + 0.9999793) * tmpvar_31);
  tmpvar_32 = (tmpvar_32 + (float(
    (abs((tmpvar_10.x / tmpvar_10.z)) > 1.0)
  ) * (
    (tmpvar_32 * -2.0)
   + 1.570796)));
  tmpvar_30 = (tmpvar_32 * sign((tmpvar_10.x / tmpvar_10.z)));
  if ((abs(tmpvar_10.z) > (1e-08 * abs(tmpvar_10.x)))) {
    if ((tmpvar_10.z < 0.0)) {
      if ((tmpvar_10.x >= 0.0)) {
        tmpvar_30 += 3.141593;
      } else {
        tmpvar_30 = (tmpvar_30 - 3.141593);
      };
    };
  } else {
    tmpvar_30 = (sign(tmpvar_10.x) * 1.570796);
  };
  vec2 tmpvar_33;
  tmpvar_33.x = (((tmpvar_30 / 3.141593) + 1.0) * 0.5);
  tmpvar_33.y = ((1.570796 - (
    sign(tmpvar_10.y)
   * 
    (1.570796 - (sqrt((1.0 - 
      abs(tmpvar_10.y)
    )) * (1.570796 + (
      abs(tmpvar_10.y)
     * 
      (-0.2146018 + (abs(tmpvar_10.y) * (0.08656672 + (
        abs(tmpvar_10.y)
       * -0.03102955))))
    ))))
  )) / 3.141593);
  vec2 tmpvar_34;
  tmpvar_34.x = (float(mod ((tmpvar_33.x + u_IBLOffset), 1.0)));
  tmpvar_34.y = tmpvar_33.y;
  vec3 tmpvar_35;
  tmpvar_35 = pow (texture2D (u_IrradianceTex, tmpvar_34).xyz, vec3(2.2, 2.2, 2.2));
  vec2 rC_36;
  vec2 rC_37;
  vec4 color2_38;
  vec4 color1_39;
  vec3 I_40;
  I_40 = -(tmpvar_7);
  vec3 tmpvar_41;
  tmpvar_41 = normalize((I_40 - (2.0 * 
    (dot (tmpvar_10, I_40) * tmpvar_10)
  )));
  float tmpvar_42;
  float tmpvar_43;
  tmpvar_43 = (min (abs(
    (tmpvar_41.x / tmpvar_41.z)
  ), 1.0) / max (abs(
    (tmpvar_41.x / tmpvar_41.z)
  ), 1.0));
  float tmpvar_44;
  tmpvar_44 = (tmpvar_43 * tmpvar_43);
  tmpvar_44 = (((
    ((((
      ((((-0.01213232 * tmpvar_44) + 0.05368138) * tmpvar_44) - 0.1173503)
     * tmpvar_44) + 0.1938925) * tmpvar_44) - 0.3326756)
   * tmpvar_44) + 0.9999793) * tmpvar_43);
  tmpvar_44 = (tmpvar_44 + (float(
    (abs((tmpvar_41.x / tmpvar_41.z)) > 1.0)
  ) * (
    (tmpvar_44 * -2.0)
   + 1.570796)));
  tmpvar_42 = (tmpvar_44 * sign((tmpvar_41.x / tmpvar_41.z)));
  if ((abs(tmpvar_41.z) > (1e-08 * abs(tmpvar_41.x)))) {
    if ((tmpvar_41.z < 0.0)) {
      if ((tmpvar_41.x >= 0.0)) {
        tmpvar_42 += 3.141593;
      } else {
        tmpvar_42 = (tmpvar_42 - 3.141593);
      };
    };
  } else {
    tmpvar_42 = (sign(tmpvar_41.x) * 1.570796);
  };
  vec2 tmpvar_45;
  tmpvar_45.x = (((tmpvar_42 / 3.141593) + 1.0) * 0.5);
  tmpvar_45.y = ((1.570796 - (
    sign(tmpvar_41.y)
   * 
    (1.570796 - (sqrt((1.0 - 
      abs(tmpvar_41.y)
    )) * (1.570796 + (
      abs(tmpvar_41.y)
     * 
      (-0.2146018 + (abs(tmpvar_41.y) * (0.08656672 + (
        abs(tmpvar_41.y)
       * -0.03102955))))
    ))))
  )) / 3.141593);
  float tmpvar_46;
  tmpvar_46 = min (u_Roughness, 0.99);
  float tmpvar_47;
  tmpvar_47 = min (7.0, (floor(
    (tmpvar_46 * 7.0)
  ) + 1.0));
  float tmpvar_48;
  tmpvar_48 = max (0.0, (tmpvar_47 - 1.0));
  float tmpvar_49;
  tmpvar_49 = exp2(tmpvar_47);
  float tmpvar_50;
  tmpvar_50 = (tmpvar_49 * 2.0);
  rC_37.x = ((float(mod ((tmpvar_45.x + u_IBLOffset), 1.0))) / tmpvar_49);
  rC_37.y = (((tmpvar_45.y / tmpvar_50) + 1.0) - (2.0 / tmpvar_50));
  vec4 tmpvar_51;
  tmpvar_51 = texture2D (u_RadianceTex, rC_37);
  color1_39.w = tmpvar_51.w;
  color1_39.xyz = (tmpvar_51.xyz / tmpvar_51.w);
  color1_39.xyz = (color1_39.xyz * (pow (
    mix (1.2, 1.5, tmpvar_51.w)
  , 
    (tmpvar_51.w * 32.0)
  ) - 1.2));
  float tmpvar_52;
  tmpvar_52 = exp2(tmpvar_48);
  float tmpvar_53;
  tmpvar_53 = (tmpvar_52 * 2.0);
  rC_36.x = ((float(mod ((tmpvar_45.x + u_IBLOffset), 1.0))) / tmpvar_52);
  rC_36.y = (((tmpvar_45.y / tmpvar_53) + 1.0) - (2.0 / tmpvar_53));
  vec4 tmpvar_54;
  tmpvar_54 = texture2D (u_RadianceTex, rC_36);
  color2_38.w = tmpvar_54.w;
  color2_38.xyz = (tmpvar_54.xyz / tmpvar_54.w);
  color2_38.xyz = (color2_38.xyz * (pow (
    mix (1.2, 1.5, tmpvar_54.w)
  , 
    (tmpvar_54.w * 32.0)
  ) - 1.2));
  tmpvar_2[0]=tmpvar_12[0];
  tmpvar_3[0]=tmpvar_13[0];
  tmpvar_4[0]=tmpvar_14[0];
  vec3 tmpvar_55;
  tmpvar_55 = mix (vec3((0.08 * u_Specular)), tmpvar_8, u_Metallic);
  vec3 tmpvar_56;
  tmpvar_56 = tmpvar_12[0];
  float tmpvar_57;
  tmpvar_57 = dot (tmpvar_10, tmpvar_56);
  float tmpvar_58;
  tmpvar_58 = dot (tmpvar_10, tmpvar_7);
  float tmpvar_59;
  tmpvar_59 = dot (tmpvar_56, tmpvar_7);
  float tmpvar_60;
  tmpvar_60 = inversesqrt((2.0 + (2.0 * tmpvar_59)));
  float tmpvar_61;
  tmpvar_61 = clamp (((tmpvar_57 + tmpvar_58) * tmpvar_60), 0.0, 1.0);
  float tmpvar_62;
  tmpvar_62 = clamp (tmpvar_57, 0.0, 1.0);
  float tmpvar_63;
  tmpvar_63 = clamp (abs(tmpvar_58), 0.0, 1.0);
  float tmpvar_64;
  tmpvar_64 = (u_Roughness * u_Roughness);
  float tmpvar_65;
  tmpvar_65 = (tmpvar_64 * tmpvar_64);
  float tmpvar_66;
  tmpvar_66 = (((
    (tmpvar_61 * tmpvar_65)
   - tmpvar_61) * tmpvar_61) + 1.0);
  float tmpvar_67;
  tmpvar_67 = pow ((1.0 - clamp (
    (tmpvar_60 + (tmpvar_60 * tmpvar_59))
  , 0.0, 1.0)), 5.0);
  final_color_1 = (((
    ((((
      (tmpvar_8 - (tmpvar_8 * vec3(u_Metallic)))
     * 0.3183099) + (
      ((tmpvar_65 / ((3.141593 * tmpvar_66) * tmpvar_66)) * (0.5 / ((
        (tmpvar_62 * ((tmpvar_63 * (1.0 - tmpvar_64)) + tmpvar_64))
       + 
        (tmpvar_63 * ((tmpvar_62 * (1.0 - tmpvar_64)) + tmpvar_64))
      ) + 1e-05)))
     * 
      ((clamp ((50.0 * tmpvar_55.y), 0.0, 1.0) * tmpvar_67) + ((1.0 - tmpvar_67) * tmpvar_55))
    )) * tmpvar_62) * tmpvar_14[0])
   * tmpvar_13[0]) * vec3(tmpvar_16)) + u_EmissiveColor);
  vec3 result_68;
  float tmpvar_69;
  tmpvar_69 = min (max (dot (tmpvar_10, tmpvar_7), 0.0), 1.0);
  vec3 tmpvar_70;
  tmpvar_70 = mix (vec3(0.04, 0.04, 0.04), tmpvar_8, u_Metallic);
  vec3 tmpvar_71;
  tmpvar_71 = (tmpvar_70 + ((
    max (vec3((0.99 - u_Roughness)), tmpvar_70)
   - tmpvar_70) * pow (
    (1.0 - tmpvar_69)
  , 5.0)));
  float tmpvar_72;
  tmpvar_72 = (1.05 - tmpvar_69);
  result_68 = (((
    (((vec3(1.0, 1.0, 1.0) - tmpvar_71) * (1.0 - u_Metallic)) * tmpvar_35)
   * tmpvar_8) + (
    (tmpvar_71 * pow ((mix (color2_38.xyz, color1_39.xyz, vec3(
      min (max (((tmpvar_46 * 7.0) - tmpvar_48), 0.0), 1.0)
    )) * vec3(1.57, 1.57, 1.57)), vec3(2.2, 2.2, 2.2)))
   * 
    mix (vec3(min (1.0, (tmpvar_72 * tmpvar_72))), tmpvar_55, u_Metallic)
  )) * max (vec3(1.0, 1.0, 1.0), (
    (((2.0404 * tmpvar_8) - 0.3324) + ((-4.7951 * tmpvar_8) + 0.6417))
   + 
    ((2.7552 * tmpvar_8) + 0.6903)
  )));
  vec3 color_73;
  color_73 = (result_68 * u_IBLIntensity);
  color_73 = ((color_73 / (color_73 + 0.187)) * 1.035);
  result_68 = color_73;
  final_color_1 = (final_color_1 + color_73);
  vec4 tmpvar_74;
  tmpvar_74.xyz = final_color_1;
  tmpvar_74.w = tmpvar_9;
  vec4 tmpvar_75;
  vec4 color_76;
  color_76.w = tmpvar_74.w;
  color_76.xyz = pow (final_color_1, vec3(0.4545454, 0.4545454, 0.4545454));
  color_76.xyz = clamp (color_76.xyz, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));
  tmpvar_75 = color_76;
  gl_FragColor = tmpvar_75;
}


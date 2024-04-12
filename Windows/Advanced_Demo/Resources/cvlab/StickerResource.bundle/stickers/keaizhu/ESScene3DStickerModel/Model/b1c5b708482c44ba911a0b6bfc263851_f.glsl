
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
uniform float u_AmbientOcclusion;
uniform float u_Specular;
uniform vec3 u_EmissiveColor;
uniform float u_Translucency;
uniform float u_Culloff;
uniform float u_IBLOffset;
uniform float u_IBLIntensity;
uniform vec3 g_unif_CameraWorldPos;
varying vec3 g_vary_WorldPosition;
varying vec3 g_vary_WorldNormal;
varying vec2 g_vary_Texcoord;
void main ()
{
  vec3 final_color_1;
  vec3 tmpvar_2[1];
  vec3 tmpvar_3[1];
  float tmpvar_4[1];
  vec2 tmpvar_5;
  vec3 tmpvar_6;
  tmpvar_6 = normalize(g_vary_WorldNormal);
  vec3 tmpvar_7;
  tmpvar_7 = normalize((g_unif_CameraWorldPos - g_vary_WorldPosition));
  tmpvar_5.x = g_vary_Texcoord.x;
  tmpvar_5.y = (1.0 - g_vary_Texcoord.y);
  vec3 tmpvar_8;
  float tmpvar_9;
  vec4 tmpvar_10;
  tmpvar_10 = texture2D (u_BaseColor, tmpvar_5);
  if ((tmpvar_10.w < u_Culloff)) {
    discard;
  };
  tmpvar_8 = pow (tmpvar_10.xyz, vec3(2.2, 2.2, 2.2));
  tmpvar_9 = (u_Translucency * tmpvar_10.w);
  vec3 tmpvar_11[1];
  vec3 tmpvar_12[1];
  float tmpvar_13[1];
  tmpvar_11[0]=tmpvar_2[0];
  tmpvar_12[0]=tmpvar_3[0];
  tmpvar_13[0]=tmpvar_4[0];
  tmpvar_11[0] = normalize(-(_AE_DIRECTIONAL_LIGHTS_DIRECTION_[0]));
  tmpvar_12[0] = _AE_DIRECTIONAL_LIGHTS_COLOR_[0];
  tmpvar_13[0] = _AE_DIRECTIONAL_LIGHTS_INTENSITY_[0];
  vec3 l_14;
  l_14 = tmpvar_11[0];
  float tmpvar_15;
  float shadow_factor_16;
  float bias_17;
  vec3 shadow_coord_18;
  if ((_AE_DIRECTIONAL_LIGHT0_SHADOW_ENABLED_ < 1.0)) {
    tmpvar_15 = 1.0;
  } else {
    float tmpvar_19;
    tmpvar_19 = max (dot (tmpvar_6, l_14), 0.0);
    vec4 tmpvar_20;
    tmpvar_20.w = 1.0;
    tmpvar_20.xyz = g_vary_WorldPosition;
    vec4 tmpvar_21;
    tmpvar_21 = (_AE_DIRECTIONAL_LIGHT0_SHADOW_MATRIX_ * tmpvar_20);
    vec3 tmpvar_22;
    tmpvar_22 = (tmpvar_21.xyz / tmpvar_21.w);
    shadow_coord_18 = tmpvar_22;
    if ((((
      (((tmpvar_22.x < 0.0) || (1.0 < tmpvar_22.x)) || (tmpvar_22.y < 0.0))
     || 
      (1.0 < tmpvar_22.y)
    ) || (tmpvar_22.z < 0.0)) || (1.0 < tmpvar_22.z))) {
      tmpvar_15 = 1.0;
    } else {
      float tmpvar_23;
      tmpvar_23 = (1.570796 - (sign(tmpvar_19) * (1.570796 - 
        (sqrt((1.0 - abs(tmpvar_19))) * (1.570796 + (abs(tmpvar_19) * (-0.2146018 + 
          (abs(tmpvar_19) * (0.08656672 + (abs(tmpvar_19) * -0.03102955)))
        ))))
      )));
      float tmpvar_24;
      tmpvar_24 = clamp ((_AE_DIRECTIONAL_LIGHT0_SHADOW_BIAS_ * (
        sin(tmpvar_23)
       / 
        cos(tmpvar_23)
      )), 0.0, 1.0);
      bias_17 = tmpvar_24;
      shadow_factor_16 = 0.0;
      if ((0.0 < _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFT_)) {
        vec2 inv_tex_size_26;
        float shadow_sum_27;
        vec2 sample_offsets_28[9];
        sample_offsets_28[0] = vec2(-1.0, -1.0);
        sample_offsets_28[1] = vec2(0.0, -1.0);
        sample_offsets_28[2] = vec2(1.0, -1.0);
        sample_offsets_28[3] = vec2(-1.0, 0.0);
        sample_offsets_28[4] = vec2(0.0, 0.0);
        sample_offsets_28[5] = vec2(1.0, 0.0);
        sample_offsets_28[6] = vec2(-1.0, 1.0);
        sample_offsets_28[7] = vec2(0.0, 1.0);
        sample_offsets_28[8] = vec2(1.0, 1.0);
        shadow_sum_27 = 0.0;
        inv_tex_size_26 = (1.0/(_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_SIZE_));
        for (highp int i_25 = 0; i_25 < 9; i_25++) {
          shadow_sum_27 = (shadow_sum_27 + float((shadow_coord_18.z < 
            (dot (texture2D (_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_, (shadow_coord_18.xy + (
              (sample_offsets_28[i_25] * _AE_DIRECTIONAL_LIGHT0_SHADOW_SOFTNESS_)
             * inv_tex_size_26))), vec4(5.960464e-08, 1.525879e-05, 0.00390625, 1.0)) + bias_17)
          )));
        };
        shadow_factor_16 = (shadow_sum_27 / 9.0);
      } else {
        shadow_factor_16 = float((tmpvar_22.z < (
          dot (texture2D (_AE_DIRECTIONAL_LIGHT0_SHADOW_TEXTURE_, tmpvar_22.xy), vec4(5.960464e-08, 1.525879e-05, 0.00390625, 1.0))
         + tmpvar_24)));
      };
      if ((shadow_factor_16 < 1.0)) {
        shadow_factor_16 = mix (1.0, shadow_factor_16, _AE_DIRECTIONAL_LIGHT0_SHADOW_STRENGTH_);
      };
      tmpvar_15 = shadow_factor_16;
    };
  };
  float tmpvar_29;
  float tmpvar_30;
  tmpvar_30 = (min (abs(
    (tmpvar_6.x / tmpvar_6.z)
  ), 1.0) / max (abs(
    (tmpvar_6.x / tmpvar_6.z)
  ), 1.0));
  float tmpvar_31;
  tmpvar_31 = (tmpvar_30 * tmpvar_30);
  tmpvar_31 = (((
    ((((
      ((((-0.01213232 * tmpvar_31) + 0.05368138) * tmpvar_31) - 0.1173503)
     * tmpvar_31) + 0.1938925) * tmpvar_31) - 0.3326756)
   * tmpvar_31) + 0.9999793) * tmpvar_30);
  tmpvar_31 = (tmpvar_31 + (float(
    (abs((tmpvar_6.x / tmpvar_6.z)) > 1.0)
  ) * (
    (tmpvar_31 * -2.0)
   + 1.570796)));
  tmpvar_29 = (tmpvar_31 * sign((tmpvar_6.x / tmpvar_6.z)));
  if ((abs(tmpvar_6.z) > (1e-08 * abs(tmpvar_6.x)))) {
    if ((tmpvar_6.z < 0.0)) {
      if ((tmpvar_6.x >= 0.0)) {
        tmpvar_29 += 3.141593;
      } else {
        tmpvar_29 = (tmpvar_29 - 3.141593);
      };
    };
  } else {
    tmpvar_29 = (sign(tmpvar_6.x) * 1.570796);
  };
  vec2 tmpvar_32;
  tmpvar_32.x = (((tmpvar_29 / 3.141593) + 1.0) * 0.5);
  tmpvar_32.y = ((1.570796 - (
    sign(tmpvar_6.y)
   * 
    (1.570796 - (sqrt((1.0 - 
      abs(tmpvar_6.y)
    )) * (1.570796 + (
      abs(tmpvar_6.y)
     * 
      (-0.2146018 + (abs(tmpvar_6.y) * (0.08656672 + (
        abs(tmpvar_6.y)
       * -0.03102955))))
    ))))
  )) / 3.141593);
  vec2 tmpvar_33;
  tmpvar_33.x = (float(mod ((tmpvar_32.x + u_IBLOffset), 1.0)));
  tmpvar_33.y = tmpvar_32.y;
  vec3 tmpvar_34;
  tmpvar_34 = pow (texture2D (u_IrradianceTex, tmpvar_33).xyz, vec3(2.2, 2.2, 2.2));
  vec2 rC_35;
  vec2 rC_36;
  vec4 color2_37;
  vec4 color1_38;
  vec3 I_39;
  I_39 = -(tmpvar_7);
  vec3 tmpvar_40;
  tmpvar_40 = normalize((I_39 - (2.0 * 
    (dot (tmpvar_6, I_39) * tmpvar_6)
  )));
  float tmpvar_41;
  float tmpvar_42;
  tmpvar_42 = (min (abs(
    (tmpvar_40.x / tmpvar_40.z)
  ), 1.0) / max (abs(
    (tmpvar_40.x / tmpvar_40.z)
  ), 1.0));
  float tmpvar_43;
  tmpvar_43 = (tmpvar_42 * tmpvar_42);
  tmpvar_43 = (((
    ((((
      ((((-0.01213232 * tmpvar_43) + 0.05368138) * tmpvar_43) - 0.1173503)
     * tmpvar_43) + 0.1938925) * tmpvar_43) - 0.3326756)
   * tmpvar_43) + 0.9999793) * tmpvar_42);
  tmpvar_43 = (tmpvar_43 + (float(
    (abs((tmpvar_40.x / tmpvar_40.z)) > 1.0)
  ) * (
    (tmpvar_43 * -2.0)
   + 1.570796)));
  tmpvar_41 = (tmpvar_43 * sign((tmpvar_40.x / tmpvar_40.z)));
  if ((abs(tmpvar_40.z) > (1e-08 * abs(tmpvar_40.x)))) {
    if ((tmpvar_40.z < 0.0)) {
      if ((tmpvar_40.x >= 0.0)) {
        tmpvar_41 += 3.141593;
      } else {
        tmpvar_41 = (tmpvar_41 - 3.141593);
      };
    };
  } else {
    tmpvar_41 = (sign(tmpvar_40.x) * 1.570796);
  };
  vec2 tmpvar_44;
  tmpvar_44.x = (((tmpvar_41 / 3.141593) + 1.0) * 0.5);
  tmpvar_44.y = ((1.570796 - (
    sign(tmpvar_40.y)
   * 
    (1.570796 - (sqrt((1.0 - 
      abs(tmpvar_40.y)
    )) * (1.570796 + (
      abs(tmpvar_40.y)
     * 
      (-0.2146018 + (abs(tmpvar_40.y) * (0.08656672 + (
        abs(tmpvar_40.y)
       * -0.03102955))))
    ))))
  )) / 3.141593);
  float tmpvar_45;
  tmpvar_45 = min (u_Roughness, 0.99);
  float tmpvar_46;
  tmpvar_46 = min (9.0, (floor(
    (tmpvar_45 * 9.0)
  ) + 1.0));
  float tmpvar_47;
  tmpvar_47 = exp2(tmpvar_46);
  float tmpvar_48;
  tmpvar_48 = (tmpvar_47 * 2.0);
  rC_36.x = ((float(mod ((tmpvar_44.x + u_IBLOffset), 1.0))) / tmpvar_47);
  rC_36.y = (((tmpvar_44.y / tmpvar_48) + 1.0) - (2.0 / tmpvar_48));
  vec4 tmpvar_49;
  tmpvar_49 = texture2D (u_RadianceTex, rC_36);
  color1_38.w = tmpvar_49.w;
  color1_38.xyz = (tmpvar_49.xyz / tmpvar_49.w);
  color1_38.xyz = (color1_38.xyz * (pow (
    mix (1.2, 1.5, tmpvar_49.w)
  , 
    (tmpvar_49.w * 32.0)
  ) - 1.2));
  float tmpvar_50;
  tmpvar_50 = exp2(max (0.0, (tmpvar_46 - 1.0)));
  float tmpvar_51;
  tmpvar_51 = (tmpvar_50 * 2.0);
  rC_35.x = ((float(mod ((tmpvar_44.x + u_IBLOffset), 1.0))) / tmpvar_50);
  rC_35.y = (((tmpvar_44.y / tmpvar_51) + 1.0) - (2.0 / tmpvar_51));
  vec4 tmpvar_52;
  tmpvar_52 = texture2D (u_RadianceTex, rC_35);
  color2_37.w = tmpvar_52.w;
  color2_37.xyz = (tmpvar_52.xyz / tmpvar_52.w);
  color2_37.xyz = (color2_37.xyz * (pow (
    mix (1.2, 1.5, tmpvar_52.w)
  , 
    (tmpvar_52.w * 32.0)
  ) - 1.2));
  tmpvar_2[0]=tmpvar_11[0];
  tmpvar_3[0]=tmpvar_12[0];
  tmpvar_4[0]=tmpvar_13[0];
  vec3 tmpvar_53;
  tmpvar_53 = mix (vec3((0.08 * u_Specular)), tmpvar_8, u_Metallic);
  vec3 tmpvar_54;
  tmpvar_54 = tmpvar_11[0];
  float tmpvar_55;
  tmpvar_55 = dot (tmpvar_6, tmpvar_54);
  float tmpvar_56;
  tmpvar_56 = dot (tmpvar_6, tmpvar_7);
  float tmpvar_57;
  tmpvar_57 = dot (tmpvar_54, tmpvar_7);
  float tmpvar_58;
  tmpvar_58 = inversesqrt((2.0 + (2.0 * tmpvar_57)));
  float tmpvar_59;
  tmpvar_59 = clamp (((tmpvar_55 + tmpvar_56) * tmpvar_58), 0.0, 1.0);
  float tmpvar_60;
  tmpvar_60 = clamp (tmpvar_55, 0.0, 1.0);
  float tmpvar_61;
  tmpvar_61 = clamp (abs(tmpvar_56), 0.0, 1.0);
  float tmpvar_62;
  tmpvar_62 = (u_Roughness * u_Roughness);
  float tmpvar_63;
  tmpvar_63 = (tmpvar_62 * tmpvar_62);
  float tmpvar_64;
  tmpvar_64 = (((
    (tmpvar_59 * tmpvar_63)
   - tmpvar_59) * tmpvar_59) + 1.0);
  float tmpvar_65;
  tmpvar_65 = pow ((1.0 - clamp (
    (tmpvar_58 + (tmpvar_58 * tmpvar_57))
  , 0.0, 1.0)), 5.0);
  final_color_1 = (((
    ((((
      (tmpvar_8 - (tmpvar_8 * vec3(u_Metallic)))
     * 0.3183099) + (
      ((tmpvar_63 / ((3.141593 * tmpvar_64) * tmpvar_64)) * (0.5 / ((
        (tmpvar_60 * ((tmpvar_61 * (1.0 - tmpvar_62)) + tmpvar_62))
       + 
        (tmpvar_61 * ((tmpvar_60 * (1.0 - tmpvar_62)) + tmpvar_62))
      ) + 1e-05)))
     * 
      ((clamp ((50.0 * tmpvar_53.y), 0.0, 1.0) * tmpvar_65) + ((1.0 - tmpvar_65) * tmpvar_53))
    )) * tmpvar_60) * tmpvar_13[0])
   * tmpvar_12[0]) * vec3(tmpvar_15)) + u_EmissiveColor);
  vec3 result_66;
  float tmpvar_67;
  tmpvar_67 = min (max (dot (tmpvar_6, tmpvar_7), 0.0), 1.0);
  vec3 tmpvar_68;
  tmpvar_68 = mix (vec3(0.04, 0.04, 0.04), tmpvar_8, u_Metallic);
  float tmpvar_69;
  tmpvar_69 = (1.0 - u_Metallic);
  float tmpvar_70;
  tmpvar_70 = (1.05 - tmpvar_67);
  result_66 = (((
    (((vec3(1.0, 1.0, 1.0) - (tmpvar_68 + 
      ((max (vec3((1.0 - u_Roughness)), tmpvar_68) - tmpvar_68) * pow ((1.0 - tmpvar_67), 5.0))
    )) * tmpvar_69) * tmpvar_34)
   * tmpvar_8) + (
    pow (mix (color2_37.xyz, color1_38.xyz, vec3(min (max (
      ((tmpvar_45 * 10.0) - tmpvar_46)
    , 0.0), 1.0))), vec3(2.2, 2.2, 2.2))
   * 
    mix (tmpvar_53, vec3(min (1.0, (tmpvar_70 * tmpvar_70))), tmpvar_69)
  )) * max (vec3(u_AmbientOcclusion), (
    ((((u_AmbientOcclusion * 
      ((2.0404 * tmpvar_8) - 0.3324)
    ) + (
      (-4.7951 * tmpvar_8)
     + 0.6417)) * u_AmbientOcclusion) + ((2.7552 * tmpvar_8) + 0.6903))
   * u_AmbientOcclusion)));
  vec3 color_71;
  color_71 = (result_66 * u_IBLIntensity);
  color_71 = ((color_71 / (color_71 + 0.187)) * 1.035);
  vec3 tmpvar_72;
  tmpvar_72 = pow (color_71, vec3(1.5, 1.5, 1.5));
  result_66 = tmpvar_72;
  final_color_1 = (final_color_1 + tmpvar_72);
  vec4 tmpvar_73;
  tmpvar_73.xyz = final_color_1;
  tmpvar_73.w = tmpvar_9;
  vec4 tmpvar_74;
  vec4 color_75;
  color_75.w = tmpvar_73.w;
  color_75.xyz = pow (final_color_1, vec3(0.4545454, 0.4545454, 0.4545454));
  color_75.xyz = clamp (color_75.xyz, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));
  tmpvar_74 = color_75;
  gl_FragColor = tmpvar_74;
}


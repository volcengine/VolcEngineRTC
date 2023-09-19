precision highp float;
varying vec2 texCoord;
varying vec2 sucaiTexCoord;
varying float varOpacity;

uniform sampler2D inputImageTexture;
uniform sampler2D videoImageTexture;
uniform sampler2D sucaiImageTexture;

uniform float intensity;

#ifdef USE_SEG
 varying vec2 segCoord;
 uniform sampler2D segMaskTexture;
#endif

float blendSoftLight(float base, float blend) {
    return (blend < 0.5) ? (2.0 * base * blend + base * base * (1.0 - 2.0 * blend)) : (sqrt(base) * (2.0 * blend - 1.0) + 2.0 * base * (1.0 - blend));
}

vec3 blendSoftLight(vec3 base, vec3 blend) {
    return vec3(blendSoftLight(base.r, blend.r), blendSoftLight(base.g, blend.g), blendSoftLight(base.b, blend.b));
}

vec3 blendSoftLight(vec3 base, vec3 blend, float opacity) {
    return (blendSoftLight(base, blend) * opacity + base * (1.0 - opacity));
}


void main(void)
{
    vec4 src = texture2D(inputImageTexture, texCoord);
    vec4 sucai = texture2D(sucaiImageTexture, sucaiTexCoord);
    

    vec3 color = blendSoftLight(src.rgb, clamp(sucai.rgb * (1.0 / sucai.a), 0.0, 1.0));
#ifdef USE_SEG
    float seg_opacity = (texture2D(segMaskTexture, segCoord)).x;
    if(clamp(segCoord, 0.0, 1.0) != segCoord) seg_opacity = 1.0;
    color = mix(src.rgb, color, seg_opacity);
#endif
  
#ifdef BLENDFUN_USEABLE
    // xiurongsucaizengjiayigealphazhi
    // yansewei 126~130:alpha=0; 0~118:alpha=1; 138~255:alpha=1; 118~126:alpha=1~0; 130~138:alpha=0~1;
    float alpha = abs(clamp(sucai.r * (1.0 / sucai.a), 0.0, 1.0) - 0.5);
    alpha = clamp((alpha - 2.0/255.0) * 32.0, 0.0, 1.0);
    alpha *= intensity * varOpacity;
    color *= alpha;
    gl_FragColor = vec4(color, alpha);
#else
    color = mix(src.rgb, color, intensity* varOpacity);
    gl_FragColor = vec4(color, 1.0);
#endif
}

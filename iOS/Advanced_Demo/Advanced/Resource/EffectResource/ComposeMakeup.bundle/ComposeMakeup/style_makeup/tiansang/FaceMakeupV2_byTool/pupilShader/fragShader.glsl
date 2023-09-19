precision highp float;
varying vec2 texCoord;
varying vec2 sucaiTexCoord;
varying float weight;
varying float varOpacity;
varying float varOpacityReflect;

uniform sampler2D inputImageTexture;
uniform sampler2D sucaiImageTexture;
uniform sampler2D reflectImageTexture;

uniform float intensity;
uniform float reflectIntensity;

#ifdef USE_SEG
 varying vec2 segCoord;
 uniform sampler2D segMaskTexture;
#endif


float blendReflect(float base, float blend) {
    return (blend==1.0)?blend:min(base*base/(1.0-blend),1.0);
}

vec3 blendReflect(vec3 base, vec3 blend) {
    return vec3(blendReflect(base.r,blend.r),blendReflect(base.g,blend.g),blendReflect(base.b,blend.b));
}


float blendScreen(float base, float blend) {
    return 1.0-((1.0-base)*(1.0-blend));
}

vec3 blendScreen(vec3 base, vec3 blend) {
    return vec3(blendScreen(base.r,blend.r),blendScreen(base.g,blend.g),blendScreen(base.b,blend.b));
}

vec3 blendFunc(vec3 base, vec3 blend, float opacity) {
    return (blendScreen(base, blend) * opacity + base * (1.0 - opacity));
}


void main(void) {
    vec4 src = texture2D(inputImageTexture, texCoord);
    
    vec4 sucai = texture2D(sucaiImageTexture, sucaiTexCoord);
    sucai.rgb  = sucai.rgb/sucai.a;
    //vec3 dstColor = src.rgb*(1.0 - sucai.a) + clamp(sucai.rgb, 0.0, 1.0)*sucai.a;
    vec3 dstColor = mix(src.rgb, clamp(sucai.rgb, 0.0, 1.0), sucai.a * intensity * varOpacity );

        vec4 reflect = texture2D(reflectImageTexture, sucaiTexCoord);
        vec3 tem = blendFunc(dstColor, clamp(reflect.rgb, 0.0, 1.0),1.0);
        dstColor = mix(dstColor, tem, intensity*reflectIntensity * reflect.a * varOpacityReflect * varOpacity );
#ifdef USE_SEG
    float seg_opacity = (texture2D(segMaskTexture, segCoord)).x;
    if(clamp(segCoord, 0.0, 1.0) != segCoord) seg_opacity = 1.0;
    dstColor = mix(src.rgb, dstColor, seg_opacity);
#endif
    gl_FragColor = vec4(dstColor, 1.0);
}

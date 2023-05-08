precision highp float;

varying vec2 inputTexCoord;
varying vec2 segTexCoord;
varying vec2 maskTexCoord;

uniform sampler2D inputImageTexture;    //原图
uniform sampler2D segMaskTexture;       //分割结果唇彩区域+牙齿区域
uniform sampler2D glossTexture;         //高光区域图
uniform sampler2D shimmerTexture;       //闪光点图像
uniform sampler2D maskTexture;          //总mask，控制区域

uniform sampler2D blendWeightTexture;
uniform sampler2D levelWeightTexture;
uniform sampler2D lutImageTexture;


uniform vec4 uMouthColor;
uniform vec4 uSpecularColor;
uniform vec4 uShimmerColor;

uniform float uScale;
uniform float uShift;
uniform float uThreshold;

uniform int uLipstickType;
uniform bool uShimmerColorMode;

uniform float intensity;
uniform float uSoomthIntensity;

vec3 applyLUT(vec3 textureColor) {
    float blueColor = textureColor.b * 63.0;
    vec2 quad1;
    quad1.y = floor(floor(blueColor) / 8.0);
    quad1.x = floor(blueColor) - (quad1.y * 8.0);
    vec2 quad2;
    quad2.y = floor(ceil(blueColor) / 8.0);
    quad2.x = ceil(blueColor) - (quad2.y * 8.0);
    vec2 texPos1;
    texPos1.x = (quad1.x * 0.125) + 0.5 / 512.0 + ((0.125 - 1.0 / 512.0) * textureColor.r);
    texPos1.y = (quad1.y * 0.125) + 0.5 / 512.0 + ((0.125 - 1.0 / 512.0) * textureColor.g);
    vec2 texPos2;
    texPos2.x = (quad2.x * 0.125) + 0.5 / 512.0 + ((0.125 - 1.0 / 512.0) * textureColor.r);
    texPos2.y = (quad2.y * 0.125) + 0.5 / 512.0 + ((0.125 - 1.0 / 512.0) * textureColor.g);
    vec4 newColor1 = texture2D(lutImageTexture,texPos1);
    vec4 newColor2 = texture2D(lutImageTexture, texPos2);
    vec4 newColor = mix(newColor1, newColor2, fract(blueColor));
    return newColor.rgb;
}

const lowp float flt_epsilon = 0.001;
vec3 RGBtoHCV(vec3 rgb) {
    vec4 p = (rgb.g < rgb.b) ? vec4(rgb.bg, -1.0, 0.66666667) : vec4(rgb.gb, 0.0, -0.33333333);
    vec4 q = (rgb.r < p.x) ? vec4(p.xyw, rgb.r) : vec4(rgb.r, p.yzx);
    float c = q.x - min(q.w, q.y);
    float h = abs((q.w - q.y) / (6.0 * c + flt_epsilon) + q.z);
    return vec3(h, c, q.x);
}

vec3 RGBtoHSL(vec3 rgb) {
    vec3 hcv = RGBtoHCV(rgb);
    float l = hcv.z - hcv.y * 0.5;
    float s = hcv.y / (1.0 - abs(l * 2.0 - 1.0) + flt_epsilon);
    return vec3(hcv.x, s, l);
}

vec3 HSLtoRGB(vec3 hsl) {
    vec3 rgb;
    float x = hsl.x * 6.0;
    rgb.r = abs(x - 3.0) - 1.0;
    rgb.g = 2.0 - abs(x - 2.0);
    rgb.b = 2.0 - abs(x - 4.0);
    rgb = clamp(rgb, 0.0, 1.0);
    float c = (1.0 - abs(2.0 * hsl.z - 1.0)) * hsl.y;
    rgb = clamp((rgb - vec3(0.5)) * vec3(c) + vec3(hsl.z), 0.0, 1.0);
    return rgb;
}


float BlendOverlayf(float base, float blend) {
    return (base < 0.5 ? (2.0 * (base) * (blend)) : (1.0 - 2.0 * (1.0 - (base)) * (1.0 - (blend))));
}

vec3 addGloss(vec3 dstColor, float glossf, vec4 color){
    vec3 tem = dstColor * (1.0 - glossf) + glossf * color.rgb;
    return mix(dstColor, tem, color.a);
}

vec3 addShimmer(vec3 dstColor, float gray){
    vec3 final = dstColor;
    // float space_weight = (min(max(abs((segTexCoord.x-0.25)*2.0 - 0.5), 0.042), 0.5) - 0.083) / 0.417;
    float space_weight = abs(segTexCoord.x - 0.5);
    space_weight = exp(-space_weight*space_weight/0.05);

    float luma_weight = gray * 3.0;
    // float shimmer_weight = 1.0 - 0.3 * space_weight;
    float shimmer_weight = space_weight;
    float shimmer = texture2D(shimmerTexture, segTexCoord).r;
    shimmer = shimmer * shimmer_weight * luma_weight;
    if(shimmer < 0.001){
        return final;
    }

    if(uShimmerColorMode){
        final = addGloss(dstColor, shimmer, uShimmerColor);
    }else{
        vec3 hsl = RGBtoHSL(dstColor);
        hsl.z = min(hsl.z + shimmer * shimmer_weight * luma_weight * uShimmerColor.a, 1.0);
        final = HSLtoRGB(hsl);
    }
    return vec3(final);
}

float getLevelWeight(float gray, float ymax, float ymin, float xth){
    float a = (ymax - ymin)/(1.0 - xth);
    return gray > xth ? -a * gray + ymin + a : ymax;
}

//第一段是square，第二代是linear，第三段是linear
float getBlendWeight(float gray, float  xth0, float yth0,  float xth1, float yth1){
    if (gray > xth1){
        return yth1 + (1.0 - yth1) / (1.0 - xth1) * (gray - xth1);
    }

    if(gray > xth0){
        return yth0 + (yth1 - yth0)/(xth1 - xth0) * (gray - xth0);
    }

    gray = gray / xth0;
    return gray * gray * gray * yth0;
}

//哑光，没有纹理
vec3 yaguang_wumian(vec3 src, float alpha){
    float gray = 0.1 * src.r + 0.6 * src.g + 0.3 * src.b;
    vec3 zhexia = mix(src, vec3(0.98, 0.9, 0.88), 0.1 * (1.0 - gray));

    float blend_weight = sqrt(gray);
    float level_weight = getLevelWeight(gray, 0.90, 0.70, 0.65); 

    vec3 color = mix(uMouthColor.rgb * zhexia.rgb, uMouthColor.rgb, blend_weight);
    vec3 dstColor = mix(src.rgb, color, level_weight);
    dstColor = mix(src.rgb, dstColor, uMouthColor.a);
    return dstColor;
}

//哑光，有一些纹理
vec3 yaguang(vec3 src, float alpha){
    float gray = 0.1 * src.r + 0.6 * src.g + 0.3 * src.b;

    float contrast = max(min((gray * uScale + uShift) * alpha + 0.5 * (1.0 - alpha), 1.0), 0.0);
    if (contrast < 0.5) contrast = 0.5 - (0.5 - contrast) * 0.5;

    float blend_weight = getBlendWeight(gray, 0.35, 0.35, 0.6, 0.8);
    float level_weight = getLevelWeight(gray, 0.90, 0.70, 0.65); 

    vec3 color = mix(uMouthColor.rgb * src.rgb, uMouthColor.rgb, blend_weight);
    vec3 dstColor = mix(src.rgb, color, level_weight);

    float diff = max(gray - uThreshold, 0.0) * alpha;
    dstColor = vec3(1.0) - (vec3(1.0) - dstColor) * vec3(1.0 - diff);

    dstColor.r = BlendOverlayf(dstColor.r, contrast);
    dstColor.g = BlendOverlayf(dstColor.g, contrast);
    dstColor.b = BlendOverlayf(dstColor.b, contrast);

    dstColor = mix(dstColor, yaguang_wumian(src, alpha), uSoomthIntensity);  //哑光与雾面之间进行过度
    dstColor = mix(src.rgb, dstColor, uMouthColor.a);
    return dstColor;
}

vec3 shuirun(vec3 src, float alpha){
    float gray = 0.1 * src.r + 0.6 * src.g + 0.3 * src.b;

    float contrast = max(min((gray * uScale + uShift) * alpha + 0.5 * (1.0 - alpha), 1.0), 0.0);
    if (contrast < 0.5) contrast = 0.5 - (0.5 - contrast) * 0.1;

    float blend_weight = getBlendWeight(gray, 0.35, 0.35, 0.6, 0.8);
    float level_weight = getLevelWeight(gray, 0.90, 0.70, 0.65); 

    vec3 color = mix(uMouthColor.rgb * src.rgb, uMouthColor.rgb, blend_weight);
    vec3 dstColor = mix(src.rgb, color, level_weight);

    float diff = max(gray - uThreshold, 0.0) * alpha;
    dstColor = vec3(1.0) - (vec3(1.0) - dstColor) * vec3(1.0 - diff);

    dstColor.r = BlendOverlayf(dstColor.r, contrast);
    dstColor.g = BlendOverlayf(dstColor.g, contrast);
    dstColor.b = BlendOverlayf(dstColor.b, contrast);

    dstColor = mix(src.rgb, dstColor, uMouthColor.a);
    return dstColor;
}

void main()
{
    vec4 source = texture2D(inputImageTexture, inputTexCoord);
    vec4 gloss = texture2D(glossTexture, inputTexCoord);
    vec4 mask = texture2D(maskTexture, maskTexCoord);            // close, open, gloss
    vec4 segMask = texture2D(segMaskTexture, segTexCoord);
    vec3 dstColor = source.rgb;
    float alpha = segMask.r;

    float intensity1 = intensity;   
    if(clamp(segTexCoord, 0.0, 1.0) != segTexCoord){    //mask超出区域做剪切
        intensity1 = 0.0;
    }

    float gray = 0.299 * source.r + 0.587 * source.g + 0.114 * source.b;

    // dstColor = applyLUT(source.rgb);
    if(uLipstickType == 0){
        dstColor = yaguang(source.rgb, alpha);
    }
    else if (uLipstickType == 1){
        dstColor = shuirun(source.rgb, alpha);
        float glossf = gloss.r * mask.b;                        //控制高光区域的范围
        dstColor = addGloss(dstColor.rgb, glossf, uSpecularColor);
    }

    dstColor = addShimmer(dstColor, gray * mask.g);
    gl_FragColor = vec4(mix(source.rgb, dstColor, intensity1 * alpha), 1.0);
}
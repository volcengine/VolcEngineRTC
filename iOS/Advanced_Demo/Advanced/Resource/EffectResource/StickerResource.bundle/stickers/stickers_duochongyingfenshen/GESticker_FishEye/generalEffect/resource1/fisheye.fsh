precision highp float;
varying vec2 textureCoordinate;

uniform sampler2D inputImageTexture;
uniform sampler2D mattingTexture;

uniform highp float uScanLineJitter_x; // 长度
uniform highp float uScanLineJitter_y; // 密度
uniform highp float uColorDrift_x; // 颜色倾斜
uniform highp float uColorDrift_y; // 整体偏移

uniform float uTimeStamp; 

vec2 uVerticalJump = vec2(0.0,0.0); // (amount, time)
uniform float uHorizontalShake;

const float offsetAbs = 0.2;
const float tallFactor = 1.1;
//毛刺效果begin

float nrand(float x, float y)
{
    return fract(sin(dot(vec2(x, y), vec2(12.9898, 78.233))) * 43758.5453);
}


vec4 skinNeeding(sampler2D inputImageTexture,vec2 textureCoordinate)
{
    float u = textureCoordinate.x;
    float v = textureCoordinate.y;

    float jitter = nrand(v, uTimeStamp) * 2.0 - 1.0;
    jitter *= step(uScanLineJitter_y, abs(jitter)) * uScanLineJitter_x;
    float jump = mix(v, fract(v + uVerticalJump.y), uVerticalJump.x);
    float shake = (nrand(uTimeStamp, 2.0) - 0.5) * uHorizontalShake;
    
    // Color drift
    float drift = sin(jump + uColorDrift_y) * uColorDrift_x;
    
    vec4 src1 = texture2D(inputImageTexture, fract(vec2(u + jitter + shake, jump)));
    vec4 src2 = texture2D(inputImageTexture, fract(vec2(u + jitter + shake + drift, jump)));
   return vec4(src1.r, src2.g, src1.b, 1.0);

}


//毛刺效果end

#define _EXECUTE_BLEND_(blendFunction, base, blend) vec4(((1.0-base.a)*blend.rgb + (1.0-blend.a)*base.rgb + blend.a*base.a*blendFunction(clamp(blend.rgb/blend.a,0.0,1.0), clamp(base.rgb/base.a,0.0,1.0), 1.0)) * (1.0 / (blend.a + (base.a * (1.0-blend.a)))), (blend.a + base.a*(1.0-blend.a)));
vec3 blendScreen(vec3  a, vec3 b, float f) { return b+a-b*a;}
vec4 blendScreen(vec4 base, vec4 blend) { return _EXECUTE_BLEND_(blendScreen, base, blend );}

void main()
{
    //原图
    vec4 human0 = texture2D(mattingTexture, vec2(textureCoordinate.x,textureCoordinate.y));
    if(human0.w < 0.5){
        human0.w = 3.0*human0.w*human0.w - 0.25;
    }
	if(human0.w < 0.0 ){
		human0.w = 0.0;
	}
    vec4 background0 = texture2D(inputImageTexture,vec2(textureCoordinate.x,textureCoordinate.y));
    float adjustment = 0.5 * tallFactor - 0.5;
    vec2 leftCoordinate = vec2((textureCoordinate.x + offsetAbs) * tallFactor - adjustment,textureCoordinate.y * tallFactor - adjustment);
    //左边
    vec4 background1 = texture2D(inputImageTexture,leftCoordinate);
    vec4 human1 = texture2D(mattingTexture, leftCoordinate);
    
	if(human1.w < 0.5){
        human1.w = 3.0*human1.w*human1.w - 0.25;
    }
	if(human1.w < 0.0 ){
		human1.w = 0.0;
	}
    
    vec2 rightCoordinate = vec2((textureCoordinate.x - offsetAbs) * tallFactor - adjustment,textureCoordinate.y * tallFactor - adjustment);
    //右边
    vec4 background2 = texture2D(inputImageTexture,rightCoordinate);
    vec4 human2 = texture2D(mattingTexture, rightCoordinate);
    if(human2.w < 0.5){
        human2.w = 3.0*human2.w*human2.w - 0.25;
    }
	if(human2.w < 0.0 ){
		human2.w = 0.0;
	}
    //vec4 background = (1.0-human0.w)*background0 + human0.w*vec4(0.0,0.0,0.0,1.0);
    vec4 result = background0;
    if(leftCoordinate.x <= 1.0 && leftCoordinate.y <= 1.0 && leftCoordinate.x >= 0.0 && leftCoordinate.y >= 0.0){
        result = background0 * (1.0-human1.w) + background1 * human1.w;
    }
    if(rightCoordinate.x <= 1.0 && rightCoordinate.y <= 1.0 && rightCoordinate.x >= 0.0 && rightCoordinate.y >= 0.0){
        result = result*(1.0-human2.w) + background2*human2.w;
    }
    
    result = result*(1.0-human0.w) + background0*human0.w;
    result.w = 1.0;
    gl_FragColor = result;
}





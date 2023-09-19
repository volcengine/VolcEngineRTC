precision mediump float;
const lowp int SAMPLES = 11;

varying vec2 textureCoordinate;

uniform sampler2D inputImageTexture;
uniform sampler2D prevGlossTexture;

// uniform float maxIntensity;
const float maxIntensity = 1.0;

uniform vec4 samplePoints[SAMPLES];

const float threshold = 0.94;
const float scope = 1.02;

vec3 rgb2hsv(vec3 c) {
    highp vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    highp vec4 p = mix(vec4(c.bg, K.wz),vec4(c.gb, K.xy), step(c.b, c.g));
    highp vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    highp float d = q.x - min(q.w, q.y);
    highp float e = 1.0e-7;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

void main() {
    float maxVal = 0.0;
    for (int i = 0; i < SAMPLES; i++) {
        vec4 color = texture2D(inputImageTexture, vec2(samplePoints[i].r, samplePoints[i].g));
        vec3 hsv = rgb2hsv(color.rgb);
        maxVal = max(maxVal, (1.0 - hsv.g) * hsv.b);
        color = texture2D(inputImageTexture, vec2(samplePoints[i].b, samplePoints[i].a));
        hsv = rgb2hsv(color.rgb);
        maxVal = max(maxVal, (1.0 - hsv.g) * hsv.b);
    }

    vec4 src = texture2D(inputImageTexture, textureCoordinate);
    vec4 prev = texture2D(prevGlossTexture, textureCoordinate);
    vec3 hsv_src = rgb2hsv(src.rgb);
    float textureValue = (1.0 - hsv_src.g) * hsv_src.b;

    maxVal = maxVal * scope;
    
    float minY = 0.05;
    float maxY = 1.0;
    float x1 = log(minY / maxY) / (threshold - 1.0);
    float value = pow(2.71828, x1 * textureValue / maxVal + log(maxY) - x1);
    value = clamp(value, 0.0, 1.0);
    value = pow(value, 0.8);

    float validValue = (0.5 * value + 0.35 * prev.g + 0.2 * prev.b + 0.1 * prev.a) * maxIntensity;
    validValue = clamp(validValue, 0.0, 1.0);

    gl_FragColor = vec4(validValue, value, prev.g, prev.b);
    // gl_FragColor = src + vec4(value);
}

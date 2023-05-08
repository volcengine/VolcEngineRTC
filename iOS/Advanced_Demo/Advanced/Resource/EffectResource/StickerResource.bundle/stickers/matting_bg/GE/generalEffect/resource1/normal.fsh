precision highp float;

varying vec2 textureCoordinate;
varying vec2 bgCoordinate;
uniform sampler2D inputImageTexture;
uniform sampler2D mattingTexture;
uniform sampler2D bgTexture;

const float influencefactor = 0.5;

void main() { 
   vec3 fgColor = texture2D(inputImageTexture,textureCoordinate).rgb;
   vec3 bgColor = texture2D(bgTexture, bgCoordinate).rgb; 
   float mattingValue = texture2D(mattingTexture, textureCoordinate).a;
   gl_FragColor = vec4(mix(bgColor, fgColor, mattingValue), 1.0);
}

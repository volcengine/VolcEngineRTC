precision highp float;

attribute vec3 attPosition;
attribute vec2 attUV;

uniform float widthOffset;
uniform float heightOffset;


varying vec2 textureCoordinate;

varying vec4 textureShift_1;
varying vec4 textureShift_2;
varying vec4 textureShift_3;
varying vec4 textureShift_4;

void main() {
    gl_Position = vec4(attPosition,1.);
    textureCoordinate = attUV.xy;
    


    textureShift_1 = vec4(attUV.st + vec2(-widthOffset,0.0),attUV.st + vec2(widthOffset,0.0));
    textureShift_2 = vec4(attUV.st + vec2(0.0,-heightOffset),attUV.st + vec2(0.0,heightOffset));
    textureShift_3 = vec4(attUV.st + vec2(widthOffset,heightOffset),attUV.st + vec2(-widthOffset,-heightOffset));
    textureShift_4 = vec4(attUV.st + vec2(-widthOffset,heightOffset),attUV.st + vec2(widthOffset,-heightOffset));
}

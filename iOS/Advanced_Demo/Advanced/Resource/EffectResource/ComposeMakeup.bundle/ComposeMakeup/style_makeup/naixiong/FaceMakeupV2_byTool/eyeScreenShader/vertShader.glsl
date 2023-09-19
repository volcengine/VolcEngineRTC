attribute vec3 attPosition;
attribute vec2 attUV;
attribute float attOpacity;

varying vec2 texCoord;
varying vec2 sucaiTexCoord;
varying float varOpacity;

uniform mat4 uMVPMatrix;
uniform mat4 uSTMatrix;

#ifdef USE_SEG
varying vec2 segCoord;
uniform mat4 uSegMatrix;
#endif

void main(void){
    gl_Position = uMVPMatrix * vec4(attPosition.xy, 0.0, 1.0);
    texCoord = 0.5 * gl_Position.xy + 0.5;
    vec4 coord = uSTMatrix * vec4(attUV.xy, 0.0, 1.0);
    sucaiTexCoord = vec2(coord.x, 1.0 - coord.y);
    varOpacity = attOpacity;
#ifdef USE_SEG
    segCoord = (uSegMatrix * vec4(attPosition.xy, 0.0, 1.0)).xy;
#endif
}
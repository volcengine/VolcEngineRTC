attribute vec3 attPosition;
attribute vec3 attUV;
attribute float attOpacity;
attribute float attOpacityReflect;

varying vec2 texCoord;
varying vec2 sucaiTexCoord;
varying float weight;
varying float varOpacity;
varying float varOpacityReflect;

uniform mat4 uMVPMatrix;

#ifdef USE_SEG
varying vec2 segCoord;
uniform mat4 uSegMatrix;
#endif

void main(void) {
    gl_Position = uMVPMatrix * vec4(attPosition.xy, 0.0, 1.0);
    texCoord = 0.5 * gl_Position.xy + 0.5;
    //sucaiTexCoord = vec2(attUV.x, 1.0 - attUV.y);
    sucaiTexCoord = attUV.xy;
    weight = attPosition.z;
    
    varOpacity = attOpacity;
    varOpacityReflect = attOpacityReflect;
#ifdef USE_SEG
    segCoord = (uSegMatrix * vec4(attPosition.xy, 0.0, 1.0)).xy;
#endif
}
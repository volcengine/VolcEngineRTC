
attribute vec3 attPosition;
attribute vec2 attUV;

varying vec2 textureCoordinate;
varying vec2 bgCoordinate;

uniform float bgTextureRotate;

void main() {
    gl_Position = vec4(attPosition, 1.);
    textureCoordinate = attUV.xy;
    if (bgTextureRotate < 0.5) {
      bgCoordinate = attUV.xy;
   } else if (bgTextureRotate < 1.5) {
      bgCoordinate = vec2(attUV.y, 1.0 - attUV.x);
   } else if (bgTextureRotate < 2.5) {
      bgCoordinate = vec2(1.0 - attUV.x, 1.0 - attUV.y);
   } else {
      bgCoordinate = vec2(1.0 - attUV.y, attUV.x);
   }
}

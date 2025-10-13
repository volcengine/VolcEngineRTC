attribute vec2 attPosition;
attribute vec2 attUV;

varying vec2 textureCoordinate;
uniform mat4 uMVPMatrix;

void main(void){
    gl_Position = uMVPMatrix * vec4(attPosition.xy, 0.0, 1.0);
    textureCoordinate = 0.5 * gl_Position.xy + 0.5;
}
precision highp float;

attribute vec3 attPosition;
attribute vec2 attUV;

varying vec2 uv0;

void main(void)
{
    gl_Position = vec4(attPosition,1.);
    uv0 = attUV.xy;
}
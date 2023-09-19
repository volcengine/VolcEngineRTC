

precision highp float;




varying highp vec2 textureCoordinate; 


varying highp vec4 textureShift_1; 
varying highp vec4 textureShift_2; 
varying highp vec4 textureShift_3; 
varying highp vec4 textureShift_4; 


uniform sampler2D inputImageTexture; 



//uniform highp float sharpen;//0.35
 
void main() 
{ 
    lowp vec4 iColor = texture2D(inputImageTexture, textureCoordinate); 

    lowp vec3 resultColor = iColor.rgb;

    mediump float sum = 0.25*iColor.g;
    sum += 0.125 *texture2D(inputImageTexture,textureShift_1.xy).g;
    sum += 0.125 *texture2D(inputImageTexture,textureShift_1.zw).g;
    sum += 0.125 *texture2D(inputImageTexture,textureShift_2.xy).g;
    sum += 0.125 *texture2D(inputImageTexture,textureShift_2.zw).g;
    sum += 0.0625*texture2D(inputImageTexture,textureShift_3.xy).g;
    sum += 0.0625*texture2D(inputImageTexture,textureShift_3.zw).g;
    sum += 0.0625*texture2D(inputImageTexture,textureShift_4.xy).g;
    sum += 0.0625*texture2D(inputImageTexture,textureShift_4.zw).g;



    float hPass = iColor.g-sum+0.5;
    float flag = step(0.5, hPass);
    highp vec3 color = mix(max(vec3(0.0), (2.0*hPass + resultColor - 1.0)), min(vec3(1.0), (resultColor + 2.0*hPass - 1.0)), flag);


    color = mix(resultColor.rgb, color.rgb, 0.4);

    gl_FragColor = vec4(color, 1.0);
}

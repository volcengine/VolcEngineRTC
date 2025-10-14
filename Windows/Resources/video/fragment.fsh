#version 330 core
in  vec2 TexCord;
uniform int      format = -1;
uniform sampler2D tex_y;
uniform sampler2D tex_u;
uniform sampler2D tex_v;
uniform sampler2D tex_uv;
out vec4 FragColor;

void main()
{
    vec3 yuv;
    vec3 rgb;


    if(format == 1)
    {
        yuv.x = texture(tex_y, TexCord).r;
        yuv.y = texture(tex_u, TexCord).r-0.5;
        yuv.z = texture(tex_v, TexCord).r-0.5;
    }
    else if(format == 2)
    {
        yuv.x = texture(tex_y, TexCord.st).r;
        yuv.y = texture(tex_uv, TexCord.st).r - 0.5;
        yuv.z = texture(tex_uv, TexCord.st).g - 0.5;
    }
    else
    {
    }

    rgb = mat3(1.0, 1.0, 1.0,
               0.0, -0.39465, 2.03211,
               1.13983, -0.58060, 0.0) * yuv;
    FragColor = vec4(rgb, 1.0);
}

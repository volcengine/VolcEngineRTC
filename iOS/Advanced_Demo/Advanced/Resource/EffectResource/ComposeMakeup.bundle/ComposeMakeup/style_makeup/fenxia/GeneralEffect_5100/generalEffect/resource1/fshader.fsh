precision highp float;
varying vec2 uv0;

uniform sampler2D u_albedo;
uniform sampler2D grain_texture;
// uniform sampler2D grain4000x1200;

uniform float u_max;//传参数
uniform float v_max;//传参数


uniform float ratio;//传参数

uniform float random_x1; // 0 ~ 1   传参数
uniform float random_y1; // 0 ~ 1   传参数

vec3 rgb2gray = vec3(0.299, 0.587, 0.114);

float check_value(float value)
{
    float int_part = floor(value);
    value = value - int_part;
    return value;
}

float get_grain_texture(vec2 uv, float random_x, float random_y, float u_max, float v_max)
{
    vec2 res;
    float random_u = check_value(uv.x + random_x);
    float random_v = check_value(uv.y + random_y);

    res.x = check_value(random_u * u_max);
    res.y = check_value(random_v * v_max);
    return texture2D(grain_texture, res).r;;
}


void main(void)
{
    vec3 ori_color = texture2D(u_albedo,uv0).rgb;
    vec3 grain_color;
    float ori_gray = dot(rgb2gray, ori_color);
    ori_gray = ori_gray * 2.0 - 1.0;
    float abs_ori_gray = abs(ori_gray);
    float abs_ori_gray2 = abs_ori_gray * abs_ori_gray;
    float abs_ori_gray3 = abs_ori_gray2 * abs_ori_gray;

    // vec2 grain_uv;
    // float grain_height;
    // float grain_width;
    // float grain_max_height = 1200.;
    // float grain_max_width = 1200.;
    // float grain_max_height_inv = 0.00195312; // 1. / 512
    // float grain_max_width_inv = 0.00195312; // 1. / 512


    // float u_max = grain_width * grain_max_width_inv;
    // float v_max = grain_height * grain_max_height_inv;

    // float random_u = check_value(uv0.x + random_x);
    // float random_v = check_value(uv0.y + random_y);

    // grain_uv.x = check_value(random_u * u_max);
    // grain_uv.y = check_value(random_v * v_max);
    // grain_gray = texture2D(grain_texture, grain_uv).r;
    float grain_gray = get_grain_texture(uv0, random_x1, random_y1, u_max, v_max);
    // grain_gray2 = get_grain_texture(uv0, random_x2, random_y2, u_max, v_max);

    // grain_gray = mix(grain_gray1, grain_gray2, count * max_count_inv);

    grain_gray = grain_gray * 2.0 - 1.0;
    float mask;
    float strength = 0.30019608;
    if(ori_gray >= 0.)
    {
        mask = (abs_ori_gray3 * 0.5 + abs_ori_gray2 * 0.5) * (strength - 0.03921569);
    }
    else
    {
        mask = (abs_ori_gray2 * 0.4 + abs_ori_gray * 0.6) * strength;
    }

    vec3 new_color = clamp(ori_color + grain_gray * (strength - mask), 0., 1.);
    new_color = mix(ori_color.rgb, new_color, ratio);

    gl_FragColor.rgb = new_color;
    gl_FragColor.a = 1.;
}

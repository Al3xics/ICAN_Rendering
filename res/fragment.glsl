#version 410

out vec4 out_color;
in vec3 position_ws;
in vec2 uv;
in vec3 normal_ws;
in vec3 normal_os;
uniform sampler2D my_texture;
uniform vec3 light_direction;
uniform vec3 point_light;

void main()
{
    vec4 texture_color = texture(my_texture, uv);
    float dir_light_intensity = -dot(normalize(normal_ws), light_direction);
    vec3 dir_to_point_light = normalize( position_ws - point_light );
    float point_light_intensity = -dot(normalize(normal_ws), dir_to_point_light);
    out_color = vec4((clamp(dir_light_intensity + point_light_intensity + 0.3, 0, 1)) * texture_color);
}
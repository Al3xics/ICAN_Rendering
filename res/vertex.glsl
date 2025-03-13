#version 410

layout(location = 0) in vec3 in_position_os;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal_os;
uniform mat4 view_projection_matrix;
uniform mat4 model_matrix;
out vec3 position_ws;
out vec2 uv;
out vec3 normal_ws;
out vec3 normal_os;

vec3 apply_matrix_to_position(mat4 matrix, vec3 point)
{
    vec4 tmp = matrix * vec4(point, 1.);
    return tmp.xyz / tmp.w;
}

vec3 apply_matrix_to_direction(mat4 matrix, vec3 direction)
{
    vec4 tmp = matrix * vec4(direction, 0.);
    return normalize(tmp.xyz);
}

void main()
{
    uv = in_uv;
    normal_os = in_normal_os;
    normal_ws = apply_matrix_to_position(model_matrix, in_normal_os);
    position_ws = apply_matrix_to_direction(model_matrix, in_position_os);

    gl_Position = view_projection_matrix * vec4(in_position_os, 1.);
}
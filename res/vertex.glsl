#version 410

// layout(location = 0) in vec2 in_position;
layout(location = 0) in vec3 in_position;
// uniform float aspect_ratio = 2;
uniform float time;
uniform float rotation_speed;
uniform mat4 view_projection_matrix;

void main()
{
    // vec3 position = in_position;
    // position.x += 0.25;
    // position.y += 0.25;
    // position.x += sin(time * rotation_speed);
    // position.y += cos(time * rotation_speed);
    // position.x /= aspect_ratio;


    // gl_Position = view_projection_matrix * vec4(in_position, 0., 1.);
    gl_Position = view_projection_matrix * vec4(in_position, 1.);
}
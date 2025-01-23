#version 410

layout(location = 0) in vec2 in_position;

void main()
{
    vec2 position = in_position;
    position.x += 0.25;
    position.y += 0.25;

    gl_Position = vec4(position, 0., 1.);
}
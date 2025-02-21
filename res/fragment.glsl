#version 410

out vec4 out_color;
in vec3 vertex_position;
in vec2 uv;
in vec3 normal;
uniform sampler2D my_texture;
uniform vec3 light_direction;

void main()
{
    vec4 texture_color = texture(my_texture, uv);
    float produit_scalaire = dot(normalize(normal), light_direction);
    produit_scalaire += 0.3;
    out_color = vec4(produit_scalaire * texture_color);
}
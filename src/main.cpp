#include "opengl-framework/opengl-framework.hpp" // Inclue la librairie qui va nous servir à faire du rendu
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

int main()
{
    // Initialisation
    gl::init("TPs de Rendering"); // On crée une fenêtre et on choisit son nom
    gl::maximize_window(); // On peut la maximiser si on veut

    auto const triangle_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position2D{0 /*Index de l'attribut dans le shader, on en reparle juste après*/}},
            .data   = {
                -1.f, -1.f, // Position2D du 1er sommet
                +1.f, -1.f, // Position2D du 2ème sommet
                0.f, +1.f  // Position2D du 3ème sommet
            },
        }},
    }};

    auto const rectangle_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position2D{0 /*Index de l'attribut dans le shader, on en reparle juste après*/}},
            .data   = {
                -0.5f, -0.5f,
                0.5f, -0.5f,
                -0.5f, 0.5f,
                0.5f, 0.5f
            },
        }},
        .index_buffer = {
            0, 1, 2,
            1, 2, 3
        },
    }};

    auto const shader = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/vertex.glsl"},
        .fragment = gl::ShaderSource::File{"res/fragment.glsl"},
    }};

    auto camera = gl::Camera{};
    gl::set_events_callbacks({camera.events_callbacks()});






    while (gl::window_is_open())
    {
        // Rendu à chaque frame
        glClearColor(0.f, 0.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // gl::bind_default_shader(); // On a besoin qu'un shader soit bind (i.e. "actif") avant de draw(). On en reparle dans la section d'après.
        shader.bind();
        // shader.set_uniform("aspect_ratio", gl::framebuffer_aspect_ratio());

        glm::mat4 const view_matrix = camera.view_matrix();
        glm::mat4 const projection_matrix = glm::infinitePerspective(glm::radians(90.f) /*field of view in radians*/, gl::framebuffer_aspect_ratio() /*aspect ratio*/, 0.001f /*near plane*/);
        glm::mat4 const rotation = glm::rotate(glm::mat4{1.f}, gl::time_in_seconds() /*angle de la rotation*/, glm::vec3{0.f, 0.f, 1.f} /* axe autour duquel on tourne */);
        glm::mat4 const translation = glm::translate(glm::mat4{1.f}, glm::vec3{0.f, 1.f, 0.f} /* déplacement */);
        // translation * rotation --> rotate le plane sur son centre
        // rotation * translation --> rotate le plane autour d'un axe (z ici)
        glm::mat4 const model_matrix = translation * rotation;

        glm::mat4 const view_projection_matrix = projection_matrix * view_matrix * model_matrix;

        shader.set_uniform("rotation_speed", 1.f);
        shader.set_uniform("time", gl::time_in_seconds());
        shader.set_uniform("view_projection_matrix", view_projection_matrix);
        // triangle_mesh.draw();
        rectangle_mesh.draw();
    }
}
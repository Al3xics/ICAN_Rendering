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
            .layout = {gl::VertexAttribute::Position2D{0 /*Index de l'attribut dans le shader, on en reparle juste après*/}, gl::VertexAttribute::UV(1)},
            .data   = {
                -1, -1, 0, 0,
                1, -1, 1, 0,
                -1, 1, 0, 1,
                1, 1, 1, 1,
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

    // auto camera = gl::Camera{};
    // gl::set_events_callbacks({camera.events_callbacks()});

    

    // auto const cube_mesh = gl::Mesh{{
    //     .vertex_buffers = {{
    //         .layout = {gl::VertexAttribute::Position3D{0 /*Index de l'attribut dans le shader, on en reparle juste après*/}},
    //         .data   = {
    //             // Face en bas
    //             -0.5f, -0.5f, -0.5f, // haut gauche : 0
    //             0.5f, -0.5f, -0.5f, // haut droite : 1
    //             -0.5f, -0.5f, 0.5f, // bas gauche : 2
    //             0.5f, -0.5f, 0.5f, // bas droite : 3
    //             // Face en haut
    //             -0.5f, 0.5f, -0.5f, // haut gauche : 4
    //             0.5f, 0.5f, -0.5f, // haut droite : 5
    //             -0.5f, 0.5f, 0.5f, // bas gauche : 6
    //             0.5f, 0.5f, 0.5f // bas droite : 7
    //         },
    //     }},
    //     .index_buffer = {
    //         // Face en bas
    //         0, 1, 2,
    //         1, 2, 3,
    //         //Face en haut
    //         4, 5, 6,
    //         5, 6, 7,
    //         // Face dèrrière
    //         0, 1, 4,
    //         1, 4, 5,
    //         // Face devant
    //         2, 3, 6,
    //         3, 6, 7,
    //         // Face gauche
    //         0, 2, 4,
    //         2, 4, 6,
    //         // Face droite
    //         1, 3, 5,
    //         3, 5, 7
    //     },
    // }};

    // glEnable(GL_DEPTH_TEST);

    auto const texture = gl::Texture{
        gl::TextureSource::File{ // Peut être un fichier, ou directement un tableau de pixels
            .path           = "res/texture.png",
            .flip_y         = true, // Il n'y a pas de convention universelle sur la direction de l'axe Y. Les fichiers (.png, .jpeg) utilisent souvent une direction différente de celle attendue par OpenGL. Ce booléen flip_y est là pour inverser la texture si jamais elle n'apparaît pas dans le bon sens.
            .texture_format = gl::InternalFormat::RGBA8, // Format dans lequel la texture sera stockée. On pourrait par exemple utiliser RGBA16 si on voulait 16 bits par canal de couleur au lieu de 8. (Mais ça ne sert à rien dans notre cas car notre fichier ne contient que 8 bits par canal, donc on ne gagnerait pas de précision). On pourrait aussi stocker en RGB8 si on ne voulait pas de canal alpha. On utilise aussi parfois des textures avec un seul canal (R8) pour des usages spécifiques.
        },
        gl::TextureOptions{
            .minification_filter  = gl::Filter::Linear, // Comment on va moyenner les pixels quand on voit l'image de loin ?
            .magnification_filter = gl::Filter::Linear, // Comment on va interpoler entre les pixels quand on zoom dans l'image ?
            .wrap_x               = gl::Wrap::Repeat,   // Quelle couleur va-t-on lire si jamais on essaye de lire en dehors de la texture ?
            .wrap_y               = gl::Wrap::Repeat,   // Idem, mais sur l'axe Y. En général on met le même wrap mode sur les deux axes.
        }
    };




    while (gl::window_is_open())
    {
        // Rendu à chaque frame
        glClearColor(0.f, 0.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // gl::bind_default_shader(); // On a besoin qu'un shader soit bind (i.e. "actif") avant de draw(). On en reparle dans la section d'après.
        shader.bind();
        shader.set_uniform("aspect_ratio", gl::framebuffer_aspect_ratio());

        // glm::mat4 const view_matrix = camera.view_matrix();
        // glm::mat4 const projection_matrix = glm::infinitePerspective(glm::radians(90.f) /*field of view in radians*/, gl::framebuffer_aspect_ratio() /*aspect ratio*/, 0.001f /*near plane*/);
        // glm::mat4 const rotation = glm::rotate(glm::mat4{1.f}, gl::time_in_seconds() /*angle de la rotation*/, glm::vec3{0.f, 0.f, 1.f} /* axe autour duquel on tourne */);
        // glm::mat4 const rotation2 = glm::rotate(glm::mat4{1.f}, gl::time_in_seconds() /*angle de la rotation*/, glm::vec3{0.f, 1.f, 0.f} /* axe autour duquel on tourne */);
        // glm::mat4 const translation = glm::translate(glm::mat4{1.f}, glm::vec3{0.f, 0.f, 0.f} /* déplacement */);
        // // translation * rotation --> rotate le plane sur son centre
        // // rotation * translation --> rotate le plane autour d'un axe (z ici)
        // glm::mat4 const model_matrix = translation * rotation * rotation2;

        // glm::mat4 const view_projection_matrix = projection_matrix * view_matrix * model_matrix;

        // shader.set_uniform("rotation_speed", 1.f);
        // shader.set_uniform("time", gl::time_in_seconds());
        // shader.set_uniform("view_projection_matrix", view_projection_matrix);
        shader.set_uniform("my_texture", texture);
        // triangle_mesh.draw();
        rectangle_mesh.draw();
        // cube_mesh.draw();
    }
}
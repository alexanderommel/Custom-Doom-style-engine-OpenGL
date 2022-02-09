#include <custom/plane_renderer.h>
#include <iostream>
#include <custom/doom_data.h>
#include <vector>
#include <custom/shader.h>

PlaneRenderer::PlaneRenderer(Shader& shader)
{
    this->shader = shader;
    this->init();
}

PlaneRenderer::~PlaneRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void PlaneRenderer::render(Texture2D& texture, mapvertex_t* vertices, unsigned int num_vertices,
    float height, int scale_factor, glm::vec3 color, float* vertex_array, float plane_width)
{

    //std::cout << "(PlaneRenderer) Rendering plane...\n";

    shader.Use();


    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_array) * 2 * num_vertices, vertex_array, GL_DYNAMIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Scale factor for textures
    float y_scale_factor = plane_width / texture.Height;
    float x_scale_factor = plane_width / texture.Width;
    
    x_scale_factor = x_scale_factor * 4;
    y_scale_factor = y_scale_factor * 4;

    //std::cout << "(PlaneRenderer) X_scale_factor -> " << x_scale_factor << "\n";


    glm::mat4 model;
    model = glm::mat4(1.0);
    //model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));

    this->shader.SetMatrix4("model", model);
    this->shader.SetFloat("height", height);
    this->shader.SetFloat("x_scale_factor", x_scale_factor);
    this->shader.SetFloat("y_scale_factor", y_scale_factor);

    // render textured quad
    this->shader.SetVector3f("plane_color", color);
    //glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, num_vertices);
    glBindVertexArray(0);
}

void PlaneRenderer::init()
{

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);


}
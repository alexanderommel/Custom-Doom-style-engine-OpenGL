#include "custom/line_renderer.h"
#include <iostream>
#include <custom/doom_data.h>

LineRenderer::LineRenderer(Shader& shader)
{
    this->shader = shader;
    this->init();
}

LineRenderer::~LineRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void LineRenderer::render(Texture2D& texture, mapvertex_t v1, mapvertex_t v2, float heigth, 
    float y_position, glm::vec3 color, float light_level,
    glm::vec3 normalVector, bool verbose)
{
    this->shader.Use();
    
    // Initialize values
    glm::vec2 vertex1 = glm::vec2(v1.x, v1.z);
    glm::vec2 vertex2 = glm::vec2(v2.x, v2.z);
    float width = computeWidth(vertex1, vertex2);
    //std::cout << "(LineRenderer) width=" << width << "\n";
    //std::cout << "(LineRenderer) height=" << heigth << "\n";
    glm::vec2 world_position = getWorldRelativePosition(vertex1, vertex2);
    glm::vec2 opengl_position = getOpenGLRelativePosition(vertex1, vertex2);
    // Testeamos la posicion global y cambiamos las coordenadas si
    // <+,+> -> <-,->
    // <-,+> -> <+,->
    // Todas las rotaciones siempre se aplican desde el eje en sentido antihorario
    /*
    float reflejar_normal = 1.0f;
    if (opengl_position.y <0 && opengl_position.x==0)
    {
        reflejar_normal = -1.0f;
    }
    if (opengl_position.x<0 && opengl_position.y ==0)
    {
        reflejar_normal = -1.0f;
    }
    if (opengl_position.x>0 && opengl_position.y==0)
    {
        reflejar_normal = -1.0f;
    }
    */
    
    if (opengl_position.x > 0 && opengl_position.y > 0)
    {
        opengl_position = opengl_position.operator*=(-1);
    }
    // Segundo test de rotacion
    if (opengl_position.x < 0 && opengl_position.y >0)
    {
        opengl_position = opengl_position.operator*=(-1);
    }
    glm::vec2 rotation_axis_vec = glm::vec2(1.0, 0.0); // X axis
    float angle = computeAngleBetweenVectors(rotation_axis_vec, opengl_position);
    // Angle must be less than 180
    float degrees = angle * 180;
    degrees = degrees / glm::pi<float>();
    glm::mat4 model;
    model = glm::mat4(1.0);

    model = glm::translate(model, glm::vec3(0.0f, y_position, 0.0f));
    model = glm::translate(model, glm::vec3(world_position.x, 0.5 * heigth, world_position.y));
    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f)); // then rotate

    int kk = 0;
    for (size_t i = 0; i < 20; i++)
    {
        kk = kk + 2;
    }


    model = glm::scale(model, glm::vec3(width, heigth, 1.0f)); // last scale

    this->shader.SetMatrix4("model", model);


    this->shader.SetVector3f("aNormal", normalVector);

    float y_scale_factor = heigth / texture.Height;
    float x_scale_factor = width / texture.Width;

    y_scale_factor = y_scale_factor * 4;
    x_scale_factor = x_scale_factor * 4;

    // render textured quad
    this->shader.SetVector3f("sidedef_color", color);
    this->shader.SetFloat("x_scale_factor", x_scale_factor);
    this->shader.SetFloat("y_scale_factor", y_scale_factor);
    this->shader.SetFloat("ambientStrength", light_level);

    // material properties
    this->shader.SetFloat("material.shininess", texture.shininess);
    this->shader.SetInteger("noSpecular", texture.noSpecularColor);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

float LineRenderer::computeWidth(glm::vec2 v1, glm::vec2 v2) {
    // y coordinate belongs to z coordinate
    glm::vec2 position = getOpenGLRelativePosition(v1, v2);
    float width = (position.x * position.x) + (position.y * position.y);
    width = sqrt(width);
    return width;
}

glm::vec2 LineRenderer::getWorldRelativePosition(glm::vec2 v1, glm::vec2 v2) {
    float x = v2.x + v1.x;
    float z = v2.y + v1.y;
    x = x / 2;
    z = z / 2;
    glm::vec2 position = glm::vec2(x, z);
    return position;
}

glm::vec2 LineRenderer::getOpenGLRelativePosition(glm::vec2 v1, glm::vec2 v2) {
    float dx = v2.x - v1.x;
    float dz = v2.y - v1.y;
    glm::vec2 position = glm::vec2(dx, dz);
    return position;
}

float LineRenderer::computeAngleBetweenVectors(glm::vec2 v1, glm::vec2 v2) {

    glm::vec2 nv1 = glm::normalize(v1);
    glm::vec2 nv2 = glm::normalize(v2);
    float dot = glm::dot(nv1, nv2);
    float angle = acos(dot);
    return angle;
}

void LineRenderer::init()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f
    };


    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
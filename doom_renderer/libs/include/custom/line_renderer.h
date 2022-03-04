#ifndef __LINE_RENDERER__
#define __LINE_RENDERER__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <custom/doom_data.h>
#include <custom/resource_manager.h>
#include "custom/texture.h"
#include "custom/shader.h"


class LineRenderer
{
public:
    LineRenderer(Shader &shader); // Data is by default a square on the 1 and 2 quadrant of a xy plane
    ~LineRenderer();
    // Renders a perpendicular quad to the xz plane
    void render(
        Texture2D &texture,
        mapvertex_t v1, // xz coordinates
        mapvertex_t v2, // xz coordinates
        float heigth,
	    float y_position, // point on y axis where the wall is raised
        glm::vec3 color,
        float light_level,
        glm::vec3 normalVector,
        bool verbose);
private:
    Shader shader; 
    unsigned int VAO;
    float computeWidth(glm::vec2 v1,glm::vec2 v2); // Computes Wall width from vertex1 and vertex2 distance
    glm::vec2 getWorldRelativePosition(glm::vec2 v1,glm::vec2 v2); // Obtains the vertex between vtx1 and vtx2, used for translation
    glm::vec2 getOpenGLRelativePosition(glm::vec2 v1,glm::vec2 v2); // Obtains the vertex between vtx1 and vtx2 but located at (0,0) 
    float computeAngleBetweenVectors(glm::vec2 v1,glm::vec2 v2); // Computes the angle between the last vector and the axis x
    void init();
};

#endif
#ifndef __PLANE_RENDERER__
#define __PLANE_RENDERER__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "custom/texture.h"
#include "custom/shader.h"
#include <vector>
#include <custom/doom_data.h>


class PlaneRenderer
{
public:
    PlaneRenderer(Shader &shader); 
    ~PlaneRenderer();
    // Renders a perpendicular quad to the xz plane
    void render(
        Texture2D &texture,
        mapvertex_t* vertices,
        unsigned int num_vertices,
	    float height,
	    int scale_factor,
        glm::vec3 color,
        float* vertex_array,
        float plane_width
    );
private:
    Shader shader; 
    unsigned int VAO;
    unsigned int VBO;
    void init();
};

#endif
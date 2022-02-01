#ifndef DOOM_MAP_H
#define DOOM_MAP_H

#include <map>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <custom/rendertree.h>
#include <custom/resource_manager.h>
#include <custom/doom_data.h>

class DoomMap
{
    public:
        DoomMap();
        bool addSectorToRenderTree(mapsector_t *sector);
        void update();
        void render();
    private:
        void compileSector(mapsector_t *sector); // Fills the null data on sidedefs
        void init(unsigned int width_, unsigned int height_); // Inicializar arbol de renderizado
        RenderTree* render_tree;
};

#endif
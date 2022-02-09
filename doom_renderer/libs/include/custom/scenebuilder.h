#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include <map>
#include <string>
#include <glad/glad.h>
#include <vector>
#include <custom/doom_map.h>
#include <custom/doom_data.h>

class SceneBuilder
{
    public:
        SceneBuilder(); 
        ~SceneBuilder();
        void buildSector(
            mapvertex_t* vertices,
            std::vector<std::string> ceil_front_texture_names,
            std::vector<std::string> ceil_back_texture_names,
            std::vector<std::string> middle_texture_names,
            std::vector<std::string> floor_front_texture_names,
            std::vector<std::string> floor_back_texture_names,
            std::string floor_texture_name,
            std::string ceil_texture_name,
            int floor_height,
            int ceil_height,
            unsigned int light_level,
            mapsector_t &target,
            int num_vertices
            );
};

#endif
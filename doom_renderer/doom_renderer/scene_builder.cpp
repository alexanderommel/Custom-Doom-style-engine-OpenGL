#include <custom/doom_data.h>
#include <custom/doom_map.h>
#include <custom/scenebuilder.h>
#include <iostream>
#include <custom/resource_manager.h>

SceneBuilder::SceneBuilder() {
}

SceneBuilder::~SceneBuilder() {

}

void SceneBuilder::buildSector(
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
) {
    std::cout << "(SceneBuilder) Creating sector\n";
    //int num_vertices = vertices.size();
     //static mapsector_t mapsectorx;
     //static mapsector_t* sector = &mapsectorx;
     mapvertex_t* sector_vertices = new mapvertex_t[num_vertices];
     maplinedef_t* sector_linedefs = new maplinedef_t[num_vertices];
     map_flatplane_t floor_plane;
     map_flatplane_t ceil_plane;
    floor_plane.texture_name = floor_texture_name;
    floor_plane.texture_name = floor_texture_name;
    floor_plane.y_position = floor_height;
    ceil_plane.texture_name = ceil_texture_name;
    ceil_plane.y_position = ceil_height;
    for (size_t i = 0; i < num_vertices; i++)
    {
        static maplinedef_t linedef;
        linedef.has_cbs = false;
        linedef.has_cfs = false;
        linedef.has_fbs = false;
        linedef.has_ffs = false;
        linedef.has_ms = false;
        // middle sidedef
        if (middle_texture_names.size()>0)
        {
            std::string texture_name = middle_texture_names[i];
            static mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.middle_sidedef = sidedef;
            linedef.has_ms = true;
        }
        // ceil front sidedef
        if (ceil_front_texture_names.size() > 0)
        {
            std::string texture_name = ceil_front_texture_names[i];
            static mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.ceil_front_sidedef = sidedef;
            linedef.has_cfs=true;
        }
        // ceil back sidedef
        if (ceil_back_texture_names.size() > 0)
        {
            std::string texture_name = ceil_back_texture_names[i];
            static mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.ceil_back_sidedef = sidedef;
            linedef.has_cbs = true;
        }
        // floor front sidedef
        if (floor_front_texture_names.size() > 0)
        {
            std::string texture_name = floor_front_texture_names[i];
            static mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.floor_front_sidedef = sidedef;
            linedef.has_ffs=true;
        }
        // floor back sidedef
        if (floor_back_texture_names.size() > 0)
        {
            std::string texture_name = floor_back_texture_names[i];
            static mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.floor_back_sidedef = sidedef;
            linedef.has_fbs = true;
        }
        sector_linedefs[i] = linedef;
        sector_vertices[i] = vertices[i];
    }
    // fill data on sector
    target.compiled = false;
    target.vertices = sector_vertices;
    target.linedefs = sector_linedefs;
    target.ceil_plane = ceil_plane;
    target.floor_plane = floor_plane;
    // light level goes from 0 to 1, but expresed from range 0 to 256
    float intensity = light_level / 256.0;
    std::cout << "(SceneBuilder) intensity-> " << intensity << "\n";
    if (intensity<0 || intensity>1)
    {
        intensity = 1.0;
    }
    target.ilumination = intensity;
    target.num_vertices = num_vertices;
    
}
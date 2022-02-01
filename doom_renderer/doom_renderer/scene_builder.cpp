#include <custom/doom_data.h>
#include <custom/doom_map.h>
#include <custom/scenebuilder.h>


SceneBuilder::SceneBuilder(DoomMap *map_) {
	this->map = map_;
}

SceneBuilder::~SceneBuilder() {

}

mapsector_t* SceneBuilder::buildSector(
    std::vector<mapvertex_t> vertices,
    std::vector<std::string> ceil_front_texture_names,
    std::vector<std::string> ceil_back_texture_names,
    std::vector<std::string> middle_texture_names,
    std::vector<std::string> floor_front_texture_names,
    std::vector<std::string> floor_back_texture_names,
    std::string floor_texture_name,
    std::string ceil_texture_name,
    int floor_height,
    int ceil_height,
    unsigned int light_level
) {
    
    int num_vertices = vertices.size();
    mapsector_t sector;
    mapvertex_t* sector_vertices = new mapvertex_t[num_vertices];
    maplinedef_t* sector_linedefs = new maplinedef_t[num_vertices];
    map_flatplane_t floor_plane, ceil_plane;
    floor_plane.texture_name = floor_texture_name;
    floor_plane.y_position = floor_height;
    ceil_plane.texture_name = ceil_texture_name;
    ceil_plane.y_position = ceil_height;
    for (size_t i = 0; i < num_vertices; i++)
    {
        maplinedef_t linedef;
        // middle sidedef
        if (middle_texture_names.size()>0)
        {
            std::string texture_name = middle_texture_names[i];
            mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.middle_sidedef = sidedef;
            linedef.has_cfs = false;
        }
        // ceil front sidedef
        if (ceil_front_texture_names.size() > 0)
        {
            std::string texture_name = ceil_front_texture_names[i];
            mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.ceil_front_sidedef = sidedef;
            linedef.has_cfs = true;
        }
        // ceil back sidedef
        if (ceil_back_texture_names.size() > 0)
        {
            std::string texture_name = ceil_back_texture_names[i];
            mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.ceil_back_sidedef = sidedef;
            linedef.has_cfs = false;
        }
        // floor front sidedef
        if (floor_front_texture_names.size() > 0)
        {
            std::string texture_name = floor_front_texture_names[i];
            mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.floor_front_sidedef = sidedef;
            linedef.has_cfs = false;
        }
        // floor back sidedef
        if (floor_back_texture_names.size() > 0)
        {
            std::string texture_name = floor_back_texture_names[i];
            mapsidedef_t sidedef;
            sidedef.texture_name = texture_name;
            linedef.floor_back_sidedef = sidedef;
            linedef.has_cfs = false;
        }
        sector_linedefs[i] = linedef;
        sector_vertices[i] = vertices[i];
    }
    // fill data on sector
    sector.compiled = false;
    sector.vertices = sector_vertices;
    sector.linedefs = sector_linedefs;
    sector.ceil_plane = ceil_plane;
    sector.floor_plane = floor_plane;
    sector.ilumination = light_level;
    mapsector_t *pointer = &sector;
    return pointer;
}
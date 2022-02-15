// Data definitions based on the original Doom Source Code definitions but with some modifications
// Names are conserved

#ifndef __DOOMDATA__
#define __DOOMDATA__

#include <string>

struct mapvertex_t
{
	int x;
	int z;
};


struct mapsidedef_t
{
	int y_position;
	unsigned int height;
	std::string texture_name;
};


struct maplinedef_t
{
	bool has_cfs;
	bool has_cbs;
	bool has_ms;
	bool has_ffs;
	bool has_fbs;
	struct mapvertex_t v1;
	struct mapvertex_t v2;
	struct mapsidedef_t ceil_front_sidedef;
	struct mapsidedef_t ceil_back_sidedef;
	struct mapsidedef_t middle_sidedef;
	struct mapsidedef_t floor_front_sidedef;
	struct mapsidedef_t floor_back_sidedef;
	bool is_shared;
	struct mapsector_t* neighbor_sector;
};

struct map_flatplane_t
{
	int y_position;
	std::string texture_name;
};

struct mapsector_t
{
	struct mapvertex_t* vertices;
	float* flatplane_vertex_array;
	struct maplinedef_t* linedefs;
	struct map_flatplane_t floor_plane;
	struct map_flatplane_t ceil_plane;
	float ilumination;
	float parent_ilumination;
	bool compiled;
	unsigned int num_vertices;
};

#endif
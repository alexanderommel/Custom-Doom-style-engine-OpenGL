#include <custom/doom_map.h>
#include <custom/doom_data.h>
#include <iostream>
#include <queue>
#include <custom/resource_manager.h>

bool isLinedefSharedWithSector(maplinedef_t* linedef, mapsector_t* sector, mapsector_t* neighbor_sector_);
void setNeighborSectors(mapsector_t* s1, std::vector<RenderNode*> neighbors);

DoomMap::DoomMap() {
	init();
	this->render_tree = new RenderTree(this->line_shader, this->plane_shader);
	
}

void DoomMap::init() {
	static Shader sidedef_shader = ResourceManager::GetShader("sidedefshader");
	static Shader flatplane_shader = ResourceManager::GetShader("flatplaneshader");
	this->line_shader = &sidedef_shader;
	this->plane_shader = &flatplane_shader;
}

// Updates the values of the mapsector using the values of the parent sector
void DoomMap::compileSector(mapsector_t* sector, mapsector_t* parent) {

	std::cout << "(DoomMap) compiling sector...\n";
	if (sector->linedefs[0].has_ms==true)
	{
		std::cout << "(DoomMap) updating main sector sidedefs...\n";
		// Sidedef y position is equal to the floor plane position
		// Sidedef height is equal to the absolute value of floor_position - ceil_position
		unsigned int height = abs(sector->ceil_plane.y_position - sector->floor_plane.y_position);
		for (size_t i = 0; i < sector->num_vertices; i++)
		{
			sector->linedefs[i].middle_sidedef.y_position = sector->floor_plane.y_position;
			sector->linedefs[i].middle_sidedef.height = height;
		}
		
	}
	if (parent!=NULL)
	{
		std::cout << "(DoomMap) updating subsector sidedefs...\n";
		unsigned int ceil_height = abs(sector->ceil_plane.y_position - parent->ceil_plane.y_position);
		unsigned int floor_height = abs(sector->floor_plane.y_position - parent->floor_plane.y_position);
		if (sector->linedefs[0].has_cfs == true)
		{
			// CFS -> Ceil Front Sidedef
			// It means that the ceil of the subsector is lower than the ceil of the parent
			for (size_t i = 0; i < sector->num_vertices; i++)
			{
				sector->linedefs[i].ceil_front_sidedef.y_position = sector->ceil_plane.y_position;
				sector->linedefs[i].ceil_front_sidedef.height = ceil_height;
			}
		}
		if (sector->linedefs[0].has_cbs == true)
		{
			// CBS -> Ceil Back Sidedef
			// It means that the ceil of the subsector is higher than the ceil of the parent
			for (size_t i = 0; i < sector->num_vertices; i++)
			{
				sector->linedefs[i].ceil_back_sidedef.y_position = parent->ceil_plane.y_position;
				sector->linedefs[i].ceil_back_sidedef.height = ceil_height;
			}
		}
		if (sector->linedefs[0].has_ffs == true)
		{
			// FFS -> Floor Front Sidedef
			// It means that the floor of the subsector is higher than the floor of the parent
			for (size_t i = 0; i < sector->num_vertices; i++)
			{
				sector->linedefs[i].floor_front_sidedef.y_position = parent->floor_plane.y_position;
				sector->linedefs[i].floor_front_sidedef.height = floor_height;
			}
		}
		if (sector->linedefs[0].has_fbs == true)
		{
			// FBS -> Floor Back Sidedef
			// It means that the floor of the subsector is lower than the floor of the parent
			for (size_t i = 0; i < sector->num_vertices; i++)
			{
				sector->linedefs[i].floor_back_sidedef.y_position = sector->floor_plane.y_position;
				sector->linedefs[i].floor_back_sidedef.height = floor_height;
			}
		}
		//Child sector inherits parent sector ilumination
		sector->parent_ilumination = parent->ilumination;
		//For each linedef, test if it is a neighbor linedef
		// if true then set linedef.shared=true
		// linedef.neighbor_sector=&sector
	}


	std::cout << "(DoomMap) updating linedef vertices...\n";
	for (unsigned int j = 0; j < sector->num_vertices-1; j++)
	{
		 mapvertex_t v1 = sector->vertices[j];
		 mapvertex_t v2 = sector->vertices[j + 1];
		sector->linedefs[j].v1 = v1;
		sector->linedefs[j].v2 = v2;
	}
	sector->linedefs[sector->num_vertices - 1].v1 = sector->vertices[sector->num_vertices - 1];
	sector->linedefs[sector->num_vertices - 1].v2 = sector->vertices[0];

	// Create vertex arrays for rendering planes
	std::cout << "(DoomMap) updating flat_planes vertex array\n";

	// each vertex has 4 coordinates

	

	float* points = new float[sector->num_vertices * 4];

	float scale_factor = 1.0f;

	float angle = 360 / sector->num_vertices;

	//  (0,1) Vertex, (2,3) Texture coordinates

	for (size_t i = 0; i < sector->num_vertices; i++)
	{
		mapvertex_t vertex = sector->vertices[i];
		int k = 4 * i;
		points[k] = vertex.x;
		points[k + 1] = vertex.z;
		float step = angle * i;
		step = step - 45;
		float radian = step * glm::pi<float>();
		radian = radian / 180;
		float coordinate_x = cos(radian);
		float coordinate_y = sin(radian);
		coordinate_x = coordinate_x / 2;
		coordinate_y = coordinate_y / 2;
		coordinate_x = coordinate_x + 0.5;
		coordinate_y = coordinate_y + 0.5;
		coordinate_x = coordinate_x * scale_factor;
		coordinate_y = coordinate_y * scale_factor;
		points[k + 2] = coordinate_x;
		points[k + 3] = coordinate_y;
	}
	sector->flatplane_vertex_array = points;

	std::cout << "(DoomMap) compilation succesful!\n";
}

// Add the mapsector to the respective node in the tree
bool DoomMap::addSectorToRenderTree(mapsector_t* sector) {
	std::cout << "(DoomMap) Adding sector to the render tree...\n";
	// Test if the tree has a root sector
	if (this->render_tree->isRootNodeNull())
	{
		if (sector->linedefs[0].has_ms==true)
		{
			compileSector(sector,NULL);
			std::cout << "(DoomMap) Setting root RenderNode\n";
			static RenderNode *root_node = new RenderNode(0, this->line_shader, this->plane_shader);
			root_node->sector = sector;
			this->render_tree->setRootNode(root_node);
			return true;
		}
		return false;
	}

	//Breadth first search

	int depth = 0;
	int breadth = 0;
	std::cout << "(DoomMap) Breadth first search for parent sectors\n";
	std::queue<RenderNode*> queue; 
	queue.push(this->render_tree->root_node);
	while (queue.empty()==false)
	{
		depth = depth + 1;
		RenderNode* current = queue.back();
		std::cout << "(DoomMap) Current node id is: " << current->id << "\n";
		queue.pop();
		std::cout << "(DoomMap) Queue size is: " << queue.size() << "\n";
		std::vector<RenderNode*> children = current->children;
		// It is assured that there's at most one child node that has a parent sector
		// We assume that the current sector is child of root sector!!!
		bool child_parent_found = false;
		for (size_t i = 0; i < children.size(); i++)
		{
			RenderNode* child = children[i];
			std::cout << "(DoomMap) Testing child with id: " << child->id << "\n";
			bool subsector_test = isSubsector(child->sector, sector);
			if (subsector_test)
			{
				std::cout << "(DoomMap) Testing passed...parent node found\n";
				queue.push(child);
				breadth = i;
				child_parent_found = true;
				break;
			}
		}
		// If no parent sector found, then the new rendernode is a neighbor of current node
		if (child_parent_found==false)
		{
			//std::cout << "(DoomMap) No child is parent of current sector\n";
			std::cout << "(DoomMap) Linking this sector to the current parent sector\n";
			std::cout << "(DoomMap) Current parent id is: " << current->id << "\n";
			// Compile basic info
			compileSector(sector, current->sector);
			// Compile info related to lights
			setNeighborSectors(sector, current->children);

			int node_id = depth*1000;
			node_id = node_id + breadth;
			std::cout << "(DoomMap) Generating new id with id=" << node_id << "\n";
			RenderNode* new_node = new RenderNode(node_id, this->line_shader, this->plane_shader);
			std::cout << "(DoomMap) Current child id is: " << new_node->id << "\n";
			new_node->sector = sector;
			new_node->children = std::vector<RenderNode*>();
			current->children.push_back(new_node);

		}	
	}
	return true;
}

bool DoomMap::isSubsector(mapsector_t* parent, mapsector_t* sector) {
	std::cout << "(DoomMap) Testing subsector condition\n";
	// All values from pnpoly must be equal to 1 in order for this to become a subsector
	// A subsector has a subsector_test equal to num_vertices
	// A neighbor sector has a subsector_test equal to 0
	int subsector_test = 0;
	for (size_t i = 0; i < sector->num_vertices; i++)
	{
		//std::cout << "(DoomMap) Testing vertex <" << sector->vertices[i].x << "," << sector->vertices[i].z << ">\n";
		int is_subsector = pnpoly(parent->num_vertices,parent->vertices, sector->vertices[i]);
		subsector_test = subsector_test + is_subsector;
		//std::cout << "(DoomMap) Status: " << is_subsector << "\n";
	}
	//std::cout << "(DoomMap) Subsector test is ->" << subsector_test << "\n";
	if (subsector_test==sector->num_vertices)
	{
		return true;
	}
	return false;
}

// 1 in, 0 out
int DoomMap::pnpoly(int nvert, mapvertex_t* vertices, mapvertex_t vertex)
{
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((vertices[i].z > vertex.z) != (vertices[j].z > vertex.z)) &&
			(vertex.x < (vertices[j].x - vertices[i].x) *
				(vertex.z - vertices[i].z) / (vertices[j].z - vertices[i].z) + vertices[i].x))
			c = !c;
	}
	return c;
}

void DoomMap::update() {

}
void DoomMap::render() {
	std::cout << "(DoomMap) Map rendering\n";
	this->render_tree->render();
	//this->render_tree->trasversalOrderPrintContent();
}

void setNeighborSectors(mapsector_t* s1, std::vector<RenderNode*> neighbors) {
	// Neighbor sectors are sectors that share a linedef
	//std::cout << "(DoomMap) Searching neighbor sectors\n";
	//std::cout << "(DoomMap) Sector 1 has " << s1->num_vertices << " linedefs\n";
	for (size_t i = 0; i < s1->num_vertices; i++)
	{
		maplinedef_t* candidate_linedef = &s1->linedefs[i];
		//std::cout << "(DoomMap) Testing linedef with vertices  (<" << candidate_linedef.v1.x << "," << candidate_linedef.v1.z << ">," <<
			//"<" << candidate_linedef.v2.x << "," << candidate_linedef.v2.z << ">)\n";
		int num_neighbors = neighbors.size();
		for (size_t j = 0; j < num_neighbors; j++)
		{
			bool found_neighbor = isLinedefSharedWithSector(candidate_linedef, s1, neighbors[j]->sector);
			if (found_neighbor)
			{
				//std::cout << "(DoomMap) Neighbor found for linedef!\n";
				break;
			}
		}
	}
	//std::cout << "(DoomMap) Search finished!\n";
}

bool isLinedefSharedWithSector(maplinedef_t* linedef, mapsector_t* sector, mapsector_t* neighbor_sector_) {
	//std::cout << "(DoomMap) Testing shared status\n";
	for (size_t i = 0; i < neighbor_sector_->num_vertices; i++)
	{
		maplinedef_t neighbor_linedef = neighbor_sector_->linedefs[i];
		if ((linedef->v1.x==neighbor_linedef.v2.x) &&
			(linedef->v2.x == neighbor_linedef.v1.x) &&
			(linedef->v1.z == neighbor_linedef.v2.z) &&
			(linedef->v2.z == neighbor_linedef.v1.z))
		{
			linedef->is_shared = true;
			linedef->neighbor_sector = neighbor_sector_;
			neighbor_linedef.is_shared = true;
			neighbor_linedef.neighbor_sector = sector;
			return true;
		}
	}
	return false;
}
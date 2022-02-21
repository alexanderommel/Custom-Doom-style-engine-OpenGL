#include <custom/rendernode.h>
#include <iostream>
#include <custom/doom_data.h>
#include <custom/shader.h>
#include <custom/resource_manager.h>
#include <custom/texture.h>
#include <custom/line_renderer.h>
#include <custom/plane_renderer.h>

RenderNode::RenderNode(unsigned int id, Shader *line_shader_, Shader *plane_shader_) {
	this->id = id;
	this->line_shader = line_shader_;
	this->plane_shader = plane_shader_;
	this->sector = NULL;
	static LineRenderer *line_renderer_ = new LineRenderer(*(this->line_shader));
	this->line_renderer = line_renderer_;
	static PlaneRenderer* plane_renderer_ = new PlaneRenderer(*(this->plane_shader));
	this->plane_renderer = plane_renderer_;
}

RenderNode::~RenderNode(){}

void RenderNode::addChild(RenderNode *node) {
	this->children.push_back(node);
}

void RenderNode::addSector(mapsector_t *sector_) {
	this->sector = sector_;
}

void RenderNode::renderMiddleSidedef() {
	//std::cout << "(RenderNode) Rendering middle sidedefs\n";
	for (size_t i = 0; i < this->sector->num_vertices; i++)
	{
		//std::cout << "(RenderNode) Rendering sidedef " << i << "\n";
		this->line_shader->Use();
		float direction = -1.0f;
		if (this->sector->counterclock==true)
		{
			direction = direction * -1;
		}
		glm::vec3 normalVector = direction * this->sector->linedefs[i].normal;

		Texture2D tex1 = ResourceManager::GetTexture(this->sector->linedefs[i].middle_sidedef.texture_name);
		tex1.Bind();
		line_renderer->render(tex1,
			this->sector->linedefs[i].v1,
			this->sector->linedefs[i].v2,
			this->sector->linedefs[i].middle_sidedef.height,
			this->sector->linedefs[i].middle_sidedef.y_position,
			glm::vec3(1.0f, 1.0f, 1.0f),this->sector->ilumination,
			normalVector,true);
		glDisable(GL_CULL_FACE);
	}
}

void RenderNode::renderCeilFrontSidedef() {
	//std::cout << "(RenderNode) Rendering ceil front sidedefs\n";
	for (size_t i = 0; i < this->sector->num_vertices; i++)
	{
		if (this->sector->linedefs[i].is_shared)
		{
			if (this->sector->linedefs[i].neighbor_sector->ceil_plane.y_position ==
				this->sector->ceil_plane.y_position)
			{
				continue;
			}
		}
		//std::cout << "(RenderNode) Rendering sidedef " << i << "\n";
		this->line_shader->Use();
		float direction = 1.0f;
		if (this->sector->counterclock==true)
		{
			direction = direction * -1;
		}
		glm::vec3 normalVector = direction * this->sector->linedefs[i].normal;
		Texture2D tex1 = ResourceManager::GetTexture(this->sector->linedefs[i].ceil_front_sidedef.texture_name);
		tex1.Bind();
		line_renderer->render(tex1,
			this->sector->linedefs[i].v1,
			this->sector->linedefs[i].v2,
			this->sector->linedefs[i].ceil_front_sidedef.height,
			this->sector->linedefs[i].ceil_front_sidedef.y_position,
			glm::vec3(1.0f, 1.0f, 1.0f), this->sector->parent_ilumination,
			normalVector,false);
	}
}

void RenderNode::renderCeilBackSidedef() {
	//std::cout << "(RenderNode) Rendering ceil back sidedefs\n";
	for (size_t i = 0; i < this->sector->num_vertices; i++)
	{
		if (this->sector->linedefs[i].is_shared)
		{
			if (this->sector->linedefs[i].neighbor_sector->ceil_plane.y_position ==
				this->sector->ceil_plane.y_position)
			{
				continue;
			}
		}
		//std::cout << "(RenderNode) Rendering sidedef " << i << "\n";
		this->line_shader->Use();
		float direction = -1.0f;
		if (this->sector->counterclock==true)
		{
			direction = direction * -1;
		}
		glm::vec3 normalVector = direction * this->sector->linedefs[i].normal;
		Texture2D tex1 = ResourceManager::GetTexture(this->sector->linedefs[i].ceil_back_sidedef.texture_name);
		tex1.Bind();
		line_renderer->render(tex1,
			this->sector->linedefs[i].v1,
			this->sector->linedefs[i].v2,
			this->sector->linedefs[i].ceil_back_sidedef.height,
			this->sector->linedefs[i].ceil_back_sidedef.y_position,
			glm::vec3(1.0f, 1.0f, 1.0f), this->sector->ilumination,
			normalVector,false);
	}
}

void RenderNode::renderFloorFrontSidedef() {
	//std::cout << "(RenderNode) Rendering floor front sidedefs\n";
	for (size_t i = 0; i < this->sector->num_vertices; i++)
	{
		if (this->sector->linedefs[i].is_shared)
		{

			if (this->sector->floor_plane.y_position < this->sector->linedefs[i]
				.neighbor_sector->floor_plane.y_position)
			{

				continue;
			}
		}
		//Configure ilumination values
		//If this sidedef is a neighbor sidedef then it uses neighbor sector ilumination
		//the otherway it uses parent ilumination
		float sidedef_ilumination_level = 1.0f;
		if (this->sector->linedefs[i].is_shared)
		{
			//std::cout << " (RenderNode) Shared linedef found!!!!\n";
			sidedef_ilumination_level = this->sector->linedefs[i].neighbor_sector->ilumination;
		}
		else {
			sidedef_ilumination_level = this->sector->parent_ilumination;
			//sidedef_ilumination_level = 0.0f;
		}
		this->line_shader->Use();
		float direction = 1.0f;
		if (this->sector->counterclock==true)
		{
			direction = direction * -1.0;
		}
		glm::vec3 normalVector = direction * this->sector->linedefs[i].normal;
		Texture2D tex1 = ResourceManager::GetTexture(this->sector->linedefs[i].floor_front_sidedef.texture_name);
		tex1.Bind();
		line_renderer->render(tex1,
			this->sector->linedefs[i].v1,
			this->sector->linedefs[i].v2,
			this->sector->linedefs[i].floor_front_sidedef.height,
			this->sector->linedefs[i].floor_front_sidedef.y_position,
			glm::vec3(1.0f, 1.0f, 1.0f), sidedef_ilumination_level,
			normalVector,false);
	}
}

void RenderNode::renderFloorBackSidedef() {
	//std::cout << "(RenderNode) Rendering floor back sidedefs\n";
	for (size_t i = 0; i < this->sector->num_vertices; i++)
	{
		if (this->sector->linedefs[i].is_shared)
		{
			if (this->sector->linedefs[i].neighbor_sector->floor_plane.y_position==
				this->sector->floor_plane.y_position)
			{
				continue;
			}
		}
		//std::cout << "(RenderNode) Rendering sidedef " << i << "\n";
		this->line_shader->Use();
		// normal vector
		float direction = -1.0f;
		if (this->sector->counterclock)
		{
			direction = direction * -1;
		}
		glm::vec3 normalVector = direction * this->sector->linedefs[i].normal;
		Texture2D tex1 = ResourceManager::GetTexture(this->sector->linedefs[i].floor_back_sidedef.texture_name);
		tex1.Bind();
		line_renderer->render(tex1,
			this->sector->linedefs[i].v1,
			this->sector->linedefs[i].v2,
			this->sector->linedefs[i].floor_back_sidedef.height,
			this->sector->linedefs[i].floor_back_sidedef.y_position,
			glm::vec3(1.0f, 1.0f, 1.0f), this->sector->ilumination,
			normalVector,false);
	}
}

void RenderNode::renderCeilPlane() {
	//std::cout << "(RenderNode) Rendering Ceil Plane\n";
	//std::cout << "(RenderNode) Sector id is -> " << this->id << "\n";
	float sector_width = abs(this->sector->vertices[0].x - this->sector->vertices[2].x);
	this->plane_shader->Use();
	// normal vector
	float direction = -1.0f;
	glm::vec3 normalVector = { 0.0f,direction,0.0f };
	Texture2D ceil_texture = ResourceManager::GetTexture(this->sector->ceil_plane.texture_name);
	ceil_texture.Bind();
	plane_renderer->render(ceil_texture,
		this->sector->vertices,
		this->sector->num_vertices,
		this->sector->ceil_plane.y_position,
		6,
		glm::vec3(1.0f, 1.0f, 1.0f), 
		this->sector->flatplane_vertex_array,sector_width,this->sector->ilumination,
		normalVector);
}

void RenderNode::renderFloorPlane() {
	//std::cout << "(RenderNode) Rendering Floor Plane\n";
	//std::cout << "(RenderNode) Sector id is -> " << this->id << "\n";
	// distance between two vertices to estimate sector width (Temporal)
	float sector_width = abs(this->sector->vertices[0].x - this->sector->vertices[2].x);
	this->plane_shader->Use();
	// normal vector
	float direction = 1.0f;
	glm::vec3 normalVector = { 0.0f,direction,0.0 };
	Texture2D floor_texture = ResourceManager::GetTexture(this->sector->floor_plane.texture_name);
	floor_texture.Bind();
	plane_renderer->render(floor_texture,
		this->sector->vertices,
		this->sector->num_vertices,
		this->sector->floor_plane.y_position,
		6,
		glm::vec3(1.0f, 1.0f, 1.0f),this->sector->flatplane_vertex_array, sector_width,
		this->sector->ilumination,
		normalVector);
}

void RenderNode::render(bool renderFloor, bool renderCeil, bool renderFloorFront) {

	//std::cout << "(RenderNode) Rendering node with id->" << this->id << "\n";

	// Render flat planes
	//glEnable(GL_DEPTH_TEST);
	
	if (renderCeil==true)
	{
		renderCeilPlane();
	}
	if (renderFloor == true)
	{
		renderFloorPlane();
	}

	glDisable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	
	// Render linedefs
	if (this->id==0)
	{
		renderMiddleSidedef();
	}
	else
	{
		if (this->sector->linedefs->has_cfs)
		{
			renderCeilFrontSidedef();
		}
		if (this->sector->linedefs->has_cbs)
		{
			renderCeilBackSidedef();
		}
		if (this->sector->linedefs->has_ffs)
		{
			if (renderFloorFront)
			{
				renderFloorFrontSidedef();
			}
		}
		if (this->sector->linedefs->has_fbs)
		{
			renderFloorBackSidedef();
		}
	}
	
	
	
}

bool RenderNode::hasChildren() {
	//std::cout << "(RenderNode) Verifying children for node: " << this->id << "\n";
	int size = this->children.size();
	return size >= 1;
}

void RenderNode::printContent() {
	std::cout << "Printing node <" << this->id << ">\n";
	if (hasChildren()==false)
	{
		return;
	}
	std::cout << "Printing children...\n";
	for (size_t i = 0; i < this->children.size(); i++)
	{
		RenderNode* temp = this->children[i];
		temp->printContent();
	}
}
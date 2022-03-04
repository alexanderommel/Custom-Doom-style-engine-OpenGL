#include <custom/rendertree.h>
#include <custom/rendernode.h>
#include <iostream>
#include <custom/shader.h>
#include <custom/plane_renderer.h>

RenderTree::RenderTree(Shader *line_shader_, Shader *plane_shader_){
	this->root_node = NULL;
	this->line_shader = line_shader_;
	this->plane_shader = plane_shader_;
	static PlaneRenderer* plane_renderer_ = new PlaneRenderer(*(this->plane_shader));
	this->plane_renderer = plane_renderer_;
}

RenderTree::~RenderTree(){
}

void RenderTree::setRootNode(RenderNode* root) {
	this->root_node = root;
}

bool RenderTree::isRootNodeNull() {
	return this->root_node == NULL;
}

void RenderTree::render() {
	//std::cout << "(RenderTree) Rendering Tree..\n";
	//this->root_node->render();
	postOrderRendering(this->root_node,nullptr);
}

void RenderTree::postOrderRendering(RenderNode* node, RenderNode* parent) {
	if (node->hasChildren() == false)
	{
		if (parent==nullptr)
		{

			node->render(true,true, true);
			return;
		}
		if (parent->sector->floor_plane.y_position!=node->sector->floor_plane.y_position
			&& parent->sector->ceil_plane.y_position!=node->sector->ceil_plane.y_position)
		{
			node->render(true, true, true);
			return;
		}
		if (parent->sector->floor_plane.y_position == node->sector->floor_plane.y_position
			&& parent->sector->ceil_plane.y_position != node->sector->ceil_plane.y_position)
		{
			node->render(false, true, true);
			return;
		}
		if (parent->sector->floor_plane.y_position != node->sector->floor_plane.y_position
			&& parent->sector->ceil_plane.y_position == node->sector->ceil_plane.y_position)
		{
			node->render(true, false, true);
			return;
		}
		if (parent->sector->floor_plane.y_position == node->sector->floor_plane.y_position
			&& parent->sector->ceil_plane.y_position == node->sector->ceil_plane.y_position)
		{
			node->render(false, false, true);
			return;
		}
	}
	std::vector<map_flatplane_t> ceil_clipping_planes;
	std::vector<map_flatplane_t> floor_clipping_planes;
	std::vector<mapvertex_t*> clipping_vertices;
	std::vector<float*> child_vertex_arrays;
	std::vector<int> num_vertices;
	for (size_t i = 0; i < node->children.size(); i++)
	{
		RenderNode* child = node->children[i];
		// Load clipping data for Stencil
		map_flatplane_t ceil_clipplin_plane = child->sector->ceil_plane;
		map_flatplane_t floor_clipping_plane = child->sector->floor_plane;
		mapvertex_t* node_vertices = child->sector->vertices;
		// Saving clipping data
		ceil_clipping_planes.push_back(ceil_clipplin_plane);
		floor_clipping_planes.push_back(floor_clipping_plane);
		clipping_vertices.push_back(node_vertices);
		child_vertex_arrays.push_back(child->sector->flatplane_vertex_array);
		num_vertices.push_back(child->sector->num_vertices);
		// Rendering child
		postOrderRendering(child,node);
	}

	
	// Clip sectors using Stencil Test
	glEnable(GL_STENCIL_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_TRUE);
	this->plane_shader->Use();
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	//glDisable(GL_DEPTH_TEST);
	for (size_t i = 0; i < ceil_clipping_planes.size(); i++)
	{

		//std::cout << "(RenderTree) Rendering Clipping Planes\n";
		map_flatplane_t ceil_plane = ceil_clipping_planes[i];
		map_flatplane_t floor_plane = floor_clipping_planes[i];
		mapvertex_t* vertices = clipping_vertices[i];
		float* child_vertex_array = child_vertex_arrays[i];
		this->plane_shader->Use();
		
		

		// Render ceil plane
		//std::cout << "(RenderTree) Rendering Clipping Ceil Plane\n";
		Texture2D ceil_texture = ResourceManager::GetTexture(ceil_plane.texture_name);
		ceil_texture.Bind();
		// normal vector
		float directionC = -1.0f;
		glm::vec3 normalVectorC = { 0.0f,0.0f,directionC };
		//
		if (ceil_plane.y_position != node->sector->ceil_plane.y_position)
		{
			plane_renderer->render(ceil_texture,
				vertices,
				num_vertices[i],
				node->sector->ceil_plane.y_position,
				3,
				glm::vec3(1.0f, 1.0f, 1.0f), child_vertex_array,10,0.0,
				normalVectorC);
		}

		

		// Render floor plane
		Texture2D floor_texture = ResourceManager::GetTexture(floor_plane.texture_name);
		floor_texture.Bind();
		// normal vector
		float direction = 1.0f;
		glm::vec3 normalVector = { 0.0f,0.0f,direction };
		if (floor_plane.y_position != node->sector->floor_plane.y_position)
		{
			plane_renderer->render(floor_texture,
				vertices,
				num_vertices[i],
				node->sector->floor_plane.y_position,
				3,
				glm::vec3(1.0f, 1.0f, 1.0f), child_vertex_array,10,0.0,
				normalVector);
		}
		
	}
	//std::cout << "(RenderTree) Rendering Parent Node with Clipping\n";
	// Render Current Parent Node
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	//glDisable(GL_DEPTH_TEST);
	


	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	if (node->id==0)
	{
		node->render(true, false, true);
	}
	else {
		node->render(true, true, true);
	}
	
	// Disable Stencil Test


	//glDisable(GL_STENCIL_TEST);
	//glStencilMask(0xFF);
	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	//glEnable(GL_DEPTH_TEST);
}

void RenderTree::trasversalOrderPrintContent() {
	//std::cout << "(RenderTree) Printing content of the tree..\n";
	if (isRootNodeNull())
	{
		std::cout << "No root node linked\n";
		return;
	}
	bool node_has_children = this->root_node->hasChildren();
	RenderNode* temp = this->root_node;
	temp->printContent();
	
}
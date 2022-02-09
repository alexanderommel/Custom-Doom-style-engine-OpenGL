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
	std::cout << "(RenderTree) Rendering Tree..\n";
	//this->root_node->render();
	postOrderRendering(this->root_node);
}

void RenderTree::postOrderRendering(RenderNode* node) {
	if (node->hasChildren() == false)
	{
		node->render();
		return;
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
		postOrderRendering(child);
	}

	
	// Clip sectors using Stencil Test
	glEnable(GL_STENCIL_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	this->plane_shader->Use();
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
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
		if (ceil_plane.y_position != node->sector->ceil_plane.y_position)
		{
			plane_renderer->render(ceil_texture,
				vertices,
				num_vertices[i],
				node->sector->ceil_plane.y_position,
				3,
				glm::vec3(1.0f, 1.0f, 1.0f), child_vertex_array,10);
		}

		// Render floor plane
		Texture2D floor_texture = ResourceManager::GetTexture(floor_plane.texture_name);
		floor_texture.Bind();
		if (floor_plane.y_position != node->sector->floor_plane.y_position)
		{
			plane_renderer->render(floor_texture,
				vertices,
				num_vertices[i],
				node->sector->floor_plane.y_position,
				3,
				glm::vec3(1.0f, 1.0f, 1.0f), child_vertex_array,10);
		}
		
	}
	std::cout << "(RenderTree) Rendering Parent Node with Clipping\n";
	// Render Current Parent Node
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	//glDisable(GL_DEPTH_TEST);
	


	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	node->render();
	// Disable Stencil Test
	glDisable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glEnable(GL_DEPTH_TEST);
}

void RenderTree::trasversalOrderPrintContent() {
	std::cout << "(RenderTree) Printing content of the tree..\n";
	if (isRootNodeNull())
	{
		std::cout << "No root node linked\n";
		return;
	}
	bool node_has_children = this->root_node->hasChildren();
	RenderNode* temp = this->root_node;
	temp->printContent();
	
}
#include <custom/rendertree.h>
#include <custom/rendernode.h>
#include <iostream>
#include <custom/shader.h>

RenderTree::RenderTree(Shader *line_shader_, Shader *plane_shader_){
	this->root_node = NULL;
	this->line_shader = line_shader_;
	this->plane_shader = plane_shader_;
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
		// Rendering child
		postOrderRendering(child);
	}
	// Clip sectors using Stencil Test
	// Render current node 'parent'
	node->render();
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
#include <custom/rendertree.h>
#include <custom/rendernode.h>
#include <iostream>

RenderTree::RenderTree(){
	this->root_node = NULL;
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
	std::cout << "Rendering Tree..\n";
}

void RenderTree::trasversalOrderPrintContent() {
	std::cout << "Printing content of the tree..\n";
	if (isRootNodeNull())
	{
		std::cout << "No root node linked\n";
		return;
	}
	bool node_has_children = this->root_node->hasChildren();
	RenderNode* temp = this->root_node;
	temp->printContent();
	
}
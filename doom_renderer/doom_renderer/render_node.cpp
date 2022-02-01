#include<custom/rendernode.h>
#include<iostream>

RenderNode::RenderNode(unsigned int id) {
	this->id = id;
	this->sector = NULL;
}

RenderNode::~RenderNode(){}

void RenderNode::addChild(RenderNode* node) {
	this->children.push_back(node);
}

void RenderNode::addSector(mapsector_t* sector_) {
	this->sector = sector_;
}

void RenderNode::render() {
	std::cout << "Rendering node with id->" << this->id << "\n";
}

bool RenderNode::hasChildren() {
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
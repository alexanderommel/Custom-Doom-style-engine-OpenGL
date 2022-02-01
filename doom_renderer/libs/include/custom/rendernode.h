#ifndef RENDER_NODE_H
#define RENDER_NODE_H

#include <map>
#include <string>
#include <glad/glad.h>
#include <vector>
#include <custom/doom_data.h>





class RenderNode


{
    public:
        RenderNode(unsigned int id); // There's not default data
        ~RenderNode();
        void addChild(RenderNode *node);
        void addSector(mapsector_t *sector_);
        bool hasChildren();
        void render(); //It uses its children to do polygon substraction
        void printContent();
        unsigned int id; 
        mapsector_t *sector;
        std::vector<RenderNode*> children;
};

#endif
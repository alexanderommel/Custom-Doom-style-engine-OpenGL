#ifndef RENDER_TREE_H
#define RENDER_TREE_H

#include <map>
#include <string>
#include <glad/glad.h>
#include <vector>
#include <custom/rendernode.h>





class RenderTree



{
    public:
        RenderTree(); 
        ~RenderTree();
        void setRootNode(RenderNode *root);
        void trasversalOrderPrintContent();
        bool isRootNodeNull();
        void render(); //It uses its children to do polygon substraction
        RenderNode *root_node;
};

#endif
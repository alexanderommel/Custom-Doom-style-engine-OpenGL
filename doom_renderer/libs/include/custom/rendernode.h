#ifndef RENDER_NODE_H
#define RENDER_NODE_H

#include <string>
#include <glad/glad.h>
#include <vector>
#include <custom/doom_data.h>
#include <custom/shader.h>
#include <custom/line_renderer.h>
#include <custom/plane_renderer.h>
//#include <custom/model.h>

class RenderNode
{
    public:
        RenderNode(unsigned int id, Shader *line_shader_, Shader *plane_shader_); // There's not default data
        ~RenderNode();
        void addChild(RenderNode* node);
        void addSector(mapsector_t* sector_);
        bool hasChildren();
        void render(bool renderFloor, bool renderCeil, bool renderFloorFront); //It uses its children to do polygon substraction
        void printContent();
        unsigned int id; 
        mapsector_t *sector;
        Shader* line_shader;
        Shader* plane_shader;
        LineRenderer* line_renderer;
        PlaneRenderer* plane_renderer;
        std::vector<RenderNode*> children;
    private:
        void renderMiddleSidedef();
        void renderCeilFrontSidedef();
        void renderCeilBackSidedef();
        void renderFloorFrontSidedef();
        void renderFloorBackSidedef();
        void renderCeilPlane();
        void renderFloorPlane();
};

#endif
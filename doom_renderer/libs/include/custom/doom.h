#ifndef _DOOM_H
#define _DOOM_H

//#include <map>
#include <string>
#include <glad/glad.h>
#include <custom/doom_map.h>
//#include <custom/doom_data.h>
//#include <custom/model.h>

class Doom
{
    public:
        Doom(unsigned int width_, unsigned int height_, unsigned int depth_); 
        ~Doom();
        unsigned int widthE;
        unsigned int heightE;
        unsigned int depthE;
        DoomMap* map;
        void init();
        void update(float time);
        void render(); 
        void updateProjectionAndView(glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos);
    private:
        void AloadTextures3();
        //void loadModels();
};

#endif
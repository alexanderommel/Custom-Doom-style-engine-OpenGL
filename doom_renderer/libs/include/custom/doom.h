#ifndef DOOM_H
#define DOOM_H

#include <map>
#include <string>
#include <glad/glad.h>
#include <vector>
#include <custom/doom_map.h>
#include <custom/doom_data.h>

class Doom
{
    public:
        Doom(unsigned int width_, unsigned int height_, unsigned int depth_); 
        ~Doom();
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        DoomMap* map;
        void init();
        void update(float dt);
        void render(); 
    private:
        void loadTextures();
};

#endif
#include <vector>
#include <custom/shader.h>
#include <custom/doom.h>
#include <custom/resource_manager.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <custom/doom_map.h>
#include <custom/doom_data.h>

Doom::Doom(unsigned int width_, unsigned int height_,unsigned int depth_)
: width(width_), height(height_), depth(depth_) {}

Doom::~Doom(){}

void Doom::init() {

    

	//Load shaders
    std::cout << "(Doom) Loading shaders...\n";
	ResourceManager::LoadShader("shaders/sidedef.vs", "shaders/sidedef.fs", NULL, "sidedefshader");
	ResourceManager::LoadShader("shaders/flatplane.vs", "shaders/flatplane.fs", NULL, "flatplaneshader");
    

	//Projection and View matrix
    //glm::mat4 projection = glm::mat4(1.0f);
	

    // CAMERA
    /*
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
        static_cast<float>(this->width) / static_cast<float>(this->height), 0.5f,
		static_cast<float>(5000));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, -25.0f, -150.0f));
	view = glm::rotate(view, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    */

	//Link matrices with the shaders
    std::cout << "(Doom) Linking projection and view matrices with the shaders\n";
    Shader sidedef_shader = ResourceManager::GetShader("sidedefshader");
    Shader flatplane_shader = ResourceManager::GetShader("flatplaneshader");
    sidedef_shader.Use();
    sidedef_shader.SetInteger("image", 0);
    //sidedef_shader.SetMatrix4("projection", projection);
    //sidedef_shader.SetMatrix4("view", view);
    flatplane_shader.Use();
    flatplane_shader.SetInteger("image", 0);
    //flatplane_shader.SetMatrix4("projection", projection);
    //flatplane_shader.SetMatrix4("view", view);

    //sidedef_shader.Use();
    //Load textures
    loadTextures();

    //Load maps

    std::cout << "(Doom) Loading map1...\n";
    DoomMap* first_map = new DoomMap();
    this->map = first_map;
}

void Doom::update(float dt) {

}

void Doom::updateProjectionAndView(glm::mat4 view, glm::mat4 proj) {
    std::cout << "(Doom-Temp) Updating projection and view matrices\n";
    Shader sidedef_shader = ResourceManager::GetShader("sidedefshader");
    Shader flatplane_shader = ResourceManager::GetShader("flatplaneshader");
    sidedef_shader.Use();
    sidedef_shader.SetMatrix4("projection", proj);
    sidedef_shader.SetMatrix4("view", view);
    flatplane_shader.Use();
    flatplane_shader.SetMatrix4("projection", proj);
    flatplane_shader.SetMatrix4("view", view);
}

void Doom::render() {
    std::cout << "(Doom) Rendering doom game\n";
    this->map->render();
}

void Doom::loadTextures() {
    std::cout << "(Doom) Loading textures...\n";
    ResourceManager::LoadTexture("textures/marbface.png", true, "MARBFACE");
    ResourceManager::LoadTexture("textures/bricks.jpg", true, "BRICKS");
    ResourceManager::LoadTexture("textures/REDBRICKS.jpg", true, "REDBRICKS");
    ResourceManager::LoadTexture("textures/teleport.png", true, "TELEPORT");

    ResourceManager::LoadTexture("textures/GSTONE1.png", true, "GSTONE1");
    ResourceManager::LoadTexture("textures/MARBFAC3.png", true, "MARBFAC3");
    ResourceManager::LoadTexture("textures/SKIN2.png", true, "SKIN2");
    ResourceManager::LoadTexture("textures/SKULL_DOOR.jpg", true, "SKULLDOOR");
    ResourceManager::LoadTexture("textures/HD_BRICKS.png", true, "HDBRICKS");
    ResourceManager::LoadTexture("textures/HD2BRICKS.png", true, "HD2BRICKS");

    // HD TEXTURES
    ResourceManager::LoadTexture("textures/hd/dem1_6.png", true, "dem1_6");
    ResourceManager::LoadTexture("textures/hd/doorblu2.png", true, "doorblu2");
    ResourceManager::LoadTexture("textures/hd/gate1.png", true, "gate1");
    ResourceManager::LoadTexture("textures/hd/gate4.png", true, "gate4");
    ResourceManager::LoadTexture("textures/hd/marble1.png", true, "marble1");
    ResourceManager::LoadTexture("textures/hd/marble2.png", true, "marble2");
    ResourceManager::LoadTexture("textures/hd/marble3.png", true, "marble3");
    ResourceManager::LoadTexture("textures/hd/metal.png", true, "metal");
    ResourceManager::LoadTexture("textures/hd/skinmet1.png", true, "skinmet1");
    ResourceManager::LoadTexture("textures/hd/slime01.png", true, "slime01");
    ResourceManager::LoadTexture("textures/hd/bigdoor5.png", true, "bigdoor5");
    ResourceManager::LoadTexture("textures/hd/bigdoor6.png", true, "bigdoor6");
    ResourceManager::LoadTexture("textures/hd/bigdoor7.png", true, "bigdoor7");
    ResourceManager::LoadTexture("textures/hd/slime01.png", true, "slime01");
    ResourceManager::LoadTexture("textures/hd/dem1_5.png", true, "dem1_5");
    ResourceManager::LoadTexture("textures/hd/mflr8_2.png", true, "mflr8_2");
    ResourceManager::LoadTexture("textures/hd/marbgray.png", true, "skinmet1");
    ResourceManager::LoadTexture("textures/hd/crbwdh64.png", true, "crbwdh64");
    ResourceManager::LoadTexture("textures/hd/ceil5_2.png", true, "ceil5_2");
    ResourceManager::LoadTexture("textures/hd/a_brown4.png", true, "a_brown4");
    ResourceManager::LoadTexture("textures/hd/nukage1.png", true, "nukage1");
    ResourceManager::LoadTexture("textures/hd/sw2skin.png", true, "sw2skin");
    ResourceManager::LoadTexture("textures/hd/sw1skin.png", true, "sw1skin");
}

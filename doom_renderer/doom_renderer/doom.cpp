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


DirLight dirLight_;

Doom::Doom(unsigned int width_, unsigned int height_,unsigned int depth_)
: width(width_), height(height_), depth(depth_) {}

Doom::~Doom(){}

void Doom::init() {

    

	//Load shaders
    std::cout << "(Doom) Loading shaders...\n";
	ResourceManager::LoadShader("shaders/sidedef.vs", "shaders/sidedef.fs", NULL, "sidedefshader");
	ResourceManager::LoadShader("shaders/flatplane.vs", "shaders/flatplane.fs", NULL, "flatplaneshader");
    

    

	//Link matrices with the shaders
    std::cout << "(Doom) Linking projection and view matrices with the shaders\n";
    Shader sidedef_shader = ResourceManager::GetShader("sidedefshader");
    Shader flatplane_shader = ResourceManager::GetShader("flatplaneshader");
    sidedef_shader.Use();
    //glm::vec3 lightPos = glm::vec3(-1472, 35, -3136);
    glm::vec3 lightPos = glm::vec3(-1472, 2235, 5888);
    glm::vec3 moon_light = glm::vec3(0.309, 0.411, 0.5333);
    glm::vec3 morning_color = glm::vec3(0.5529, 0.7166, 0.75686);
    glm::vec3 white_light = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 red_light = glm::vec3(1.0, 0.447, 0.4627);
    sidedef_shader.SetInteger("image", 0);

    /*
    // dir light
    //sidedef_shader.SetVector3f("dirLight.direction", dirLight_.direction);
    //sidedef_shader.SetVector3f("dirLight.ambient", dirLight_.ambient);
    //sidedef_shader.SetVector3f("dirLight.diffuse", dirLight_.diffuse);
    //sidedef_shader.SetVector3f("dirLight.specular", dirLight_.specular);
    sidedef_shader.SetVector3f("material.specular", 0.3, 0.3, 0.3);
    // point light 
    sidedef_shader.SetVector3f("pointLights[0].position", l1.position);
    sidedef_shader.SetVector3f("pointLights[0].ambient", l1.ambient);
    sidedef_shader.SetVector3f("pointLights[0].diffuse", l1.diffuse);
    sidedef_shader.SetVector3f("pointLights[0].specular", l1.specular);
    sidedef_shader.SetFloat("pointLights[0].constant", l1.constant);
    sidedef_shader.SetFloat("pointLights[0].linear", l1.linear);
    sidedef_shader.SetFloat("pointLights[0].quadratic", l1.quadratic);
    sidedef_shader.SetVector3f("pointLights[1].position", l2.position);
    sidedef_shader.SetVector3f("pointLights[1].ambient", l1.ambient);
    sidedef_shader.SetVector3f("pointLights[1].diffuse", l1.diffuse);
    sidedef_shader.SetVector3f("pointLights[1].specular", l1.specular);
    sidedef_shader.SetFloat("pointLights[1].constant", l1.constant);
    sidedef_shader.SetFloat("pointLights[1].linear", l1.linear);
    sidedef_shader.SetFloat("pointLights[1].quadratic", l1.quadratic);
    */
    //sidedef_shader.SetMatrix4("projection", projection);
    //sidedef_shader.SetMatrix4("view", view);
    flatplane_shader.Use();
    flatplane_shader.SetInteger("image", 0);
    //flatplane_shader.SetVector3f("lightPos", lightPos);
    //flatplane_shader.SetVector3f("lightColor", moon_light);
    flatplane_shader.SetVector3f("material.specular", 0.3,0.3,0.3);


    /*
    //flatplane_shader.SetVector3f("dirLight.direction", dirLight_.direction);
    //flatplane_shader.SetVector3f("dirLight.ambient", dirLight_.ambient);
    //flatplane_shader.SetVector3f("dirLight.diffuse", dirLight_.diffuse);
    //flatplane_shader.SetVector3f("dirLight.specular", dirLight_.specular);
    // point light 
    flatplane_shader.SetVector3f("pointLights[0].position", l1.position);
    flatplane_shader.SetVector3f("pointLights[0].ambient", l1.ambient);
    flatplane_shader.SetVector3f("pointLights[0].diffuse", l1.diffuse);
    flatplane_shader.SetVector3f("pointLights[0].specular", l1.specular);
    flatplane_shader.SetFloat("pointLights[0].constant", l1.constant);
    flatplane_shader.SetFloat("pointLights[0].linear", l1.linear);
    flatplane_shader.SetFloat("pointLights[0].quadratic", l1.quadratic);
    flatplane_shader.SetVector3f("pointLights[1].position", l2.position);
    flatplane_shader.SetVector3f("pointLights[1].ambient", l1.ambient);
    flatplane_shader.SetVector3f("pointLights[1].diffuse", l1.diffuse);
    flatplane_shader.SetVector3f("pointLights[1].specular", l1.specular);
    flatplane_shader.SetFloat("pointLights[1].constant", l1.constant);
    flatplane_shader.SetFloat("pointLights[1].linear", l1.linear);
    flatplane_shader.SetFloat("pointLights[1].quadratic", l1.quadratic);
    */
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

void Doom::updateProjectionAndView(glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos) {
    //std::cout << "(Doom-Temp) Updating projection and view matrices\n";
    Shader sidedef_shader = ResourceManager::GetShader("sidedefshader");
    Shader flatplane_shader = ResourceManager::GetShader("flatplaneshader");
    sidedef_shader.Use();
    glm::mat4 proj2 = glm::mat4(1.5) * proj;
    sidedef_shader.SetMatrix4("projection", proj);
    sidedef_shader.SetMatrix4("view", view);
    sidedef_shader.SetVector3f("viewPos", cameraPos);
    flatplane_shader.Use();
    flatplane_shader.SetMatrix4("projection", proj);
    flatplane_shader.SetMatrix4("view", view);
    flatplane_shader.SetVector3f("viewPos", cameraPos);
}

void Doom::render() {
    //std::cout << "(Doom) Rendering doom game\n";
    this->map->render();
}

void Doom::loadTextures() {
    std::cout << "(Doom) Loading textures...\n";

    float chrome_shininess = 0.45;
    float marble_faces_shininess = 0.3;
    float pearl_shininess = 0.15;
    float no_shininess = 0.0;

    // HD TEXTURES
    ResourceManager::LoadTexture("textures/hd/dem1_6.png", true, "dem1_6",chrome_shininess, false);
    ResourceManager::LoadTexture("textures/hd/doorblu2.png", true, "doorblu2", chrome_shininess, true);
    ResourceManager::LoadTexture("textures/hd/marble1.png", true, "marble1",0.1,true);
    ResourceManager::LoadTexture("textures/hd/hdmarbgray.png", true, "marble2", pearl_shininess, true);
    ResourceManager::LoadTexture("textures/hd/hdmarbgray.png", true, "marble3", pearl_shininess, true);
    ResourceManager::LoadTexture("textures/hd/metal.png", true, "metal", 0.1, true);
    ResourceManager::LoadTexture("textures/hd/skinmet1.png", true, "skinmet1",0.1,true);
    ResourceManager::LoadTexture("textures/hd/slime01.png", true, "slime01",0.3,true);
    ResourceManager::LoadTexture("textures/hd/bigdoor5.png", true, "bigdoor5",0.1,true);
    ResourceManager::LoadTexture("textures/hd/bigdoor6.png", true, "bigdoor6",0.1,true);
    ResourceManager::LoadTexture("textures/hd/bigdoor7.png", true, "skulldoor7", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/marbfac3.png", true, "bigdoor7",marble_faces_shininess,false);
    ResourceManager::LoadTexture("textures/hd/marbface.png", true, "marbface",marble_faces_shininess,false);
    //marbface
    ResourceManager::LoadTexture("textures/hd/dem1_5.png", true, "dem1_5",0.25,true);
    //ResourceManager::LoadTexture("textures/hd/mflr8_2.png", true, "mflr8_2",0.1,true);
    ResourceManager::LoadTexture("textures/hd/hdsand.png", true, "mflr8_2", 0.1, true);
    ResourceManager::LoadTexture("textures/hd/marbgray.png", true, "skinmet1",0.2,true);
    ResourceManager::LoadTexture("textures/hd/marbgray.png", true, "marbgray", 0.2, true);
    ResourceManager::LoadTexture("textures/hd/crbwdh64.png", true, "crbwdh64",0.05,true);
    ResourceManager::LoadTexture("textures/hd/ceil5_2.png", true, "ceil5_2",0.3,true);
    ResourceManager::LoadTexture("textures/hd/a_brown4.png", true, "a_brown4", 0.0001, true);
    ResourceManager::LoadTexture("textures/hd/sflr6_4.png", true, "lava1", 0.00001, true);
    ResourceManager::LoadTexture("textures/hd/sw2skin.png", true, "sw2skin", 0.2,true);
    ResourceManager::LoadTexture("textures/hd/sw1skin.png", true, "sw1skin", 0.2,true);
    ResourceManager::LoadTexture("textures/hd/a-mosbri.png", true, "amosbri",0.3,true);
    ResourceManager::LoadTexture("textures/hd/flat5_3.png", true, "flat5_3",0.3,false);
    ResourceManager::LoadTexture("textures/hd/support3.png", true, "support3", 0.3, true);
    // cajas
    ResourceManager::LoadTexture("textures/hd/crate1.png", true, "crate1", 0.35, true);
    ResourceManager::LoadTexture("textures/hd/crate2.png", true, "crate2", 0.35, true);
    ResourceManager::LoadTexture("textures/hd/cratelit.png", true, "cratelit", 0.35, true);
    ResourceManager::LoadTexture("textures/hd/cratwide.png", true, "cratwide", 0.35, true);
    ResourceManager::LoadTexture("textures/hd/crwdh64b.png", true, "crwdh64b", 0.35, true);
    // liquidos
    ResourceManager::LoadTexture("textures/hd/hdacido.png", true, "dbrain1", 0.35, true);
    ResourceManager::LoadTexture("textures/hd/hdacido.png", true, "nukage1", 0.35, true);
    // tubos 
    ResourceManager::LoadTexture("textures/hd/pipewal2.png", true, "pipewal2", 0.4, false);
    ResourceManager::LoadTexture("textures/hd/pipes.png", true, "pipes", 0.3, false);
    //flat5_3
    // cuadros gigantes super hd
    ResourceManager::LoadTexture("textures/hd/hduac.png", true, "hduac", 0.3, false);
    ResourceManager::LoadTexture("textures/hd/hdmarbfac3.png", true, "hdmarbfac3", 0.3, false);
    ResourceManager::LoadTexture("textures/hd/hdmancubus.png", true, "hdmancubus", 0.3, false);
    ResourceManager::LoadTexture("textures/hd/hdwall.png", true, "hdwall", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/hdredbricks.png", true, "hdredbricks", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/hdredfloor.png", true, "hdredfloor", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/hdbrown.png", true, "hdbrown1", 0.6, false);

    ResourceManager::LoadTexture("textures/hd/hdgstone.png", true, "hdgstone", 0.4, false);
    ResourceManager::LoadTexture("textures/hd/hdmarbgray.png", true, "hdmarbgray", 0.4, true);
    ResourceManager::LoadTexture("textures/hd/hdmarbgrayface.png", true, "hdmarbgrayface", 0.4, false);
    ResourceManager::LoadTexture("textures/hd/hdblueskull.png", true, "hdblueskull", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/hdfloor.png", true, "hdfloor", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/hdwhiterocks.png", true, "hdwhiterocks", 0.3, true);
    //
    ResourceManager::LoadTexture("textures/hd/hdpoisonwall.png", true, "hdpoisonskull", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/hdpoisonwallnoskull.png", true, "hdpoisonwall", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/hdwoodenmetal.png", true, "hdwooden", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/hdblood.png", true, "hdblood", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/hdwater.png", true, "hdwater", 0.3, true);
    ResourceManager::LoadTexture("textures/hd/flat5_4.png", true, "flat5_4", 0.3, false);
    //ResourceManager::LoadTexture("textures/hd/hdgstoneblood.jpg", true, "hdgstoneblood", 0.4, true);
    //ResourceManager::LoadTexture("textures/hd/hdwallbloods.jpg", true, "hdwallbloods", 0.4, true);
}

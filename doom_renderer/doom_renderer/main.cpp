#include <custom/rendertree.h>
#include <custom/rendernode.h>
#include <custom/doom_data.h>
#include <vector>
#include <custom/doom_map.h>
#include <iostream>
#include <string>
#include <custom/scenebuilder.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <custom/camera.h>
#include <custom/doom.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCREEN_WIDTH = 1500;
const unsigned int SCREEN_HEIGHT = 900;
const unsigned int SCREEN_DEPTH = 4000;
Camera camera(glm::vec3(0.0f, 100.0f, 500.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
const char WINDOW_TITLE[] = "No title sorry";
static Doom *doom = new Doom(SCREEN_WIDTH, SCREEN_HEIGHT,SCREEN_DEPTH);
float dt = 0;

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // OpenGL configuration
    // --------------------
    //glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



    // initialize game
    // ---------------
    doom->init();


    // Initialize data

    static mapsector_t sector1;
    mapvertex_t v1, v2, v3, v4;
    v1.x = -384; v1.z = -1728; v2.x = 448; v2.z = -1728; v3.x = 448; v3.z = 64; v4.x = -384; v4.z = 64;
    mapvertex_t va1[4] = { v1,v2,v3,v4 };
    std::vector<std::string> middle_textures = { "marble1","marble1","marble1","marble1" };

    static mapsector_t sector2;
    mapvertex_t v1s2, v2s2, v3s2, v4s2, v5s2, v6s2, v7s2, v8s2;
    v1s2.x = -320; v1s2.z = -1216; v2s2.x = -256; v2s2.z = -1280;
    v3s2.x = 320; v3s2.z = -1280; v4s2.x = 384; v4s2.z = -1216;
    v5s2.x = 384; v5s2.z = -832; v6s2.x = 320; v6s2.z = -768;
    v7s2.x = -256; v7s2.z = -768; v8s2.x = -320; v8s2.z = -832;
    mapvertex_t va2[8] = { v1s2,v2s2,v3s2,v4s2,v5s2,v6s2,v7s2,v8s2 };
    std::vector<std::string> floor_back_textures_s2 = { "metal","metal","metal","metal",
    "metal","metal","metal","metal" };

    // 

    static mapsector_t sector3;
    mapvertex_t v1s3, v2s3, v3s3, v4s3;
    v1s3.x = -256; v1s3.z = -1088; v2s3.x = -128; v2s3.z = -1088;
    v3s3.x = -128; v3s3.z = -960; v4s3.x = -256; v4s3.z = -960;
    mapvertex_t va3[4] = { v1s3,v2s3,v3s3,v4s3 };
    std::vector<std::string> floor_front_textures_s345 = { "marble2","marble2","marble2",
    "marble2" };

    static mapsector_t sector4;
    mapvertex_t v1s4, v2s4, v3s4, v4s4;
    v1s4.x = -32; v1s4.z = -1088; v2s4.x = 96; v2s4.z = -1088;
    v3s4.x = 96; v3s4.z = -960; v4s4.x = -32; v4s4.z = -960;
    mapvertex_t va4[4] = { v1s4,v2s4,v3s4,v4s4 };

    static mapsector_t sector5;
    mapvertex_t v1s5, v2s5, v3s5, v4s5;
    v1s5.x = 192; v1s5.z = -1088; v2s5.x = 320; v2s5.z = -1088;
    v3s5.x = 320; v3s5.z = -960; v4s5.x = 192; v4s5.z = -960;
    mapvertex_t va5[4] = { v1s5,v2s5,v3s5,v4s5 };

    //

    static mapsector_t sector6;
    mapvertex_t v1s6, v2s6, v3s6, v4s6;
    v1s6.x = -378; v1s6.z = -1216; v2s6.x = -352; v2s6.z = -1216;
    v3s6.x = -352; v3s6.z = -704; v4s6.x = -378; v4s6.z = -704;
    mapvertex_t va6[4] = { v1s6,v2s6,v3s6,v4s6 };
    std::vector<std::string> ceil_front_texture_s6 = { "metal","bigdoor7",
    "metal","metal" };

    static mapsector_t sector7;
    mapvertex_t v1s7, v2s7, v3s7, v4s7;
    v1s7.x = 416; v1s7.z = -1216; v2s7.x = 442; v2s7.z = -1216;
    v3s7.x = 442; v3s7.z = -704; v4s7.x = 416; v4s7.z = -704;
    mapvertex_t va7[4] = { v3s7,v4s7,v1s7,v2s7 };

    // plataforma

    static mapsector_t sector8;
    mapvertex_t v1s8, v2s8, v3s8, v4s8;
    v1s8.x = -368; v1s8.z = -224; v2s8.x = 432; v2s8.z = -224;
    v3s8.x = 432; v3s8.z = 60; v4s8.x = -368; v4s8.z = 60;
    mapvertex_t va8[4] = { v1s8,v2s8,v3s8,v4s8 };
    std::vector<std::string> ceil_floor_ft_s8 = { "skinmet1","skinmet1","skinmet1","skinmet1" };


    static mapsector_t sector9;
    mapvertex_t v1s9, v2s9, v3s9, v4s9;
    v1s9.x = -32; v1s9.z = 58; v2s9.x = 96; v2s9.z = 58;
    v3s9.x = 96; v3s9.z = 59; v4s9.x = -32; v4s9.z = 59;
    mapvertex_t va9[4] = { v1s9,v2s9,v3s9,v4s9 };
    std::vector<std::string> ceil_front_texture_s9 = { "bigdoor7","metal","metal","metal" };

    static mapsector_t sector10;
    mapvertex_t v1s10, v2s10, v3s10, v4s10;
    v1s10.x = -320; v1s10.z = -176; v2s10.x = -256; v2s10.z = -176;
    v3s10.x = -256; v3s10.z = -112; v4s10.x = -320; v4s10.z = -112;
    mapvertex_t va10[4] = { v1s10,v2s10,v3s10,v4s10 };

    static mapsector_t sector11;
    mapvertex_t v1s11, v2s11, v3s11, v4s11;
    v1s11.x = 320; v1s11.z = -176; v2s11.x = 384; v2s11.z = -176;
    v3s11.x = 384; v3s11.z = -112; v4s11.x = 320; v4s11.z = -112;
    mapvertex_t va11[4] = { v1s11,v2s11,v3s11,v4s11 };

    std::vector<std::string> floor_front_texture_s10and11 = {
        "metal","metal","metal","metal"
    };

        // blue skull lights
    static mapsector_t sector12;
    mapvertex_t va12[4] = { {-224,-176},{-208,-176},{-208,-160},{-224,-160} };
    static mapsector_t sector13;
    mapvertex_t va13[4] = { {-176,-176},{-160,-176},{-160,-160},{-176,-160} };
    static mapsector_t sector14;
    mapvertex_t va14[4] = { {-128,-176},{-112,-176},{-112,-160},{-128,-160} };
    static mapsector_t sector15;
    mapvertex_t va15[4] = { {176,-176},{192,-176},{192,-160},{176,-160} };
    static mapsector_t sector16;
    mapvertex_t va16[4] = { {224,-176},{240,-176},{240,-160},{224,-160} };
    static mapsector_t sector17;
    mapvertex_t va17[4] = { {272,-176},{288,-176},{288,-160},{272,-160} };
    std::vector<std::string> floor_front_texture_blueskulls = {
        "doorblu2","doorblu2","doorblu2","doorblu2"
    };

    std::vector<std::string> NULLL; // FRIENDLY VARIABLE

    // gradas

    static mapsector_t sector18;
    mapvertex_t va18[4] = { {-32,-480},{96,-480},{96,-416},{-32,-416} };
    static mapsector_t sector19;
    mapvertex_t va19[4] = { {-32,-416},{96,-416},{96,-352},{-32,-352} };
    static mapsector_t sector20;
    mapvertex_t va20[4] = { {-32,-352},{96,-352},{96,-288},{-32,-288} };
    std::vector<std::string> fft_sector20 = {
        "a_brown4","metal","metal","metal"
    };
    static mapsector_t sector21;
    mapvertex_t va21[4] = { {-32,-288},{96,-288},{96,-224},{-32,-224} };
    std::vector<std::string> front_floor_texture_gradas = {
        "metal","metal","metal","metal"
    };

    // extensiones plataforma
    static mapsector_t sector22;
    mapvertex_t va22[5] = { {-256,-384},{-192,-448},{-36,-448},
        {-36,-228} , {-256,-228} };
    static mapsector_t sector23;
    mapvertex_t va23[5] = { {100,-448},{256,-448},{320,-384},
        {320,-228} , {100,-228} };
    std::vector<std::string> fft_cft_marbgray5 = {
        "skinmet1","skinmet1","skinmet1","skinmet1","skinmet1"
    };

    // mini torres
    static mapsector_t sector24;
    mapvertex_t va24[4] = { {-352,-608}, {-288,-608}, {-288,-544}, {-352, -544} };
    static mapsector_t sector25;
    mapvertex_t va25[4] = { {352,-608}, {416,-608}, {416,-544}, {352, -544} };
    std::vector<std::string> fft_sector24y25 = {
        "crbwdh64","crbwdh64","crbwdh64","crbwdh64"
    };

    // Build sectors

    static SceneBuilder* builder = new SceneBuilder();
    builder->buildSector(
        va1,
        std::vector<std::string>(),
        std::vector<std::string>(),
        middle_textures,
        std::vector<std::string>(),
        std::vector<std::string>(),
        "mflr8_2",
        "dem1_5",
        -16,
        432,
        256,
        sector1,
        4
    );

    // hueco

    builder->buildSector(
        va2,
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        floor_back_textures_s2,
        "slime01",
        "dem1_5",
        -152,
        432,
        256,
        sector2,
        8
    );

    // plataformas en lava

    builder->buildSector(
        va3,
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        floor_front_textures_s345,
        std::vector<std::string>(),
        "dem1_5",
        "dem1_5",
        104,
        432,
        256,
        sector3,
        4
    );

    builder->buildSector(
        va4,
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        floor_front_textures_s345,
        std::vector<std::string>(),
        "dem1_6",
        "dem1_5",
        -24,
        432,
        256,
        sector4,
        4
    );

    builder->buildSector(
        va5,
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        floor_front_textures_s345,
        std::vector<std::string>(),
        "dem1_5",
        "dem1_5",
        104,
        432,
        256,
        sector5,
        4
    );

    // cuadros 

    builder->buildSector(
        va6,
        ceil_front_texture_s6,
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        "mflr8_2",
        "metal",
        -16,
        304,
        256,
        sector6,
        4
    );

    builder->buildSector(
        va7,
        ceil_front_texture_s6,
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        "mflr8_2",
        "metal",
        -16,
        304,
        256,
        sector7,
        4
    );

    // plataforma

    builder->buildSector(
        va8,
        ceil_floor_ft_s8,
        std::vector<std::string>(),
        std::vector<std::string>(),
        ceil_floor_ft_s8,
        std::vector<std::string>(),
        "dem1_6",
        "dem1_6",
        120,
        368,
        256,
        sector8,
        4
    );

    // puerta

    builder->buildSector(
        va9,
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        ceil_front_texture_s9,
        std::vector<std::string>(),
        "dem1_6",
        "dem1_6",
        240,
        368,
        256,
        sector9,
        4
    );

    // barras metalicas

    builder->buildSector(
        va10,
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        floor_front_texture_s10and11,
        std::vector<std::string>(),
        "dem1_6",
        "dem1_6",
        368,
        368,
        256,
        sector10,
        4
    );

    builder->buildSector(
        va11,
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::string>(),
        floor_front_texture_s10and11,
        std::vector<std::string>(),
        "dem1_6",
        "dem1_6",
        368,
        368,
        256,
        sector11,
        4
    );

    // build skulls

    builder->buildSector(va12,NULLL,NULLL,NULLL,floor_front_texture_blueskulls,NULLL,
        "metal",
        "dem1_6",
        248,
        368,
        256,
        sector12,
        4
    );
    builder->buildSector(va13, NULLL, NULLL, NULLL, floor_front_texture_blueskulls, NULLL,
        "metal",
        "dem1_6",
        248,
        368,
        256,
        sector13,
        4
    );
    builder->buildSector(va14, NULLL, NULLL, NULLL, floor_front_texture_blueskulls, NULLL,
        "metal",
        "dem1_6",
        248,
        368,
        256,
        sector14,
        4
    );
    builder->buildSector(va15, NULLL, NULLL, NULLL, floor_front_texture_blueskulls, NULLL,
        "metal",
        "dem1_6",
        248,
        368,
        256,
        sector15,
        4
    );
    builder->buildSector(va16, NULLL, NULLL, NULLL, floor_front_texture_blueskulls, NULLL,
        "metal",
        "dem1_6",
        248,
        368,
        256,
        sector16,
        4
    );
    builder->buildSector(va17, NULLL, NULLL, NULLL, floor_front_texture_blueskulls, NULLL,
        "metal",
        "dem1_6",
        248,
        368,
        256,
        sector17,
        4
    );

    // build gradas
    builder->buildSector(va18, NULLL, NULLL, NULLL, front_floor_texture_gradas, NULLL,
        "metal",
        "dem1_5",
        8,
        432,
        256,
        sector18,
        4
    );

    builder->buildSector(va19, front_floor_texture_gradas, NULLL, NULLL, front_floor_texture_gradas, NULLL,
        "metal",
        "ceil5_2",
        32,
        400,
        256,
        sector19,
        4
    );

    builder->buildSector(va20, fft_sector20, NULLL, NULLL, front_floor_texture_gradas, NULLL,
        "metal",
        "ceil5_2",
        56,
        272,
        256,
        sector20,
        4
    );

    builder->buildSector(va21, front_floor_texture_gradas, NULLL, NULLL, front_floor_texture_gradas, NULLL,
        "metal",
        "dem1_6",
        80,
        368,
        256,
        sector21,
        4
    );

    // build extensiones

    builder->buildSector(va22, fft_cft_marbgray5, NULLL, NULLL, fft_cft_marbgray5, NULLL,
        "dem1_6",
        "dem1_6",
        112,
        304,
        256,
        sector22,
        5
    );

    builder->buildSector(va23, fft_cft_marbgray5, NULLL, NULLL, fft_cft_marbgray5, NULLL,
        "dem1_6",
        "dem1_6",
        112,
        304,
        256,
        sector23,
        5
    );


    // mini torres

    builder->buildSector(va24, NULLL, NULLL, NULLL, fft_sector24y25, NULLL,
        "ceil5_2",
        "dem1_5",
        248,
        432,
        256,
        sector24,
        4
    );

    builder->buildSector(va25, NULLL, NULLL, NULLL, fft_sector24y25, NULLL,
        "ceil5_2",
        "dem1_5",
        248,
        432,
        256,
        sector25,
        4
    );


    // Add to map

    doom->map->addSectorToRenderTree(&sector1);
    doom->map->addSectorToRenderTree(&sector2);
    doom->map->addSectorToRenderTree(&sector3);
    doom->map->addSectorToRenderTree(&sector4);
    doom->map->addSectorToRenderTree(&sector5);
    doom->map->addSectorToRenderTree(&sector6);
    doom->map->addSectorToRenderTree(&sector7);
    doom->map->addSectorToRenderTree(&sector8);
    doom->map->addSectorToRenderTree(&sector9);
    doom->map->addSectorToRenderTree(&sector10);
    doom->map->addSectorToRenderTree(&sector11);

    doom->map->addSectorToRenderTree(&sector12);
    doom->map->addSectorToRenderTree(&sector13);
    doom->map->addSectorToRenderTree(&sector14);
    doom->map->addSectorToRenderTree(&sector15);
    doom->map->addSectorToRenderTree(&sector16);
    doom->map->addSectorToRenderTree(&sector17);

    doom->map->addSectorToRenderTree(&sector18);
    doom->map->addSectorToRenderTree(&sector19);
    doom->map->addSectorToRenderTree(&sector20);
    doom->map->addSectorToRenderTree(&sector21);

    doom->map->addSectorToRenderTree(&sector22);
    doom->map->addSectorToRenderTree(&sector23);

    doom->map->addSectorToRenderTree(&sector24);
    doom->map->addSectorToRenderTree(&sector25);


    // end init

    float last_time = 0;

    while (!glfwWindowShouldClose(window))
    {

        float current_time = glfwGetTime();
        dt = current_time - last_time;
        dt = 35 * dt;
        last_time = current_time;

        processInput(window);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearStencil(0);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
            static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.5f,
            static_cast<float>(8000));

        glm::mat4 view = camera.GetViewMatrix();

        doom->updateProjectionAndView(view, projection);


        doom->render();

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        dt = 8 * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, dt);
    
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
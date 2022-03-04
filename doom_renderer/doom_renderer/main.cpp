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
#include <custom/model.h>
#include <functional>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCREEN_WIDTH = 1540;
const unsigned int SCREEN_HEIGHT = 840;
const unsigned int SCREEN_DEPTH = 7500;
Camera camera(glm::vec3(0.0f, 100.0f, 0.0f));
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

    std::vector<std::string> NULLL;
    std::vector<std::string> sw2skin_4_textures = { "sw2skin","sw2skin","sw2skin","sw2skin" };
    std::vector<std::string> amosbri_4_textures = { "amosbri","amosbri","amosbri","amosbri" };
    std::vector<std::string> marble1_8_textures =
    { "marble1","marble1","marble1","marble1", "marble1", "marble1", "marble1", "marble1"};
    std::vector<std::string> marble1_5_textures = 
    { "marble1","marble1","marble1","marble1", "marble1"};
    std::vector<std::string> marble1_4_textures = { "marble1","marble1","marble1","marble1" };
    std::vector<std::string> marble1_3_textures = { "marble1","marble1","marble1"};
    std::vector<std::string> marble2_4_textures = { "marble2","marble2","marble2","marble2" };
    std::vector<std::string> marble2_8_textures = { "marble2","marble2","marble2","marble2",
    "marble2","marble2","marble2","marble2" };
    std::vector<std::string> marble3_4_textures = { "marble3","marble3","marble3","marble3" };
    std::vector<std::string> marble3_8_textures = { "marble3","marble3","marble3","marble3",
    "marble3","marble3","marble3","marble3" };
    std::vector<std::string> metal_8_textures = { "metal","metal","metal","metal" ,
    "metal","metal","metal","metal" };
    std::vector<std::string> metal_4_textures = { "metal","metal","metal","metal" };
    std::vector<std::string> metal_3_textures = { "metal","metal","metal" };
    std::vector<std::string> marbgray_4_textures = {
        "skinmet1","skinmet1","skinmet1","skinmet1","skinmet1"
    };
    std::vector<std::string> marbface_4_textures = { "marbface","marbface","marbface","marbface" };
    std::vector<std::string> bigdoor7_4_textures = {"bigdoor7","bigdoor7","bigdoor7","bigdoor7"};
    std::vector<std::string> bloodboxes_4_textures = { "crbwdh64","crbwdh64","crbwdh64","crbwdh64" };

    std::vector<std::string> a_brown4_4_textures = { "a_brown4","a_brown4","a_brown4","a_brown4" };
    std::vector<std::string> support3_4_textures = { "support3","support3","support3","support3" };
    //texturas de cajas
    std::vector<std::string> crate1_4_textures = { "crate1","crate1","crate1","crate1" };
    std::vector<std::string> crate2_4_textures = { "crate2","crate2","crate2","crate2" };
    std::vector<std::string> cratelit_4_textures = { "cratelit","cratelit","cratelit","cratelit" };
    std::vector<std::string> cratwide_4_textures = { "cratwide","cratwide","cratwide","cratwide" };
    std::vector<std::string> tntbox_4_textures = { "crwdh64b","crwdh64b","crwdh64b","crwdh64b" };
    // texturas de tubos
    std::vector<std::string> pipewal2_4_textures = { "pipewal2","pipewal2","pipewal2","pipewal2" };
    std::vector<std::string> pipes_4_textures = { "pipes","pipes","pipes","pipes" };

   
    //----- Sector principal

    static mapsector_t sector1;
    //mapvertex_t va1[4] = { {-4096,-3776}, {1164,-3776},
      //  {1164,16720}, {-4096, 16720} };

    mapvertex_t va1[4] = { {-10232,-3776}, {6912,-3776},
        {6912,21248}, {-10232, 21248} };

    static mapsector_t river_sector;
    mapvertex_t va_river[8] = { {-1856,5760},{-1088,5760},{4200,6920},{6904,9536},{6904,21240},
        {-10231,21240},{-10231,9536},{-7144,6920} };

    //----- Sectores de relleno

    static mapsector_t sector2;
    mapvertex_t va2[3] = { {-1856,-3774},
        {-3452,-3136}, {-3452,-3474} };

    static mapsector_t sector3;
    mapvertex_t va3[3] = { {508,-3475},
        {508,-3136}, {-1088,-3775} };

    static mapsector_t sector4;
    mapvertex_t va4[4] = { {-4096,-2816}, {-3004,-3312},
        {-3384,-2204}, {-4096, -1792} };

    static mapsector_t sector5;
    mapvertex_t va5[4] = { {1152,-2872}, {60,-3312},
        {376,-2204}, {1152, -1792} };

    // Plataforma 1

    static mapsector_t sector6;
    mapvertex_t va6[8] = { {-4032,-1728}, {-3328,-1728},
        {-3008,-1536}, {-2816, -1216},
        {-2816,-768} , {-3008,-448}, 
        {-3328,-256}, {-4032,-256}  };

    static mapsector_t sector6_2;
    mapvertex_t va6_2[8] = { {1088,-1728}, {384,-1728},
        {64,-1536}, {-128, -1216},
        {-128,-768} , {64,-448},
        {384,-256}, {1088,-256} };

    // Plataforma 2

    static mapsector_t sector7;
    mapvertex_t va7[8] = { {-4032,-192}, {-3328,-192},
        {-3008,0}, {-2816, 320},
        {-2816,768} , {-3008,1088},
        {-3328,1280}, {-4032,1280} };

    static mapsector_t sector7_2;
    mapvertex_t va7_2[8] = { {1088,-192}, {384,-192},
        {64,0}, {-128, 320},
        {-128,768} , {64,1088},
        {384,1280}, {1088,1280} };

    // Plataforma 3

    static mapsector_t sector8;
    mapvertex_t va8[4] = { {-4032,1344}, {-3008,1344},
        {-3008,3200}, {-4032, 3200} };

    static mapsector_t sector8_2;
    mapvertex_t va8_2[4] = { {1088,1344}, {64,1344},
        {64,3200}, {1088, 3200} };


    // Contenido Plataforma 1

    static mapsector_t sector9; // caja demoniaca
    mapvertex_t va9[4] = { {-3712,-1536}, {-3456,-1536},
        {-3456,-1280}, {-3712, -1280} };

    static mapsector_t sector10; // caja demoniaca
    mapvertex_t va10[4] = { {-3712,-704}, {-3456,-704},
        {-3456,-448}, {-3712, -448} };

    static mapsector_t sector11; // soportes
    mapvertex_t va11[4] = { {-3680,-1408}, {-3584,-1504},
        {-3488,-1408}, {-3584, -1312} };

    static mapsector_t sector12; // soportes
    mapvertex_t va12[4] = { {-3680,-576}, {-3584,-672},
        {-3488,-576}, {-3584, -480} };

    static mapsector_t sector13; // mini caja demoniaca
    mapvertex_t va13[4] = { {-3264,-832}, {-3136,-832},
        {-3136,-704}, {-3264, -704} };

    static mapsector_t sector14; // mini caja demoniaca
    mapvertex_t va14[4] = { {-3072,-1152}, {-2944,-1152},
        {-2944,-1024}, {-3072, -1024} };


    // Contenido plataforma 1 derecha

    static mapsector_t sector9_2; // caja demoniaca
    mapvertex_t va9_2[4] = { {704,-1536}, {448,-1536},
        {448,-1280}, {704, -1280} };

    static mapsector_t sector10_2; // caja demoniaca
    mapvertex_t va10_2[4] = { {704,-704}, {448,-704},
        {448,-448}, {704, -448} };

    static mapsector_t sector11_2; // soportes
    mapvertex_t va11_2[4] = { {672,-1408}, {576,-1504},
        {480,-1408}, {576, -1312} };

    static mapsector_t sector12_2; // soportes
    mapvertex_t va12_2[4] = { {672,-576}, {576,-672},
        {480,-576}, {576, -480} };

    
    // Contenido plataforma 2

    static mapsector_t sector15; // plataforma mini
    mapvertex_t va15[4] = { {-3968,-160}, {-3648,-160},
        {-3648,1248}, {-3968, 1248} };

    static mapsector_t sector16; // luz 1 abajo
    mapvertex_t va16[4] = { {-3904,-64}, {-3776,-64},
        {-3776,192}, {-3904, 192} };

    static mapsector_t sector17; // luz 2 arriba
    mapvertex_t va17[4] = { {-3904,896}, {-3776,896},
        {-3776,1152}, {-3904, 1152} };

    static mapsector_t sector18; // caja demoniaca 1 arriba
    mapvertex_t va18[4] = { {-3328,704}, {-3072,704},
        {-3072,960}, {-3328, 960} };

    static mapsector_t sector19; // caja demoniaca 2 abajo
    mapvertex_t va19[4] = { {-3328,128}, {-3072,128},
        {-3072,384}, {-3328, 384} };

    static mapsector_t sector20; // soporte arriba
    mapvertex_t va20[4] = { {-3264,832}, {-3200,768},
        {-3136,832}, {-3200, 896} };

    static mapsector_t sector21; // soporte abajo
    mapvertex_t va21[4] = { {-3264,256}, {-3200,192},
        {-3136,256}, {-3200, 320} };


    // contenido plataforma 3

    static mapsector_t sector22; // cuadro grande
    mapvertex_t va22[4] = { {-3904,1472}, {-3136,1472},
        {-3136,3072}, {-3904, 3072} };

    static mapsector_t sector23; // cuadro mediano
    mapvertex_t va23[4] = { {-3776,1600}, {-3264,1600},
        {-3264,2944}, {-3776, 2944} };

    static mapsector_t sector24; // caja demoniaca abajo
    mapvertex_t va24[4] = { {-3648,1664}, {-3392,1664},
        {-3392,1920}, {-3648, 1920} };

    static mapsector_t sector25; // caja demoniaca arriba
    mapvertex_t va25[4] = { {-3648,2624}, {-3392,2624},
        {-3392,2880}, {-3648, 2880} };


    static mapsector_t sector26; // barra demoniaca abajo
    mapvertex_t va26[4] = { {-3616,1792}, {-3520,1696},
        {-3424,1792}, {-3520, 1888} };

    static mapsector_t sector27; // barra demoniaca arriba
    mapvertex_t va27[4] = { {-3616,2752}, {-3520,2656},
        {-3424,2752}, {-3520, 2848} };

    // contenido plataforma 3 derecha

    static mapsector_t sector22_2; // cuadro grande
    mapvertex_t va22_2[4] = { {960,1472}, {192,1472},
        {192,3072}, {960, 3072} };

    static mapsector_t sector23_2; // cuadro mediano
    mapvertex_t va23_2[4] = { {832,1600}, {320,1600},
        {320,2944}, {832, 2944} };


    static mapsector_t sector24_2; // caja demoniaca abajo
    mapvertex_t va24_2[4] = { {704,1664}, {448,1664},
        {448,1920}, {704, 1920} };

    static mapsector_t sector25_2; // caja demoniaca arriba
    mapvertex_t va25_2[4] = { {704,2624}, {448,2624},
        {448,2880}, {704, 2880} };


    static mapsector_t sector26_2; // barra demoniaca abajo
    mapvertex_t va26_2[4] = { {672,1792}, {576,1696},
        {480,1792}, {576, 1888} };

    static mapsector_t sector27_2; // barra demoniaca arriba
    mapvertex_t va27_2[4] = { {672,2752}, {576,2656},
        {480,2752}, {576, 2848} };

    
    //------ contenido plataforma 2 derecha 'estrella'

    static mapsector_t sector40; // centro estrella
    mapvertex_t va40[8] = { {384,480},{416,448},{544,448},{576,480},
        {576,608}, {544,640}, {416,640}, {384,608} };
    static mapsector_t sector41; // flecha izquierda
    mapvertex_t va41[3] = { {64,544},{384,480},{384,608} };
    static mapsector_t sector42; // flecha abajo
    mapvertex_t va42[3] = { {416,448},{480,128},{544,448} };
    static mapsector_t sector43; // flecha derecha
    mapvertex_t va43[3] = { {896,544},{576,608},{576,480} };
    static mapsector_t sector44; // flecha arriba
    mapvertex_t va44[3] = { {544,640},{480,960},{416,640} };

    static mapsector_t sector45; // soporte izquierdo
    mapvertex_t va45[4] = { {-64,480},{64,480},{64,608},{-64,608} };
    static mapsector_t sector46; // soporte derecho
    mapvertex_t va46[4] = { {896,480},{1024,480},{1024,608},{896,608} };
    static mapsector_t sector47; // soporte abajo
    mapvertex_t va47[4] = { {416,0},{544,0},{544,128},{416,128} };
    static mapsector_t sector48; // soporte arriba
    mapvertex_t va48[4] = { {416,960},{544,960},{544,1088},{416,1088} };

    static mapsector_t sector49; // ojo parte superior izquierda
    mapvertex_t va49[4] = { {64,768},{192,768},{192,896},{64,896} };

    static mapsector_t sector50; // ojo parte superior derecha
    mapvertex_t va50[4] = { {768,768},{896,768},{896,896},{768,896} };

    static mapsector_t sector51; // ojo parte inferior izquierda
    mapvertex_t va51[4] = { {64,192},{192,192},{192,320},{64,320} };

    static mapsector_t sector52; // ojo parte inferior derecha
    mapvertex_t va52[4] = { {768,192},{896,192},{896,320},{768,320} };

    static mapsector_t sector53; // caja demoniaca arriba
    mapvertex_t va53[4] = { {768,960},{1024,960},{1024,1216},{768,1216} };

    static mapsector_t sector54; // caja demoniaca abajo
    mapvertex_t va54[4] = { {768,-128},{1024,-128},{1024,128},{768,128} };

    static mapsector_t sector55; // caja de madera arriba
    mapvertex_t va55[4] = { {128,960},{256,960},{256,1088},{128,1088} };

    static mapsector_t sector56; // caja de madera abajo
    mapvertex_t va56[4] = { {128,0},{256,0},{256,128},{128,128} };


    // Plataforma 4

    static mapsector_t sector70;
    mapvertex_t va70[4] = { {-2304,4352},{-640,4352},{-640,5120},{-2304,5120} };

    // Cuadros plataformas

    // calaveras plataforma 3 izquierda
    static mapsector_t sector71;
    mapvertex_t va71[4] = { {-3003,1760},{-3001,1760},{-3001,2784},{-3003,2784} };
    static mapsector_t sector72;
    mapvertex_t va72[4] = { {-3005,1760},{-2950,1760},{-2950,2784},{-3005,2784} };
    // calaveras plataforma 3 derecha
    static mapsector_t sector73;
    mapvertex_t va73[4] = { {58,1760},{61,1760},{61,2784},{58,2784} };
    static mapsector_t sector74;
    mapvertex_t va74[4] = { {30,1760},{56,1760},{56,2784},{30,2784} };

    // CAJAS grandes
    static mapsector_t s75;
    mapvertex_t va75[4] = { {-512,-2304},{-128,-2304},{-128,-1920},{-512,-1920} };
    static mapsector_t s76;
    mapvertex_t va76[4] = { {-2848,-2304},{-2464,-2304},{-2464,-1920},{-2848,-1920} };

    // cajas en tierra
    static mapsector_t c1;
    mapvertex_t vac1[4] = { {-2752,1920},{-2496,1920},{-2496,2112},{-2752,2112} };

    // contenido plataforma 4
    static mapsector_t s78;
    mapvertex_t va78[4] = { {-2304,4224},{-2176,4224},{-2176,4352},{-2304,4352} };
    static mapsector_t s79;
    mapvertex_t va79[4] = { {-768,4224},{-640,4224},{-640,4352},{-768,4352} };
            // base soportes
    static mapsector_t s80; //  left down
    mapvertex_t va80[4] = {{-2272,4384},{-2112,4384},{-2112,4544},{-2272,4544}};
    static mapsector_t s81; //  left up
    mapvertex_t va81[4] = { {-2272,4928},{-2112,4928},{-2112,5088},{-2272,5088} };
    static mapsector_t s82; //  right down
    mapvertex_t va82[4] = { {-832,4384},{-672,4384},{-672,4544},{-832,4544} };
    static mapsector_t s83; //  right up
    mapvertex_t va83[4] = { {-832,4928},{-672,4928},{-672,5088},{-832,5088} };
            // soportes
    static mapsector_t s84; //  left down
    mapvertex_t va84[4] = { {-2240,4416},{-2144,4416},{-2144,4512},{-2240,4512} };
    static mapsector_t s85; //  left top
    mapvertex_t va85[4] = { {-2240,4960},{-2144,4960},{-2144,5056},{-2240,5056} };
    static mapsector_t s86; //  right down
    mapvertex_t va86[4] = { {-800,4416},{-704,4416},{-704,4512},{-800,4512} };
    static mapsector_t s87; //  right top
    mapvertex_t va87[4] = { {-800,4960},{-704,4960},{-704,5056},{-800,5056} };
            // caja demoniaca
    static mapsector_t s88; 
    mapvertex_t va88[4] = { {-1536,4992},{-1408,4992},{-1408,5119},{-1536,5119} };

    // ACIDO

    static mapsector_t s89;
    mapvertex_t va89[4] = { {-3328,-256},{-3221,-320},{-2832,-96},{-2944,-32} };

    // HUECO DE SANGRE
    static mapsector_t s100;
    mapvertex_t va100[4] = { {1280,1536},{2880,1536},{2880,3008},{1280,3008} };

    // PIEDRAS 
    std::vector<std::string> hdwall_3_tex = { "hdwall","hdwall","hdwall" };
    std::vector<std::string> hdwall_4_tex = { "hdwall","hdwall","hdwall","hdwall" };
    std::vector<std::string> hdwall_5_tex = { "hdwall","hdwall","hdwall","hdwall",
    "hdwall" };
    std::vector<std::string> hdwall_6_tex = { "hdwall","hdwall","hdwall" ,
    "hdwall" ,"hdwall" ,"hdwall" };
    std::vector<std::string> hdwall_7_tex = { "hdwall","hdwall","hdwall" ,
    "hdwall" ,"hdwall" ,"hdwall" ,"hdwall" };
    std::vector<std::string> hdmflr8_4_tex = { "mflr8_2","mflr8_2","mflr8_2",
        "mflr8_2" };
    std::vector<std::string> hdmflr8_5_tex = { "mflr8_2","mflr8_2","mflr8_2",
        "mflr8_2","mflr8_2"};
    static mapsector_t r1;
    mapvertex_t var1[4] = { {512,-3772},{1660,-3772},{1664,-3768},{512,-3768} };
    static mapsector_t r2;
    mapvertex_t var2[3] = { {3068,-3772},{3068,-2064},{1664,-3772} };
    static mapsector_t r3;
    mapvertex_t var3[4] = { {1092,-192},{3068,-192},{3068,1280},{1092,1280} };
    static mapsector_t r4;
    mapvertex_t var4[5] = { {1300,-3380},{1756,-3368},{1567,-2888},
        {1332,-2860},{1140,-3152} };
    static mapsector_t r5;
    mapvertex_t var5[4] = { {1756,-3368},{2660,-2220},{1496,-1440},{1304,-2220} };
    static mapsector_t r6;
    mapvertex_t var6[4] = { {2660,-2220},{2820,-1628},{2504,-1264},{1496,-1440} };
    static mapsector_t r7;
    mapvertex_t var7[4] = { {1496,-1440},{2504,-1264},{2116,-680},{1664,-972} };
    static mapsector_t r8;
    mapvertex_t var8[4] = { {2820,-1628},{2956,-1252},{2904,-1052},{2504,-1264} };
    static mapsector_t r9;
    mapvertex_t var9[4] = { {2504,-1264},{2904,-1052},{2980,-232},{2116,-680} };
    static mapsector_t r10;
    mapvertex_t var10[4] = { {1664,-972},{2116,-680},{1640,-336},{1304,-680} };
    static mapsector_t r11;
    mapvertex_t var11[3] = { {1640,-336},{2116,-680},{2980,-232} };

    // rocas izquierda
    static mapsector_t r12;
    mapvertex_t var12[5] = { {-6140,-3772},{-4664,-3772},{-4880,-2468},
        {-5540,-2304},{-6140,-2764} };
    static mapsector_t r13;
    mapvertex_t var13[4] = { {-6140,-2764},{-4036,-1152},{-4036,3328},{-6140,3328} };
    static mapsector_t r14;
    mapvertex_t var14[5] = { {-4880,-2468},{-4096,-1792},{-4036,3328}, {-4672,3248},{-5540,-2304} };
    static mapsector_t r15;
    mapvertex_t var15[4] = { {-4664,-3772},{-4100,-2816},{-4096,-1792},{-4880,-2468} };
    static mapsector_t r16;
    mapvertex_t var16[4] = { {-4660,-3772},{-4092,-2820},{-4100,-2816},{-4664,-3772} };

    // rocas abajo
    static mapsector_t  r17;
    mapvertex_t var17[4] = { {-1848,-3772},{-1096,-3772},{0,-3312},{-3016,-3312} };
    static mapsector_t r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31, r32, r33, r34,
        r35, r36, r37, r38, r39, r40, r41, r42, r43, r44, r45, r46, r47, r48, r49, r50, r51,r52,r53,r54,r55
        ,r56,r57,r58,r59,r60,r61,r62,r63,r64,r65,r66,r67,r68,r69,r70;
    mapvertex_t var18[5] = { {-508,-3312},{56,-3312},{260,-2580},{-96,-2580},{-512,-3080} }; //der
    mapvertex_t var19[5] = { {-3016,-3308},{-2452,-3308},{-2452,-3072},{-2880,-2580},{-3256,-2580} }; // iz

    // rocas arriba izquierda
    mapvertex_t var20[4] = { {-5888,4864},{-5520,4992},{-5520,5376},{-6048,5568} }; //1
    mapvertex_t var21[6] = { {-5776,4347},{-5408,4336},{-5200,4608},{-5520,4992}, {-5888,4864},{-5952,4464} }; //2
    mapvertex_t var22[6] = { {-5200,4608},{-4544,5142},{-4896,5456},{-5216,5568}, {-5520,5376},{-5520,4992} }; //3
    mapvertex_t var23[4] = { {-4992,4240},{-4160,4800},{-4544,5142},{-5200,4608} }; //4
    mapvertex_t var24[5] = { {-5504,4032},{-5168,3920},{-4992,4240},{-5200,4608}, {-5408,4336} }; //5
    mapvertex_t var25[4] = { {-5168,3920},{-4528,3712},{-4640,4477},{-4992,4240} }; //6
    mapvertex_t var26[5] = { {-4528,3712},{-3936,3696},{-3648,4416},{-4160,4800},{-4640,4477} }; //7
    mapvertex_t var27[4] = { {-4160,4800},{-3936,5200},{-4064,5568},{-4896,5456} }; //8
    mapvertex_t var28[5] = { {-3648,4416},{-3264,4784},{-3360,5328},{-3936,5200}, {-4160,4800} }; //9
    mapvertex_t var29[6] = { {-3264,3856},{-2832,4096},{-2624,4512},{-2750,4800}, {-3264,4784},{-3648,4416} }; //10
    mapvertex_t var30[4] = { {-3264,4784},{-2750,4800},{-2896,5136},{-3360,5328} }; //11
    mapvertex_t var31[4] = { {-3936,5200},{-3360,5328},{-3440,5728},{-4064,5568} }; //12
    mapvertex_t var32[3] = { {-3360,5328},{-2912,5680},{-3440,5728} }; //13
    mapvertex_t var33[4] = { {-2896,5136},{-2560,5376},{-2912,5680},{-3360,5328} }; //14
    mapvertex_t var34[5] = { {-2624,4512},{-2304,4688},{-2304,5120},{-2560,5376},{-2896,5136} }; // 15


    // rocas arriba derecha
    mapvertex_t var35[4] = { {-640,5120},{0,4736},{0,5248},{-384,5376} }; //1
    mapvertex_t var36[4] = { {-384,5376},{0,5248},{0,5696},{-384,5632} }; //2
    mapvertex_t var37[4] = { {0,5248},{640,5248},{768,5504},{0,5696} }; //3
    mapvertex_t var38[6] = { {256,4352},{768,4352},{896,4736},{640,5248} ,{0,5248} ,{0,4736} }; //4
    mapvertex_t var39[5] = { {896,4736},{1280,4864},{1408,5248},{768, 5504} , {640, 5248} }; //5
    mapvertex_t var40[6] = { {1024,4096},{1408,4096},{1664,4480},{1280, 4864}, {896,4736},{768,4352} }; //6
    mapvertex_t var41[5] = { {768,3840},{1024,4096},{768,4352},{256,4352}, {512,3968} }; //7
    mapvertex_t var42[4] = { {1408,5248},{2176,5376},{1536,5632},{768,5504} }; //8
    mapvertex_t var43[5] = { {1664,4480},{2176,4864},{2176,5376},{1408,5248}, {1280,4864} }; //9
    mapvertex_t var44[5] = { {1664,3712},{2048,3712},{2304,4096},{1664,4480}, {1408,4096} }; //10
    mapvertex_t var45[4] = { {2432,3584},{2816,3584},{2688,4352},{2304, 4096} }; // 11
    mapvertex_t var46[5] = { {2304,4096},{2688,4352},{2688,4736},{2176,4864}, {1664,4480} }; //12
    mapvertex_t var47[4] = { {2176,4864},{2688,4736},{2816,5632},{2176,5376} }; //13
    mapvertex_t var48[4] = { {2688,4736},{3056,4736},{3056,5632},{2816,5632} }; //14


    // ROCAS GIGANTES IZQUIERDA
    mapvertex_t var49[6] = { {-8640,-3760},{-6160,-3760},{-6416,-2800},{-7160,-2472},{-7968,-2480},{-8552,-2952} };
    mapvertex_t var50[5] = { {-8552,-2952},{-7968,-2480},{-8208,-2088},{-8904,-1992},{-9240,-2384} };
    mapvertex_t var51[6] = { {-9824,-3744},{-8640,-3760},{-8552,-2952},{-9240,-2384},{-9944,-2528}, {-10176,-3336} };
    mapvertex_t var52[6] = { {-9944,-2528},{-9240,-2384},{-8904,-1992},{-8584,-1080},{-8656,-40}, {-10056,280} };
    mapvertex_t var53[5] = { {-8612,-672},{-8160,-664},{-7904,-144},{-8564,424},{-8656,-40} };
    mapvertex_t var54[5] = { {-10056,280},{-8656,-40},{-8416,1176},{-9400,2312},{-10016,1312} };
    mapvertex_t var55[5] = { {-10120,2256},{-9400,2312},{-8576,3352},{-9416,3744},{-10120,3800} };
    mapvertex_t var56[7] = { {-8576, 3352},{-7632,3280},{-6728,4168},{-6046,5392},{-8432,5472}, {-9472,4664},
        {-9416,3744} };

    // ROCAS GIGANTES DERECHA
    mapvertex_t var57[5] = { {3068,-3772},{5947, -2968},{5632,-1808},{3864,-1512},{3068,-2064} };
    mapvertex_t var58[4] = { {4728,-1657},{5632,-1808},{6832, -960},{5520, 344} };
    mapvertex_t var59[3] = { {5947,-2968},{6832,-960},{5632,-1808} };
    mapvertex_t var60[4] = { {5191,-488},{5520,344},{5312,1440},{4512,672} };
    mapvertex_t var61[4] = { {5520,344},{6832,-960},{6824,2888},{5312,1440} };
    mapvertex_t var62[4] = { {4512,672},{5312,1440},{5296,2712},{4720,3360} };
    mapvertex_t var63[4] = { {5296,2712},{6824,2888},{6112,4080},{4720,3360} };
    mapvertex_t var64[7] = { {4720,3360},{6112,4080},{6312,4936},{5896,5552},{4808,5592},{3094,5096},{3644,4320} };

    // gradas

    static mapsector_t g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14, g15, g16, g17, g18, g19, g20,
        g21, g22, g23, g24, g25, g26, g27, g28, g29, g30, g31, g32, g33, g34, g35, g36, g37, g38, g39, g40,g41,g42,
        g43,g44,g45,g46,g47,g48,g49,g50,g51,g52,g53,g54,g55,g56,g57,g58,g59,g60;

    int step = 128;

    mapvertex_t vag1[4] = { {-1856,-2944} , {-1088,-2944}, {-1088,-2816}, {-1856,-2816} };
    mapvertex_t vag2[4] = { {-1856,-2944 + 1 * step} , {-1088,-2944 + 1 * step}, {-1088,-2816 + 1 * step}, {-1856,-2816 + 1 * step} };
    mapvertex_t vag3[4] = { {-1856,-2944 + 2 * step} , {-1088,-2944 + 2 * step}, {-1088,-2816 + 2 * step}, {-1856,-2816 + 2 * step} };
    mapvertex_t vag4[4] = { {-1856,-2944 + 3 * step} , {-1088,-2944 + 3 * step}, {-1088,-2816 + 3 * step}, {-1856,-2816 + 3 * step} };
    mapvertex_t vag5[4] = { {-1856,-2944 + 4 * step} , {-1088,-2944 + 4 * step}, {-1088,-2816 + 4 * step}, {-1856,-2816 + 4 * step} };
    mapvertex_t vag6[4] = { {-1856,-2944 + 5 * step} , {-1088,-2944 + 5 * step}, {-1088,-2816 + 5 * step}, {-1856,-2816 + 5 * step} };
    mapvertex_t vag7[4] = { {-1856,-2944 + 6 * step} , {-1088,-2944 + 6 * step}, {-1088,-2816 + 6 * step}, {-1856,-2816 + 6 * step} };
    mapvertex_t vag8[4] = { {-1856,-2944 + 7 * step} , {-1088,-2944 + 7 * step}, {-1088,-2816 + 7 * step}, {-1856,-2816 + 7 * step} };
    mapvertex_t vag9[4] = { {-1856,-2944 + 8 * step} , {-1088,-2944 + 8 * step}, {-1088,-2816 + 8 * step}, {-1856,-2816 + 8 * step} };
    mapvertex_t vag10[4] = { {-1856,-2944 + 9 * step} , {-1088,-2944 + 9 * step}, {-1088,-2816 + 9 * step}, {-1856,-2816 + 9 * step} };
    mapvertex_t vag11[4] = { {-1856,-2944 + 10 * step} , {-1088,-2944 + 10 * step}, {-1088,-2816 + 10 * step}, {-1856,-2816 + 10 * step} };
    mapvertex_t vag12[4] = { {-1856,-2944 + 11 * step} , {-1088,-2944 + 11 * step}, {-1088,-2816 + 11 * step}, {-1856,-2816 + 11 * step} };
    mapvertex_t vag13[4] = { {-1856,-2944 + 12 * step} , {-1088,-2944 + 12 * step}, {-1088,-2816 + 12 * step}, {-1856,-2816 + 12 * step} };
    mapvertex_t vag14[4] = { {-1856,-2944 + 13 * step} , {-1088,-2944 + 13 * step}, {-1088,-2816 + 13 * step}, {-1856,-2816 + 13 * step} };
    mapvertex_t vag15[4] = { {-1856,-2944 + 14 * step} , {-1088,-2944 + 14 * step}, {-1088,-2816 + 14 * step}, {-1856,-2816 + 14 * step} };
    mapvertex_t vag16[4] = { {-1856,-2944 + 15 * step} , {-1088,-2944 + 15 * step}, {-1088,-2816 + 15 * step}, {-1856,-2816 + 15 * step} };
    mapvertex_t vag17[4] = { {-1856,-2944 + 16 * step} , {-1088,-2944 + 16 * step}, {-1088,-2816 + 16 * step}, {-1856,-2816 + 16 * step} };
    mapvertex_t vag18[4] = { {-1856,-2944 + 17 * step} , {-1088,-2944 + 17 * step}, {-1088,-2816 + 17 * step}, {-1856,-2816 + 17 * step} };
    mapvertex_t vag19[4] = { {-1856,-2944 + 18 * step} , {-1088,-2944 + 18 * step}, {-1088,-2816 + 18 * step}, {-1856,-2816 + 18 * step} };
    mapvertex_t vag20[4] = { {-1856,-2944 + 19 * step} , {-1088,-2944 + 19 * step}, {-1088,-2816 + 19 * step}, {-1856,-2816 + 19 * step} };
    mapvertex_t vag21[4] = { {-1856,-2944 + 20 * step} , {-1088,-2944 + 20 * step}, {-1088,-2816 + 20 * step}, {-1856,-2816 + 20 * step} };
    mapvertex_t vag22[4] = { {-1856,-2944 + 21 * step} , {-1088,-2944 + 21 * step}, {-1088,-2816 + 21 * step}, {-1856,-2816 + 21 * step} };
    mapvertex_t vag23[4] = { {-1856,-2944 + 22 * step} , {-1088,-2944 + 22 * step}, {-1088,-2816 + 22 * step}, {-1856,-2816 + 22 * step} };
    mapvertex_t vag24[4] = { {-1856,-2944 + 23 * step} , {-1088,-2944 + 23 * step}, {-1088,-2816 + 23 * step}, {-1856,-2816 + 23 * step} };
    mapvertex_t vag25[4] = { {-1856,-2944 + 24 * step} , {-1088,-2944 + 24 * step}, {-1088,-2816 + 24 * step}, {-1856,-2816 + 24 * step} };
    mapvertex_t vag26[4] = { {-1856,-2944 + 25 * step} , {-1088,-2944 + 25 * step}, {-1088,-2816 + 25 * step}, {-1856,-2816 + 25 * step} };
    mapvertex_t vag27[4] = { {-1856,-2944 + 26 * step} , {-1088,-2944 + 26 * step}, {-1088,-2816 + 26 * step}, {-1856,-2816 + 26 * step} };
    mapvertex_t vag28[4] = { {-1856,-2944 + 27 * step} , {-1088,-2944 + 27 * step}, {-1088,-2816 + 27 * step}, {-1856,-2816 + 27 * step} };
    mapvertex_t vag29[4] = { {-1856,-2944 + 28 * step} , {-1088,-2944 + 28 * step}, {-1088,-2816 + 28 * step}, {-1856,-2816 + 28 * step} };
    mapvertex_t vag30[4] = { {-1856,-2944 + 29 * step} , {-1088,-2944 + 29 * step}, {-1088,-2816 + 29 * step}, {-1856,-2816 + 29 * step} };
    mapvertex_t vag31[4] = { {-1856,-2944 + 30 * step} , {-1088,-2944 + 30 * step}, {-1088,-2816 + 30 * step}, {-1856,-2816 + 30 * step} };
    mapvertex_t vag32[4] = { {-1856,-2944 + 31 * step} , {-1088,-2944 + 31 * step}, {-1088,-2816 + 31 * step}, {-1856,-2816 + 31 * step} };
    mapvertex_t vag33[4] = { {-1856,-2944 + 32 * step} , {-1088,-2944 + 32 * step}, {-1088,-2816 + 32 * step}, {-1856,-2816 + 32 * step} };
    mapvertex_t vag34[4] = { {-1856,-2944 + 33 * step} , {-1088,-2944 + 33 * step}, {-1088,-2816 + 33 * step}, {-1856,-2816 + 33 * step} };
    mapvertex_t vag35[4] = { {-1856,-2944 + 34 * step} , {-1088,-2944 + 34 * step}, {-1088,-2816 + 34 * step}, {-1856,-2816 + 34 * step} };
    mapvertex_t vag36[4] = { {-1856,-2944 + 35 * step} , {-1088,-2944 + 35 * step}, {-1088,-2816 + 35 * step}, {-1856,-2816 + 35 * step} };
    mapvertex_t vag37[4] = { {-1856,-2944 + 36 * step} , {-1088,-2944 + 36 * step}, {-1088,-2816 + 36 * step}, {-1856,-2816 + 36 * step} };
    mapvertex_t vag38[4] = { {-1856,-2944 + 37 * step} , {-1088,-2944 + 37 * step}, {-1088,-2816 + 37 * step}, {-1856,-2816 + 37 * step} };
    mapvertex_t vag39[4] = { {-1856,-2944 + 38 * step} , {-1088,-2944 + 38 * step}, {-1088,-2816 + 38 * step}, {-1856,-2816 + 38 * step} };
    mapvertex_t vag40[4] = { {-1856,-2944 + 39 * step} , {-1088,-2944 + 39 * step}, {-1088,-2816 + 39 * step}, {-1856,-2816 + 39 * step} };
    mapvertex_t vag41[4] = { {-1856,-2944 + 40 * step} , {-1088,-2944 + 40 * step}, {-1088,-2816 + 40 * step}, {-1856,-2816 + 40 * step} };
    mapvertex_t vag42[4] = { {-1856,-2944 + 41 * step} , {-1088,-2944 + 41 * step}, {-1088,-2816 + 41 * step}, {-1856,-2816 + 41 * step} };
    mapvertex_t vag43[4] = { {-1856,-2944 + 42 * step} , {-1088,-2944 + 42 * step}, {-1088,-2816 + 42 * step}, {-1856,-2816 + 42 * step} };
    mapvertex_t vag44[4] = { {-1856,-2944 + 43 * step} , {-1088,-2944 + 43 * step}, {-1088,-2816 + 43 * step}, {-1856,-2816 + 43 * step} };
    mapvertex_t vag45[4] = { {-1856,-2944 + 44 * step} , {-1088,-2944 + 44 * step}, {-1088,-2816 + 44 * step}, {-1856,-2816 + 44 * step} };
    mapvertex_t vag46[4] = { {-1856,-2944 + 45 * step} , {-1088,-2944 + 45 * step}, {-1088,-2816 + 45 * step}, {-1856,-2816 + 45 * step} };
    mapvertex_t vag47[4] = { {-1856,-2944 + 46 * step} , {-1088,-2944 + 46 * step}, {-1088,-2816 + 46 * step}, {-1856,-2816 + 46 * step} };
    mapvertex_t vag48[4] = { {-1856,-2944 + 47 * step} , {-1088,-2944 + 47 * step}, {-1088,-2816 + 47 * step}, {-1856,-2816 + 47 * step} };
    mapvertex_t vag49[4] = { {-1856,-2944 + 48 * step} , {-1088,-2944 + 48 * step}, {-1088,-2816 + 48 * step}, {-1856,-2816 + 48 * step} };
    mapvertex_t vag50[4] = { {-1856,-2944 + 49 * step} , {-1088,-2944 + 49 * step}, {-1088,-2816 + 49 * step}, {-1856,-2816 + 49 * step} };
    mapvertex_t vag51[4] = { {-1856,-2944 + 50 * step} , {-1088,-2944 + 50 * step}, {-1088,-2816 + 50 * step}, {-1856,-2816 + 50 * step} };
    mapvertex_t vag52[4] = { {-1856,-2944 + 51 * step} , {-1088,-2944 + 51 * step}, {-1088,-2816 + 51 * step}, {-1856,-2816 + 51 * step} };
    mapvertex_t vag53[4] = { {-1856,-2944 + 52 * step} , {-1088,-2944 + 52 * step}, {-1088,-2816 + 52 * step}, {-1856,-2816 + 52 * step} };
    mapvertex_t vag54[4] = { {-1856,-2944 + 53 * step} , {-1088,-2944 + 53 * step}, {-1088,-2816 + 53 * step}, {-1856,-2816 + 53 * step} };
    mapvertex_t vag55[4] = { {-1856,-2944 + 54 * step} , {-1088,-2944 + 54 * step}, {-1088,-2816 + 54 * step}, {-1856,-2816 + 54 * step} };
    mapvertex_t vag56[4] = { {-1856,-2944 + 55 * step} , {-1088,-2944 + 55 * step}, {-1088,-2816 + 55 * step}, {-1856,-2816 + 55 * step} };
    mapvertex_t vag57[4] = { {-1856,-2944 + 56 * step} , {-1088,-2944 + 56 * step}, {-1088,-2816 + 56 * step}, {-1856,-2816 + 56 * step} };
    


    //----------------------------------------------------------------------------------------------------

    // Construimos los sectores
    static SceneBuilder* builder = new SceneBuilder();

    float main_sector_height = 4000;

    std::vector<std::string> hdbricks_4_textures = { "hdwall","hdwall","hdwall","hdwall" };
    std::vector<std::string> hdbricks_8_textures = { "hdgstone","hdwall","hdwall","hdwall" , "hdwall",
    "hdwall","hdwall","hdwall"};
    std::vector<std::string> hdbricks_3_textures = { "hdwall","hdwall","hdwall" };
    std::vector<std::string> hdredbr_4_textures = { "hdredbricks","hdredbricks",
        "hdredbricks","hdredbricks" };

    //--- sector principal
    builder->buildSector(va1, NULLL, NULLL, hdbricks_4_textures, NULLL, NULLL,
        "mflr8_2",
        "dem1_5",
        0,
        main_sector_height,
        70,
        sector1,
        4
    );


    builder->buildSector(va_river, NULLL,NULLL,NULLL,NULLL, hdbricks_8_textures,
        "hdwater","hdwater",-500,main_sector_height, 70,river_sector, 8);


    //---- sectores de relleno
    builder->buildSector(va2, NULLL, NULLL, NULLL, hdbricks_3_textures, NULLL,
        "ceil5_2","dem1_5",main_sector_height,main_sector_height,210,sector2,3
    );
    builder->buildSector(va3, NULLL, NULLL, NULLL, hdbricks_3_textures, NULLL,
        "ceil5_2", "dem1_5", main_sector_height, main_sector_height, 210, sector3, 3
    );
    builder->buildSector(va4, NULLL, NULLL, NULLL, hdbricks_4_textures, NULLL,
        "ceil5_2", "dem1_5", main_sector_height, main_sector_height, 210, sector4, 4
    );
    builder->buildSector(va5, NULLL, NULLL, NULLL, hdbricks_4_textures, NULLL,
        "ceil5_2", "dem1_5", main_sector_height, main_sector_height, 210, sector5, 4
    );

    //---- plataforma1

    std::vector<std::string> poison_8_textures = { "hdpoisonwall","hdpoisonwall",
    "hdpoisonwall","hdpoisonwall","hdpoisonwall","hdpoisonwall","hdpoisonwall",
    "hdpoisonwall" };

    builder->buildSector(va6, marble3_8_textures, NULLL, NULLL, NULLL, poison_8_textures,
        "dbrain1", "dem1_5", -160, 917, 25, sector6, 8
    );
    builder->buildSector(va6_2, marble3_8_textures, NULLL, NULLL, NULLL, poison_8_textures,
        "dbrain1", "dem1_5", -160, 917, 25, sector6_2, 8
    );

    //---- plataforma2

    std::vector<std::string> plataform2_textures = { "hdmarbgray","hdmarbgray","hdmarbgray"
        ,"hdmarbgray","hdmarbgray","hdmarbgray","hdmarbgray","hdmarbgrayface" };

    builder->buildSector(va7, marble3_8_textures, NULLL, NULLL, plataform2_textures, NULLL,
        "dem1_6", "dem1_6", 1088, 1957, 115, sector7, 8
    );
    builder->buildSector(va7_2, marble3_8_textures, NULLL, NULLL, plataform2_textures, NULLL,
        "dem1_6", "dem1_6", 1088, 1957, 115, sector7_2, 8
    );

    //---- plataforma3

    builder->buildSector(va8, marble2_4_textures, NULLL, NULLL, marble2_4_textures, NULLL,
        "dem1_6", "dem1_6", 1752, 2592, 135, sector8, 4
    );
    builder->buildSector(va8_2, marble2_4_textures, NULLL, NULLL, marble2_4_textures, NULLL,
        "dem1_6", "dem1_6", 1752, 2592, 135, sector8_2, 4
    );

    //----- contenido plataforma 1

    builder->buildSector(va9, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_6", 96, 789, 110, sector9, 4
    );

    builder->buildSector(va10, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_6", 96, 789, 110, sector10, 4
    );

    builder->buildSector(va11, NULLL, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_6", 789, 789, 135, sector11, 4
    );

    builder->buildSector(va12, NULLL, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_6", 789, 789, 135, sector12, 4
    );

    builder->buildSector(va13, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_6", 224, 917, 135, sector13, 4
    );

    builder->buildSector(va14, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_6", 96, 917, 135, sector14, 4
    );

    //----- contenido plataforma 1 extra

    builder->buildSector(va9_2, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_6", 96, 789, 110, sector9_2, 4
    );

    builder->buildSector(va10_2, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_6", 96, 789, 110, sector10_2, 4
    );

    builder->buildSector(va11_2, NULLL, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_6", 789, 789, 135, sector11_2, 4
    );

    builder->buildSector(va12_2, NULLL, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_6", 789, 789, 135, sector12_2, 4
    );

    //----- contenido plataforma 2

    builder->buildSector(va15, bloodboxes_4_textures, NULLL, NULLL, bloodboxes_4_textures, NULLL,
        "ceil5_2", "dem1_6", 1360, 1701, 200, sector15, 4
    );
    builder->buildSector(va16, metal_4_textures, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_6", "doorblu2", 1376, 1669, 240, sector16, 4
    );
    builder->buildSector(va17, metal_4_textures, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_6", "doorblu2", 1376, 1669, 240, sector17, 4
    );
    builder->buildSector(va18, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_6", "dem1_6", 1216, 1829, 125, sector18, 4
    );
    builder->buildSector(va19, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_6", "dem1_6", 1216, 1829, 125, sector19, 4
    );
    builder->buildSector(va20, metal_4_textures, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_6", "dem1_6", 1829, 1829, 125, sector20, 4
    );
    builder->buildSector(va21, metal_4_textures, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_6", "dem1_6", 1829, 1829, 125, sector21, 4
    );

    // contenido plataforma 3

    builder->buildSector(va22, marble1_4_textures, NULLL, NULLL, marble1_4_textures, NULLL,
        "dem1_6", "dem1_6", 1872, 2462, 110, sector22, 4
    );

    builder->buildSector(va23, marble1_4_textures, NULLL, NULLL, marble1_4_textures, NULLL,
        "dem1_6", "dem1_6", 2000, 2462, 85, sector23, 4
    );

    builder->buildSector(va24, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_5", 2128, 2336, 75, sector24, 4
    );

    builder->buildSector(va25, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_5", 2128, 2336, 75, sector25, 4
    );

    builder->buildSector(va26, metal_4_textures, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_5", 2336, 2336, 75, sector26, 4
    );

    builder->buildSector(va27, metal_4_textures, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_5", 2336, 2336, 75, sector27, 4
    );

    //------- contenido plataforma 3 extra

    builder->buildSector(va22_2, marble1_4_textures, NULLL, NULLL, marble1_4_textures, NULLL,
        "dem1_6", "dem1_6", 1872, 2462, 110, sector22_2, 4
    );

    builder->buildSector(va23_2, marble1_4_textures, NULLL, NULLL, marble1_4_textures, NULLL,
        "dem1_6", "dem1_6", 2000, 2462, 85, sector23_2, 4
    );

    builder->buildSector(va24_2, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_5", 2128, 2336, 75, sector24_2, 4
    );

    builder->buildSector(va25_2, bigdoor7_4_textures, NULLL, NULLL, bigdoor7_4_textures, NULLL,
        "dem1_5", "dem1_5", 2128, 2336, 75, sector25_2, 4
    );

    builder->buildSector(va26_2, metal_4_textures, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_5", 2336, 2336, 75, sector26_2, 4
    );

    builder->buildSector(va27_2, metal_4_textures, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_5", 2336, 2336, 75, sector27_2, 4
    );

    //------ contenido plataforma 2 extra

    // estrella
    builder->buildSector(va40, metal_8_textures, NULLL, NULLL, metal_8_textures, NULLL,
        "flat5_3", "flat5_3", 1100, 1805, 220, sector40, 8
    ); 

    builder->buildSector(va41, metal_3_textures, NULLL, NULLL, metal_3_textures, NULLL ,
        "flat5_3", "flat5_3", 1100, 1805, 220, sector41, 3
    );
    builder->buildSector(va42, metal_3_textures, NULLL, NULLL, metal_3_textures, NULLL  ,
        "flat5_3", "flat5_3", 1100, 1805, 220, sector42, 3
    );
    builder->buildSector(va43, metal_3_textures, NULLL, NULLL, metal_3_textures, NULLL ,
        "flat5_3", "flat5_3", 1100, 1805, 220, sector43, 3
    );
    builder->buildSector(va44, metal_3_textures, NULLL, NULLL, metal_3_textures, NULLL ,
        "flat5_3", "flat5_3", 1100, 1805, 220, sector44, 3
    );

    // soportes

    builder->buildSector(va45, NULLL, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_5", 1957, 1957, 75, sector45, 4
    );
    builder->buildSector(va46, NULLL, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_5", 1957, 1957, 75, sector46, 4
    );
    builder->buildSector(va47, NULLL, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_5", 1957, 1957, 75, sector47, 4
    );
    builder->buildSector(va48, NULLL, NULLL, NULLL, metal_4_textures, NULLL,
        "dem1_5", "dem1_5", 1957, 1957, 75, sector48, 4
    );

    // OJOS

    builder->buildSector(va49, sw2skin_4_textures, NULLL, NULLL, NULLL, NULLL,
        "dem1_6", "dem1_5", 1088, 1845, 75, sector49, 4
    );

    builder->buildSector(va50, sw2skin_4_textures, NULLL, NULLL, NULLL, NULLL,
        "dem1_6", "dem1_5", 1088, 1845, 75, sector50, 4
    );

    builder->buildSector(va51, sw2skin_4_textures, NULLL, NULLL, NULLL, NULLL,
        "dem1_6", "dem1_5", 1088, 1845, 75, sector51, 4
    );

    builder->buildSector(va52, sw2skin_4_textures, NULLL, NULLL, NULLL, NULLL,
        "dem1_6", "dem1_5", 1088, 1845, 75, sector52, 4
    );

    // cajas demoniacas

    builder->buildSector(va53, NULLL, NULLL, NULLL, marbface_4_textures, NULLL,
        "dem1_6", "dem1_6", 1344, 1957, 75, sector53, 4
    );

    builder->buildSector(va54, NULLL, NULLL, NULLL, marbface_4_textures, NULLL,
        "dem1_6", "dem1_6", 1344, 1957, 75, sector54, 4
    );

    // cajas con sangre
    builder->buildSector(va55, NULLL, NULLL, NULLL, bloodboxes_4_textures, NULLL,
        "ceil5_2", "dem1_6", 1352, 1957, 75, sector55, 4
    );
    builder->buildSector(va56, NULLL, NULLL, NULLL, bloodboxes_4_textures, NULLL,
        "ceil5_2", "dem1_6", 1352, 1957, 75, sector56, 4
    );

    std::vector<std::string> hdwooden_4_tex = { "hdgstone","hdgstone","hdgstone","hdgstone" };

    //--------- plataforma 4

    builder->buildSector(va70, hdwooden_4_tex, NULLL, NULLL, hdwooden_4_tex, NULLL,
        "dem1_6", "dem1_6", 1824, 2208, 70, sector70, 4
    );

    //------ Cuadros en paredes

    std::vector<std::string> texttt = { "metal","hdmarbfac3","metal","metal" };
    std::vector<std::string> texttt2 = { "metal","metal","metal","hdmancubus" };
    std::vector<std::string> skulldoor7_4_textures = { "metal","skulldoor7","metal","skulldoor7" };

    builder->buildSector(va71, skulldoor7_4_textures, NULLL, NULLL, NULLL , NULLL,
        "mflr8_2", "dem1_6", 0, 2848, 70, sector71, 4
    );
    
    builder->buildSector(va72, texttt, NULLL, NULLL, NULLL, NULLL,
        "mflr8_2", "metal", 0, 2976, 70, sector72, 4
    );

    builder->buildSector(va73, skulldoor7_4_textures, NULLL, NULLL, NULLL, NULLL,
        "mflr8_2", "dem1_6", 0, 2848, 70, sector73, 4
    );

    builder->buildSector(va74, texttt2, NULLL, NULLL, NULLL, NULLL,
        "mflr8_2", "metal", 0, 2976, 70, sector74, 4
    );

    //---------- CAJAS GIGANTES
    builder->buildSector(va75, NULLL, NULLL, NULLL, a_brown4_4_textures, NULLL,
        "ceil5_2", "dem1_6", 384, main_sector_height, 70, s75, 4
    );
    builder->buildSector(va76, NULLL, NULLL, NULLL, a_brown4_4_textures, NULLL,
        "ceil5_2", "dem1_6", 384, main_sector_height, 70, s76, 4
    );
    //--------- CAJAS EN TIERRA
    builder->buildSector(vac1, NULLL, NULLL, NULLL, crate1_4_textures, NULLL,
        "ceil5_2", "dem1_6", 640, main_sector_height, 70, c1, 4
    );
    //------------ contenido plataforma 4
    builder->buildSector(va78, NULLL, NULLL, NULLL, support3_4_textures, NULLL,
        "ceil5_2", "dem1_5", 1688, main_sector_height, 70, s78, 4
    );
    builder->buildSector(va79, NULLL, NULLL, NULLL, support3_4_textures, NULLL,
        "ceil5_2", "dem1_5", 1688, main_sector_height, 70, s79, 4
    );
    builder->buildSector(va80, NULLL, NULLL, NULLL, support3_4_textures, NULLL,
        "metal", "dem1_5", 1920, 2208, 70, s80, 4
    );
    builder->buildSector(va81, NULLL, NULLL, NULLL, support3_4_textures, NULLL,
        "metal", "dem1_5", 1920, 2208, 70, s81, 4
    );
    builder->buildSector(va82, NULLL, NULLL, NULLL, support3_4_textures, NULLL,
        "metal", "dem1_5", 1920, 2208, 70, s82, 4
    );
    builder->buildSector(va83, NULLL, NULLL, NULLL, support3_4_textures, NULLL,
        "metal", "dem1_5", 1920, 2208, 70, s83, 4
    );
    builder->buildSector(va84, NULLL, NULLL, NULLL, pipewal2_4_textures, NULLL,
        "metal", "dem1_5", 2208, 2208, 70, s84, 4
    );
    builder->buildSector(va85, NULLL, NULLL, NULLL, pipewal2_4_textures, NULLL,
        "metal", "dem1_5", 2208, 2208, 70, s85, 4
    );
    builder->buildSector(va86, NULLL, NULLL, NULLL, pipewal2_4_textures, NULLL,
        "metal", "dem1_5", 2208, 2208, 70, s86, 4
    );
    builder->buildSector(va87, NULLL, NULLL, NULLL, pipewal2_4_textures, NULLL,
        "metal", "dem1_5", 2208, 2208, 70, s87, 4
    );
    builder->buildSector(va88, NULLL, NULLL, NULLL, marbface_4_textures, NULLL,
        "metal", "dem1_5", 1952, 2208, 70, s88, 4
    );
    
    // acido
    builder->buildSector(va89, NULLL, NULLL, NULLL, NULLL , marble1_4_textures,
        "nukage1", "dem1_5", -32, main_sector_height, 70, s89, 4
    );

    // --------------------------ROCKS
    builder->buildSector(var1, NULLL, NULLL, NULLL, hdwall_4_tex, NULLL,
        "mflr8_2", "mflr8_2", main_sector_height, main_sector_height, 30, r1, 4);
    builder->buildSector(var2, NULLL, NULLL, NULLL, hdwall_3_tex, NULLL,
        "mflr8_2", "hdfloor", main_sector_height, main_sector_height, 30, r2, 3);
    builder->buildSector(var3, NULLL, NULLL, NULLL, hdwall_4_tex, NULLL,
        "mflr8_2", "mflr8_2", main_sector_height, main_sector_height, 30, r3, 4);
    builder->buildSector(var4, hdmflr8_5_tex, NULLL, NULLL, NULLL, hdmflr8_5_tex,
        "hdfloor", "hdfloor", -128, 960, 30, r4, 5);
    builder->buildSector(var5, hdwall_4_tex, NULLL, NULLL, hdwall_4_tex, NULLL,
        "mflr8_2", "hdfloor", 144, 1264, 30, r5, 4);
    builder->buildSector(var6, hdwall_4_tex, NULLL, NULLL, hdwall_4_tex, NULLL ,
        "mflr8_2", "hdfloor", 27, 1064, 30, r6, 4);
    builder->buildSector(var7, hdwall_4_tex, NULLL, NULLL, NULLL, hdwall_4_tex,
        "hdwater", "hdfloor", -32, 596, 30, r7, 4);
    builder->buildSector(var8, hdwall_4_tex, NULLL, NULLL, hdwall_4_tex, NULLL,
        "mflr8_2", "hdfloor", 424, 1836, 30, r8, 4);
    builder->buildSector(var9, hdwall_4_tex, NULLL, NULLL, hdwall_4_tex, NULLL,
        "mflr8_2", "hdfloor", 632, 1680, 30, r9, 4);
    builder->buildSector(var10, hdwall_4_tex, NULLL, NULLL, hdwall_4_tex, NULLL,
        "mflr8_2", "hdfloor", 352, 1570, 30, r10, 4);
    builder->buildSector(var11, hdwall_3_tex, NULLL, NULLL, hdwall_3_tex, NULLL,
        "mflr8_2", "hdfloor", 1170, 1441, 30, r11, 3);

    //---- left
    builder->buildSector(var12, NULLL, NULLL, NULLL, hdwall_5_tex, NULLL,
        "mflr8_2", "mflr8_2", main_sector_height, main_sector_height, 30, r12, 5);
    builder->buildSector(var13, NULLL, NULLL, NULLL, hdwall_4_tex, NULLL,
        "mflr8_2", "mflr8_2", main_sector_height, main_sector_height, 30, r13, 4);
    builder->buildSector(var14, hdwall_5_tex, NULLL, NULLL, hdwall_5_tex, NULLL,
        "mflr8_2", "mflr8_2", 44, 512, 30, r14, 5);
    builder->buildSector(var15, hdwall_4_tex, NULLL, NULLL, NULLL, hdwall_4_tex,
        "hdwater", "mflr8_2", -10, 488, 30, r15, 4);
    builder->buildSector(var16, NULLL, NULLL, NULLL, hdwall_4_tex, NULLL,
        "mflr8_2", "mflr8_2", main_sector_height, main_sector_height, 30, r16, 4);
    
    // rocas abajo 
    builder->buildSector(var17, hdwall_4_tex, NULLL, NULLL, NULLL, NULLL,
        "mflr8_2", "hdfloor", 0, 680, 30, r17, 4);
    builder->buildSector(var18, hdwall_5_tex , NULLL, NULLL, NULLL, NULLL,
        "mflr8_2", "hdfloor", 0, 1416, 30, r18, 5);
    builder->buildSector(var19, hdwall_5_tex, NULLL, NULLL, NULLL, NULLL,
        "mflr8_2", "hdfloor", 0, 1416, 30, r19, 5);

    //rocas  izquierda arriba (20-34)

    std::vector<std::string> hd_whiterock_3_tex = { "hdwall","hdwall",
        "hdwall" };
    std::vector<std::string> hd_whiterock_4_tex = { "hdwall","hdwall",
        "hdwall","hdwall" };
    std::vector<std::string> hd_whiterock_5_tex = { "hdwall","hdwall",
        "hdwall","hdwall","hdwall" };
    std::vector<std::string> hd_whiterock_6_tex = { "hdwall","hdwall",
        "hdwall","hdwall","hdwall","hdwall" };

    std::vector<std::string> hd_whiterock_7_tex = { "hdwall","hdwall",
        "hdwall","hdwall","hdwall","hdwall", "hdwall" };

    builder->buildSector(var20, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 1496, main_sector_height, 100, r20, 4);
    builder->buildSector(var21, NULLL, NULLL, NULLL, hd_whiterock_6_tex, NULLL,
        "hdfloor", "hdfloor", 960, main_sector_height, 100, r21, 6);
    builder->buildSector(var22, NULLL, NULLL, NULLL, hd_whiterock_6_tex, NULLL,
        "hdfloor", "hdfloor", 1207, main_sector_height, 100, r22, 6);
    builder->buildSector(var23, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 504, main_sector_height, 100, r23, 4);
    builder->buildSector(var24, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 664, main_sector_height, 100, r24, 5);
    builder->buildSector(var25, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 352, main_sector_height, 100, r25, 4);
    builder->buildSector(var26, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 199, main_sector_height, 100, r26, 5);
    builder->buildSector(var27, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 899, main_sector_height, 100, r27, 4);
    builder->buildSector(var28, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 592, main_sector_height, 100, r28, 5);
    builder->buildSector(var29, NULLL, NULLL, NULLL, hd_whiterock_6_tex, NULLL,
        "hdfloor", "hdfloor", 128, main_sector_height, 100, r29, 6);
    builder->buildSector(var30, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 288, main_sector_height, 100, r30, 4);
    builder->buildSector(var31, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 752, main_sector_height, 100, r31, 4);
    builder->buildSector(var32, NULLL, NULLL, NULLL, hd_whiterock_3_tex, NULLL,
        "hdfloor", "hdfloor", 1244, main_sector_height, 100, r32, 3);
    builder->buildSector(var33, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 992, main_sector_height, 100, r33, 4);
    builder->buildSector(var34, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 688, main_sector_height, 100, r34, 5);


    // rocas derecha arriba
    builder->buildSector(var35, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 232, main_sector_height, 100, r35, 4); //1

    builder->buildSector(var36, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 1128, main_sector_height, 100, r36, 4); //2

    builder->buildSector(var37, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 888, main_sector_height, 100, r37, 4); // 3

    builder->buildSector(var38, NULLL, NULLL, NULLL, hd_whiterock_6_tex, NULLL,
        "hdfloor", "hdfloor", 408, main_sector_height, 100, r38, 6); //4

    builder->buildSector(var39, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 666, main_sector_height, 100, r39, 5); //5

    builder->buildSector(var40, NULLL, NULLL, NULLL, hd_whiterock_6_tex, NULLL,
        "hdfloor", "hdfloor", 264, main_sector_height, 100, r40, 6); //6

    builder->buildSector(var41, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 99, main_sector_height, 100, r41, 5); //7

    builder->buildSector(var42, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 1336, main_sector_height, 100, r42, 4); //8

    builder->buildSector(var43, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 528, main_sector_height, 100, r43, 5); // 9

    builder->buildSector(var44, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 473, main_sector_height, 100, r44, 5); // 10

    builder->buildSector(var45, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 936, main_sector_height, 100, r45, 4);

    builder->buildSector(var46, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 689, main_sector_height, 100, r46, 5); // 12

    builder->buildSector(var47, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 1127, main_sector_height, 100, r47, 4); //13

    builder->buildSector(var48, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 1300, main_sector_height, 100, r48, 4); //14

    //---------- ROCAS ALREDEDORES IZQUIERDA
    builder->buildSector(var49, NULLL, NULLL, NULLL, hd_whiterock_6_tex, NULLL,
        "hdfloor", "hdfloor", 1498, main_sector_height, 100, r49, 6); 

    builder->buildSector(var50, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 896, main_sector_height, 100, r50, 5);

    builder->buildSector(var51, NULLL, NULLL, NULLL, hd_whiterock_6_tex, NULLL,
        "hdfloor", "hdfloor", 2224, main_sector_height, 100, r51, 6);

    builder->buildSector(var52, NULLL, NULLL, NULLL, hd_whiterock_6_tex, NULLL,
        "hdfloor", "hdfloor", 1538, main_sector_height, 100, r52, 6);

    builder->buildSector(var53, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 488, main_sector_height, 100, r53, 5);

    builder->buildSector(var54, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 2384, main_sector_height, 100, r54, 5);

    builder->buildSector(var55, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 1771, main_sector_height, 100, r55, 5);

    builder->buildSector(var56, NULLL, NULLL, NULLL, hd_whiterock_7_tex, NULLL,
        "hdfloor", "hdfloor", 1222, main_sector_height, 100, r56, 7);

    //------------- ROCAS ALREDEDORES DERECHA

    builder->buildSector(var57, NULLL, NULLL, NULLL, hd_whiterock_5_tex, NULLL,
        "hdfloor", "hdfloor", 1472, main_sector_height, 100, r57, 5);

    builder->buildSector(var58, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 999, main_sector_height, 100, r58, 4);

    builder->buildSector(var59, NULLL, NULLL, NULLL, hd_whiterock_3_tex, NULLL,
        "hdfloor", "hdfloor", 2720, main_sector_height, 100, r59, 3);

    builder->buildSector(var60, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 1477, main_sector_height, 100, r60, 4);

    builder->buildSector(var61, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 2100, main_sector_height, 100, r61, 4);

    builder->buildSector(var62, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 688, main_sector_height, 100, r62, 4);

    builder->buildSector(var63, NULLL, NULLL, NULLL, hd_whiterock_4_tex, NULLL,
        "hdfloor", "hdfloor", 1477, main_sector_height, 100, r63, 4);

    builder->buildSector(var64, NULLL, NULLL, NULLL, hd_whiterock_7_tex, NULLL,
        "hdfloor", "hdfloor", 988, main_sector_height, 100, r64, 7);


    //------------------------------------- HUECO DE SANGRE
    std::vector<std::string> bloodwalls_4_tex = {"support3","support3","support3",
    "support3"};
    builder->buildSector(va100, NULLL, NULLL, NULLL, NULLL, bloodwalls_4_tex,
        "hdblood", "mflr8_2", -736, main_sector_height, 80, s100, 4);

    //----- gradas

    int f_step = 32;
    int light_gradas = 70;
    std::string floor_text_gradas = "ceil5_2";
    std::string ceil_text_gradas = "dem1_5";
    std::vector<std::string> textura_gradas = {"metal","support3","support3","support3"};
    int ceil_height_gradas = main_sector_height;

    builder->buildSector(vag1, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 1*f_step, ceil_height_gradas, light_gradas, g1, 4);
    builder->buildSector(vag2, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 2 * f_step, ceil_height_gradas, light_gradas, g2, 4);
    builder->buildSector(vag3, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 3 * f_step, ceil_height_gradas, light_gradas, g3, 4);
    builder->buildSector(vag4, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 4 * f_step, ceil_height_gradas, light_gradas, g4, 4);
    builder->buildSector(vag5, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 5 * f_step, ceil_height_gradas, light_gradas, g5, 4);
    builder->buildSector(vag6, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 6 * f_step, ceil_height_gradas, light_gradas, g6, 4);
    builder->buildSector(vag7, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 7 * f_step, ceil_height_gradas, light_gradas, g7, 4);
    builder->buildSector(vag8, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 8 * f_step, ceil_height_gradas, light_gradas, g8, 4);
    builder->buildSector(vag9, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 9 * f_step, ceil_height_gradas, light_gradas, g9, 4);
    builder->buildSector(vag10, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 10 * f_step, ceil_height_gradas, light_gradas, g10, 4);
    builder->buildSector(vag11, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 11 * f_step, ceil_height_gradas, light_gradas, g11, 4);
    builder->buildSector(vag12, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 12 * f_step, ceil_height_gradas, light_gradas, g12, 4);
    builder->buildSector(vag13, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 13 * f_step, ceil_height_gradas, light_gradas, g13, 4);
    builder->buildSector(vag14, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 14 * f_step, ceil_height_gradas, light_gradas, g14, 4);
    builder->buildSector(vag15, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 15 * f_step, ceil_height_gradas, light_gradas, g15, 4);
    builder->buildSector(vag16, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 16 * f_step, ceil_height_gradas, light_gradas, g16, 4);
    builder->buildSector(vag17, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 17 * f_step, ceil_height_gradas, light_gradas, g17, 4);
    builder->buildSector(vag18, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 18 * f_step, ceil_height_gradas, light_gradas, g18, 4);
    builder->buildSector(vag19, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 19 * f_step, ceil_height_gradas, light_gradas, g19, 4);
    builder->buildSector(vag20, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 20 * f_step, ceil_height_gradas, light_gradas, g20, 4);
    builder->buildSector(vag21, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 21 * f_step, ceil_height_gradas, light_gradas, g21, 4);
    builder->buildSector(vag22, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 22 * f_step, ceil_height_gradas, light_gradas, g22, 4);
    builder->buildSector(vag23, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 23 * f_step, ceil_height_gradas, light_gradas, g23, 4);
    builder->buildSector(vag24, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 24 * f_step, ceil_height_gradas, light_gradas, g24, 4);
    builder->buildSector(vag25, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 25 * f_step, ceil_height_gradas, light_gradas, g25, 4);
    builder->buildSector(vag26, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 26 * f_step, ceil_height_gradas, light_gradas, g26, 4);
    builder->buildSector(vag27, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 27 * f_step, ceil_height_gradas, light_gradas, g27, 4);
    builder->buildSector(vag28, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 28 * f_step, ceil_height_gradas, light_gradas, g28, 4);
    builder->buildSector(vag29, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 29 * f_step, ceil_height_gradas, light_gradas, g29, 4);
    builder->buildSector(vag30, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 30 * f_step, ceil_height_gradas, light_gradas, g30, 4);
    builder->buildSector(vag31, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 31 * f_step, ceil_height_gradas, light_gradas, g31, 4);
    builder->buildSector(vag32, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 32 * f_step, ceil_height_gradas, light_gradas, g32, 4);
    builder->buildSector(vag33, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 33 * f_step, ceil_height_gradas, light_gradas, g33, 4);
    builder->buildSector(vag34, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 34 * f_step, ceil_height_gradas, light_gradas, g34, 4);
    builder->buildSector(vag35, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 35 * f_step, ceil_height_gradas, light_gradas, g35, 4);
    builder->buildSector(vag36, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 36 * f_step, ceil_height_gradas, light_gradas, g36, 4);
    builder->buildSector(vag37, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 37 * f_step, ceil_height_gradas, light_gradas, g37, 4);
    builder->buildSector(vag38, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 38 * f_step, ceil_height_gradas, light_gradas, g38, 4);
    builder->buildSector(vag39, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 39 * f_step, ceil_height_gradas, light_gradas, g39, 4);
    builder->buildSector(vag40, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 40 * f_step, ceil_height_gradas, light_gradas, g40, 4);
    builder->buildSector(vag41, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 41 * f_step, ceil_height_gradas, light_gradas, g41, 4);
    builder->buildSector(vag42, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 42 * f_step, ceil_height_gradas, light_gradas, g42, 4);
    builder->buildSector(vag43, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 43 * f_step, ceil_height_gradas, light_gradas, g43, 4);
    builder->buildSector(vag44, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 44 * f_step, ceil_height_gradas, light_gradas, g44, 4);
    builder->buildSector(vag45, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 45 * f_step, ceil_height_gradas, light_gradas, g45, 4);
    builder->buildSector(vag46, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 46 * f_step, ceil_height_gradas, light_gradas, g46, 4);
    builder->buildSector(vag47, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 47 * f_step, ceil_height_gradas, light_gradas, g47, 4);
    builder->buildSector(vag48, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 48 * f_step, ceil_height_gradas, light_gradas, g48, 4);
    builder->buildSector(vag49, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 49 * f_step, ceil_height_gradas, light_gradas, g49, 4);
    builder->buildSector(vag50, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 50 * f_step, ceil_height_gradas, light_gradas, g50, 4);
    builder->buildSector(vag51, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 51 * f_step, ceil_height_gradas, light_gradas, g51, 4);
    builder->buildSector(vag52, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 52 * f_step, ceil_height_gradas, light_gradas, g52, 4);
    builder->buildSector(vag53, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 53 * f_step, ceil_height_gradas, light_gradas, g53, 4);
    builder->buildSector(vag54, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 54 * f_step, ceil_height_gradas, light_gradas, g54, 4);
    builder->buildSector(vag55, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 55 * f_step, ceil_height_gradas, light_gradas, g55, 4);
    builder->buildSector(vag56, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 56 * f_step, ceil_height_gradas, light_gradas, g56, 4);
    builder->buildSector(vag57, NULLL, NULLL, NULLL, textura_gradas, NULLL,
        floor_text_gradas, ceil_text_gradas, 57 * f_step, ceil_height_gradas, light_gradas, g57, 4);


    //-----------------------------------------------------------------------------------------------------

    // Añadimos al mapa
    doom->map->addSectorToRenderTree(&sector1);
    doom->map->addSectorToRenderTree(&river_sector);
    doom->map->addSectorToRenderTree(&sector2);
    doom->map->addSectorToRenderTree(&sector3);
    doom->map->addSectorToRenderTree(&sector4);
    doom->map->addSectorToRenderTree(&sector5);
    doom->map->addSectorToRenderTree(&sector6);
    doom->map->addSectorToRenderTree(&sector7);
    doom->map->addSectorToRenderTree(&sector6_2);
    doom->map->addSectorToRenderTree(&sector7_2);
    doom->map->addSectorToRenderTree(&sector8);
    doom->map->addSectorToRenderTree(&sector8_2);
    doom->map->addSectorToRenderTree(&sector9);
    doom->map->addSectorToRenderTree(&sector10);
    doom->map->addSectorToRenderTree(&sector11);
    doom->map->addSectorToRenderTree(&sector12);
    doom->map->addSectorToRenderTree(&sector9_2);
    doom->map->addSectorToRenderTree(&sector10_2);
    doom->map->addSectorToRenderTree(&sector11_2);
    doom->map->addSectorToRenderTree(&sector12_2);
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
    doom->map->addSectorToRenderTree(&sector22_2);
    doom->map->addSectorToRenderTree(&sector23);
    doom->map->addSectorToRenderTree(&sector23_2);
    doom->map->addSectorToRenderTree(&sector24);
    doom->map->addSectorToRenderTree(&sector25);
    doom->map->addSectorToRenderTree(&sector26);
    doom->map->addSectorToRenderTree(&sector27);
    doom->map->addSectorToRenderTree(&sector24_2);
    doom->map->addSectorToRenderTree(&sector25_2);
    doom->map->addSectorToRenderTree(&sector26_2);
    doom->map->addSectorToRenderTree(&sector27_2);
    doom->map->addSectorToRenderTree(&sector40);
    doom->map->addSectorToRenderTree(&sector41);
    doom->map->addSectorToRenderTree(&sector42);
    doom->map->addSectorToRenderTree(&sector43);
    doom->map->addSectorToRenderTree(&sector44);
    doom->map->addSectorToRenderTree(&sector45);
    doom->map->addSectorToRenderTree(&sector46);
    doom->map->addSectorToRenderTree(&sector47);
    doom->map->addSectorToRenderTree(&sector48);
    doom->map->addSectorToRenderTree(&sector49);
    doom->map->addSectorToRenderTree(&sector50);
    doom->map->addSectorToRenderTree(&sector51);
    doom->map->addSectorToRenderTree(&sector52);
    doom->map->addSectorToRenderTree(&sector53);
    doom->map->addSectorToRenderTree(&sector54);
    doom->map->addSectorToRenderTree(&sector55);
    doom->map->addSectorToRenderTree(&sector56);
    doom->map->addSectorToRenderTree(&sector70);
    doom->map->addSectorToRenderTree(&sector71);
    doom->map->addSectorToRenderTree(&sector72);
    doom->map->addSectorToRenderTree(&sector73);
    doom->map->addSectorToRenderTree(&sector74);
    doom->map->addSectorToRenderTree(&s75);
    doom->map->addSectorToRenderTree(&s76);
    doom->map->addSectorToRenderTree(&s78);
    doom->map->addSectorToRenderTree(&s79);
    doom->map->addSectorToRenderTree(&s80);
    doom->map->addSectorToRenderTree(&c1);
    doom->map->addSectorToRenderTree(&s81);
    doom->map->addSectorToRenderTree(&s82);
    doom->map->addSectorToRenderTree(&s83);
    doom->map->addSectorToRenderTree(&s84);
    doom->map->addSectorToRenderTree(&s85);
    doom->map->addSectorToRenderTree(&s86);
    doom->map->addSectorToRenderTree(&s87);
    doom->map->addSectorToRenderTree(&s88);
    doom->map->addSectorToRenderTree(&s100);
    //doom->map->addSectorToRenderTree(&s89);
    // gradas
    doom->map->addSectorToRenderTree(&g1);
    doom->map->addSectorToRenderTree(&g2);
    doom->map->addSectorToRenderTree(&g3);
    doom->map->addSectorToRenderTree(&g4);
    doom->map->addSectorToRenderTree(&g5);
    doom->map->addSectorToRenderTree(&g6);
    doom->map->addSectorToRenderTree(&g7);
    doom->map->addSectorToRenderTree(&g8);
    doom->map->addSectorToRenderTree(&g9);
    doom->map->addSectorToRenderTree(&g10);
    doom->map->addSectorToRenderTree(&g11);
    doom->map->addSectorToRenderTree(&g12);
    doom->map->addSectorToRenderTree(&g13);
    doom->map->addSectorToRenderTree(&g14);
    doom->map->addSectorToRenderTree(&g15);
    doom->map->addSectorToRenderTree(&g16);
    doom->map->addSectorToRenderTree(&g17);
    doom->map->addSectorToRenderTree(&g18);
    doom->map->addSectorToRenderTree(&g19);
    doom->map->addSectorToRenderTree(&g20);
    doom->map->addSectorToRenderTree(&g21);
    doom->map->addSectorToRenderTree(&g22);
    doom->map->addSectorToRenderTree(&g23);
    doom->map->addSectorToRenderTree(&g24);
    doom->map->addSectorToRenderTree(&g25);
    doom->map->addSectorToRenderTree(&g26);
    doom->map->addSectorToRenderTree(&g27);
    doom->map->addSectorToRenderTree(&g28);
    doom->map->addSectorToRenderTree(&g29);
    doom->map->addSectorToRenderTree(&g30);
    doom->map->addSectorToRenderTree(&g31);
    doom->map->addSectorToRenderTree(&g32);
    doom->map->addSectorToRenderTree(&g33);
    doom->map->addSectorToRenderTree(&g34);
    doom->map->addSectorToRenderTree(&g35);
    doom->map->addSectorToRenderTree(&g36);
    doom->map->addSectorToRenderTree(&g37);
    doom->map->addSectorToRenderTree(&g38);
    doom->map->addSectorToRenderTree(&g39);
    doom->map->addSectorToRenderTree(&g40);
    doom->map->addSectorToRenderTree(&g41);
    doom->map->addSectorToRenderTree(&g42);
    doom->map->addSectorToRenderTree(&g43);
    doom->map->addSectorToRenderTree(&g44);
    doom->map->addSectorToRenderTree(&g45);
    doom->map->addSectorToRenderTree(&g46);
    doom->map->addSectorToRenderTree(&g47);
    doom->map->addSectorToRenderTree(&g48);
    doom->map->addSectorToRenderTree(&g49);
    doom->map->addSectorToRenderTree(&g50);
    doom->map->addSectorToRenderTree(&g51);
    doom->map->addSectorToRenderTree(&g52);
    doom->map->addSectorToRenderTree(&g53);
    doom->map->addSectorToRenderTree(&g54);
    doom->map->addSectorToRenderTree(&g55);
    doom->map->addSectorToRenderTree(&g56);
    doom->map->addSectorToRenderTree(&g57);

    // ROCKS
    doom->map->addSectorToRenderTree(&r1);
    doom->map->addSectorToRenderTree(&r2);
    doom->map->addSectorToRenderTree(&r3);
    doom->map->addSectorToRenderTree(&r4);
    doom->map->addSectorToRenderTree(&r5);
    doom->map->addSectorToRenderTree(&r6);
    doom->map->addSectorToRenderTree(&r7);
    doom->map->addSectorToRenderTree(&r8);
    doom->map->addSectorToRenderTree(&r9);
    doom->map->addSectorToRenderTree(&r10);
    doom->map->addSectorToRenderTree(&r11);
    doom->map->addSectorToRenderTree(&r12);
    //doom->map->addSectorToRenderTree(&r13);
    doom->map->addSectorToRenderTree(&r14);
    doom->map->addSectorToRenderTree(&r15);
    doom->map->addSectorToRenderTree(&r16);
    doom->map->addSectorToRenderTree(&r17);
    doom->map->addSectorToRenderTree(&r18);
    doom->map->addSectorToRenderTree(&r19);
    doom->map->addSectorToRenderTree(&r20);
    doom->map->addSectorToRenderTree(&r21);
    doom->map->addSectorToRenderTree(&r22);
    doom->map->addSectorToRenderTree(&r23);
    doom->map->addSectorToRenderTree(&r24);
    doom->map->addSectorToRenderTree(&r25);
    doom->map->addSectorToRenderTree(&r26);
    doom->map->addSectorToRenderTree(&r27);
    doom->map->addSectorToRenderTree(&r28);
    doom->map->addSectorToRenderTree(&r29);
    doom->map->addSectorToRenderTree(&r30);
    doom->map->addSectorToRenderTree(&r31);
    doom->map->addSectorToRenderTree(&r32);
    doom->map->addSectorToRenderTree(&r33);
    doom->map->addSectorToRenderTree(&r34);
    // right upper rocks
    doom->map->addSectorToRenderTree(&r35);
    doom->map->addSectorToRenderTree(&r36);
    doom->map->addSectorToRenderTree(&r37);
    doom->map->addSectorToRenderTree(&r38);
    doom->map->addSectorToRenderTree(&r39);
    doom->map->addSectorToRenderTree(&r40);
    doom->map->addSectorToRenderTree(&r41);
    doom->map->addSectorToRenderTree(&r42);
    doom->map->addSectorToRenderTree(&r43);
    doom->map->addSectorToRenderTree(&r44);
    doom->map->addSectorToRenderTree(&r45);
    doom->map->addSectorToRenderTree(&r46);
    doom->map->addSectorToRenderTree(&r47);
    doom->map->addSectorToRenderTree(&r48);
    // left GIANT rocks
    doom->map->addSectorToRenderTree(&r49);
    doom->map->addSectorToRenderTree(&r50);
    doom->map->addSectorToRenderTree(&r51);
    doom->map->addSectorToRenderTree(&r52);
    doom->map->addSectorToRenderTree(&r53);
    doom->map->addSectorToRenderTree(&r54);
    doom->map->addSectorToRenderTree(&r55);
    doom->map->addSectorToRenderTree(&r56);
    doom->map->addSectorToRenderTree(&r57);
    doom->map->addSectorToRenderTree(&r58);
    doom->map->addSectorToRenderTree(&r59);
    doom->map->addSectorToRenderTree(&r60);
    doom->map->addSectorToRenderTree(&r61);
    doom->map->addSectorToRenderTree(&r62);
    doom->map->addSectorToRenderTree(&r63);
    doom->map->addSectorToRenderTree(&r64);
    // LIGHTS

    DirLight dirLight_;

    dirLight_.direction = glm::vec3(0.0, -1.0, -0.35);
    dirLight_.ambient = glm::vec3(0.2, 0.2, 0.2);
    dirLight_.diffuse = glm::vec3(0.009, 0.111, 0.2333);
    //dirLight_.specular = glm::vec3(0.3, 0.3, 0.3);
    dirLight_.specular = glm::vec3(0.7, 0.7, 0.7);

    doom->map->addDirectionalLight(dirLight_);

    PointLight l1, l2;
    l1.ambient = glm::vec3(0.1, 0.1, 0.1); l2.ambient = glm::vec3(0.1, 0.1, 0.1);
    l1.diffuse = glm::vec3(0.0, 0.0, 1.0); l2.diffuse = glm::vec3(0.0, 0.0, 1.0);
    l1.specular = glm::vec3(0.0, 0.0, 1.0); l2.specular = glm::vec3(0.0, 0.0, 1.0);
    l1.position = glm::vec3(-3840, 1605, 1024); l2.position = glm::vec3(-3840, 1605, 64);
    l1.constant = 1.1f; l2.constant = 1.5f;
    l1.linear = 0.00009f; l2.linear = 0.00009f;
    l1.quadratic = 0.000032f; l2.quadratic = 0.000032f;

    doom->map->addPointLight(l1,0);
    doom->map->addPointLight(l2, 1);

    PointLight l3, l4, l5, l6, l7, l8, l9, l10;
    l3.ambient = glm::vec3(0.1, 0.5, 0.1); l3.diffuse = glm::vec3(0.0, 0.88, 0.0);
    l3.specular = glm::vec3(0.0, 1.0, 0.0);
    l3.constant = 0.7f; l3.linear = 0.00009f; l3.quadratic = 0.00008f;
    l3.position = glm::vec3(-3776, -260, -416);
    doom->map->addPointLight(l3, 2);
    l3.position = glm::vec3(-3776, -260, -1632);
    doom->map->addPointLight(l3, 3);
    l3.position = glm::vec3(-3296, -260, -1216);
    doom->map->addPointLight(l3, 4);
    l3.position = glm::vec3(-3296, -260, -800);
    doom->map->addPointLight(l3, 5);
    l3.position = glm::vec3(-2912, -260, -672);
    doom->map->addPointLight(l3, 6);
    l3.position = glm::vec3(-3232, -260, -512);
    doom->map->addPointLight(l3, 7);
    l3.position = glm::vec3(-3904, -260, -992);
    doom->map->addPointLight(l3, 8);
    // luces estrella roja
    l4.ambient = glm::vec3(0.5, 0.1, 0.1); l4.diffuse = glm::vec3(0.8, 0.0, 0.0);
    l4.specular = glm::vec3(0.3, 0.3, 0.3);
    l4.constant = 0.9f; l4.linear = 0.00009f; l4.quadratic = 0.000032f;
    l4.position = glm::vec3(480, 1730, 544);
    doom->map->addPointLight(l4, 9);
    l4.position = glm::vec3(480, 1182, 544);
    //doom->map->addPointLight(l4, 10);
    // luces mini templos
    l5.ambient = glm::vec3(0.3, 0.3, 0.3); l5.diffuse = glm::vec3(0.8, 0.8, 0.8);
    l5.specular = glm::vec3(0.99, 0.99, 0.99);
    l5.constant = 0.9f; l5.linear = 0.00009f; l5.quadratic = 0.000032f;
    l5.position = glm::vec3(256, 2400, 2880);
    doom->map->addPointLight(l5, 10);
    l5.position = glm::vec3(256, 2400, 1664);
    doom->map->addPointLight(l5, 11);
    l5.position = glm::vec3(896, 2400, 2880);
    doom->map->addPointLight(l5, 12);
    l5.position = glm::vec3(896, 2400, 1664);
    doom->map->addPointLight(l5, 13);

    l5.position = glm::vec3(-3200, 2400, 2880);
    doom->map->addPointLight(l5, 14);
    l5.position = glm::vec3(-3200, 2400, 1664);
    doom->map->addPointLight(l5, 15);
    l5.position = glm::vec3(-3840, 2400, 2880);
    doom->map->addPointLight(l5, 16);
    l5.position = glm::vec3(-3840, 2400, 1664);
    doom->map->addPointLight(l5, 17);

    // luz gigante
    l6.ambient = glm::vec3(0.37, 0.37, 0.37); l6.diffuse = glm::vec3(0.95, 0.95, 0.95);
    l6.specular = glm::vec3(1, 1, 1);
    l6.constant = 0.6f; l6.linear = 0.00009f; l6.quadratic = 0.000004f;
    l6.position = glm::vec3(-2624, 3400, 2272);
    //doom->map->addPointLight(l6, 19);
    l7.ambient = glm::vec3(0.3, 0.3, 0.3); l7.diffuse = glm::vec3(0.90, 0.1, 0.1);
    l7.specular = glm::vec3(1, 0.1, 0.1);
    l7.constant = 0.6f; l7.linear = 0.00009f; l7.quadratic = 0.000008f;
    l7.position = glm::vec3(1664, -800, 1856);
    //doom->map->addPointLight(l7, 19);
    l7.position = glm::vec3(1664, -800, 2688);
    //doom->map->addPointLight(l7, 20);
    l7.position = glm::vec3(2496, -800, 1856);
    //doom->map->addPointLight(l7, 21);
    l7.position = glm::vec3(2496, -800, 2688);
    //doom->map->addPointLight(l7, 22);
    // luz sangre

    // MODELOS

    // Render Scene Background
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBOS, VAOS;
    glGenVertexArrays(1, &VAOS);
    glGenBuffers(1, &VBOS);
    glBindVertexArray(VAOS);
    glBindBuffer(GL_ARRAY_BUFFER, VBOS);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader scene_shader = ResourceManager::GetShader("sceneshader");
    ResourceManager::LoadTexture("textures/sky/sky6.jpg", true, "scene_texture", 0.3, false);
    Texture2D scene_texture = ResourceManager::GetTexture("scene_texture");
    scene_shader.Use();
    scene_shader.SetInteger("texture1", 0);

    glBindVertexArray(0);

    float last_time = 0;

    while (!glfwWindowShouldClose(window))
    {

        

        float current_time = glfwGetTime();
        dt = current_time - last_time;
        dt = 80 * dt;
        last_time = current_time;

        processInput(window);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
        glClearStencil(0);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
            static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.1f,
            static_cast<float>(39000));

        glm::mat4 view = camera.GetViewMatrix();

        

        doom->updateProjectionAndView(view, projection, camera.Position);

        //glm::mat4 projection33 = glm::perspective(glm::radians(camera.Zoom), (float)1500 / (float)900, 0.1f, 10.0f);
        //glm::mat4 view33 = camera.GetViewMatrix();
        //glm::mat4 model33 = glm::mat4(1.0f);
        //model33 = glm::translate(model33, glm::vec3(0.0f, 0.0f, 0.0f));
        //model33 = glm::scale(model33, glm::vec3(1.5f, 1.5f, 6.5f));
        //model_shader.SetMatrix4("projection", projection33);
        //model_shader.SetMatrix4("view", view33);
        //model_shader.SetMatrix4("model", model33);
        //arcoCalaveral.Draw(model_shader);

        

        // RENDER SCENE GIANT CUBE
        glm::mat4 modelYY = glm::mat4(1.0f);
        modelYY = glm::translate(modelYY, glm::vec3(0, 0, 5000));
        modelYY = glm::rotate(modelYY,glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        modelYY = glm::scale(modelYY, glm::vec3(35000.0f, 35000.0f, 35000.0f));
        scene_shader.Use();
        scene_shader.SetMatrix4("model", modelYY);
        scene_texture.Bind();
        glBindVertexArray(VAOS);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        /*
        * Render Models
        */

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
        dt = 4 * dt;
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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(SPACE, 2*dt);
    }
    
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
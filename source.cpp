//ongoing
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "bed.h"
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionalLight.h"
#include "SpotLight.h"
#include "walls.h"
#include "bench.h"
#include "stand.h"
#include "cube.h"
#include "stb_image.h"
#include "cylinder.h"
#include <iostream>
#include "sphere.h"
#include "drawcube.h"
#include <cmath>
#include <vector>
#include "circ_extra.h"
#include "sphereWithTexture.h"

struct Point {
    float x;
    float y;
    float z;
};
std::vector<float>cXALL;
std::vector<float>cZALL;
float cRALL = 6.5;

int kp1 = 0;
int kp3 = 0;
int kp4 = 0;
int kp5 = 0;
int flagDOLNA = 0;



std::vector<float>cX2;
std::vector<float>cZ2;
float cR2 = 6;
float dseatheta = 0.0;
int flagsd = -2;
int flagsd1 = -2;
float dseatheta100 = 0.0;
//float dyy = 0.0;
//float dxxx = 0.0;
float dxx_rseat = 0.0;
float dyy_rseat = 0.0;

bool GATE_OPEN = false;
float GATE_OPEN_ANGLE = 0.0f;

bool PLAY_OPEN = false;
float PLAY_OPEN_ANGLE = 0.0f;

bool HAUNT_OPEN = false;
float HAUNT_OPEN_ANGLE = 0.0f;

float CIRCULAR_HEAD_ANGLE = 0.0f;
bool IS_CIRCULAR_HEAD_ON = false;
float CIRCULAR_HEAD_SPEED = 0.5f;


float rtheta = 0.0;
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//Function Callbacks
void hauntedHead(unsigned int& bezierTree, unsigned int& bezierHead, unsigned int& cubeVAO, Shader& lightingShader, Sphere& sphere, float tx1, float ty1, float tz1, float sx1, float sy1, float sz1);
void drawPlayhouse(Shader& lightingShader, unsigned int bezierCylinderVAO, unsigned int bezierConeVAO, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& indicesCone, float rotateAngle_X,
    float rotateAngle_Y, float rotateAngle_Z, float ctz, float dyy_rseat);
void drawSeat(unsigned int cubeVAO, Shader& lightingShader, glm::mat4 altogether, float seatAngle, float dthetaY, float dxx_rseat, float dyy_rseat);
void tree(unsigned int& bezierTree, unsigned int& bezierHead, unsigned int& bezierCylinder, unsigned int& cubeVAO, Shader &lightingShader, Sphere& sphere, float tx1, float ty1, float tz1, float sx1, float sy1, float sz1);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void generateFractalTree(float x, float y, float angle, int depth, float length, std::vector<float>& vertices);

void rocketDriver(unsigned int& bezierCylinderVAO, unsigned int& bezierCyCurve, unsigned int& bezierHead, unsigned int& cubeVAO, Shader& lightingShader, vector<float>&
    , vector<float>& cz1, float txr, float tyr, float tzr, float ctz);
void tree(unsigned int& bezierTree, unsigned int& bezierHead, unsigned int& bezierCylinder, unsigned int& cubeVAO, Shader& lightingShader, Sphere& sphere, float tx1, float ty1, float tz1, float sx1, float sy1, float sz1);
long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
void rocket_seats(unsigned int& bezierCylinderVAO, unsigned int& bezierCyCurve, unsigned int& bezierHead, unsigned int& cubeVAO, Shader& lightingShader, Shader& lightingShaderWithTexture, Cube& cube2,
    vector<float>& cx1, vector<float>& cz1,
    float txr, float tyr, float tzr, float ctz, glm::mat4 altogether
);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);
void shop(unsigned int& cubeVAO, Cube& coffee, Cube& c1, Cube& c2, Cube& c3, Shader& lightingShader, Shader& lightingShaderWithTexture, float txC, float tyC, float tzC);
void drawFractalTree(
    Shader& shader,          // your shader
    glm::mat4 model,         // current model transform
    int depth,               // current recursion depth
    int maxDepth,            // how deep we want the recursion
    float branchLength       // length of this branch
);
glm::mat4 transform(float tr_x, float tr_y, float tr_z, float rot_x, float rot_y, float rot_z, float scal_x, float scal_y, float scal_z) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(tr_x, tr_y, tr_z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rot_x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rot_z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scal_x, scal_y, scal_z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    return model;
}
// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float dx = 0.000;
int  flag = 4;
int nightflag = 1;
int flagSD = 4;
float dy = 0.0000;
float dxx = 0.0000;
float dtheta = 0.0;
float dthetaY = 0.0;
float dtheta12 = 0.0;
int flagR = 0;
float dyL = 0.0;
//int flagTest = 1;
int flagRocket = 0;
float dthetaX = 0.0;
int rocketI = 0;


float treeX = 10.0f;
float treeY = 0.0f;
float treeZ = -5.0f;

//float txr = 0.0;
//float tyr = 0.0;
//float tzr = 0.0;


//control points
vector<float> cntrlPoints
{
    -0.1200, 1.9950, 5.1000,
    -0.3150, 1.8950, 5.1000,
    -0.4600, 1.7800, 5.1000,
    -0.6000, 1.6600, 5.1000,
    -0.7050, 1.5650, 5.1000,
    -0.8500, 1.4550, 5.1000,
    -0.9550, 1.3800, 5.1000,
    -1.0550, 1.2850, 5.1000,
};
vector<float> cntrlForDolna
{
    -0.6700, 1.7400, 5.1000,
    -0.6650, 1.5000, 5.1000,
    -0.5750, 1.2950, 5.1000,
    -0.4150, 1.1700, 5.1000,
    -0.2350, 1.0550, 5.1000,
};
vector<float> cntrlPointsCylinder
{
-0.4500, 1.7950, 5.1000,
-0.4550, 1.4950, 5.1000,
-0.4550, 1.0000, 5.1000,
};
vector<float> cntrlPointsForNagordola
{
    -0.5900, 1.7200, 5.1000,
    -0.5100, 1.3700, 5.1000,
    -0.4050, 1.2150, 5.1000,
    -0.2850, 1.1150, 5.1000,
    -0.2300, 1.0450, 5.1000,
    -0.3050, 0.9650, 5.1000,
    -0.3850, 0.9250, 5.1000,
};
vector<float> cntrlPointstree
{


-0.2500, 1.8350, 5.1000,
-0.4700, 1.6950, 5.1000,
-0.7050, 1.4400, 5.1000,
-0.6600, 1.2550, 5.1000,
-0.4150, 1.2000, 5.1000,


};
vector<float> cntrlCyCurve
{
-0.3100, 1.5250, 5.1000,
-0.4400, 1.2950, 5.1000,
-0.5450, 1.1200, 5.1000,
-0.6350, 0.9500, 5.1000,
};

vector<float> cntrlmatha
{

    -0.0200, 1.9100, 5.1000,
    -0.1850, 1.7550, 5.1000,
    -0.3300, 1.5600, 5.1000,

};
float tentTopPoints[] = {
   0.0300, 0.9850, 5.1000,
   -0.1050, 0.9350, 5.1000,
   -0.1750, 0.8750, 5.1000,
   -0.3050, 0.7750, 5.1000,
   -0.3950, 0.7100, 5.1000,
   -0.5000, 0.6250, 5.1000,
   -0.6100, 0.5450, 5.1000,
   -0.7750, 0.4100, 5.1000,
   -0.8900, 0.3550, 5.1000,
   -0.9950, 0.2800, 5.1000,
   -1.1050, 0.2000, 5.1000,
   -1.2100, 0.1500, 5.1000,
   -1.3250, 0.0650, 5.1000,
   -1.4400, 0.0150, 5.1000,
};



int tiii = 3599;
int tii = 2699;
int ti = 1799;
int t = 899;
float irt = 0.0;
float irtz = 0.0;

vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;
class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];
int mouseButtonFlag = 0;
FILE* fp;
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = false;
bool showHollowBezier = false;
bool lineMode = false;
unsigned int bezierVAO;
unsigned int bezierCylinderVAO;
unsigned int bezierForNagordola;
unsigned int bezierTree;
unsigned int bezierCyCurve;
unsigned int bezierHead;
unsigned int bezierDolna;

// camera
//Camera camera(glm::vec3(-10.5f + 25, 16.15f, -6.6 + 0.25f + 60.0f));
Camera camera(glm::vec3(28.0, 10.15f, 0.25f + 120.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);


// positions of the point lights

glm::vec3 pointLightPositions[] = {
    glm::vec3(70.0f,  24.15f,  -6.6 + 0.25f + 55.0f),// front right
    glm::vec3(-20.5f,  24.15f,   -32.5f), // back left
    glm::vec3(82.0f, 24.15f, -32.5f), //back right
    glm::vec3(-10.5f,  24.15f,   -6.6 + 0.25f + 55.0f), //front left
    
};

PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.014f,  //k_l
    0.0007, //k_q
    1       // light number
);

PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.014f,  //k_l
    0.0007, //k_q
    2       // light number
);

PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.014f,  //k_l
    0.0007, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.014f,  //k_l
    0.0007, //k_q
    4       // light number
);



DirLight dirLight(
        -0.2f, -1.0f, -0.3f,
        0.05f, 0.05f, 0.05f,
        .5f, 0.5f, 0.5f,     // diffuse
        0.5f, 0.5f, 0.5f
);


SpotLight spotLight(
    -3.50f, 4.0f, -2.0f,
    0.6f, -1.0f, 0.5f,
    0.5f, 0.0f, 0.5f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,
    0.09f,
    0.032f,
    12.5f,
    15.0f
);



// light settings
bool PointToggle1 = true;
bool PointToggle2 = true;
bool PointToggle3 = true;
bool PointToggle4 = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 1.5f;    // time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
    cout << "SkyDrop: N" << endl;
    cout << "RockerDriver: Z & 1" << endl;
    cout << "Haunted House: U & T" << endl;
    cout << "Playhouse: J & K" << endl;
    cout << "Entry: F & G" << endl;
   
    // glfw: initialize and configure
    // ------------------------------
    int ti = 0;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, //back side of cube, surface normal on -z 
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO; 
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO); 

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);



    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //cylinder sd points
    std::vector<Point> cylinder;
    //cylinder.push_back({ 0, 0, -8 });
    float radius1 = 2.0;
    float radius = 1.0;
    for (float theta = 0; theta <= 360; theta += 1) {
        float x = radius * glm::cos(glm::radians(theta));
        float y = radius * glm::sin(glm::radians(theta));

        float x1 = radius1 * glm::cos(glm::radians(theta));
        float y1 = radius1 * glm::sin(glm::radians(theta));

        cylinder.push_back({ x, y, 0.0f });
        cylinder.push_back({ x1, y1, -2.0f }); // normal cylinder
        //cylinder.push_back({ x * .5f, y * .5f, -8.0f }); // cylinder with different circle radius
    }

   

    unsigned int CVBO, CVAO;
    glGenVertexArrays(1, &CVAO);
    glGenBuffers(1, &CVBO);

    glBindVertexArray(CVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(struct Point) * cylinder.size(), cylinder.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Point), (void*)0);
    glEnableVertexAttribArray(0);
    //end of sd cylinder point

    //CYLINDER CIRCLE POINTS START
    std::vector<Point> cylindercircle;
    cylindercircle.push_back({ 0, 0, -8 });
    float radiusC = 6.0;
    //float radius = 1.0;
    for (float theta = 0; theta <= 360; theta += 1) {
        float x = radiusC * glm::cos(glm::radians(theta));
        float y = radiusC * glm::sin(glm::radians(theta));

        //float x1 = radius1 * glm::cos(glm::radians(theta));
        //float y1 = radius1 * glm::sin(glm::radians(theta));

        cylindercircle.push_back({ x, y, -8.0f });
        //cylinder.push_back({ x1, y1, -2.0f }); // normal cylinder
        //cylinder.push_back({ x * .5f, y * .5f, -8.0f }); // cylinder with different circle radius
    }

    unsigned int CcVBO, CcVAO;
    glGenVertexArrays(1, &CcVAO);
    glGenBuffers(1, &CcVBO);

    glBindVertexArray(CcVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CcVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Point) * cylindercircle.size(), cylindercircle.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Point), (void*)0);
    glEnableVertexAttribArray(0);
    //end of sd cylinderCIRCLE point







    // cylinder cone points start
    std::vector<Point> cylinderCone;
    cylinderCone.push_back({ 0, 0, -15 });
    float radiusM = 6.0;
    //float radius = 1.0;
    for (float theta = 0; theta <= 360; theta += 1) {
        float x = radiusM * glm::cos(glm::radians(theta));
        float y = radiusM * glm::sin(glm::radians(theta));

        //float x1 = radius1 * glm::cos(glm::radians(theta));
        //float y1 = radius1 * glm::sin(glm::radians(theta));

        cylinderCone.push_back({ x, y, -8.0f });
        //cylinder.push_back({ x1, y1, -2.0f }); // normal cylinder
        //cylinder.push_back({ x * .5f, y * .5f, -8.0f }); // cylinder with different circle radius
    }

    unsigned int CMVBO, CMVAO;
    glGenVertexArrays(1, &CMVAO);
    glGenBuffers(1, &CMVBO);

    glBindVertexArray(CMVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CMVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Point) * cylinderCone.size(), cylinderCone.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Point), (void*)0);
    glEnableVertexAttribArray(0);
    //end of sd cylinderCone point


    //cylinder for rider shade
    std::vector<Point> cylinderShade;
    //cylinder.push_back({ 0, 0, -8 });
    float radiusSh = 3.0;
    for (float theta = 0; theta <= 360; theta += 1) {
        float x = radiusSh * glm::cos(glm::radians(theta));
        float y = radiusSh * glm::sin(glm::radians(theta));

        cylinderShade.push_back({ x, y, 0.0f });
        cylinderShade.push_back({ x, y, -2.0f }); // normal cylinder
        //cylinder.push_back({ x * .5f, y * .5f, -8.0f }); // cylinder with different circle radius
    }

    unsigned int CSVBO, CSVAO;
    glGenVertexArrays(1, &CSVAO);
    glGenBuffers(1, &CSVBO);

    glBindVertexArray(CSVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CSVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Point) * cylinderShade.size(), cylinderShade.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Point), (void*)0);
    glEnableVertexAttribArray(0);


    bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierCylinderVAO = hollowBezier(cntrlPointsCylinder.data(), ((unsigned int)cntrlPointsCylinder.size() / 3) - 1);
    //cout << bezierCylinderVAO << endl;
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierForNagordola = hollowBezier(cntrlPointsForNagordola.data(), ((unsigned int)cntrlPointsForNagordola.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierTree = hollowBezier(cntrlPointstree.data(), ((unsigned int)cntrlPointstree.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierCyCurve = hollowBezier(cntrlCyCurve.data(), ((unsigned int)cntrlCyCurve.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierHead = hollowBezier(cntrlmatha.data(), ((unsigned int)cntrlmatha.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierDolna = hollowBezier(cntrlForDolna.data(), ((unsigned int)cntrlForDolna.size() / 3) - 1);



    //end of cylinderShade point

    //points for move an object in circle
    std::vector<float>cX;
    std::vector<float>cZ;
    float cR = 6;
    for (float itheta = 0;itheta <= 360;itheta = itheta + 0.1)
    {
        float x = cR * glm::cos(glm::radians(itheta));
        float z = cR * glm::sin(glm::radians(itheta));
        cX.push_back(x);
        cZ.push_back(z);
    }
    for (float itheta = 0;itheta <= 360;itheta = itheta + 0.1)
    {
        float x = cRALL * glm::cos(glm::radians(itheta));
        float z = cRALL * glm::sin(glm::radians(itheta));
        cXALL.push_back(x);
        cZALL.push_back(z);
    }
    std::cout << cX.size() << endl;
    std::cout << cZ.size() << endl;
    std::vector<float>cXt;
    std::vector<float>cZt;
    float cR1 = 6;
    for (float itheta = 1;itheta <= 360;itheta = itheta + 1.0)
    {
        float x = cR1 * glm::cos(glm::radians(itheta));
        float z = cR1 * glm::sin(glm::radians(itheta));
        cXt.push_back(x);
        cZt.push_back(z);
    }
    cout << "cXt = " << cXt.size() << endl;
    //cX2.push_back(0.0);
    //cZ2.push_back(0.0);
    /*for (float itheta = 0;itheta <= 360;itheta = itheta + 0.5)
    {
        float x = cR2 * glm::cos(glm::radians(itheta));
        float z = cR2 * glm::sin(glm::radians(itheta));
        cX2.push_back(x);
        cZ2.push_back(z);
    }
    cout << cX2.size() << endl;*/


    
    
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------

    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    //Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    string diffuseMapPath = "./grass.jpg";
    string specularMapPath = "./grass.jpg";
    string diffuseMapRoad = "./road.jpg";
    string specularMapRoad = "./road.jpg";
    string diffuseMapSky = "./skyy.jpg";
    string specularMapSky = "./skyy.jpg";
    string diffuseMapBrick = "./color8.jpg";
    string specularMapBrick = "./color8.jpg";
    string diffuseMapColor = "./color5.jpg";
    string specularMapColor = "./color5.jpg";
    string diffuseMapSofa = "./k1.jpg";
    string specularMapSofa = "./k1.jpg";
    string diffuseMapWater =  "./rasta.jpg";
    string specularMapWater = "./water.jpg";
    string diffuseMaphaunt = "./pumpkin.jpg";
    string specularMaphaunt = "./pumpkin.jpg";

    string diffuseMapNexthaunt = "./enterhall.jpg";
    string specularMapNexthaunt = "./enterhall.jpg";

    string diffuseMapWell = "./wel.png";
    string specularMapWell = "./wel.png";

    string diffuseMapWood = "./wood.jpg";
    string specularMapWood = "./wood.jpg";

    string diffuseMapGate = "./gate3.jpg";
    string specularMapGate = "./gate3.jpg";

    string diffuseMapWall = "./wall3.jpg";
    string specularMapWall = "./wall3.jpg";

    string diffuseMapHouse = "./houseWood2.jpg";
    string specularMapHouse = "./houseWood2.jpg";

    string diffuseMapHouseDoor = "./vut2.jpg";
    string specularMapHouseDoor = "./vut2.jpg";

    string diffuseMapTreeTex = "./treeTex.jpg";
    string specularMapTreeTex = "./treeTex.jpg";

    string diffuseMapGhost = "./spooky.jpg";
    string specularMapGhost = "./spooky.jpg";

    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap1 = loadTexture(diffuseMapRoad.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap1 = loadTexture(specularMapRoad.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap2 = loadTexture(diffuseMapSky.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapSky.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap3 = loadTexture(diffuseMapBrick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapBrick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap4 = loadTexture(diffuseMapSofa.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapSofa.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap5 = loadTexture(diffuseMapColor.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapColor.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap6 = loadTexture(diffuseMapWater.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap6 = loadTexture(specularMapWater.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap7 = loadTexture(diffuseMaphaunt.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap7 = loadTexture(specularMaphaunt.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap8 = loadTexture(diffuseMaphaunt.c_str(), GL_REPEAT , GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap8 = loadTexture(specularMaphaunt.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap9 = loadTexture(diffuseMapNexthaunt.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap9 = loadTexture(specularMapNexthaunt.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap10 = loadTexture(diffuseMapWell.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap10 = loadTexture(specularMapWell.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    unsigned int diffMap11 = loadTexture(diffuseMapWood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap11 = loadTexture(specularMapWood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap12 = loadTexture(diffuseMapGate.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap12 = loadTexture(specularMapGate.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap13 = loadTexture(diffuseMapWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap13 = loadTexture(specularMapWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap14 = loadTexture(diffuseMapHouse.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap14 = loadTexture(specularMapHouse.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    unsigned int diffMap15 = loadTexture(diffuseMapHouseDoor.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap15 = loadTexture(specularMapHouseDoor.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    unsigned int diffMap16 = loadTexture(diffuseMapTreeTex.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap16 = loadTexture(specularMapTreeTex.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    unsigned int diffMap17 = loadTexture(diffuseMapGhost.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap17 = loadTexture(specularMapGhost.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube road = Cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 2.0f, 2.0f);
    Cube water = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 100.0f, 100.0f);
    Cube brick = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube sky = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube sofa = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube color = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube box = Cube(diffMap7, specMap7, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube boxT = Cube(diffMap8, specMap8, 32.0f, 0.0f, 0.0f, 3.0f, 1.0f);
    Cube hallenter = Cube(diffMap9, specMap9, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube well = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    Cube wood = Cube(diffMap11, specMap11, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube gate = Cube(diffMap12, specMap12, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wall = Cube(diffMap13, specMap13, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube house = Cube(diffMap14, specMap14, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube hhouseDoor = Cube(diffMap15, specMap15, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube treeTex = Cube(diffMap16, specMap16, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube gHead = Cube(diffMap17, specMap17, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
 
    //std::cout << diffMap << ' ' << specMap << std::endl;
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 20.0f, 20.0f);
    Cube cube1 = Cube();
    Sphere sphere = Sphere(0.8);
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.5294f, 0.8078f, 0.9804f, 0.08f);
        if (nightflag == 2)
        {
            glClearColor(0.0f,0.0f,0.0f, 0.08f);
            

        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        //pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight2.setUpPointLight(lightingShader);
        // point light 4
        pointlight3.setUpPointLight(lightingShader);
        pointlight4.setUpPointLight(lightingShader);
        dirLight.setUpDirLight(lightingShader);
        spotLight.setUpSpotLight(lightingShader);
        lightingShader.use();
       
        //<<<<<<<<<<<<<<<<<<<<<<<<<Lamp>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        //Front right
        glm::mat4 modelLight = glm::mat4(1.0f);
        modelLight = glm::translate(modelLight, glm::vec3(70.5f+0.5, 24.15f, -7.6 + 0.25f + 55.0f+0.5+0.5));
        modelLight = glm::scale(modelLight, glm::vec3(0.50f, -40.0f, 0.5f)); // Make it a smaller cube
        lightingShader.setMat4("model", modelLight);
        lightingShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
        drawCube(cubeVAO, lightingShader, modelLight, 1.0f, 0.0f, 0.0f);
        //house.drawCubeWithTexture(lightingShaderWithTexture, modelLight);

        //back left
        modelLight = glm::mat4(1.0f);
        modelLight = glm::translate(modelLight, glm::vec3(-10.0f+0.5-10, 25.15f, -33.5f+0.5+0.5));
        modelLight = glm::scale(modelLight, glm::vec3(0.50f, -40.0f, 0.5f)); // Make it a smaller cube
        lightingShader.setMat4("model", modelLight);
        lightingShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
        drawCube(cubeVAO, lightingShader, modelLight, 0.0f, 0.0f, 1.0f);
        //house.drawCubeWithTexture(lightingShaderWithTexture, modelLight);


        //back right
        modelLight = glm::mat4(1.0f);
        modelLight = glm::translate(modelLight, glm::vec3(72.5f+10.5, 25.15f, -33.5f+0.5+0.5));
        modelLight = glm::scale(modelLight, glm::vec3(0.50f, -40.0f, 0.5f)); // Make it a smaller cube
        lightingShader.setMat4("model", modelLight);
        lightingShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
        drawCube(cubeVAO, lightingShader, modelLight, 1.0f, 0.0f, 1.0f);
        //house.drawCubeWithTexture(lightingShaderWithTexture, modelLight);


        //front left
        modelLight = glm::mat4(1.0f);
        modelLight = glm::translate(modelLight, glm::vec3(-10.0f+0.5, 24.15f, -7.6 + 0.25f + 55.0f+0.5+0.5));
        modelLight = glm::scale(modelLight, glm::vec3(0.50f, -40.0f, 0.5f)); // Make it a smaller cube
        lightingShader.setMat4("model", modelLight);
        lightingShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
        drawCube(cubeVAO, lightingShader, modelLight, 0.0f, 1.0f, 0.0f);
        //house.drawCubeWithTexture(lightingShaderWithTexture, modelLight);
        




        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 1000.0f);
        lightingShader.setMat4("projection", projection);


        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

       
        tree(bezierTree, bezierHead, bezierCylinderVAO, cubeVAO, lightingShader, sphere, -47 + 94, 0, 35, 0, 0, 0);
        int treeI = 0;
        int treeII;
        for (int i = 0; i < 6; i++)
        {
            tree(bezierTree, bezierHead, bezierCylinderVAO, cubeVAO, lightingShader, sphere, -48, 0, 35 + treeI, 0, 0, 0);
            treeI = treeI - 10;

        }
        treeII = treeI;
        treeI = 0;
        for (int i = 0;i < 9;i++)
        {
            tree(bezierTree, bezierHead, bezierCylinderVAO, cubeVAO, lightingShader, sphere, -48+treeI, 0, 45 + treeII, 0, 0, 0);
            treeI = treeI + 10;

        }

        treeI = 0;
        for (int i = 0;i < 6;i++)
        {
            tree(bezierTree, bezierHead, bezierCylinderVAO, cubeVAO, lightingShader, sphere, -47 + 94, 0, 35 + treeI, 0, 0, 0);
            treeI = treeI - 10;

        }
        rocketDriver(bezierCylinderVAO, bezierCyCurve, bezierHead, cubeVAO, lightingShader, cX, cZ, -15.0, 10, 20.0, -8.0);
        //dolna(bezierCylinderVAO, bezierDolna, bezierHead, cubeVAO, lightingShader, cX, cZ, 4.0, 0.0, -24.0 + 22);//JINAT2
        //lamp(cubeVAO, lightingShader, 35.0, -3.50, -20.0, 0.0, 0.0, 0.0);
       


        // camera/view transformation
        float degree = 0;
        glm::mat4 view = camera.GetViewMatrix();
        float r = glm::length(camera.Position - glm::vec3(view[3]));
        ourShader.setMat4("view", view);
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);


        //..................................PlayhouseSeat............................//
        glm :: mat4 rotateXMatrix_cone;
        glm::mat4 modelCone1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0+dx, -4.0 + 1.0 + 3+11, (6.0 * 3)-10-40+5));
        rotateXMatrix_cone = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(model, glm::vec3(1.0f, 1.0f,  1.0f));
        modelCone1 = translateMatrix * rotateXMatrix_cone * scaleMatrix;
        ourShader.setMat4("model", modelCone1);
        ourShader.setVec3("color", glm::vec3(1.0, 0.0, 0.0));
        ourShader.use();
        glBindVertexArray(CMVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, cylinderCone.size());

        
        glm::mat4 model1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0+dx, -2.5 + 3 + 11, (6.0 * 3)-10-40+3));
        //rotateXMatrix = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(model, glm::vec3(0.8f, 1.2f, 0.8f));
        model1 = translateMatrix * rotateXMatrix * scaleMatrix;
        ourShader.setMat4("model", model1);
        ourShader.setVec3("color", glm::vec3(0.176, 0.153, 0.969));
        ourShader.use();
        glBindVertexArray(CVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, cylinder.size());
  

        if (flag == 1)
        {
            dx = dx + 0.1;
            if (dx >=47)
            {
                flag = 2;
            }
        }
        if (flag == 2)
        {
            dx = dx - 0.1;
            if (dx <= -2)
            {
                flag = 4;
            }
            
        }




        //.............. we now draw as many light bulbs as we have point lights.................//
        glBindVertexArray(lightCubeVAO);
        ourShader.use();
        for (unsigned int i = 0; i < 4; i++)
        { 
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(2.0f,2.0f,0.9f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
            
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            
            
        }
       

        //.................................skyDrive stand................................//
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);
        lightingShaderWithTexture.use();
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        //pointlight3.setUpPointLight(lightingShaderWithTexture);
        pointlight4.setUpPointLight(lightingShaderWithTexture);

        //cube for skyDrive stand
        glm::mat4 modelMatrixForContainer1 = glm::mat4(1.0f);
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 6.00, -2.5, 8.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 18.0f, 0.25f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        

        

        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 6.00, -2.5, 8.0 - 30 - 1));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 18.0f, 0.25f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);

        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 12.50, -2.5, 8.0 - 30 - 1.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 18.0f, 0.25f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);

        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 12.50, -2.5, 8.0 - 30 - 9.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 18.0f, 0.25f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        /*lightingShader.setMat4("model", modelMatrixForContainer1);
        drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);*/

        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 9.85 + 4.5 + 40.00, -2.5, 8.0-30-10+4));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 18.0f, 0.25f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        /*lightingShader.setMat4("model", modelMatrixForContainer1);
        drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);*/




        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Playhouse <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        //drawPlayhouse( lightingShader,  bezierCylinderVAO,  bezierConeVAO,  indices,    indicesCone,   rotateAngle_X, rotateAngle_Y, rotateAngle_Z, ctz, dyy_rseat);

        //Stair Bottom-Right part
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 11.50, -2.5 + 12.2, 8.0 - 30 - 10));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-60.f), glm::vec3(0.0, 0.0, 1.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.0f, 1.50f, 0.70f));
        modelMatrixForContainer1 = translateMatrix * rotateZMatrix* scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);

        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);
        
        //Stair Bottom-Left part
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 11.50, -2.5 + 12.2, 8.0 - 30 - 1-0.7+0.005));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-60.f), glm::vec3(0.0, 0.0, 1.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.0f, 1.50f, 0.70f));
        modelMatrixForContainer1 = translateMatrix * rotateZMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);

        //Stair Upper-Left part
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 12.50, -2.5 + 18.2-0.25, 8.0 - 30 - 1 - 0.7+0.25));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-60.f), glm::vec3(0.0, 0.0, 1.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(22.0f, 0.250f, 0.25f));
        modelMatrixForContainer1 = translateMatrix * rotateZMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);

        //Stair Upper-Right part
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 12.50, -2.5 + 18.2 - 0.25, 8.0 - 30 - 1-9+0.5));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-60.f), glm::vec3(0.0, 0.0, 1.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(22.0f, 0.250f, 0.25f));
        modelMatrixForContainer1 = translateMatrix * rotateZMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);

        //Stair 1
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 12.60, -2.5 + 10.2, 8.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.50f, 0.30f, 9.0f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);
        
        //Stair 2
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 12.60+1.5-0.4, -2.5 + 8.2, 8.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.50f, 0.30f, 9.0f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);

        //Stair 3
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 12.60 + 1.5*2-0.75, -2.5 + 6.2, 8.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.50f, 0.30f, 9.0f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);

        //Stair 4
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 12.60 + 1.5 * 3-1, -2.5 + 4.2, 8.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.50f, 0.30f, 9.0f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //lightingShader.setMat4("model", modelMatrixForContainer1);
        ////lightingShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 0.0f, 1.0f);

        //Stair 5
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 12.60 + 1.5 * 4-1.25, -2.5 + 2.2, 8.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.50f, 0.30f, 9.0f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);


        //base of stand
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 6.00, -2.5 + 12.2, 8.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.0f, 1.50f, 9.0f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);

        //house border right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 6.00, -2.5 + 12.2 + 1.50, 8.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.0f, 8.0f, 0.5f));
        model =  translateMatrix * scaleMatrix;
        house.drawCubeWithTexture(lightingShaderWithTexture, model);
        ////house border back
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 6.00, -2.5 + 12.2 + 1.50, 8.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 8.0f, 9.0f));
        model = translateMatrix * scaleMatrix;
        house.drawCubeWithTexture(lightingShaderWithTexture, model);
        //house border left
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 6.00, -2.5 + 12.2 + 1.50, 8.0 - 30 - 10 + 9));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.0f, 8.0f, 0.5f));
        model = translateMatrix * scaleMatrix;
        house.drawCubeWithTexture(lightingShaderWithTexture, model);
        //house border front left
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 6.00 + 7, -2.5 + 12.2 + 1.50, 8.0 - 30 - 10 + 9));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 8.0f, -4.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(PLAY_OPEN_ANGLE), glm::vec3(0.0, 1.0, 0.0));
        model =  translateMatrix * rotateXMatrix * scaleMatrix;
        house.drawCubeWithTexture(lightingShaderWithTexture, model);
        //house border front right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 6.00 + 7, -2.5 + 12.2 + 1.50, 8.0 - 30 - 10));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f - PLAY_OPEN_ANGLE), glm::vec3(0.0, 1.0, 0.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 8.0f, 4.5f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        house.drawCubeWithTexture(lightingShaderWithTexture, model);

        if (PLAY_OPEN) {
            if (PLAY_OPEN_ANGLE < 90.0) {
                PLAY_OPEN_ANGLE += 1.0;
            }
        }
        else
        {
            if (PLAY_OPEN_ANGLE > 0.0) {
                PLAY_OPEN_ANGLE -= 1.0;
            }
        }





        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Shop<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        //hauntedHead(bezierTree, bezierHead, cubeVAO, lightingShader, sphere, 0, 5, 0, 0, 0 ,0);

        //model = glm::rotate(identityMatrix, glm::radians(ROTATE_ANGLE_SKY), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(identityMatrix, glm::vec3(1.0f, 1.0, 1.0));
        //model = glm::translate(model, glm::vec3(11.0f, 0.35f, 6.0f));
        //sphereWithTexture.drawSphereWithTexture(lightingShaderWithTexture, model);

        Sphere sphere = Sphere();
        glm::mat4 modelHead = glm::mat4(1.0f);
        modelHead = glm::translate(modelHead, glm::vec3(30.5, 2.5, -19.0)) * glm::rotate(glm::mat4(1.0f), glm::radians(CIRCULAR_HEAD_ANGLE), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(identityMatrix, glm::vec3(8.0f,8.0f, 8.0f));
        SphereWithTexture* sphereWithTexture = new SphereWithTexture(0.25f, 144, 44, glm::vec3(0.898f, 0.459f, 0.125f), glm::vec3(0.898f, 0.459f, 0.125f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap17, specMap17, 0.0f, 0.0f, 1.0f, 1.0f);
        shop(cubeVAO, boxT,box, hallenter, house ,  lightingShader, lightingShaderWithTexture, 0.0, 0.0, 0.0);

        sphereWithTexture->drawSphereWithTexture(lightingShaderWithTexture, modelHead);
        if (IS_CIRCULAR_HEAD_ON) {
                CIRCULAR_HEAD_ANGLE += 1.0;
                CIRCULAR_HEAD_SPEED += 0.5;
        }
        else
        {
            if (CIRCULAR_HEAD_ANGLE > 0.0) {
                CIRCULAR_HEAD_ANGLE -= 1.0;
            }
        }

        //.....skyHI Rider stand..............//


        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 66 + 5 + 8, -2.5, 10.0 - 30 - 10));
        //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-12.5f, 2.0f, 9.5f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        drawCube(cubeVAO, lightingShader, modelMatrixForContainer1, 1.0f, 1.0f, 1.0f);

        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 63 + 5 + 8, -2.5 + 2, 10.0 - 30 - 10));
        //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-6.5f, 30.0f, 2.5f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        brick.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);


        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 64 + 5 + 8, -2.5 + 2 + dy, 12.0 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-8.5f, 04.0f, 0.60f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        color.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);

        //seat
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 64 + 5 + 8, -2.5 + 2 + 1 + dy, 12.8 - 30 - 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-8.5f, 0.50f, 1.60f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        color.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //handle
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 64 + 5 + 8 + 1.5, -2.5 + 2 + 1.5 + dy, 12.8 - 30 - 10 + 1.60));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-12.0f, 0.50f, 0.80f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);

        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 64 + 5 + 8 + 1.5, -2.5 + 2 + 1.5 + dy, 12.8 - 30 - 10 + 1.60 - 1.60 * 2));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-12.0f, 0.50f, 0.80f));
        modelMatrixForContainer1 = translateMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);

        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 64 + 5 + 8 + 1.5, -2.5 + 2 + 1.5 + dy, 12.8 - 30 - 10 + 1.60 - 1.60 * 2));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-4.0f, 0.50f, 0.80f));
        modelMatrixForContainer1 = translateMatrix * rotateYMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);

        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 64 + 5 + 8 + 1.5 - 12.75, -2.5 + 2 + 1.5 + dy, 12.8 - 30 - 10 + 1.60 - 1.60 * 2));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-4.0f, 0.50f, 0.80f));
        modelMatrixForContainer1 = translateMatrix * rotateYMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        sofa.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);
        //handle done
        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 64 + 5 + 8, -2.5 + 2 + dy, 12.0 - 30 - 10));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-2.5f, 02.0f, 0.60f));
        modelMatrixForContainer1 = translateMatrix * rotateYMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        color.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);

        modelMatrixForContainer1 = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5 + 60 + 8, -2.5 + 2 + dy, 12.0 - 30 - 10));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-2.5f, 02.0f, 0.60f));
        modelMatrixForContainer1 = translateMatrix * rotateYMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelMatrixForContainer1);
        color.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer1);

        if (flagSD == 1)
        {
            dy = dy + 0.05;
            if (dy >= 30)
            {
                flagSD = 2;
            }
        }
        if (flagSD == 2)
        {
            dy = dy - 0.1;
            if (dy <= 0)
            {
                flagSD = 4;
            }

        }



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);
        //2nd part of cube draw
        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight3.setUpPointLight(lightingShaderWithTexture);

        // surface
        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5, -2.5, -32.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(90, .5, 50));
        modelMatrixForContainer = translateMatrix * scaleMatrix;
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        // brick surface
        modelMatrixForContainer = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-400.5, -2.6, -47.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1100, .5, 700));
        modelMatrixForContainer = translateMatrix * scaleMatrix;
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        water.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        // We start at a certain position for the tree trunk:
        glm::mat4 modeltree(1.0f);
        modeltree = glm::translate(identityMatrix, glm::vec3(treeX, treeY, treeZ));
        // Possibly rotate the base if you want it angled
        // model = glm::rotate(model, glm::radians(...), glm::vec3(0,1,0));

        int maxDepth = 6;         // how many recursive levels
        float trunkLength = 2.0f; // base trunk length


        drawFractalTree(lightingShader, model, 0, maxDepth, trunkLength);

        // Generate the vertices for the fractal tree
        std::vector<float> vertices;
        // Starting at (0, -0.8) near the bottom of the screen
        // Angle = PI/2 (straight up), depth=10 for recursion, initial branch length=0.3
        generateFractalTree(0.0f, -0.8f, 3.14159f / 2.0f, 10, 0.3f, vertices);

        // Create VAO and VBO
        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Bind and fill data
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(float),
            vertices.data(),
            GL_STATIC_DRAW
        );

        // Position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind to be clean
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

      

        glm::mat4 modelRocket = transform(4, 12, -1.8f, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
        rocket_seats(bezierCylinderVAO, bezierCyCurve, bezierHead, cubeVAO, lightingShader, lightingShaderWithTexture, color, cX, cZ, -15.0, 10, 20.0, -8.0, modelRocket);




        //Gate Structure
        //gate-PILLER-l
        translateMatrix = glm::translate(identityMatrix, glm::vec3( 20, -2, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 18.0f, 0.5f));
        model =  translateMatrix * scaleMatrix;
        gate.drawCubeWithTexture(lightingShaderWithTexture, model);


        //gate-PILLER-t
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 16, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(16.0f, 0.5f, 0.5f));
        model =  translateMatrix * scaleMatrix;
        gate.drawCubeWithTexture(lightingShaderWithTexture, model);

        //gate-PILLER-r
        translateMatrix = glm::translate(identityMatrix, glm::vec3(35.5, -2, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 18.0f, 0.5f));
        model =  translateMatrix * scaleMatrix;
        gate.drawCubeWithTexture(lightingShaderWithTexture, model);

        //GATE-l
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20.5, -2, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.5f, 17.5f, 0.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(GATE_OPEN_ANGLE), glm::vec3(0.0, 1.0, 0.0));
        model =  translateMatrix * rotateXMatrix * scaleMatrix;
        gate.drawCubeWithTexture(lightingShaderWithTexture, model);

        //GATE-R
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.5f, 17.5f, 0.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(180.0f - GATE_OPEN_ANGLE), glm::vec3(0.0, 1.0, 0.0));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(35.5f, -2.0, 25.5f));
        model =  translateMatrix * rotateXMatrix * scaleMatrix;
        gate.drawCubeWithTexture(lightingShaderWithTexture, model);

        //gate-PILLER-lE
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0, -2, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-31.0f, 16.0f, 0.5f));
        model = translateMatrix * scaleMatrix;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model);
        //gate-PILLER-LEE
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.0, -2, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-20.0f, 16.0f, 0.5f));
        model = translateMatrix * scaleMatrix;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model);
        //gate-PILLER-RE
        translateMatrix = glm::translate(identityMatrix, glm::vec3(35.5, -2, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 16.0f, 0.5f));
        model = translateMatrix * scaleMatrix;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model);
        //gate-PILLER-REE
        translateMatrix = glm::translate(identityMatrix, glm::vec3(65.5, -2, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(25.0f, 16.0f, 0.5f));
        model = translateMatrix * scaleMatrix;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model);

        if (GATE_OPEN) {
            if (GATE_OPEN_ANGLE < 90.0) {
                GATE_OPEN_ANGLE += 1.0;
            }
        }
        else
        {
            if (GATE_OPEN_ANGLE > 0.0) {
                GATE_OPEN_ANGLE -= 1.0;
            }
        }

        //<<<<<<<<<<<<<<<<<<<<<<<<<<Boundary>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        //boundary-left
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-31.0, -2, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 16.0f, -70.5f));
        model = translateMatrix * scaleMatrix;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model);
        //boundary back 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-31.0, -2, 25 - 70.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.5f, 16.0f, 0.5f));
        model = translateMatrix * scaleMatrix;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model);
        //boundary back 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-31.0 + 60.5, -2, 25 - 70.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.5f, 16.0f, 0.5f));
        model = translateMatrix * scaleMatrix;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model);
        //boundary right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-31.0 + 60.5 + 60.5, -2, 25 - 70.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 16.0f, 70.5f));
        model = translateMatrix * scaleMatrix;
        wall.drawCubeWithTexture(lightingShaderWithTexture, model);


        //Curved Track
        //// Create CylinderWithTexture instance
        //CylinderWithTexture texturedCylinder(1.0f, 1.0f, 2.0f, 50, 1, glm::vec3(0.2f, 0.2f, 0.2f),
        //    glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
        //    32.0f, diffMap14, specMap14);

        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-31.0 + 60.5 + 60.5, -2, 25 - 70.5));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 5.0f, 0.0f));
        //model = texturedCylinder * translateMatrix * scaleMatrix;
        //texturedCylinder.drawCylinder(lightingShader, model, camera);

        // Apply transformations
        glm::mat4 modelRobo = glm::mat4(1.0f);
        model1 = glm::translate(modelRobo, glm::vec3(65.0f, 1.0, -1.5f));  // Translate (x, y, z)
        //model1 = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));  // Rotate 45 degrees around Y-axis
        //model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));  // Scale uniformly in all directions
        CylinderWithTexture* texturedCylinder = new CylinderWithTexture(
            1.5f, 1.5f, 2.0f,  // Base radius, top radius, height
            36, 1,             // Sector count, stack count
            glm::vec3(0.2f, 0.2f, 0.2f),  // Ambient
            glm::vec3(0.8f, 0.8f, 0.8f),  // Diffuse
            glm::vec3(1.0f, 1.0f, 1.0f),  // Specular
            32.0f,                        // Shininess
            diffMap14, specMap14      // Textures
        );
        texturedCylinder->drawCylinder(lightingShaderWithTexture, model1, camera.Position);

        CylinderWithTexture* texturedCylinder1 = new CylinderWithTexture(
            1.5f, 1.5f, 2.0f,  // Base radius, top radius, height
            36, 1,             // Sector count, stack count
            glm::vec3(0.2f, 0.2f, 0.2f),  // Ambient
            glm::vec3(0.8f, 0.8f, 0.8f),  // Diffuse
            glm::vec3(1.0f, 1.0f, 1.0f),  // Specular
            32.0f,                        // Shininess
            diffMap14, specMap14      // Textures
        );
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(modelRobo, glm::vec3(60.0f, 1.0, -1.5f));
        texturedCylinder1->drawCylinder(lightingShaderWithTexture, model2, camera.Position);

        CylinderWithTexture* texturedCylinder2 = new CylinderWithTexture(
            1.5f, 1.5f, 5.0f,  // Base radius, top radius, height
            36, 1,             // Sector count, stack count
            glm::vec3(0.2f, 0.2f, 0.2f),  // Ambient
            glm::vec3(0.8f, 0.8f, 0.8f),  // Diffuse
            glm::vec3(1.0f, 1.0f, 1.0f),  // Specular
            32.0f,                        // Shininess
            diffMap14, specMap14      // Textures
        );
        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(modelRobo, glm::vec3(62.5f, 1.0, -1.5f));
        texturedCylinder2->drawCylinder(lightingShaderWithTexture, model3, camera.Position);

       //humanoid


        if (flagR == 5)
        {
            dxx = dxx + 0.08;
            if (dxx >= 39)
            {
                flagR = 0;
                dxx = 0;
            }
            
        }



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
    {
        IS_CIRCULAR_HEAD_ON = true;
       // sphereRotationAngle -= 5.0f;  // Rotate counter-clockwise
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
    {
        IS_CIRCULAR_HEAD_ON = false; 
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        //GATE OPEN
        GATE_OPEN = true;
        //GATE_OPEN_ANGLE = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        //GATE CLOSE
        GATE_OPEN = false;
        //GATE_OPEN_ANGLE = 90.0;
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        // Play House OPEN
        PLAY_OPEN = true;
        //PLAY_OPEN_ANGLE = 0.0;

    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        //Play House CLOSE
        PLAY_OPEN = false;
        //PLAY_OPEN_ANGLE = 90.0;

    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        HAUNT_OPEN = true;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        HAUNT_OPEN = false;
    }

    //}
    //if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
    {
        pointlight1.turnOn();

    }

    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    {
        pointlight1.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
    {
        pointlight2.turnOn();
    }

    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
    {
        pointlight2.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
    {
        pointlight3.turnOn();
    }

    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
    {
        pointlight3.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
    {
        pointlight4.turnOn();
    }

    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
    {
        pointlight4.turnOff();

    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        nightflag = 1;
        pointlight1.turnOn();
        pointlight3.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        nightflag = 2;
        pointlight1.turnOff();
        pointlight3.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    /*if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        flagTest = 2;
        cout << flagTest << endl;
    }*/

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        flagR = 5;

    }



    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    /*if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }*/

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    /*if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }*/
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        flagRocket = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        flagRocket = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }


    ///new add
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {

        pointlight4.turnOn();
        cout << "on" << endl;
    }
    /*if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {

        pointlight4.turnOff();
        cout << "Off" << endl;
    }*/
    //newadddd
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        spotLight.turnDiffuseOn();
        dirLight.turnDiffuseOn();

    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {

        pointlight1.turnOff();
        pointlight3.turnOff();
        dirLight.turnOff();
        spotLight.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        flagSD = 1;

    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        dirLight.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        dirLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        spotLight.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        spotLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOn();
        pointlight3.turnAmbientOn();
        spotLight.turnAmbientOn();
        dirLight.turnAmbientOn();
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight2.turnSpecularOn();
        pointlight3.turnSpecularOn();
        pointlight4.turnSpecularOn();
        spotLight.turnSpecularOn();
        dirLight.turnSpecularOn();
    }






}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
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
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}


void tree(unsigned int& bezierTree, unsigned int& bezierHead, unsigned int& bezierCylinder, unsigned int& cubeVAO, Shader &lightingShader, Sphere& sphere,float tx1, float ty1, float tz1, float sx1, float sy1, float sz1)
{
    Cube cube = Cube();
    glm::mat4 identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(tx1 + 34.0f, ty1 + 1.0f, tz1 - 20.5f));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3 + sx1, 5 + sy1, 3 + sz1));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 25.0f);

    glBindVertexArray(bezierTree);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(tx1 + 34.0f, ty1 - 1.0f, tz1 - 20.5f));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(4 + sx1, 5 + sy1, 4 + sz1));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 25.0f);
    glBindVertexArray(bezierTree);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(tx1 + 34.0f, ty1 -3.0f, tz1 - 20.5f));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5 + sx1, 5 + sy1, 5 + sz1));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 25.0f);
    glBindVertexArray(bezierTree);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(tx1 + 34.0f, ty1 + 2.0f, tz1 - 20.5f));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3 + sx1, 5 + sy1, 3 + sz1));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 25.0f);
    glBindVertexArray(bezierHead);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(tx1 + 33.9f, ty1 - 14.0f, tz1 - 20.5f));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 1.0f, 1.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(1.0f, 1.0f, 1.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(1.0f, 1.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1, 10.0, 1));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.647f, 0.165f, 0.165f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.647f, 0.165f, 0.165f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 0.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 25.0f);
    glBindVertexArray(bezierCylinder);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

}


void shop(unsigned int& cubeVAO, Cube& box, Cube& box1, Cube& box2, Cube& box3, Shader& lightingShader, Shader& lightingShaderWithTexture, float txC, float tyC, float tzC)
{
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, modelWall;

    //back wall
    modelWall = glm::mat4(1.0f);
    modelWall = transform(28.0, -1.9, -25.0, 0.0, 0.0, 0.0, 20.0f, 15.00f, 1.0f);
    box1.drawCubeWithTexture(lightingShaderWithTexture, modelWall);

    //top wall
    modelWall = glm::mat4(1.0f);
    modelWall = transform(28.0, -1.9 + 15 - 0.5, -25.00, 0.0, 0.0, 0.0, 19.50f, 0.50f, 15.0f);
    lightingShader.setMat4("model", modelWall);
    drawCube(cubeVAO, lightingShader,modelWall, 1.0f, 1.0f, 1.0f);
    box1.drawCubeWithTexture(lightingShaderWithTexture, modelWall);

    //left wall
    modelWall = glm::mat4(1.0f);
    modelWall = transform(28.0, -1.9, -25.10, 0.0, -90.0, 0.0, 16.0f, 15.00f, 0.50f);
    /*lightingShader.setMat4("model", modelFence);
    drawCube(cubeVAO, lightingShader,modelFence, 0.0f, 1.0f, 1.0f);*/
    box1.drawCubeWithTexture(lightingShaderWithTexture, modelWall);

    //right wall
    modelWall = glm::mat4(1.0f);
    modelWall = transform(48.0, -1.9, -25.0, 0.0, -90.0, 0.0, 15.0f, 15.00f, 0.50f);
    box1.drawCubeWithTexture(lightingShaderWithTexture, modelWall);

    //front wall
    modelWall = glm::mat4(1.0f);
    modelWall = transform(28.0, -1.9, -25.0 + 15.0, 0.0, 0.0, 0.0, 15.0f, 15.00f, 0.50f);
    box2.drawCubeWithTexture(lightingShaderWithTexture, modelWall);

    //door
    modelWall = glm::mat4(1.0f);
    scaleMatrix = glm::scale(modelWall, glm::vec3(4.5f, 15.0f, 0.5f));
    rotateXMatrix = glm::rotate(modelWall, glm::radians(180.0f + HAUNT_OPEN_ANGLE), glm::vec3(0.0, 1.0, 0.0));
    translateMatrix = glm::translate(modelWall, glm::vec3(47.5, -1.9, -25.0+15));
    modelWall =  translateMatrix * rotateXMatrix * scaleMatrix;
    box3.drawCubeWithTexture(lightingShaderWithTexture, modelWall);

    //Table In
    modelWall = glm::mat4(1.0f);
    modelWall = transform(28.0, -1.9, -25.10, 0.0, -90.0, 0.0, 10.0f, 3.00f, -8.0f);
    /*lightingShader.setMat4("model", modelFence);
    drawCube(cubeVAO, lightingShader,modelFence, 0.0f, 1.0f, 1.0f);*/
    box3.drawCubeWithTexture(lightingShaderWithTexture, modelWall);





    if (HAUNT_OPEN) {
        if (HAUNT_OPEN_ANGLE < 90.0) {
            HAUNT_OPEN_ANGLE += 1.0;
        }
    }
    else
    {
        if (HAUNT_OPEN_ANGLE > 0.0) {
            HAUNT_OPEN_ANGLE -= 1.0;
        }
    }

    //resting table chair
    modelWall = glm::mat4(1.0f);
    modelWall = transform(68.0, -1.9+3, 9.0, 0.0, -90.0, 0.0, 8.50f, 0.50f, 4.0f);
    /*lightingShader.setMat4("model", modelFence);
    drawCube(cubeVAO, lightingShader,modelFence, 1.0f, 1.0f, 1.0f);*/
    box2.drawCubeWithTexture(lightingShaderWithTexture, modelWall);

    modelWall = glm::mat4(1.0f);
    modelWall = transform(65.0, -1.9, 9.0, 0.0, 00.0, 0.0, 2.50f, 3.00f, 0.50f);
    lightingShader.setMat4("model", modelWall);
    drawCube(cubeVAO, lightingShader, modelWall, 1.0f, 1.0f, 1.0f);
    //box2.drawCubeWithTexture(lightingShaderWithTexture, modelFence);

    modelWall = glm::mat4(1.0f);
    modelWall = transform(65.0, -1.9, 16.50, 0.0, 00.0, 0.0, 2.50f, 3.00f, 0.50f);
    lightingShader.setMat4("model", modelWall);
    drawCube(cubeVAO, lightingShader, modelWall, 1.0f, 1.0f, 1.0f);
    //box2.drawCubeWithTexture(lightingShaderWithTexture, modelFence);


    modelWall = glm::mat4(1.0f);
    modelWall = transform(64.0, -1.9 + 1.5, -12.0+1.00+20.00, 0.0, -90.0, 0.0, 4.50f, 0.50f, 2.0f);
    lightingShader.setMat4("model", modelWall);
    drawCube(cubeVAO, lightingShader, modelWall, 1.0f, 1.0f, 1.0f);
    //box2.drawCubeWithTexture(lightingShaderWithTexture, modelFence);

    modelWall = glm::mat4(1.0f);
    modelWall = transform(64.0, -1.9, -11.0+1.00+20.00, 0.0, -90.0, 0.0, 0.50f, 2.00f, 2.00f);
    lightingShader.setMat4("model", modelWall);
    drawCube(cubeVAO, lightingShader, modelWall, 1.0f, 1.0f, 1.0f);
    //box2.drawCubeWithTexture(lightingShaderWithTexture, modelFence);

    modelWall = glm::mat4(1.0f);
    modelWall = transform(64.0, -1.9, -9.0+1.00+20.00, 0.0, -90.0, 0.0, 0.50f, 2.00f, 2.00f);
    lightingShader.setMat4("model", modelWall);
    drawCube(cubeVAO, lightingShader, modelWall, 1.0f, 1.0f, 1.0f);
    //box2.drawCubeWithTexture(lightingShaderWithTexture, modelFence);

    modelWall = glm::mat4(1.0f);
    modelWall = transform(71.0, -1.9 + 1.5, -12.0 + 1.00 + 20.00, 0.0, -90.0, 0.0, 4.50f, 0.50f, 2.0f);
    lightingShader.setMat4("model", modelWall);
    drawCube(cubeVAO, lightingShader, modelWall, 1.0f, 1.0f, 1.0f);
    //box2.drawCubeWithTexture(lightingShaderWithTexture, modelFence);

    modelWall = glm::mat4(1.0f);
    modelWall = transform(71.0, -1.9, -11.0 + 1.00 + 20.00, 0.0, -90.0, 0.0, 0.50f, 2.00f, 2.00f);
    lightingShader.setMat4("model", modelWall);
    drawCube(cubeVAO, lightingShader, modelWall, 1.0f, 1.0f, 1.0f);
    //box2.drawCubeWithTexture(lightingShaderWithTexture, modelFence);

    modelWall = glm::mat4(1.0f);
    modelWall = transform(71.0, -1.9, -9.0 + 1.00 + 20.00, 0.0, -90.0, 0.0, 0.50f, 2.00f, 2.00f);
    lightingShader.setMat4("model", modelWall);
    drawCube(cubeVAO, lightingShader, modelWall, 1.0f, 1.0f, 1.0f);
    //box2.drawCubeWithTexture(lightingShaderWithTexture, modelFence);


}

void drawFractalTree(
    Shader& shader,          // your shader
    glm::mat4 model,         // current model transform
    int depth,               // current recursion depth
    int maxDepth,            // how deep we want the recursion
    float branchLength       // length of this branch
)
{
    if (depth >= maxDepth) {
        return;
    }

    // 1) Draw the trunk/branch at this level
    //    Here, we assume you have a VAO that draws a simple cylinder or cube from
    //    (0,0,0) to (0,1,0) in local coords. We'll scale it by `branchLength`.
    {
        glm::mat4 branchModel = model;

        // scale the geometry so it's "branchLength" tall
        branchModel = glm::scale(branchModel, glm::vec3(0.1f, branchLength, 0.1f));
        // (0.1, branchLength, 0.1) => a thin, tall cylinder or cube

        shader.use();
        shader.setMat4("model", branchModel);

        // set up wood or bark-like color
        shader.setVec3("material.ambient", glm::vec3(0.55f, 0.27f, 0.07f));
        shader.setVec3("material.diffuse", glm::vec3(0.55f, 0.27f, 0.07f));
        shader.setVec3("material.specular", glm::vec3(0.1f, 0.1f, 0.1f));
        shader.setFloat("material.shininess", 16.0f);

        unsigned int branchVAO;
        int branchIndexCount = 0;
        glGenVertexArrays(1, &branchVAO);
        glBindVertexArray(branchVAO);
       
        glBindVertexArray(0);

        // draw the branch geometry
        glBindVertexArray(branchVAO);       // your cylinder or cube VAO
        glDrawElements(GL_TRIANGLES, branchIndexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    // 2) Move upward to the top of this branch
    glm::mat4 topOfBranch = glm::translate(model, glm::vec3(0.0f, branchLength, 0.0f));

    // 3) Create two or more sub-branches
    //    For example, left branch and right branch
    float angle = 20.0f; // angle between branches
    // (You can randomize or tweak angle to get different looks)

    // left branch
    {
        glm::mat4 leftModel = topOfBranch;
        // rotate around Z or X or Y as you prefer:
        leftModel = glm::rotate(leftModel, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        // now call recursively with a shorter length
        drawFractalTree(shader, leftModel, depth + 1, maxDepth, branchLength * 0.7f);
    }

    // right branch
    {
        glm::mat4 rightModel = topOfBranch;
        rightModel = glm::rotate(rightModel, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
        drawFractalTree(shader, rightModel, depth + 1, maxDepth, branchLength * 0.7f);
    }

    // You can add more branches if you want a more “bushy” tree
}


//void newtree(unsigned int& cubeVAO, BezierCurve& treeCurve, BezierCurve& treeBaseCurve, Shader& lightingShader, Shader& lightingShaderWithTexture, map<string, Cube>& textures, glm::mat4 als) {
//
//    glm::mat4 identityMatrix = glm::mat4(1.0f);
//    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, rotationMatrix, initModel, temp;
//
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.0f, 0.0));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
//    model = als * translateMatrix * scaleMatrix;
//    treeCurve.drawBezierCurvewithTexture(lightingShaderWithTexture, model, glm::vec3(1.0, 1.0, 1.0));
//
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
//    model = als * translateMatrix * scaleMatrix;
//    treeBaseCurve.drawBezierCurvewithTexture(lightingShaderWithTexture, model, glm::vec3(1.0, 1.0, 1.0));
//
//}



void generateFractalTree(float x, float y, float angle, int depth, float length, std::vector<float>& vertices)
{
    if(depth == 0)
        return;

    // Compute end position of the current branch
    float x2 = x + std::cos(angle) * length;
    float y2 = y + std::sin(angle) * length;

    // Store the line segment (two points)
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(x2);
    vertices.push_back(y2);

    // Decrease length for child branches
    float newLength = length * 0.7f;

    // Adjust angles slightly for branching
    float angleOffset = 0.3f;

    // Recursively generate left and right branches
    generateFractalTree(x2, y2, angle + angleOffset, depth - 1, newLength, vertices);
    generateFractalTree(x2, y2, angle - angleOffset, depth - 1, newLength, vertices);

}

void rocketDriver(unsigned int& bezierCylinderVAO, unsigned int& bezierCyCurve, unsigned int& bezierHead, unsigned int& cubeVAO, Shader& lightingShader,
    vector<float>& cx1, vector<float>& cz1,
    float txr, float tyr, float tzr, float ctz
)
{

    if (flagRocket == 1)
    {
        if (dthetaX <= -40.0 && irt >= 7.6)
        {
            dthetaY = dthetaY - 0.1;
            rocketI = rocketI + 1;
            if (rocketI == 720)
            {
                rocketI = 0;
            }

        }
        if (dthetaX >= -40.0)
        {
            dthetaX = dthetaX - 0.06;

        }
        if (irt <= 7.6)
        {
            irt = irt + 0.0110;
        }
        if (irt <= 2.5)
        {
            irtz = irtz + 0.01;
        }

    }
    else
    {
        dthetaY = 0.0;
        dthetaX = 0.0;

    }

    glm::mat4 identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(34.0f - 30, -5.0f, 20.5f - 15 + ctz));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(15, 2.5, 15));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(bezierCylinderVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(34.0f - 30, -16.0f, 20.5f - 15 + ctz));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5, 15, 5));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 0.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(bezierCylinderVAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    //blue one
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(34.0f - 30, -16.0f + 16.5f, 20.5f - 15 + ctz));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(4, 10, 4));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(bezierCylinderVAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    //blue curve
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(34.0f - 30, -16.0f + 16.5f, 20.5f - 15 + ctz));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3.8, 10, 3.8));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(bezierCyCurve);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    //Shewla one
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(34.0f - 30, -16.0f + 24.0f, 20.5f - 15 + ctz));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 10, 3));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 0.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(bezierCylinderVAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    //shewla curve
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(34.0f - 30, -16.0f + 24.0f, 20.5f - 15 + ctz));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 10, 3));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 0.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(bezierCyCurve);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(34.0f - 30, -16.0f + 24.0f + 16.0, 20.5f - 15 + ctz));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 2, 3));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0, 0.0, 0.0));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0, 0.0, 0.0));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 0.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(bezierCyCurve);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);


    //identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    ////glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    //identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(34.0f - 30, -16.0f + 24.0f + 3.0, 20.5f - 15 + ctz));
    //rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 10, 3));
    //modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    //lightingShader.setMat4("model", modelforCurve);
    //lightingShader.use();
    //lightingShader.setVec3("material.ambient", glm::vec3(0, 0, 1));
    //lightingShader.setVec3("material.diffuse", glm::vec3(0, 0, 1));
    //lightingShader.setVec3("material.specular", glm::vec3(0.0f, 0.0f, 0.0f));
    //lightingShader.setFloat("material.shininess", 25.0f);
    //glBindVertexArray(bezierHead);
    //glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    //glBindVertexArray(0);

}


void rocket_seats(unsigned int& bezierCylinderVAO, unsigned int& bezierCyCurve, unsigned int& bezierHead, unsigned int& cubeVAO, Shader& lightingShader, Shader& lightingShaderWithTexture, Cube& cube2,
    vector<float>& cx1, vector<float>& cz1,
    float txr, float tyr, float tzr, float ctz, glm::mat4 altogether)
{
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, modelStand;
    modelStand = glm::mat4(1.0f);
    //Four rotating stands
   //1st stand
    modelStand = transform(0.0, 0.0, 0.0, 50.0 + dthetaX, 0.0, 0.0, 0.25f, 0.75f, 15.8f);
    modelStand = transform(0.0,0.0, 0.0, 0.0, 0.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 0.0f, 0.0f);
    //2nd stand
    modelStand = transform(0.0, 0.0, 0.0, 50.0 + dthetaX, 0.0, 0.0, 0.25f, 0.75f, 15.8f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 1.0f, 1.0f);
    //3rd stand
    modelStand = transform(0.0, 0.0, 0.0, 50.0 + dthetaX, 0.0, 0.0, 0.25f, 0.75f, 15.8f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 180.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 0.0f, 0.0f);
    //4th stand
    modelStand = transform(0.0, 0.0, 0.0, 50.0 + dthetaX, 0.0, 0.0, 0.25f, 0.75f, 15.8f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 270.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 1.0f, 1.0f);
    lightingShaderWithTexture.use();

    //First rotating seat.........................................
    //bottom part
    modelStand = transform(0.0 - 1.75, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, 0.0, 7.0f, 0.2f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 0.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 0.0f, 0.0f);
    //Right part
    modelStand = transform(0.0, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, -90.0, 00.0, 0.0, 5.0f, 0.2f, 1.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 0.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 0.0f, 0.0f);
    //Left part
    modelStand = transform(0.0, -13.1035 + dyy_rseat, 12.50 + dxx_rseat, -90.0, 00.0, 0.0, 5.0f, 0.2f, 1.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 0.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 0.0f, 0.0f);
    //Back part
    modelStand = transform(0.0 - 1.75 + 6.75, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, 0.0, 0.20f, 3.0f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 0.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 0.0f, 0.0f);
    //Front part
    modelStand = transform(0.0 - 1.75, -12.98 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, -50.0, 0.20f, 3.0f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 0.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 1.0f, 1.0f);


    //Second rotating seat
    //bottom
    modelStand = transform(0.0 - 1.75, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, 0.0, 7.0f, 0.2f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 180.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 0.0f, 0.0f);
    //right
    modelStand = transform(0.0, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, -90.0, 00.0, 0.0, 5.0f, 0.2f, 1.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 180.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 0.0f, 0.0f);
    //left
    modelStand = transform(0.0, -13.1035 + dyy_rseat, 12.50 + dxx_rseat, -90.0, 00.0, 0.0, 5.0f, 0.2f, 1.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 180.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 0.0f, 0.0f);
    //back
    modelStand = transform(0.0 - 1.75 + 6.75, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, 0.0, 0.20f, 3.0f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 180.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 1.0f, 0.0f);
    //front
    modelStand = transform(0.0 - 1.75, -12.98 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, -50.0, 0.20f, 3.0f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 180.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 1.0f, 1.0f);


    //third rotating seat
    //bottom
    modelStand = transform(0.0 - 1.75, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, 0.0, 7.0f, 0.2f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 0.0f, 0.0f);
    //right
    modelStand = transform(0.0, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, -90.0, 00.0, 0.0, 5.0f, 0.2f, 1.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 1.0f, 1.0f);
    //left
    modelStand = transform(0.0, -13.1035 + dyy_rseat, 12.50 + dxx_rseat, -90.0, 00.0, 0.0, 5.0f, 0.2f, 1.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 1.0f, 1.0f);
    //back
    modelStand = transform(0.0 - 1.75 + 6.75, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, 0.0, 0.20f, 3.0f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 1.0f, 0.0f);
    //front
    modelStand = transform(0.0 - 1.75, -12.98 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, -50.0, 0.20f, 3.0f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, 90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 1.0f, 0.0f);


    //fourth rotating seat
    //bottom
    modelStand = transform(0.0 - 1.75, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, 0.0, 7.0f, 0.2f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, -90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 0.0f, 0.0f);
    //right
    modelStand = transform(0.0, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, -90.0, 00.0, 0.0, 5.0f, 0.2f, 1.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, -90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 0.0f, 0.0f);
    //left
    modelStand = transform(0.0, -13.1035 + dyy_rseat, 12.50 + dxx_rseat, -90.0, 00.0, 0.0, 5.0f, 0.2f, 1.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, -90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 0.0f, 0.0f);
    //back
    modelStand = transform(0.0 - 1.75 + 6.75, -13.1035 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, 0.0, 0.20f, 3.0f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, -90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 0.0f, 1.0f);
    //front
    modelStand = transform(0.0 - 1.75, -12.98 + dyy_rseat, 9.00 + dxx_rseat, 0.0, 0.0, -50.0, 0.20f, 3.0f, 3.5f);
    modelStand = transform(0.0, 0.0, 0.0, 0.0, -90.0 + dthetaY, 0.0, 1, 1, 1) * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 1.0f, 1.0f);
    //done with seats



    if (flagRocket == 1)
    {
        if (dthetaX <= -40.0 && irt >= 7.6)
        {
            dthetaY = dthetaY - 0.4;
            rocketI = rocketI + 1;
            if (rocketI == 720)
            {
                rocketI = 0;
            }

        }
        if (dthetaX >= -40.0)
        {
            dthetaX = dthetaX - 0.06;
            dyy_rseat = 15.8 * glm::sin(glm::radians(-dthetaX));
            dxx_rseat = dxx_rseat + 0.0155;
            //dyy_rseat = dyy_rseat + 0.0152;



        }
        if (irt <= 7.6)
        {
            irt = irt + 0.0110;
        }
        if (irt <= 2.5)
        {
            irtz = irtz + 0.01;
        }

    }
    else
    {
        dthetaY = 0.0;
        dthetaX = 0.0;
        dyy_rseat = 0.0;
        dxx_rseat = 0.0;

    }

   
}



void drawSeat(
    unsigned int cubeVAO,
    Shader& lightingShader,
    glm::mat4 altogether,
    float seatAngle,  // e.g. 0 + dthetaY, or 180 + dthetaY, etc.
    float dthetaY,
    float dxx_rseat,
    float dyy_rseat
)
{
    if (flagRocket == 1)
    {
        if (dthetaX <= -40.0 && irt >= 7.6)
        {
            dthetaY -= 0.1f;
            rocketI = rocketI + 1;
            if (rocketI == 720) rocketI = 0;
        }
        if (dthetaX >= -40.0) {
            dthetaX -= 0.06f;
        }
        if (irt <= 7.6) {
            irt += 0.0110f;
        }
        if (irt <= 2.5) {
            irtz += 0.01f;
        }
    }
    else
    {
        dthetaY = 0.0f;
        dthetaX = 0.0f;
    }
    glm::mat4 modelStand = glm::mat4(1.0f);

    // Bottom part
    modelStand = transform(
        /* translateX */ (0.0 - 1.75),
        /* translateY */ (-13.1035 + dyy_rseat),
        /* translateZ */ (9.00 + dxx_rseat),
        /* rotateX */ 0.0,
        /* rotateY */ 0.0,
        /* rotateZ */ 0.0,
        /* scaleX */ 7.0f,
        /* scaleY */ 0.2f,
        /* scaleZ */ 3.5f
    );
    // Then apply seatAngle + dthetaY
    modelStand = transform(0.0, 0.0, 0.0, 0.0, seatAngle + dthetaY, 0.0, 1, 1, 1)
        * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, /*color*/ 0.0f, 0.0f, 0.0f);

    // Right part
    modelStand = transform(
        0.0, -13.1035 + dyy_rseat, 9.00 + dxx_rseat,
        -90.0, 0.0, 0.0,
        5.0f, 0.2f, 1.5f
    );
    modelStand = transform(0.0, 0.0, 0.0, 0.0, seatAngle + dthetaY, 0.0, 1, 1, 1)
        * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 0.0f, 0.0f);

    // Left part
    modelStand = transform(
        0.0, -13.1035 + dyy_rseat, 12.50 + dxx_rseat,
        -90.0, 0.0, 0.0,
        5.0f, 0.2f, 1.5f
    );
    modelStand = transform(0.0, 0.0, 0.0, 0.0, seatAngle + dthetaY, 0.0, 1, 1, 1)
        * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 0.0f, 0.0f);

    // Back part
    modelStand = transform(
        (0.0 - 1.75 + 6.75), -13.1035 + dyy_rseat, (9.00 + dxx_rseat),
        0.0, 0.0, 0.0,
        0.20f, 3.0f, 3.5f
    );
    modelStand = transform(0.0, 0.0, 0.0, 0.0, seatAngle + dthetaY, 0.0, 1, 1, 1)
        * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 0.0f, 0.0f, 0.0f);

    // Front part
    modelStand = transform(
        (0.0 - 1.75), -12.98 + dyy_rseat, (9.00 + dxx_rseat),
        0.0, 0.0, -50.0,
        0.20f, 3.0f, 3.5f
    );
    modelStand = transform(0.0, 0.0, 0.0, 0.0, seatAngle + dthetaY, 0.0, 1, 1, 1)
        * modelStand;
    lightingShader.setMat4("model", modelStand);
    drawCube(cubeVAO, lightingShader, altogether * modelStand, 1.0f, 1.0f, 1.0f);

    // done this seat
}

void drawPlayhouse(
    Shader& lightingShader,
    unsigned int bezierCylinderVAO,
    unsigned int bezierConeVAO,
    const std::vector<unsigned int>& indices,
    const std::vector<unsigned int>& indicesCone,
    float rotateAngle_X,
    float rotateAngle_Y,
    float rotateAngle_Z,
    float ctz,
    float dyy_rseat // if needed
)
{
    // 1) Draw cylinder #1
    {
        glm::mat4 identity = glm::mat4(1.0f);

        glm::mat4 translate = glm::translate(identity,
            glm::vec3(34.0f - 30, -5.0f, 20.5f - 15 + ctz));
        glm::mat4 rotX = glm::rotate(identity, glm::radians(rotateAngle_X),
            glm::vec3(1, 0, 0));
        glm::mat4 rotY = glm::rotate(identity, glm::radians(rotateAngle_Y),
            glm::vec3(0, 1, 0));
        glm::mat4 rotZ = glm::rotate(identity, glm::radians(rotateAngle_Z),
            glm::vec3(0, 0, 1));
        glm::mat4 scale = glm::scale(identity, glm::vec3(15.f, 2.5f, 15.f));

        glm::mat4 model = translate * rotX * rotY * rotZ * scale;

        lightingShader.use();
        lightingShader.setMat4("model", model);
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 25.0f);

        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(),
            GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
    }

    // 2) Cone on top
    {
        glm::mat4 identity = glm::mat4(1.0f);

        // Let’s guess the top is near y = (-5 + 2.5) = -2.5
        // shift up a bit more
        glm::mat4 translate = glm::translate(identity,
            glm::vec3(34.0f - 30, -2.5f, 20.5f - 15 + ctz));
        glm::mat4 rotX = glm::rotate(identity, glm::radians(rotateAngle_X),
            glm::vec3(1, 0, 0));
        glm::mat4 rotY = glm::rotate(identity, glm::radians(rotateAngle_Y),
            glm::vec3(0, 1, 0));
        glm::mat4 rotZ = glm::rotate(identity, glm::radians(rotateAngle_Z),
            glm::vec3(0, 0, 1));
        // Make the cone smaller or bigger
        glm::mat4 scale = glm::scale(identity, glm::vec3(10.f, 10.f, 10.f));

        glm::mat4 modelCone = translate * rotX * rotY * rotZ * scale;

        lightingShader.use();
        lightingShader.setMat4("model", modelCone);
        lightingShader.setVec3("material.ambient", glm::vec3(0.4f, 0.4f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.4f, 0.4f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);

        glBindVertexArray(bezierConeVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indicesCone.size(),
            GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
    }
}

void hauntedHead(unsigned int& bezierTree, unsigned int& bezierHead, unsigned int& cubeVAO, Shader& lightingShader, Sphere& sphere, float tx1, float ty1, float tz1, float sx1, float sy1, float sz1)
{
    Cube cube = Cube();
    glm::mat4 identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(tx1 + 34.0f, ty1 + 1.0f, tz1 - 20.5f));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3 + sx1, 5 + sy1, 3 + sz1));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 25.0f);
    glBindVertexArray(bezierTree);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(tx1 + 34.0f, ty1 - 1.0f, tz1 - 20.5f));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(4 + sx1, 5 + sy1, 4 + sz1));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 25.0f);
    glBindVertexArray(bezierTree);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(tx1 + 34.0f, ty1 - 3.0f, tz1 - 20.5f));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5 + sx1, 5 + sy1, 5 + sz1));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 25.0f);
    glBindVertexArray(bezierTree);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
    identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(tx1 + 34.0f, ty1 + 0.5f, tz1 - 20.5f));
    rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3 + sx1, 5 + sy1, 3 + sz1));
    modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
    lightingShader.setMat4("model", modelforCurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(0.0f, 1.0f, 0.0f));
    lightingShader.setFloat("material.shininess", 25.0f);
    glBindVertexArray(bezierHead);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);



}

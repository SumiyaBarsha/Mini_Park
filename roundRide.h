#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"
#include <map>
#include "cube.h"
#include "circ_extra.h"


void circularRide(unsigned int& cubeVAO, Shader& lightingShader, Shader& lightingShaderWithTexture, map<string, Cube>& textures, glm::mat4 als, float ANGLE) {

    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, rotationMatrix, initModel, temp;

    Cylinder cylinder = Cylinder(0.2f, 1.0f, 50);
    model = als * glm::translate(identityMatrix, glm::vec3(-2.5f, 0.3, 7.5f));
    cylinder.drawCylinder(lightingShader, model, 0.7, 0.33, 0.24);

    for (int i = 0; i < 4; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, 0.3, 7.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.4f, 10.1f, 11.8f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)(ANGLE + (i * 90.0))), glm::vec3(0.0f, 1.0f, 0.0f));
        model = als * translateMatrix * rotateYMatrix * scaleMatrix;
        textures["wood2"].drawCubeWithTexture(lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, 0.48, 7.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.05f, 0.3f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)(ANGLE + (i * 90.0))), glm::vec3(0.0f, 1.0f, 0.0f));
        model = als * translateMatrix * rotateYMatrix * scaleMatrix;
        model = model * glm::translate(identityMatrix, glm::vec3(0.0f, 0.0, 5.0f));
        textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, 0.38, 7.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.5f, 0.05f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)(ANGLE + (i * 90.0))), glm::vec3(0.0f, 1.0f, 0.0f));
        model = als * translateMatrix * rotateYMatrix * scaleMatrix;
        model = model * glm::translate(identityMatrix, glm::vec3(0.0f, 0.0, 35.0f));
        textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);
    }




}



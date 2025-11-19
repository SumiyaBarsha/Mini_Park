#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawCube.h"
#include<map>
#include "cube.h"
using namespace std;

void curvedTrack(unsigned int& cubeVAO, BezierCurve & hollowCircleCurve, Shader& lightingShader, Shader& lightingShaderWithTexture, map<string, Cube>& textures, glm::mat4 als, float TRAIN_Z) {

	glm::mat4 identityMatrix = glm::mat4(1.0f);
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, rotationMatrix, initModel, temp;
	glm::vec3 baseTranslationVec;


	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
	rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = rotateYMatrix * rotateZMatrix;
	baseTranslationVec = glm::vec3(-8.5, 0.5, -7.0);

	for (int i = 0; i < 10; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(baseTranslationVec[0], baseTranslationVec[1], baseTranslationVec[2] + (i * 1.1)));
		model = als * translateMatrix * rotationMatrix * scaleMatrix;
		hollowCircleCurve.drawBezierCurvewithTexture(lightingShaderWithTexture, model, glm::vec3(1.0f, 1.0f, 1.0f));
	}


}



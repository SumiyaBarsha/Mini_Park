#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

#define PI 3.14159265358979323846

class HalfCylinder {
public:
    unsigned int VAO;
    float radius;
    float height;
    int sectorCount;
    unsigned int diffuseMap, specularMap;

    HalfCylinder(float r, float h, int sectors, unsigned int diffuseTex, unsigned int specularTex)
        : radius(r), height(h), sectorCount(sectors), diffuseMap(diffuseTex), specularMap(specularTex) {
        generateVertices();
        setupMesh();
    }

    void draw(Shader& shader, glm::mat4 modelMatrix) {
        shader.use();
        shader.setMat4("model", modelMatrix);

        // Activate texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        shader.setInt("material.diffuse", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        shader.setInt("material.specular", 1);

        shader.setFloat("material.shininess", 32.0f);

        // Draw the half-cylinder
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void generateVertices() {
        float sectorStep = PI / sectorCount;  // Half-circle
        float stackStep = height / 1;         // Single stack

        for (int i = 0; i <= 1; ++i) {         // Single stack
            float y = -height / 2 + i * stackStep;
            for (int j = 0; j <= sectorCount; ++j) {
                float theta = -PI / 2 + j * sectorStep;
                float x = radius * cos(theta);
                float z = radius * sin(theta);

                // Position
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                // Normals
                glm::vec3 normal = glm::normalize(glm::vec3(x, 0.0f, z));
                vertices.push_back(normal.x);
                vertices.push_back(normal.y);
                vertices.push_back(normal.z);

                // Texture coordinates
                vertices.push_back((float)j / sectorCount);
                vertices.push_back((float)i / 1);
            }
        }

        for (int i = 0; i < 1; ++i) {
            for (int j = 0; j < sectorCount; ++j) {
                int k1 = i * (sectorCount + 1) + j;
                int k2 = k1 + sectorCount + 1;
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);

                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    void setupMesh() {
        unsigned int VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture coordinate attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }
};

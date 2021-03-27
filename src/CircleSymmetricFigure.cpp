#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "CircleSymmetricFigure.h"

CircleSymmetricFigure::CircleSymmetricFigure(int newSectorsCount): Figure(newSectorsCount) {}

void CircleSymmetricFigure::linkVAO() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexWithNormal), &vertices[0], GL_STATIC_DRAW);  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithNormal), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithNormal), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  
  glBindVertexArray(0);
}

std::vector<VertexWithNormal> CircleSymmetricFigure::generateCircleUnitVectors() const {
    const float PI = 3.1415926f;
  float sectorStep = 2 * PI / sectorsCount;

  float angle;
  std::vector<VertexWithNormal> result;

  for(int i = 0; i < sectorsCount; i++) {
    angle = i * sectorStep;
    VertexWithNormal v;

    v.x = std::cos(angle);
    v.y = std::sin(angle);
    v.z = 0;

    result.push_back(v);
  }

  return result;
}
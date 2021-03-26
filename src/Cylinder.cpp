#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Cylinder.h"

Cylinder::Cylinder(int newSectorsCount): sectorsCount(newSectorsCount) {
  std::vector<VertexWithNormal> unitVertices = generateUnitVectors();

  // generate side vertices
  for(int i = 0; i < 2; i++) {
    float h = -0.5 + i + 1.0;

    for(const auto& ver: unitVertices) {
      VertexWithNormal v;
      v.x = ver.x;
      v.y = ver.y;
      v.z = h;

      v.normalX = ver.x;
      v.normalY = ver.y;
      v.normalZ = 0;

      vertices.push_back(v);
    }
  }

  // save indexes of centers;
  unsigned int baseCenterIndex = vertices.size();
  unsigned int topCenterIndex = baseCenterIndex + unitVertices.size() + 1;

  // generate top and bottom verticies
  for(int i = 0; i < 2; i++) {
    float h = -0.5 + i + 1.0;
    float nz = -1 + i * 2;

    VertexWithNormal center;
    center.x = 0;
    center.y = 0;
    center.z = h;
    center.normalX = 0;
    center.normalY = 0;
    center.normalZ = nz;

    vertices.push_back(center);

    for(const auto& ver: unitVertices) {
      VertexWithNormal v;
      v.x = ver.x;
      v.y = ver.y;
      v.z = h;

      v.normalX = 0;
      v.normalY = 0;
      v.normalZ = nz;

      vertices.push_back(v);
    }
  }

  // generate indexes of side
  unsigned int bottomIndex = 0;
  unsigned int topIndex = unitVertices.size();

  for(int i = 0; i < unitVertices.size(); i++, bottomIndex++, topIndex++) {
    if (i != unitVertices.size() - 1) {
      indices.push_back(bottomIndex);
      indices.push_back(bottomIndex + 1);
      indices.push_back(topIndex + 1);

      indices.push_back(topIndex);
      indices.push_back(topIndex + 1);
      indices.push_back(bottomIndex);
    } else {
      indices.push_back(bottomIndex);
      indices.push_back(0);
      indices.push_back(unitVertices.size());

      indices.push_back(topIndex);
      indices.push_back(unitVertices.size());
      indices.push_back(bottomIndex);
    }
  }

  // generate indexes of bottom
  for(int i = 0, k = baseCenterIndex + 1; i < unitVertices.size(); i++, k++) {
    if (i != unitVertices.size() - 1) {
      indices.push_back(baseCenterIndex);
      indices.push_back(k);
      indices.push_back(k + 1);
    } else {
      indices.push_back(baseCenterIndex);
      indices.push_back(k);
      indices.push_back(baseCenterIndex + 1);
    }
  }

  // generate indexes of top
  for(int i = 0, k = topCenterIndex + 1; i < unitVertices.size(); i++, k++) {
    if (i != unitVertices.size() - 1) {
      indices.push_back(topCenterIndex);
      indices.push_back(k);
      indices.push_back(k + 1);
    } else {
      indices.push_back(topCenterIndex);
      indices.push_back(k);
      indices.push_back(topCenterIndex + 1);
    }
  }

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

std::vector<VertexWithNormal> Cylinder::generateUnitVectors() {
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

void Cylinder::Draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Sphere.h"

Sphere::Sphere(int verticalSectors, int horizontalSectors) : verticalCount(verticalSectors), horizontalCount(horizontalSectors) {
  std::vector<VertexWithNormal> unitVertices = generateUnitVectors();

  const float PI = 3.1415926f;
  float sectorStep = PI / verticalCount;

  // generate side vertices
  float angle;
  for(int i = 1; i < verticalCount - 1; i++) {
    angle = i * sectorStep;
    float z = std::cos(angle);
    float plain = std::sin(angle);

    for(const auto& ver: unitVertices) {
      VertexWithNormal v;
      v.x = ver.x * plain;
      v.y = ver.y * plain;
      v.z = z;

      v.normalX = ver.x * plain;
      v.normalY = ver.y * plain;
      v.normalZ = z;

      vertices.push_back(v);
    }
  }

  // save indexes of centers;
  unsigned int baseCenterIndex = vertices.size();
  unsigned int topCenterIndex = baseCenterIndex + unitVertices.size() + 1;

  // generate top and bottom vertices  
  for(int i = 0; i < 2; i++) {
    float h = -1 + i * 2;

    VertexWithNormal center;
    center.x = 0;
    center.y = 0;
    center.z = h;
    center.normalX = 0;
    center.normalY = 0;
    center.normalZ = h;

    vertices.push_back(center);

    angle = (PI - i * PI) + h * sectorStep;
    float plain = std::sin(angle);
    float z = std::cos(angle);

    for(const auto& ver: unitVertices) {
      VertexWithNormal v;
      v.x = ver.x * plain;
      v.y = ver.y * plain;
      v.z = z;

      v.normalX = ver.x * plain;
      v.normalY = ver.y * plain;
      v.normalZ = z;

      vertices.push_back(v);
    }
  }

  // generate indexes of side
  unsigned int bottomIndex = 0;
  unsigned int topIndex = unitVertices.size();

  for(int i = 1; i < verticalCount - 1; i++) {
    float botStart = bottomIndex;
    float topStart = topIndex;

    for(int j = 0; j < unitVertices.size(); j++, bottomIndex++, topIndex++) {
      if (j != unitVertices.size() - 1) {
        indices.push_back(bottomIndex);
        indices.push_back(bottomIndex + 1);
        indices.push_back(topIndex + 1);

        indices.push_back(topIndex);
        indices.push_back(topIndex + 1);
        indices.push_back(bottomIndex);
      } else {
        indices.push_back(bottomIndex);
        indices.push_back(botStart);
        indices.push_back(topStart);

        indices.push_back(topIndex);
        indices.push_back(topStart);
        indices.push_back(bottomIndex);
      }
    }

    bottomIndex = topStart;
    topIndex = topStart + unitVertices.size();
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

std::vector<VertexWithNormal> Sphere::generateUnitVectors() {
  const float PI = 3.1415926f;
  float sectorStep = 2 * PI / horizontalCount;

  float angle;
  std::vector<VertexWithNormal> result;

  for(int i = 0; i < horizontalCount; i++) {
    angle = i * sectorStep;
    VertexWithNormal v;

    v.x = std::cos(angle);
    v.y = std::sin(angle);
    v.z = 0;

    result.push_back(v);
  }

  return result;
}

void Sphere::Draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
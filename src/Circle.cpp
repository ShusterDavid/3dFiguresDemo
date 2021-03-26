#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Circle.h"

Circle::Circle(int amoutOfSectors): sectorsCount(amoutOfSectors) {
  const float PI = 3.1415926f;
  float sectorStep = 2 * PI / sectorsCount;
  Vertex center = { 0.0f, 0.0f, 0.0f };
  vertices.push_back(center);

  Vertex ver;
  for(int i = 0; i <= sectorsCount; i++) {
    float angle = i * sectorStep;

    ver.x = std::cos(angle);
    ver.y = std::sin(angle);
    ver.z = 0.0f;

    vertices.push_back(ver);
  }

  for(int i = 1; i < vertices.size(); i++) {
    if (i == vertices.size() - 1) {
      indices.push_back(0);
      indices.push_back(i);
      indices.push_back(1);
    } else {
      indices.push_back(0);
      indices.push_back(i);
      indices.push_back(i + 1);
    }
  }

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);	

  glBindVertexArray(0);
}

void Circle::Draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
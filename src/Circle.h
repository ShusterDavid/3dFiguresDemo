#pragma once
#include <vector>
#include "Vertex.h"

class Circle {
  public:
    Circle(int amoutOfSectors);
    void Draw();
  private:
    int sectorsCount;
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

#pragma once
#include <vector>
#include "Vertex.h"

class Sphere {
  public:
    Sphere(int verticalSectors, int horizontalSectors);
    void Draw();
  private:
    std::vector<VertexWithNormal> generateUnitVectors();
    int verticalCount;
    int horizontalCount;
    unsigned int VAO, VBO, EBO;
    std::vector<VertexWithNormal> vertices;
    std::vector<unsigned int> indices;
};

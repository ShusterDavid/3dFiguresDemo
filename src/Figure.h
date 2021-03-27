#pragma once
#include "Vertex.h"
#include <vector>

class Figure {
  public:
    Figure(int newSectorsCount);
    void Draw() const;
  protected:
    int sectorsCount;
    unsigned int VAO, VBO, EBO;
    std::vector<VertexWithNormal> vertices;
    std::vector<unsigned int> indices;
};
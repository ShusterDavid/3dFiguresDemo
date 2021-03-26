#pragma once
#include <vector>

struct VertexWithNormal {
  float x;
  float y;
  float z;

  float normalX;
  float normalY;
  float normalZ;
};

class Cylinder {
  public:
    Cylinder(int newSectorsCount);
    void Draw();
  private:
    std::vector<VertexWithNormal> generateUnitVectors();
    int sectorsCount;
    unsigned int VAO, VBO, EBO;
    std::vector<VertexWithNormal> vertices;
    std::vector<unsigned int> indices;
};
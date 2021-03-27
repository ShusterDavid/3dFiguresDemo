#pragma once
#include <vector>
#include "Vertex.h"
#include "Figure.h"

class CircleSymmetricFigure: public Figure {
  public:
    CircleSymmetricFigure(int newSectorsCount);
  protected:
    void linkVAO();
    std::vector<VertexWithNormal> generateCircleUnitVectors() const;
};

#pragma once
#include "Figure.h"
#include "Sphere.h"
#include "Cylinder.h"

enum class SHAPE_TYPES {
  SPHERE,
  CYLINDER,
};

class Drawer {
  public:
    Drawer(int newSectorsCount);
    void Draw() const;
    void SwitchFigure(SHAPE_TYPES type);
  private:
    SHAPE_TYPES type;
    int sectorsCount;
};

#include "Drawer.h"

Drawer::Drawer(int newSectorsCount): sectorsCount(newSectorsCount), type(SHAPE_TYPES::CYLINDER) {}

void Drawer::SwitchFigure(SHAPE_TYPES type) {
  this->type = type;
}

void Drawer::Draw() const {
  Figure* fPtr;

  switch (type) {
    case SHAPE_TYPES::CYLINDER: 
      fPtr = new Cylinder(sectorsCount);
      break;
    case SHAPE_TYPES::SPHERE:
      fPtr = new Sphere(sectorsCount);
      break;
  }

  fPtr->Draw();
}


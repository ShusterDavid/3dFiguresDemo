#include <cmath>
#include "Sphere.h"

Sphere::Sphere(int newSectorsCount) : CircleSymmetricFigure(newSectorsCount) {
  std::vector<VertexWithNormal> unitVertices = generateCircleUnitVectors();

  const float PI = 3.1415926f;
  float sectorStep = PI / sectorsCount;

  // generate side vertices
  float angle;
  for(int i = 1; i < sectorsCount - 1; i++) {
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

  for(int i = 1; i < sectorsCount - 1; i++) {
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

  linkVAO();
}

#include "Figure.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Figure::Figure(int newSectorsCount): sectorsCount(newSectorsCount) {}

void Figure::Draw() const {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
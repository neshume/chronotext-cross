#include "gl/QuadBuffer.h"

using namespace std;

namespace chr
{
  namespace gl
  {
    QuadBuffer::QuadBuffer()
    {
      vertices.reserve(4);
    }

    void QuadBuffer::shutdown()
    {
      if (vertexVBOId > 0)
      {
        glDeleteBuffers(1, &vertexVBOId);
      }
    }

    void QuadBuffer::draw(float x1, float y1, float x2, float y2)
    {
      vertices.clear();
      vertices.emplace_back(x1, y1);
      vertices.emplace_back(x2, y1);
      vertices.emplace_back(x1, y2);
      vertices.emplace_back(x2, y2);

      apply();
    }

    template <>
    void QuadBuffer::draw<GL_CCW>(const glm::mat4 &matrix, float x1, float y1, float x2, float y2)
    {
      vertices.clear();
      addTransformedQuad<GL_TRIANGLE_STRIP>(matrix, Quad<>(x1, y1, x2, y2), vertices, GL_CCW);

      apply();
    }

    template <>
    void QuadBuffer::draw<GL_CW>(const glm::mat4 &matrix, float x1, float y1, float x2, float y2)
    {
      vertices.clear();
      addTransformedQuad<GL_TRIANGLE_STRIP>(matrix, Quad<>(x1, y1, x2, y2), vertices, GL_CW);

      apply();
    }

    void QuadBuffer::setMatrix(const glm::mat4 &matrix)
    {
      glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &matrix[0][0]);
    }

    void QuadBuffer::setColor(float r, float g, float b, float a)
    {
      glVertexAttrib4fv(colorLocation, &glm::vec4(r, g, b, a)[0]);
    }

    void QuadBuffer::setColor(const glm::vec4 &color)
    {
      glVertexAttrib4fv(colorLocation, &color[0]);
    }

    void QuadBuffer::apply()
    {
      if (vertexVBOId == 0)
      {
        glGenBuffers(1, &vertexVBOId);

        glBindBuffer(GL_ARRAY_BUFFER, vertexVBOId);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
      }

      // ---

      glBindBuffer(GL_ARRAY_BUFFER, vertexVBOId);
      glEnableVertexAttribArray(positionLocation);
      glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(glm::vec3), vertices.data());

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glDisableVertexAttribArray(positionLocation);
    }
  }
}

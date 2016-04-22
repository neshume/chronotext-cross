#pragma once

#include "glm.h"

namespace chr
{
  namespace gl
  {
    enum
    {
      _XYZ = 0,
      _N = 1,
      _UV = 2,
      _RGBA = 4
    };

    struct xyz
    {
      xyz() = default;

      constexpr operator const int() const { return _XYZ; }

      struct n
      {
        constexpr operator const int() const { return _XYZ|_N; }

        struct uv
        {
          constexpr operator const int() const { return _XYZ|_N|_UV; }

          struct rgba
          {
            constexpr operator const int() const { return _XYZ|_N|_UV|_RGBA; }
          };

          rgba RGBA;
        };

        struct rgba
        {
          constexpr operator const int() const { return _XYZ|_N|_RGBA; }
        };

        uv UV;
        rgba RGBA;
      };

      struct uv
      {
        constexpr operator const int() const { return _XYZ|_UV; }

        struct rgba
        {
          constexpr operator const int() const { return _XYZ|_UV|_RGBA; }
        };

        rgba RGBA;
      };

      struct rgba
      {
        constexpr operator const int() const { return _XYZ|_RGBA; }
      };

      n N;
      uv UV;
      rgba RGBA;
    };

    static constexpr xyz XYZ = {};

    // ---

    template<int T = XYZ> struct Vertex
    {};

    template<> struct Vertex<XYZ>
    {
      union
      {
        glm::vec3 position;

        struct
        {
          float x, y, z;
        };
      };

      Vertex()
      {}

      Vertex(float x, float y, float z = 0)
      :
      x(x),
      y(y),
      z(z)
      {}

      Vertex(const glm::vec3 &position)
      :
      position(position)
      {}
    };

    template<> struct Vertex<XYZ.UV> : Vertex<XYZ>
    {
      union
      {
        glm::vec2 coords;

        struct
        {
          float u, v;
        };
      };

      Vertex()
      {}

      Vertex(float x, float y, float z, float u, float v)
      :
      Vertex<>(x, y, z),
      u(u),
      v(v)
      {}

      Vertex(const glm::vec3 &position, float u, float v)
      :
      Vertex<>(position),
      u(u),
      v(v)
      {}

      Vertex(const glm::vec3 &position, const glm::vec2 &coords)
      :
      Vertex<>(position),
      coords(coords)
      {}
    };

    template<> struct Vertex<XYZ.RGBA> : Vertex<>
    {
      union
      {
        glm::vec4 color;

        struct
        {
          float r, g, b, a;
        };
      };

      Vertex()
      {}

      Vertex(float x, float y, float z, const glm::vec4 &color)
      :
      Vertex<>(x, y, z),
      color(color)
      {}

      Vertex(const glm::vec3 &position, const glm::vec4 &color)
      :
      Vertex<>(position),
      color(color)
      {}
    };

    template<> struct Vertex<XYZ.UV.RGBA> : Vertex<XYZ.UV>
    {
      union
      {
        glm::vec4 color;

        struct
        {
          float r, g, b, a;
        };
      };

      Vertex()
      {}

      Vertex(float x, float y, float z, float u, float v, const glm::vec4 &color)
      :
      Vertex<XYZ.UV>(x, y, z, u, v),
      color(color)
      {}

      Vertex(const glm::vec3 &position, const glm::vec2 &coords, const glm::vec4 &color)
      :
      Vertex<XYZ.UV>(position, coords),
      color(color)
      {}
    };

    template<> struct Vertex<XYZ.N> : Vertex<>
    {
      union
      {
        glm::vec3 normal;

        struct
        {
          float nx, ny, nz;
        };
      };

      Vertex()
      {}

      Vertex(float x, float y, float z, const glm::vec3 &normal)
      :
      Vertex<>(x, y, z),
      normal(normal)
      {}

      Vertex(const glm::vec3 &position, const glm::vec3 &normal)
      :
      Vertex<>(position),
      normal(normal)
      {}
    };

    template<> struct Vertex<XYZ.N.UV> : Vertex<XYZ.N>
    {
      union
      {
        glm::vec2 coords;

        struct
        {
          float u, v;
        };
      };

      Vertex()
      {}

      Vertex(float x, float y, float z, const glm::vec3 &normal, float u, float v)
      :
      Vertex<XYZ.N>(x, y, z, normal),
      u(u),
      v(v)
      {}

      Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &coords)
      :
      Vertex<XYZ.N>(position, normal),
      coords(coords)
      {}
    };

    template<> struct Vertex<XYZ.N.UV.RGBA> : Vertex<XYZ.N.UV>
    {
      union
      {
        glm::vec4 color;

        struct
        {
          float r, g, b, a;
        };
      };

      Vertex()
      {}

      Vertex(float x, float y, float z, const glm::vec3 &normal, float u, float v, const glm::vec4 &color)
      :
      Vertex<XYZ.N.UV>(x, y, z, normal, u, v),
      color(color)
      {}

      Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &coords, const glm::vec4 &color)
      :
      Vertex<XYZ.N.UV>(position, normal, coords),
      color(color)
      {}
    };
  }
}

#pragma once

#include "Log.h"
#include "Platform.h"

#if defined(CHR_PLATFORM_DESKTOP)
  #include <glad/glad.h>
  #include <GLFW/glfw3.h>
#elif defined(CHR_PLATFORM_EMSCRIPTEN)
  #include <emscripten.h>
  #include <emscripten/html5.h>
  #include <GLES2/gl2.h>
#endif

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

static constexpr float D2R (M_PI / 180.0);
static constexpr float R2D (180.0 / M_PI);

namespace chr
{
  class CrossSketch
  {
  public:
    static GLuint makeShader(GLenum type, const char *text);
    static GLuint makeShaderProgram(const char *vs_text, const char *fs_text);

  #if defined(CHR_PLATFORM_DESKTOP)
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  #elif defined(CHR_PLATFORM_EMSCRIPTEN)
    static void performDraw(void *data);
  #endif

    void init(int width, int height);
    double getTime();

    virtual void setup() {}
    virtual void shutdown() {}
    virtual void draw() {}

  protected:
    bool initialized = false;
    glm::vec2 screenSize;

  #if defined(CHR_PLATFORM_DESKTOP)
    GLFWwindow* window = nullptr;
  #endif
  };
}

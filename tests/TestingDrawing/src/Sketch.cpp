#include "Sketch.h"

#include "gl/draw/Texture.h"
#include "gl/draw/Rect.h"
#include "gl/draw/Circle.h"

using namespace std;
using namespace chr;
using namespace gl;

void Sketch::setup()
{
  initTextures();

  // ---

  textureBatch.setShader(textureAlphaShader);
  textureBatch.setTexture(texture);

  colorBatch.setShader(colorShader);

  // ---

  glm::mat4 projectionMatrix = glm::ortho(0.0f, windowInfo.size.x, 0.0f, windowInfo.size.y);

  Matrix modelViewMatrix;
  modelViewMatrix.translate(windowInfo.size.x / 2, windowInfo.size.y / 2);
  modelViewMatrix.scale(1, -1);

  glm::mat4 mvpMatrix = modelViewMatrix * projectionMatrix;

  colorBatch.setShaderMatrix(mvpMatrix);
  textureBatch.setShaderMatrix(mvpMatrix);
  
  // ---

  Matrix matrix;

  matrix.push();
  matrix.translate(200, 100);
  matrix.rotateZ(30 * D2R);
  draw::Rect<RGBA>(colorBatch).fill(matrix, math::Rectf(-200, -150, 300, 150), glm::vec4(1, 1, 0.5f, 1));
  matrix.pop();

  draw::Circle<RGBA>(colorBatch)
    .setRadius(100)
    .fill(matrix, 0, 0, glm::vec4(1, 0.5f, 0, 1));

  matrix.push();
  matrix.scale(0.5f);
  matrix.rotateZ(-15 * D2R);
  draw::Texture<UV|RGBA>(textureBatch).fillFromCenter(matrix, 0, 0, glm::vec4(1, 1, 1, 1));
  matrix.pop();

  // ---

  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Sketch::draw()
{
  glClearColor(0.5f, 0.5f, 0.5f, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // ---

  colorBatch.flush();
  textureBatch.flush();
}

void Sketch::initTextures()
{
  texture = Texture(Texture::Request("lys_32.png")
                      .setFlags(image::FLAGS_TRANSLUCENT_INVERSE)
                      .setMipmap(true)
                      .setWrap(GL_REPEAT, GL_REPEAT));

  LOGI << texture.width << " " << texture.height << endl;

  // ---

  #if defined(CHR_PLATFORM_EMSCRIPTEN)
    emscripten_webgl_enable_extension(emscripten_webgl_get_current_context(), "EXT_texture_filter_anisotropic");
    emscripten_webgl_enable_extension(emscripten_webgl_get_current_context(), "WEBKIT_EXT_texture_filter_anisotropic");
  #endif

  GLfloat maxAnisotropy;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
}

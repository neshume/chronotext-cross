set(GLFW_ROOT "$ENV{CROSS_PATH}/deps/glfw/dist/${PLATFORM}")
set(GLM_ROOT "$ENV{CROSS_PATH}/deps/glm/dist")
set(JPEG_ROOT "$ENV{CROSS_PATH}/deps/libjpeg-turbo")
set(PNG_ROOT "$ENV{CROSS_PATH}/deps/libpng/dist/${PLATFORM}")
set(LIBTESS2_ROOT "$ENV{CROSS_PATH}/deps/libtess2/dist/${PLATFORM}")


# ---

set(GLM_INCLUDE_DIR "${GLM_ROOT}/include")

list(APPEND INCLUDE_DIRS
  ${GLM_INCLUDE_DIR}
)

# ---

set(JPEG_INCLUDE_DIR "${JPEG_ROOT}/include")
set(JPEG_LIBRARY "${JPEG_ROOT}/lib/${PLATFORM}/libjpeg.a")

set(PNG_INCLUDE_DIRS "${PNG_ROOT}/include")
set(PNG_LIBRARIES "${PNG_ROOT}/lib/libpng17.a")

set(LIBTESS2_INCLUDE_DIR "${LIBTESS2_ROOT}/include")
set(LIBTESS2_LIBRARY "${LIBTESS2_ROOT}/lib/libtess2.a")

list(APPEND INCLUDE_DIRS
  ${JPEG_INCLUDE_DIR}
  ${PNG_INCLUDE_DIRS}
  ${LIBTESS2_INCLUDE_DIR}
)

list(APPEND LIBRARIES
  ${JPEG_LIBRARY}
  ${PNG_LIBRARIES}
  ${LIBTESS2_LIBRARY}
)

# ---

if (PLATFORM MATCHES emscripten)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s TOTAL_MEMORY=25165824")

  set(ZLIB_INCLUDE_DIRS "$ENV{HOME}/.emscripten_cache/ports-builds/zlib")
  set(ZLIB_LIBRARIES "$ENV{HOME}/.emscripten_cache/zlib.bc")

elseif (PLATFORM MATCHES ios)
  set(ZLIB_INCLUDE_DIRS "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/usr/include")
  set(ZLIB_LIBRARIES "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/usr/lib/libz.tbd")

else()
  find_package(ZLIB)
endif()

list(APPEND INCLUDE_DIRS
  ${ZLIB_INCLUDE_DIRS}
)

list(APPEND LIBRARIES
  ${ZLIB_LIBRARIES}
)

# ---

list(APPEND SRC_FILES
  "${CROSS_ROOT}/src/cross/CrossSketch.cpp"
  "${CROSS_ROOT}/src/cross/CrossDelegateBase.cpp"
  "${CROSS_ROOT}/src/system/SystemManagerBase.cpp"
  "${CROSS_ROOT}/src/system/DisplayHelperBase.cpp"
  "${CROSS_ROOT}/src/Random.cpp"
  "${CROSS_ROOT}/src/Timer.cpp"
  "${CROSS_ROOT}/src/time/Clock.cpp"
  "${CROSS_ROOT}/src/time/FrameClock.cpp"
  "${CROSS_ROOT}/src/utils/Utils.cpp"
  "${CROSS_ROOT}/src/gl/Utils.cpp"
  "${CROSS_ROOT}/src/gl/ShaderProgram.cpp"
  "${CROSS_ROOT}/src/gl/ShaderHelper.cpp"
  "${CROSS_ROOT}/src/gl/Camera.cpp"
  "${CROSS_ROOT}/src/gl/Matrix.cpp"
  "${CROSS_ROOT}/src/gl/Texture.cpp"
  "${CROSS_ROOT}/src/gl/State.cpp"
  "${CROSS_ROOT}/src/gl/Buffer.cpp"
  "${CROSS_ROOT}/src/gl/Vertex.cpp"
  "${CROSS_ROOT}/src/gl/Triangulator.cpp"
  "${CROSS_ROOT}/src/gl/Revolver.cpp"
  "${CROSS_ROOT}/src/gl/draw/Circle.cpp"
  "${CROSS_ROOT}/src/gl/draw/Rect.cpp"
  "${CROSS_ROOT}/src/gl/draw/Sprite.cpp"
  "${CROSS_ROOT}/src/gl/draw/Cube.cpp"
  "${CROSS_ROOT}/src/gl/shaders/ColorShader.cpp"
  "${CROSS_ROOT}/src/gl/shaders/LambertShader.cpp"
  "${CROSS_ROOT}/src/gl/shaders/TextureAlphaShader.cpp"
  "${CROSS_ROOT}/src/gl/shaders/TextureShader.cpp"
  "${CROSS_ROOT}/src/path/ASPC.cpp"
  "${CROSS_ROOT}/src/path/Path.cpp"
  "${CROSS_ROOT}/src/path/Shape.cpp"
  "${CROSS_ROOT}/src/path/FollowablePath2D.cpp"
  "${CROSS_ROOT}/src/path/FollowablePath3D.cpp"
  "${CROSS_ROOT}/src/path/SVGDocument.cpp"
  "${CROSS_ROOT}/src/math/MatrixAffine.cpp"
  "${CROSS_ROOT}/src/math/Utils.cpp"
  "${CROSS_ROOT}/src/math/Rect.cpp"
  "${CROSS_ROOT}/src/math/Box.cpp"
  "${CROSS_ROOT}/src/image/Utils.cpp"
)

# ---

if (PLATFORM MATCHES osx|mxe)
  set(GLFW_INCLUDE_DIR "${GLFW_ROOT}/include")
  set(GLFW_LIBRARY "${GLFW_ROOT}/lib/libglfw3.a")
  set(GLFW_SRC "$ENV{CROSS_PATH}/deps/glfw/build/src")

  list(APPEND INCLUDE_DIRS
    ${GLFW_INCLUDE_DIR}
    "${GLFW_SRC}/deps"
  )

  list(APPEND LIBRARIES
    ${GLFW_LIBRARY}
  )

  list(APPEND SRC_FILES
    "${GLFW_SRC}/deps/glad.c"
    "${CROSS_ROOT}/src/desktop/CrossDelegate.cpp"
    "${CROSS_ROOT}/src/desktop/system/DisplayHelper.cpp"
    "${CROSS_ROOT}/src/desktop/system/SystemManager.cpp"
  )
endif()


if (PLATFORM MATCHES osx)
  list(APPEND LIBRARIES
    "-framework CoreFoundation"
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
  )

elseif (PLATFORM MATCHES mxe)
  list(APPEND LIBRARIES
    gdi32
    opengl32
  )

elseif (PLATFORM MATCHES emscripten)
  list(APPEND SRC_FILES
    "${CROSS_ROOT}/src/emscripten/CrossDelegate.cpp"
    "${CROSS_ROOT}/src/emscripten/system/DisplayHelper.cpp"
    "${CROSS_ROOT}/src/emscripten/system/SystemManager.cpp"
  )

elseif (PLATFORM MATCHES ios)
  list(APPEND LIBRARIES
    "-framework GLKit"
    "-framework UIKit"
    "-framework OpenGLES"
    "-framework CoreGraphics"
    "-framework CoreVideo"
  )

  list(APPEND SRC_FILES
    "src/ios/Application.mm"
    "${CROSS_ROOT}/src/ios/CrossDelegate.mm"
    "${CROSS_ROOT}/src/ios/system/DisplayHelper.mm"
    "${CROSS_ROOT}/src/ios/system/SystemManager.mm"
    "${CROSS_ROOT}/src/ios/GLViewController.mm"
    "${CROSS_ROOT}/src/ios/CrossBridge.mm"
    "${CROSS_ROOT}/src/cocoa/NSDictionary+DefautValues.m"
    "${CROSS_ROOT}/src/cocoa/NSMutableDictionary+Merge.m"
    "${CROSS_ROOT}/src/cocoa/NSString+JSON.m"
  )

elseif (PLATFORM MATCHES android)
  list(APPEND SRC_FILES
    "${CROSS_ROOT}/src/android/CrossBridge.cpp"
    "${CROSS_ROOT}/src/android/CrossDelegate.cpp"
    "${CROSS_ROOT}/src/android/system/DisplayHelper.cpp"
    "${CROSS_ROOT}/src/android/system/SystemManager.cpp"
  )
endif()

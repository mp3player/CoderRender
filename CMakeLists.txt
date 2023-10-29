cmake_minimum_required(VERSION 3.10)
project(miracle)

set(CMAKE_CXX_STANDARD 14)

link_directories(/usr/local/lib)

include_directories(./include /usr/local/include)
include_directories(/usr/local/include/opencv4)


add_executable(miracle 

# opengl 
src/glad.c


# core 
src/Ref.cpp
src/Buffer.cpp

# util 
src/Layer.cpp


# component
src/Component.cpp
src/Light.cpp
src/Camera.cpp
src/Mesh.cpp
src/Renderer.cpp
src/Material.cpp
src/Texture.cpp

# window 
src/Window.cpp

# shader 
src/Program.cpp

# entity 
src/Node.cpp
src/Scene.cpp

# system 
src/System.cpp
src/CoordinateSystem.cpp
src/RenderSystem.cpp
src/TimeSystem.cpp

# application
src/Application.cpp

# main
main.cc 

)

target_link_libraries(miracle assimp glfw3 GL Xrandr Xi X11 pthread dl Xinerama Xcursor 
    opencv_core opencv_highgui opencv_imgproc opencv_photo opencv_imgcodecs
    blas lapack dlib
)
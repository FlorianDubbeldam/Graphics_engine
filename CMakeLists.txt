cmake_minimum_required(VERSION 3.30)
project(3D_lijntekeningen)

set(CMAKE_CXX_STANDARD 20)

add_executable(3D_lijntekeningen main.cpp
        Parsers/vector3d.cc
        Parsers/ini_configuration.cc
        Parsers/l_parser.cc
        Parsers/easy_image.cc
        TransformFunctions.cpp
        #Figure3DGenerator.cpp
        Bodies/Cube.cpp
        Bodies/Tetrahedron.cpp
        Bodies/Body.cpp
        Bodies/Octahedron.cpp
        Bodies/Octahedron.h
        Bodies/Icosahedron.cpp
        Bodies/Icosahedron.h
        Figure2DFunctions.cpp
        Figure2DFunctions.h
        LineDrawing.cpp
        LineDrawing.h
        Bodies/Dodecahedron.cpp
        Bodies/Dodecahedron.h
        Bodies/Sphere.cpp
        Bodies/Sphere.h
        Bodies/Cone.cpp
        Bodies/Cone.h
        Bodies/Cylinder.cpp
        Bodies/Cylinder.h
        Bodies/Torus.cpp
        Bodies/Torus.h
        ZBuffer.cpp
        ZBuffer.h
)

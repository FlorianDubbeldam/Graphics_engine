//
// Created by flori on 26-3-2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_FIGURE2DFUNCTIONS_H
#define INC_3D_LIJNTEKENINGEN_FIGURE2DFUNCTIONS_H

#include "TransformFunctions.h"

// Dit is 2D, ik gebruik gewoon Vector3D
class Triangle{
public:
    Vector3D A;
    Vector3D B;
    Vector3D C;

    img::Color color;
};


class Figure2DFunctions {

public:
    static void fixPoints(std::vector<Shape>& lines, int windowSize);

    static double getImageWidth(std::vector<Vector3D *> &points);

    static double getImageHeight(std::vector<Vector3D *> &points);

    static double getMinX(std::vector<Vector3D *> &points);

    static double getMinY(std::vector<Vector3D *> &points);

    static std::vector<Triangle> getTriangles(std::vector<Shape>& lines);
};


#endif //INC_3D_LIJNTEKENINGEN_FIGURE2DFUNCTIONS_H

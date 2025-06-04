//
// Created by flori on 24-3-2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_TRANSFORMFUNCTIONS_H
#define INC_3D_LIJNTEKENINGEN_TRANSFORMFUNCTIONS_H


#include "Parsers/vector3d.h"
#include <cmath>
#include <vector>

#include "Parsers/easy_image.h"
#include "Parsers/ini_configuration.h"



class Point2D{
public:
    double x;
    double y;
};


class Line2D{
public:
    Vector3D p1;
    Vector3D p2;
    img::Color color;

};

class Shape{
public :
    std::vector<Line2D> lines;
    img::Color color;
};


class TransformFunctions{

public:


    static img::Color colorConvert(std::vector<double> input);

    static double degToRad(double degrees);

    static Matrix Mscale(double scale);

    static Matrix Mx(double phi);

    static Matrix Mz(double phi);

    static Matrix toEye(Vector3D &Eye);

    static Vector3D project(Vector3D &point, Vector3D &Eye);

    static Matrix My(double phi);

    static Matrix translateMatrix(Vector3D &translatie);

    static Matrix getEntireMatrix(ini::Configuration &conf, std::string &figureName);
};


#endif //INC_3D_LIJNTEKENINGEN_TRANSFORMFUNCTIONS_H

//
// Created by flori on 20-3-2025.
//

#include "TransformFunctions.h"








img::Color TransformFunctions::colorConvert(std::vector<double> input){
    img::Color color;

    color.red = input[0]*255;
    color.green = input[1]*255;
    color.blue = input[2]*255;

    return color;
}

double TransformFunctions::degToRad(double degrees){
    double rad = degrees* M_PI/180.0;

    return rad;
}


Matrix TransformFunctions::Mscale(double scale){
    Matrix S;
    S(1,1) =  scale;
    S(2,2) = scale;
    S(3,3) = scale;

    return S;
}

Matrix TransformFunctions::Mx(double phi){
    Matrix mx;

    //Kolom per kolom
    mx(2,2) = cos(phi);
    mx(2,3) = sin(phi);
    mx(3,2) = -sin(phi);
    mx(3,3) = cos(phi);

    return mx;


}

Matrix TransformFunctions::My(double phi){
    Matrix my;

    my(1,1) = cos(phi);
    my(1,3) = -sin(phi);
    my(3,1) = sin(phi);
    my(3,3) = cos(phi);

    return my;
}

Matrix TransformFunctions::Mz(double phi){
    Matrix mz;

    mz(1,1) = cos(phi);
    mz(1,2) = sin(phi);
    mz(2,1) = -sin(phi);
    mz(2,2) = cos(phi);

    return mz;
}


//Er is iets mis met die andere matrix functies denk ik...
Matrix TransformFunctions::toEye(Vector3D& Eye){
    double r = sqrt(pow(Eye.x, 2.0) + pow(Eye.y, 2.0) + pow(Eye.z, 2.0));
    double phi = acos(Eye.z/r);

    double theta = atan2(Eye.y, Eye.x);
    //double theta = asin(Eye.y/(r*sin(phi)));


    Matrix T;
    T(4,3) = -r;
//
//    Matrix V = Mz(M_PI/2 + theta)*Mx(phi)*T;

    Matrix m;
    Matrix V;


    V = Mz(M_PI/2 + theta)*Mx(phi)*T;
    //V.print(std::cout);

    // Row 1 (right vector)
    m(1,1) = -sin(theta);
    m(1,2) = -cos(theta) * cos(phi);
    m(1,3) =  cos(theta) * sin(phi);
    m(1,4) = 0;

    // Row 2 (up vector)
    m(2,1) =  cos(theta);
    m(2,2) = -sin(theta) * cos(phi);
    m(2,3) =  sin(theta) * sin(phi);
    m(2,4) = 0;

    // Row 3 (forward vector) -- flip its sign so the camera looks from the front
    m(3,1) = 0;
    m(3,2) = sin(phi);
    m(3,3) = cos(phi);
    m(3,4) = 0;

    // Translation row: also flip the sign on the z component
    m(4,1) = 0;
    m(4,2) = 0;
    m(4,3) = -r;
    m(4,4) = 1;

    return m;

}


// Punt moet al zijn omgezet naar Eye-coördinatensysteem!!
Vector3D TransformFunctions::project(Vector3D& point, Vector3D& Eye){
    //double d = 1;


    double d = sqrt(pow(Eye.x, 2.0) + pow(Eye.y, 2.0) + pow(Eye.z, 2.0));

    double newX= (d*point.x)/(-point.z);
    double newY= (d*point.y)/(-point.z);

//    Point2D newPoint;
//    newPoint.x = newX;
//    newPoint.y = newY;

    // Voor die z-buffering onthoud ik die z-waarde van elk punt nu wel(was eerst 1.0)

    Vector3D newPoint = Vector3D::point(newX, newY, point.z);

    return newPoint;

}

Matrix TransformFunctions::translateMatrix(Vector3D& translatie){
    Matrix m;
    m(4,1) = translatie.x;
    m(4,2) = translatie.y;
    m(4,3) = translatie.z;

    return m;
}

Matrix TransformFunctions::getEntireMatrix(ini::Configuration& conf, std::string& figureName){
    auto eyeVector = conf["General"]["eye"].as_double_tuple_or_die();
    Vector3D Eye = Vector3D::point(eyeVector[0], eyeVector[1], eyeVector[2]);

    double scale = conf[figureName]["scale"].as_double_or_die();
    std::vector<double> centerVect = conf[figureName]["center"].as_double_tuple_or_die();

    double rotateX = TransformFunctions::degToRad(conf[figureName]["rotateX"].as_double_or_die());
    double rotateY = TransformFunctions::degToRad(conf[figureName]["rotateY"].as_double_or_die());
    double rotateZ = TransformFunctions::degToRad(conf[figureName]["rotateZ"].as_double_or_die());

    Vector3D center = Vector3D::point(centerVect[0], centerVect[1], centerVect[2]);

    Matrix transMatrix = TransformFunctions::translateMatrix(center);
    Matrix scaleMatrix = TransformFunctions::Mscale(scale);

    Matrix rotXMatrix = TransformFunctions::Mx(rotateX);
    Matrix rotYMatrix = TransformFunctions::My(rotateY);
    Matrix rotZMatrix = TransformFunctions::Mz(rotateZ);

    Matrix eyeMatrix = TransformFunctions::toEye(Eye);

    Matrix entireMatrix =
                         scaleMatrix
                         * rotXMatrix
                         * rotYMatrix
                         * rotZMatrix
                         * transMatrix
                         * eyeMatrix;

    return entireMatrix;



}

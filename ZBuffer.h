//
// Created by flori on 07/04/2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_ZBUFFER_H
#define INC_3D_LIJNTEKENINGEN_ZBUFFER_H

#include <utility>
#include <vector>
#include "TransformFunctions.h"
#include "Figure2DFunctions.h"

// voor abs
#include <cmath>
#include <algorithm>

class ZBufPoint{
public:
    Vector3D point;
    img::Color color;
};


class ZBuffer {
private:
    std::vector<Shape> shapes;
    std::vector<Triangle> triangles;
    std::vector<Line2D> lines;

    std::vector<std::vector<double>> zBuf={{}};
    std::vector<ZBufPoint> points={};
    std::vector<std::vector<ZBufPoint>> pointsMap={{}};

public:
    ZBuffer(std::vector<Shape> everyShapes={}, std::vector<Triangle> triangleList={})
        : shapes(std::move(everyShapes)),
        triangles(std::move(triangleList))
    {
        varInit();
        bufSetup();
        generateBuffer();

    }

    static std::vector<Vector3D> getLinePoints(const Vector3D& startPoint, const Vector3D& endPoint);

    void bufSetup();
    void generateBuffer();
    void varInit();

    img::EasyImage& genImage(img::EasyImage& image);


    void generateBufferTriangle();


    double calcZ(Vector3D &point1, Vector3D &point2, int i, int a);

    void generateImage(std::string filename);
};


#endif //INC_3D_LIJNTEKENINGEN_ZBUFFER_H

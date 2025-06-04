//
// Created by flori on 26-3-2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_LINEDRAWING_H
#define INC_3D_LIJNTEKENINGEN_LINEDRAWING_H

#include "Parsers/ini_configuration.h"
#include "Parsers/l_parser.h"
#include "Parsers/vector3d.h"
#include "TransformFunctions.h"

class LineDrawing {
private:
    ini::Configuration& conf;
    std::string figureName;
    img::Color color;

    std::vector<Vector3D> points;

    void initVars();

public:
    LineDrawing(ini::Configuration& config, std::string& figName) : conf(config) {
            figureName = figName;
            color = TransformFunctions::colorConvert(conf[figName]["color"].as_double_tuple_or_die());
            initVars();
    }
    std::vector<Vector3D> getPoints();
    std::vector<Shape> getShapes();
    void transform(Matrix& transformMatrix, Vector3D Eye);
};


#endif //INC_3D_LIJNTEKENINGEN_LINEDRAWING_H

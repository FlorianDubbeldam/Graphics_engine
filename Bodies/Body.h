//
// Created by flori on 26-3-2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_BODY_H
#define INC_3D_LIJNTEKENINGEN_BODY_H

#include "../Parsers/ini_configuration.h"
#include "../Parsers/l_parser.h"
#include "../Parsers/vector3d.h"
#include "../TransformFunctions.h"


class Body {
    ini::Configuration& conf;
    std::string figureName;
    img::Color color;



protected:
    std::vector<std::vector<double>> pointsMatrix;
    std::vector<std::vector<int>> facesMatrix;
    std::vector<Vector3D> points;

    // Kopieert de matrix steeds en dat is lelijk, maar ja.
    std::vector<Shape> getShapesFromMatrix();
    void initVars();

public:
    Body(ini::Configuration& config, std::string& figName) : conf(config) {
        figureName = figName;
        color = TransformFunctions::colorConvert(conf[figName]["color"].as_double_tuple_or_die());
    }
    std::vector<Vector3D> getPoints();
    std::vector<Shape> getShapes();
    void transform(Matrix& transformMatrix, Vector3D Eye);

};


#endif //INC_3D_LIJNTEKENINGEN_BODY_H

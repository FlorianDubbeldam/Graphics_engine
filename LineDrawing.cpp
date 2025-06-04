//
// Created by flori on 26-3-2025.
//

#include "LineDrawing.h"


 std::vector<Vector3D> LineDrawing::getPoints(){
    return points;
}

//let op! elke std::vector<Vector3D*> heeft maximaal 2 elementen(want een lijn bestaat uit 2 punten)
// We weten niet uit hoeveel vormpjes die lineDrawing bestaat, dus we maken er gewoon 1 grote shape van :)
std::vector<Shape> LineDrawing::getShapes(){
    std::vector<Shape> shapesList;
    std::vector<Line2D> linesList;

    int nrLines = conf[figureName]["nrLines"].as_int_or_die();
    linesList.resize(nrLines);

    std::string lineName;

    for(int i=0; i<nrLines; i++){
        lineName = "line" + std::to_string(i);

        auto lineVector = conf[figureName][lineName].as_int_tuple_or_die();
        Line2D currentLine;
        currentLine.p1 = points[lineVector[0]];
        currentLine.p2 = points[lineVector[1]];
        currentLine.color = TransformFunctions::colorConvert(conf[figureName]["color"].as_double_tuple_or_die());

        linesList.emplace_back(currentLine);

    }

    Shape currentShape = Shape(linesList);
    shapesList.push_back(currentShape);

    linesList = {};

    return shapesList;


}

void LineDrawing::initVars(){
    int nrPoints = conf[figureName]["nrPoints"].as_int_or_die();
    std::string pointName;

    for(int i=0; i<nrPoints; i++){
        pointName = "point" + std::to_string(i);
        auto pointVector = conf[figureName][pointName].as_double_tuple_or_die();

        points.emplace_back(Vector3D::point(pointVector[0], pointVector[1], pointVector[2]));

    }
}

void LineDrawing::transform(Matrix& transformMatrix, Vector3D Eye) {
    for(auto& point : points){
        point*=transformMatrix;
        point = TransformFunctions::project(point, Eye);
    }

}

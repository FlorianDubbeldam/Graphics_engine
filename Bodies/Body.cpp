//
// Created by flori on 26-3-2025.
//

#include "Body.h"



std::vector<Shape> Body::getShapesFromMatrix() {
    std::vector<std::vector<int>> matrix = facesMatrix;

    int maxRij = matrix.size();
    int maxKolom = matrix[0].size();

    std::vector<Line2D> lines;
    std::vector<Shape> shapes;

    for(int kolom =0; kolom <maxKolom; kolom++) {
        for (int rij=0; rij<maxRij; rij++){
            Line2D currentLine;
            currentLine.p1 = points[matrix[rij][kolom]-1];

            if (rij == maxRij-1) {

                currentLine.p2 = points[matrix[0][kolom]-1];

            }
            // Normale case
            else {
                currentLine.p2 = points[matrix[rij+1][kolom]-1];

            }

            currentLine.color = color;

            // Voor die z-buffering
            // Edit, het was al een Vector3D die ik in die line2D stopte, dus ik hoef niet apart
            // 2 z-veriabelen te maken :)


            lines.push_back(currentLine);
        }
        Shape currentShape = Shape(lines);
        shapes.push_back(currentShape);
        lines = {};


    }


    return shapes;

}

std::vector<Shape> Body::getShapes() {
    std::vector<Shape> shapes;
    shapes = getShapesFromMatrix();

    return shapes;
}

std::vector<Vector3D> Body::getPoints(){
    return points;
}


void Body::initVars() {
    for(int kolom=0; kolom<pointsMatrix[0].size(); kolom++){
        Vector3D newPoint = Vector3D::point(pointsMatrix[0][kolom], pointsMatrix[1][kolom], pointsMatrix[2][kolom]);
        points.push_back(newPoint);
    }
}

void Body::transform(Matrix& transformMatrix, Vector3D Eye) {

    for(auto& point : points){
        point*=transformMatrix;

//        std::cout << "voor: ";
//        point.print(std::cout << std::endl);
//        point = TransformFunctions::project(point, Eye);
//        std::cout << "na: ";
//        point.print(std::cout << std::endl);

    }



}
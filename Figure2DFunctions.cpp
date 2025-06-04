//
// Created by flori on 26-3-2025.
//

#include "Figure2DFunctions.h"


// Ik zat eerst nog effe te twijfelen over die ocathedron, die je kunt maken uit enkel 3hoekjes, maar
// daardoor ontstaat er wel een vierkant in het midden. Maar dit maakt eigenlijk niet uit,
// Want je wilt het midden niet opvullen toch?

// Trouwens, deze code gaat ervan uit dat alle driehoekjes/ vierkantjes zo mooi achter elkaar staan,
// dus p0, p1, p2 vormen een driehoek, p3, p4, p5 vormen een driehoek enz.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// En als er meerdere verschillende figuren in hetzelfde plaatje staan gaat het ook mis,
// want je kunt maar 1 figureType meegeven!!!!!!!!!!!!!!!!!!!

std::vector<Triangle> Figure2DFunctions::getTriangles(std::vector<Shape> &shapes) {
    std::vector<Triangle> triangles;

    // number of points van de kleine figuurtjes waar de grote zijn uit opgemaakt.
    int n=0;
//
//    if (figureType == "Cube"){
//        n=4;
//    } else if (figureType == "Tetrahedron"){
//        n=3;
//    } else if (figureType == "Octahedron"){
//        n=3;
//    }else if (figureType == "Icosahedron"){
//        n=3;
//    }else if (figureType == "Dodecahedron"){
//        n=5;
//    }else if (figureType == "Sphere"){
//        n=3;
//    }else if (figureType == "Cone"){
//        n=3;
//    }else if (figureType == "Cylinder"){
//        n=4;
//    }else if (figureType == "Torus") {
//        n=4;
//    }else{
//        std::cout << "Geen geldige figureType, kan er geen driehoeken van maken" << std::endl;
//    }


    for(auto& shape : shapes) {
        std::vector<Line2D> shapeLines = shape.lines;

        int n = shapeLines.size();


        std::vector<Vector3D> shapePoints;


        for (int j = 0; j < n; j++) {
            Vector3D currentPoint = Vector3D(shapeLines[j].p1);
            shapePoints.push_back(currentPoint);

        }

        for (int x = 0; x < n - 2; x++) {
            Triangle triangle = Triangle(shapePoints[0], shapePoints[x + 1], shapePoints[x + 2],
                                         shapeLines[0].color);
            triangles.push_back(triangle);

        }



    }

    return triangles;


}



double Figure2DFunctions::getMinX(std::vector<Vector3D *> &points) {
    double min_x;

    min_x = points[0]->x;

    // weet niet zeker of het zo'n goed idee is om er steeds else if van te maken i.p.v. if
    for (auto &point: points) {
        if (point->x < min_x) {
            min_x = point->x;
        }
    }
    return min_x;
}

double Figure2DFunctions::getMinY(std::vector<Vector3D *> &points) {
    double min_y;

    min_y = points[0]->y;


    for(auto& point : points) {
        if (point->y < min_y) {
            min_y = point->y;
        }
    }

    return min_y;
}

double Figure2DFunctions::getImageWidth(std::vector<Vector3D*>& points) {
    double max_x;
    double min_x;

    max_x = points[0]->x;
    min_x = points[0]->x;

    // weet niet zeker of het zo'n goed idee is om er steeds else if van te maken i.p.v. if
    for (auto &point: points) {
        if (point->x < min_x) {
            min_x = point->x;
        } else if (point->x > max_x) {
            max_x = point->x;
        }

    }

    double imageWidth = max_x - min_x;

    return imageWidth;


}

double Figure2DFunctions::getImageHeight(std::vector<Vector3D*>& points){
    double max_y;
    double min_y;

    max_y = points[0]->y;
    min_y = points[0]->y;


    for(auto& point : points){
        if(point->y < min_y){
            min_y = point->y;
        } else if (point->y > max_y){
            max_y = point->y;
        }

    }

    double imageHeight = max_y - min_y;

    return imageHeight;

}

// misschien fuckt hij dit op omdat ik niet zeker weet of hij de klasse Line2D ook als refrence meeneem met mijn code..

void Figure2DFunctions::fixPoints(std::vector<Shape> &shapes, int windowSize) {



    std::vector<Vector3D*> points;

    for(auto& shape: shapes) {
        std::vector<Line2D>& lines = shape.lines;
        for (auto &line: lines) {
            points.push_back(&line.p1);
            points.push_back(&line.p2);
        }
    }

    // Nabewerken van de lijntjes(schalen enzo)

    double imageWidth = getImageWidth(points);
    double imageHeight = getImageHeight(points);
    double biggestSize = imageWidth;

    if(imageHeight > imageWidth){
        biggestSize = imageHeight;
    }

    double scaleFactor = 0.95*windowSize/biggestSize;
    std::cout << "scaleFactor: " << scaleFactor << std::endl;

    Point2D windowMid;
    windowMid.x = windowSize/2.0;
    windowMid.y = windowSize/2.0;

    Point2D imageMid;
    imageMid.x = getMinX(points) + imageWidth/2.0;
    imageMid.y = getMinY(points) + imageHeight/2.0;

    std::cout << "windowMid: " << windowMid.x << "," << windowMid.y << std::endl;
    std::cout << "imageMid: " << imageMid.x << "," << imageMid.y << std::endl;

    Point2D posChange;
    posChange.x = windowMid.x-imageMid.x;
    posChange.y = windowMid.y-imageMid.y;

    // chatgpt heeft mij gegund, weet niet echt hoe dit werkt.

    for (auto& point : points) {
        point->x = (point->x - imageMid.x) * scaleFactor + windowMid.x;
        point->y = (point->y - imageMid.y) * scaleFactor + windowMid.y;
    }

}


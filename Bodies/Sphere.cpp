//
// Created by flori on 03/04/2025.
//

#include "Sphere.h"


void Sphere::generateNewTriangles() {
    std::vector<Vector3D> newPoints;
    std::vector<std::vector<int>> newFaces = {{}, {}, {}};

    for(int i=0; i<facesMatrix[0].size(); i++){
        int firstPoint = facesMatrix[0][i]-1;
        int secondPoint = facesMatrix[1][i]-1;
        int thirdPoint = facesMatrix[2][i]-1;

        // Hier werd een foutje gemaakt jongens, ik moet niet meer gaan programeren als het zo laat is.

        Vector3D A = points[firstPoint];//Vector3D::point(pointsMatrix[0][firstPoint], pointsMatrix[1][firstPoint], pointsMatrix[2][firstPoint]);
        Vector3D B = points[secondPoint];//Vector3D::point(pointsMatrix[0][secondPoint], pointsMatrix[1][secondPoint], pointsMatrix[2][secondPoint]);
        Vector3D C = points[thirdPoint];//Vector3D::point(pointsMatrix[0][thirdPoint], pointsMatrix[1][thirdPoint], pointsMatrix[2][thirdPoint]);

        Vector3D D = Vector3D::point((A.x+B.x)/2, (A.y+B.y)/2, (A.z+B.z)/2);
        Vector3D E = (A+C)/2;//Vector3D::point((A.x+C.x)/2, (A.y+C.y)/2, (A.z+C.z)/2);
        Vector3D F = (B+C)/2;//Vector3D::point((B.x+C.x)/2, (B.y+C.y)/2, (B.z+C.z)/2);

        //En nu kan ik niet meer nadenken omdat ik moe ben
        // voor morgen gwn alles toevoegen aan newPoints en dan die faces enzo aanpassen(jow, ik kan echt niet meer nadenken)

        newPoints.push_back(A);    // 1
        newPoints.push_back(B);    // 2
        newPoints.push_back(C);    // 3

        newPoints.push_back(D);    // 4
        newPoints.push_back(E);    // 5
        newPoints.push_back(F);    // 6

        // Ok, de nieuwe driehoekjes worden:
        // ADE, BFD, CEF en DFE

        int p = i*6;

        std::vector<std::vector<int>> smallFace = {{1+p, 2+p, 3+p, 4+p},
                                                   {4+p, 6+p, 5+p, 6+p},
                                                   {5+p, 4+p, 6+p, 5+p}
        };



        // nu alles bij die newFaces toevoegen
        newFaces[0].insert(newFaces[0].end(), smallFace[0].begin(), smallFace[0].end());
        newFaces[1].insert(newFaces[1].end(), smallFace[1].begin(), smallFace[1].end());
        newFaces[2].insert(newFaces[2].end(), smallFace[2].begin(), smallFace[2].end());


    }


    points = newPoints;
    facesMatrix = newFaces;
}

void Sphere::resizeTriangles() {
    for (Vector3D& point : points){
        double deler = sqrt((pow(point.x, 2)+ pow(point.y, 2)+ pow(point.z, 2)));
        point.x /= deler;
        point.y /= deler;
        point.z /= deler;

    }
}
//
// Created by flori on 03/04/2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_DODECAHEDRON_H
#define INC_3D_LIJNTEKENINGEN_DODECAHEDRON_H

#include "Body.h"

class Dodecahedron : public Body{
    using Body::Body;
public:
    Dodecahedron(ini::Configuration& config, std::string& figName) : Body(config, figName) {
        // Beetje sad dat ik dit moet kopieren van de icosahedron
        const double sqrt5Over2 = std::sqrt(5.0) / 2.0;

        // Afzonderlijke vectoren voor elk type punt
        std::vector<double> xCoords1(12,0.0);
        std::vector<double> yCoords1(12,0.0);
        std::vector<double> zCoords1(12,0.0);

        xCoords1[0] = 0.0;
        yCoords1[0] = 0.0;
        zCoords1[0] = sqrt5Over2;

        xCoords1[11] = 0.0;
        yCoords1[11] = 0.0;
        zCoords1[11] = -sqrt5Over2;

        for(int i = 1; i <= 5; ++i) {
            double angle = (i - 1) * 2 * M_PI / 5.0;
            xCoords1[i] = std::cos(angle);
            yCoords1[i] = std::sin(angle);
            zCoords1[i] = 0.5;
        }

        for(int i = 6; i <= 10; ++i) {
            double angle = M_PI / 5.0 + (i - 6) * 2 * M_PI / 5.0;
            xCoords1[i] = std::cos(angle);
            yCoords1[i] = std::sin(angle);
            zCoords1[i] = -0.5;
        }

        std::vector<std::vector<double>> icoPointMatrix = {
                xCoords1,  // x coordinates
                yCoords1,  // y coordinates
                zCoords1, // z coordinates
        };

        std::vector<std::vector<int>> icoFaceMatrix = {
                {1, 1, 1, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 2, 12, 12, 12, 12, 12},
                {2, 3, 4, 5, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 8, 9, 10, 11, 7},
                {3, 4, 5, 6, 2, 3, 8, 4, 9, 5, 10, 6, 11, 2, 7, 7, 8, 9, 10, 11}
        };

        // Elk punt is elk punt van de driehoek/3 (midden van die driehoek)
        // Niet mooi maar kben te lui om andere manier op te zoeken

        for(int i=0; i<3; i++){
            pointsMatrix.push_back({});
        }

        for (int i=0; i<icoFaceMatrix[0].size(); i++){
            int firstPoint = icoFaceMatrix[0][i]-1;
            int secondPoint = icoFaceMatrix[1][i]-1;
            int thirdPoint = icoFaceMatrix[2][i]-1;

            double x = (icoPointMatrix[0][firstPoint] + icoPointMatrix[0][secondPoint] + icoPointMatrix[0][thirdPoint])/3;
            double y = (icoPointMatrix[1][firstPoint] + icoPointMatrix[1][secondPoint] + icoPointMatrix[1][thirdPoint])/3;
            double z = (icoPointMatrix[2][firstPoint] + icoPointMatrix[2][secondPoint] + icoPointMatrix[2][thirdPoint])/3;

            pointsMatrix[0].push_back(x);
            pointsMatrix[1].push_back(y);
            pointsMatrix[2].push_back(z);

        }


        facesMatrix = {
                {1, 1, 2,  3,  4,  5,  20, 20, 19, 18, 17, 16},
                {2, 6, 8,  10, 12, 14, 19, 15, 13, 11, 9, 7},
                {3, 7, 9,  11, 13, 15, 18, 14, 12, 10, 8, 6},
                {4, 8, 10, 12, 14, 6,  17, 13, 11,  9, 7, 15},
                {5, 2, 3,  4,  5,  1,  16, 19, 18, 17, 16, 20}
        };

        initVars();


    }

};


#endif //INC_3D_LIJNTEKENINGEN_DODECAHEDRON_H

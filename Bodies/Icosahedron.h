//
// Created by flori on 26-3-2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_ICOSAHEDRON_H
#define INC_3D_LIJNTEKENINGEN_ICOSAHEDRON_H

#include "Body.h"

class Icosahedron : public Body {
    using Body::Body;

public:
    Icosahedron(ini::Configuration& config, std::string& figName) : Body(config, figName) {


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

        pointsMatrix = {
                xCoords1,  // x coordinates
                yCoords1,  // y coordinates
                zCoords1, // z coordinates
        };

        facesMatrix = {
                {1, 1, 1, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 2, 12, 12, 12, 12, 12},
                {2, 3, 4, 5, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 8, 9, 10, 11, 7},
                {3, 4, 5, 6, 2, 3, 8, 4, 9, 5, 10, 6, 11, 2, 7, 7, 8, 9, 10, 11}
        };

        initVars();

    }

};



#endif //INC_3D_LIJNTEKENINGEN_ICOSAHEDRON_H

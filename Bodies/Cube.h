//
// Created by flori on 20-3-2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_CUBE_H
#define INC_3D_LIJNTEKENINGEN_CUBE_H

#include "Body.h"

class Cube : public Body {
    using Body::Body;

public:
    Cube(ini::Configuration& config, std::string& figName) : Body(config, figName) {
        // Direct aanpassen van pointsMatrix
        pointsMatrix =  {
                { 1, -1, 1, -1, 1, -1, 1, -1 },  // x coordinates
                { -1, 1, 1, -1, 1, -1, -1, 1 },  // y coordinates
                { -1, -1, 1, 1, -1, -1, 1, 1 }   // z coordinates
        };

        facesMatrix = {
                { 1, 5, 2, 6, 7, 1 },
                { 5, 2, 6, 1, 3, 6 },
                { 3, 8, 4, 7, 8, 2 },
                { 7, 3, 8, 4, 4, 5 }
        };

        initVars();

    }

};

#endif //INC_3D_LIJNTEKENINGEN_CUBE_H

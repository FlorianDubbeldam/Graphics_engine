//
// Created by flori on 26-3-2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_OCTAHEDRON_H
#define INC_3D_LIJNTEKENINGEN_OCTAHEDRON_H

#include "Body.h"


class Octahedron : public Body {
    using Body::Body;

public:
    Octahedron(ini::Configuration& config, std::string& figName) : Body(config, figName) {
        // Direct aanpassen van pointsMatrix
        pointsMatrix =  {
                { 1, 0, -1, 0, 0, 0 },  // x coordinates
                { 0, 1, 0, -1, 0, 0 },  // y coordinates
                { 0, 0, 0, 0, -1, 1 }   // z coordinates
        };

        facesMatrix = {
                { 1, 2, 3, 4, 2, 3, 4, 1 },
                { 2, 3, 4, 1, 1, 2, 3, 4 },
                { 6, 6, 6, 6, 5, 5, 5, 5 }
        };

        initVars();

    }

};


#endif //INC_3D_LIJNTEKENINGEN_OCTAHEDRON_H

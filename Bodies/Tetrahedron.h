//
// Created by flori on 20-3-2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_Tetrahedron_H
#define INC_3D_LIJNTEKENINGEN_Tetrahedron_H

#include "../Parsers/ini_configuration.h"
#include "../Parsers/l_parser.h"
#include "../Parsers/vector3d.h"
#include "../TransformFunctions.h"
#include "Body.h"


class Tetrahedron : public Body {
    using Body::Body;

public:
    Tetrahedron(ini::Configuration& config, std::string& figName) : Body(config, figName) {
        // Direct aanpassen van pointsMatrix
        pointsMatrix =  {
                { 1, -1, 1, -1 },  // x coordinates
                { -1, 1, 1, -1 },  // y coordinates
                { -1, -1, 1, 1 }   // z coordinates
        };

        facesMatrix = {
                { 1, 2, 1, 1 },
                { 2, 4, 4, 3 },
                { 3, 3, 2, 4}
        };

        initVars();

    }

};


#endif //INC_3D_LIJNTEKENINGEN_Tetrahedron_H

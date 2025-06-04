//
// Created by flori on 03/04/2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_SPHERE_H
#define INC_3D_LIJNTEKENINGEN_SPHERE_H

#include "Icosahedron.h"
#include "../Parsers/vector3d.h"

class Sphere : public Icosahedron {
private:
    using Icosahedron::Icosahedron;

    void generateNewTriangles();
    void resizeTriangles();

public:
    Sphere(ini::Configuration& config, std::string& figName) : Icosahedron(config, figName){
        // Eerst die driehoekjes kleiner maken

        int n = config[figName]["n"].as_int_or_die();

        for(int i=0; i<n; i++){
            generateNewTriangles();

        }

        resizeTriangles();

        // Hier hoeft geen initVars(); omdat het al gedaan is in Icosahedron zelfs voordat de eerste functie van Sphere
        // uitgevoerd is :)

    }



};


#endif //INC_3D_LIJNTEKENINGEN_SPHERE_H

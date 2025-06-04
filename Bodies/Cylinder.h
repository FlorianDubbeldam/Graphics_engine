//
// Created by flori on 05/04/2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_CYLINDER_H
#define INC_3D_LIJNTEKENINGEN_CYLINDER_H

#include "Body.h"

class Cylinder : public Body{
private:
    using Body::Body;

public:

    Cylinder(ini::Configuration& config, std::string& figName) : Body(config, figName) {
        int n = config[figName]["n"].as_int_or_die();
        double h = config[figName]["height"].as_double_or_die();

        facesMatrix = {{},
                       {},
                       {},
                       {}
        };
        pointsMatrix = {{},
                        {},
                        {}};

        for(int i=0; i<n; i++){
            pointsMatrix[0].push_back(cos((2*i*M_PI)/n));
            pointsMatrix[1].push_back(sin((2*i*M_PI)/n));
            pointsMatrix[2].push_back(0);
        }

        for(int i=0; i<n; i++){
            pointsMatrix[0].push_back(cos((2*i*M_PI)/n));
            pointsMatrix[1].push_back(sin((2*i*M_PI)/n));
            pointsMatrix[2].push_back(h);
        }

        // Kan mooier met modulo maar ja...

        for(int i=0; i<n-1; i++){
            facesMatrix[0].push_back(i+1);
            facesMatrix[1].push_back(i+2);
            facesMatrix[2].push_back(n+i+2);
            facesMatrix[3].push_back(n+i+1);
        }

        // Laatste lijntje

        facesMatrix[0].push_back(n);
        facesMatrix[1].push_back(1);
        facesMatrix[2].push_back(n+1);
        facesMatrix[3].push_back(2*n);


        initVars();


    }


};


#endif //INC_3D_LIJNTEKENINGEN_CYLINDER_H

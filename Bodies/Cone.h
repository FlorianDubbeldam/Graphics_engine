//
// Created by flori on 05/04/2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_CONE_H
#define INC_3D_LIJNTEKENINGEN_CONE_H

#include "Body.h"

class Cone : public Body {
private:
    using Body::Body;

public:
    Cone(ini::Configuration& config, std::string& figName) : Body(config, figName) {
        int n = config[figName]["n"].as_int_or_die();
        double h = config[figName]["height"].as_double_or_die();

        facesMatrix = {{},
                       {},
                       {}};
        pointsMatrix = {{},
                        {},
                        {}};

        for (int i =0; i<n; i++){
            pointsMatrix[0].push_back(cos((2*i*M_PI)/n));
            pointsMatrix[1].push_back(sin((2*i*M_PI)/n));
            pointsMatrix[2].push_back(0);


            // Nu de faces

            facesMatrix[0].push_back(i+1);
            facesMatrix[1].push_back(i+2);
            facesMatrix[2].push_back(n+1);

        }

        // Het laatste lijntje nog trekken
        // Ik trek er 3 terwijl ik er eigenlijk maar 2 moet trekken maar ja..

        facesMatrix[0].push_back(n);
        facesMatrix[1].push_back(1);
        facesMatrix[2].push_back(n+1);


        // Nu de top van de kegel

        pointsMatrix[0].push_back(0);
        pointsMatrix[1].push_back(0);
        pointsMatrix[2].push_back(h);


        initVars();
    }



};


#endif //INC_3D_LIJNTEKENINGEN_CONE_H

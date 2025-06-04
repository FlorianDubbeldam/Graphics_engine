//
// Created by flori on 05/04/2025.
//

#ifndef INC_3D_LIJNTEKENINGEN_TORUS_H
#define INC_3D_LIJNTEKENINGEN_TORUS_H

#include "Body.h"

class Torus : public Body{
private:
    using Body::Body;
public:
    Torus(ini::Configuration& config, std::string& figName) : Body(config, figName) {
        int r = config[figName]["r"].as_int_or_die();
        double R = config[figName]["R"].as_double_or_die();
        int m = config[figName]["m"].as_int_or_die();
        int n = config[figName]["n"].as_int_or_die();


        pointsMatrix = {{},
                        {},
                        {}};

        facesMatrix = {{},
                       {},
                       {},
                       {}};

        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                double u = (2.0*i*M_PI)/n;
                double v = (2.0*j*M_PI)/m;

                pointsMatrix[0].push_back((R+r*cos(v))*cos(u));
                pointsMatrix[1].push_back((R+r*cos(v))*sin(u));
                pointsMatrix[2].push_back(r*sin(v));

            }
        }

        for (int i=0; i<n; i++) {
            for (int j = 0; j < m; j++) {
                int x = j + i*m; // Is eigenlijk de huidige locatie (i, j)
                int y = j + ((i+1)%n)*m; // i+1, j
                int z = (j+1)%m + ((i+1)%n)*m; // i+1, j+1
                int q = (j+1)%m + i*m;    // (i, j+1)

                facesMatrix[0].push_back(x+1);
                facesMatrix[1].push_back(y+1);
                facesMatrix[2].push_back(z+1);
                facesMatrix[3].push_back(q+1);



            }
        }

        initVars();


    }

};


#endif //INC_3D_LIJNTEKENINGEN_TORUS_H

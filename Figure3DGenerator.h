////
//// Created by flori on 25-3-2025.
////
//
//#include <iostream>
//#include "Parsers/vector3d.h"
//#include <cmath>
//#include <vector>
//
//#include "Parsers/easy_image.h"
//#include "Parsers/ini_configuration.h"
//#include "Parsers/l_parser.h"
//#include <fstream>
//
//#ifndef INC_3D_LIJNTEKENINGEN_FIGURE3DGENERATOR_H
//#define INC_3D_LIJNTEKENINGEN_FIGURE3DGENERATOR_H
//
//
//
//class Figure3DGenerator {
//public:
//    // Genereert de image op basis van de .ini configuratie
//    img::EasyImage generate(const ini::Configuration& config);
//
//    struct Figure3D {
//        std::vector<Vector3D> points;
//        std::vector<std::pair<int, int>> lines; // Een lijn is een verbinding tussen twee point indices
//        Vector3D color = Vector3D::vector(1, 1, 1); // Default kleur is wit
//    };
//
//private:
//
////    // Helper struct om 3D objecten te representeren
//
//
//    // Matrix creatie methodes
//    Matrix scaleMatrix(double scale);
//    Matrix rotateXMatrix(double angle);
//    Matrix rotateYMatrix(double angle);
//    Matrix rotateZMatrix(double angle);
//    Matrix translateMatrix(const Vector3D &translation);
//
//    // Eye transformatie methode
//    Matrix eyePointTrans(const Vector3D &eye);
//
//    // Projectie methode
//    Vector3D doProjection(const Vector3D &point, double d);
//
//    // Transformeert een vector van punten
//    void applyTransformation(std::vector<Vector3D> &points, const Matrix &m);
//
//    // Maakt een LineDrawing figuur aan van een .ini sectie
//    Figure3D createLineDrawing(const ini::Configuration &config, const std::string &figureKey);
//
//    // Primitive creatie methodes
//    Figure3D createCube();
//    Figure3D createTetrahedron();
//    Figure3D createOctahedron();
//    Figure3D createIcosahedron();
//    Figure3D createDodecahedron();
//    Figure3D createCylinder(int n, double height);
//    Figure3D createCone(int n, double height);
//    Figure3D createSphere(int subdivisions);
//    Figure3D createTorus(double R, double r, int n, int m);
//
//    void subdivideIco(std::vector<Vector3D> &points, std::vector<std::array<int,3>> &triangles);
//    int getMiddlePoint(int i1, int i2, std::vector<Vector3D> &points, std::map<long long,int> &middlePointCache);
//
//
//};
//
//
//#endif //INC_3D_LIJNTEKENINGEN_FIGURE3DGENERATOR_H

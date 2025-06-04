#include <iostream>
#include "Parsers/vector3d.h"
#include <cmath>
#include <vector>

#include "Parsers/easy_image.h"
#include "Parsers/ini_configuration.h"
#include "Parsers/l_parser.h"
#include <fstream>
#include "TransformFunctions.h"

#include "Bodies/Cube.h"
#include "Bodies/Tetrahedron.h"
#include "Bodies/Octahedron.h"
#include "Bodies/Icosahedron.h"
#include "Bodies/Dodecahedron.h"
#include "Bodies/Sphere.h"
#include "Bodies/Cone.h"
#include "Bodies/Cylinder.h"
#include "Bodies/Torus.h"
#include "LineDrawing.h"

#include "Figure2DFunctions.h"
#include "ZBuffer.h"





img::EasyImage& genImage(ini::Configuration& configuration, std::vector<Shape>& shapes, img::EasyImage& image, std::string& figureName){

    img::Color lineColor;

    std::vector<Line2D> lines;

    for(auto& shape : shapes){
        lines.insert(lines.begin(), shape.lines.begin(), shape.lines.end());
    }



        for (const auto& line: lines) {
            try{
            lineColor = line.color;
            image.draw_line(static_cast<int>(line.p1.x), static_cast<int>(line.p1.y),
                            static_cast<int>(line.p2.x), static_cast<int>(line.p2.y), lineColor);
            }catch(...){
                std::cout << "kleine error met tekenen"<< std::endl;
            }
        }


    return image;

}

void loadConf(ini::Configuration& conf, std::string& fileName){
    std::ifstream fin(fileName);
    fin >> conf;
    fin.close();

}


void writeBmp(std::string& fileName, img::EasyImage& image){

    if(image.get_height() > 0 && image.get_width() > 0)
    {

        try
        {
            std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
            f_out << image;

        }
        catch(std::exception& ex)
        {
            std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Could not generate image for " << fileName << std::endl;
    }


}


void drawIni(std::string& fileName, std::string& outputName){
    ini::Configuration conf;
    loadConf(conf, fileName);

    int size = conf["General"]["size"].as_int_or_die();
    int nrFigures = conf["General"]["nrFigures"].as_int_or_die();
    std::string generalType = conf["General"]["type"].as_string_or_die();

    std::string figureName;
    img::EasyImage image(size, size);

    img::Color bgColor = TransformFunctions::colorConvert(conf["General"]["backgroundcolor"].as_double_tuple_or_die());
    image.clear(bgColor);


    std::vector<Shape> everyShapes;
    std::vector<Shape> allShapes;

    std::vector<Triangle> triangles;


    for(int i=0; i<nrFigures; i++){
        figureName = "Figure" + std::to_string(i);

        auto eyeVector = conf["General"]["eye"].as_double_tuple_or_die();
        Vector3D Eye = Vector3D::point(eyeVector[0], eyeVector[1], eyeVector[2]);

        std::string figureType = conf[figureName]["type"].as_string_or_die();
        Matrix fullMatrix = TransformFunctions::getEntireMatrix(conf, figureName);


        // Jammergenoeg moet met deze mooie code de projectie ook in de body zelf gebeuren :(



        if (figureType == "LineDrawing") {
            LineDrawing lineDrawing(conf, figureName);
            lineDrawing.transform(fullMatrix, Eye);
            allShapes = lineDrawing.getShapes();

        }else if (figureType == "Cube"){
            Cube cube(conf, figureName);
            cube.transform(fullMatrix, Eye);
            allShapes = cube.getShapes();
        } else if (figureType == "Tetrahedron"){
            Tetrahedron tetrahedron(conf, figureName);
            tetrahedron.transform(fullMatrix, Eye);
            allShapes = tetrahedron.getShapes();
        } else if (figureType == "Octahedron"){
            Octahedron octahedron(conf, figureName);
            octahedron.transform(fullMatrix, Eye);
            allShapes = octahedron.getShapes();
        }else if (figureType == "Icosahedron"){
            Icosahedron icosahedron(conf, figureName);
            icosahedron.transform(fullMatrix, Eye);
            allShapes = icosahedron.getShapes();
        }else if (figureType == "Dodecahedron"){
            Dodecahedron dodecahedron(conf, figureName);
            dodecahedron.transform(fullMatrix, Eye);
            allShapes = dodecahedron.getShapes();
        }else if (figureType == "Sphere"){
            Sphere sphere(conf,figureName);
            sphere.transform(fullMatrix, Eye);
            allShapes = sphere.getShapes();
        }else if (figureType == "Cone"){
            Cone cone(conf, figureName);
            cone.transform(fullMatrix, Eye);
            allShapes = cone.getShapes();
        }else if (figureType == "Cylinder"){
            Cylinder cylinder(conf, figureName);
            cylinder.transform(fullMatrix, Eye);
            allShapes = cylinder.getShapes();
        }else if (figureType == "Torus"){
            Torus torus(conf, figureName);
            torus.transform(fullMatrix, Eye);
            allShapes = torus.getShapes();
        }else{
            std::cout << "figureType: " << figureType << " not found";
        }

//
//        if (generalType == "ZBuffering"){
//            std::vector<Triangle> smallTriangles = Figure2DFunctions::getTriangles(allLines, figureType);
//            triangles.insert(triangles.end(), smallTriangles.begin(), smallTriangles.end());
//        }


        // Ik laat dit hier staan, om me te herinneren waar ik meer dan 5 uur debugging aan heb besteed...

//        fixPoints(allPoints, size);
//        image = genImage(conf, allLines, image, figureName);


        everyShapes.insert(everyShapes.end(), allShapes.begin(), allShapes.end());

//        allLines.clear();  // Verwijdert alle elementen uit de vector
//        allPoints.clear();

    }

    // Maakt niet uit dat x en y veranderen, z blijft hetzelfde(nog steeds voor die z-buffering)

    std::cout << everyShapes.size() << std::endl;

    Figure2DFunctions::fixPoints(everyShapes, size);


    // Dit stukje is voor die z-buffering
    // Trouwens, mijn code snijdt de image niet bij als er zwart over is dat niet wordt gebruikt,
    // Dus de size van de image blijft gewoon (size, size) :)
    // Das misschien iets makkelijker


    //generalType = "Wireframe";
    if (generalType == "ZBuffering"){
        // Die figureType wordt straks nog een probleem wanneer er meerdere figuren komen.
        std::string figureType = "Cube";

        std::vector<Triangle> smallTriangles = Figure2DFunctions::getTriangles(everyShapes);
        //triangles.insert(triangles.end(), smallTriangles.begin(), smallTriangles.end());

        //std::vector<Triangle> last(triangles.begin()+0, triangles.begin()+2);

        ZBuffer zbuf = ZBuffer({}, smallTriangles);
        image = zbuf.genImage(image);

    }
    else if (generalType == "ZBufferedWireframe"){
        ZBuffer zbuf = ZBuffer(everyShapes);
        image = zbuf.genImage(image);
    } else if(generalType == "Wireframe"){
        image = genImage(conf, everyShapes, image, figureName);
    } else{
        std::cout << "general Type not recognized" << std::endl;
    }



    writeBmp(outputName, image);


}

void drawAll(std::string& fileList){
    std::ifstream file(fileList);  // Open het bestand

    if (!file) {
        std::cerr << "Fout: Kon bestand niet openen!" << std::endl;
    }

    std::string outputName;
    std::string line;
    int i =1;
    while (std::getline(file, line)) {  // Lees elke regel in de string 'line'
        outputName = "output" + std::to_string(i) + ".bmp";
        std::cout << "Creating picture: " << line << std::endl; // Print de regel

        drawIni(line, outputName);

        i++;

    }

    file.close();  // Sluit het bestand
}


// DIT THYFUSPROGRAMMA WERKT VOOR ALLES BEHALVE DIE LAATSTE!
// Edit: dit thyfusprogramma werkt helemaal!

int main() {
    std::string fileName = "../z_buffering/z_buffering036.ini";
    //std::string fileName = "../z_buffered_wireframes/z_buffered_wireframes118.ini";
    //std::string fileName = "../wireframes/wireframes001.ini";
    std::string outputName = "out.bmp";


    ini::Configuration conf;
    loadConf(conf, fileName);

//    Figure3DGenerator fig;
//    img::EasyImage image;
//    image = fig.generate(conf);
//
//    writeBmp(outputName, image);

    drawIni(fileName, outputName);

//
//
//    std::string fileList = "../wireframes/filelist";
//
//    drawAll(fileList);


    return 0;
}

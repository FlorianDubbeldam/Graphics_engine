//
// Created by flori on 07/04/2025.
//

#include "ZBuffer.h"
#include <iomanip>
#include <fstream>

//!!!!!!!!!!!!
// DUS GOED BLIJVEN OPLETTEN IEDEREEN! DE VECTOR3D IS GEEN VECTOR3D MAAR DE X EN Y WAARDE VAN HET GEPROJECTEERDE
// PUNT SAMEN MET ZIJN OUDE Z-WAARDE (OM DE Z-BUFFER TE BEREKENEN)


// DE 1/z WORDT OPGESLAGEN IN DE Z-BUFFER, DE Z WORDT OPGESLAGEN IN DE VECTOR3D(POINT)


void ZBuffer::generateImage(std::string filename) {
    int width = zBuf[0].size();
    int height = zBuf[1].size()-1;

    double minValue = 0;
    double maxValue = std::numeric_limits<double>::infinity();

    // Scale all depths to become a number between 0 and 1
    double range = maxValue - minValue;
    if (range == 0) range = 1;  // Prevent division by zero

    img::EasyImage image(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double colorFactor = 0;
            if (zBuf[y][x] != std::numeric_limits<double>::infinity()) {
                colorFactor = ((zBuf[y][x] - minValue) / range);
                std::cout << colorFactor << std::endl;
                //colorFactor = 100;
            }
            //std::cout << "jes" << std::endl;
            image(x, y) = img::Color(255 * colorFactor,
                                     255 * colorFactor,
                                     255 * colorFactor);
        }
    }
    std::ofstream f_out(filename.c_str(), std::ios::trunc | std::ios::out | std::ios::binary);
    f_out << image;
}

img::EasyImage& ZBuffer::genImage(img::EasyImage &image) {
    // Eerst pointsMap genereren, daarna schrijven naar &image

    for(auto point: points){

        int x = static_cast<int>(round(point.point.x));
        int y = static_cast<int>(round(point.point.y));
        if (fabs(point.point.z - 1/zBuf[y][x]) < 1){


            try{
            img::Color pixelColor = point.color;
            image.draw_line(static_cast<int>(point.point.x), static_cast<int>(point.point.y),
                            static_cast<int>(point.point.x), static_cast<int>(point.point.y), pixelColor);

            }catch(...){
                std::cout << "kleine error met tekenen"<< std::endl;
            }
        }

    }

//    for(int i=0; i<pointsMap.size(); i++){
//        for(int j=0; j<pointsMap[0].size(); j++){
//            try{
//                ZBufPoint currentPoint = pointsMap[i][j];
//                img::Color pixelColor = currentPoint.color;
//                image.draw_line(static_cast<int>(currentPoint.point.x), static_cast<int>(currentPoint.point.y),
//                                static_cast<int>(currentPoint.point.x), static_cast<int>(currentPoint.point.y), pixelColor);
//
//            }catch(...){
//                std::cout << "kleine error met tekenen"<< std::endl;
//            }
//        }
    //}


    std::string a = "cool.bmp";
    //ZBuffer::generateImage(a);
    return image;

}


// Vergeet niet, dit is allemaal in 2d!!!!
// Die Vector3D staat er gewoon nog omdat ik lui ben

//En misschien is het beter om deze functie in Figure2DFunctions te zetten
//
//std::vector<Vector3D> ZBuffer::getLinePoints(const Vector3D& startPoint,const Vector3D& endPoint) {
//    int x0 = startPoint.x;
//    int x1 = endPoint.x;
//    int y0 = startPoint.y;
//    int y1 = endPoint.y;
//
//    std::vector<Vector3D> points;
//    Vector3D currentPoint;
//
//    if (x0 == x1)
//    {
//        // Special case for vertical line
//        for (int i = (int) (std::max(y0, y1) - std::min(y0, y1)); i >= 0; i--)
//        {
//            //(*this)(x0, std::min(y0, y1) + i) = color;
//            currentPoint.x = x0;
//            currentPoint.y = std::min(y0, y1)+i;
//
//            points.push_back(currentPoint);
//
//        }
//    }
//    else if (y0 == y1)
//    {
//        // Special case for horizontal line
//        for (int i = (int) (std::max(x0, x1) - std::min(x0, x1)); i >= 0; i--)
//        {
//            //(*this)(std::min(x0, x1) + i, y0) = color;
//            currentPoint.x = std::min(x0, x1)+i;
//            currentPoint.y = y0;
//
//            points.push_back(currentPoint);
//        }
//    }
//    else
//    {
//        if (x0 > x1)
//        {
//            // Flip points if x1 > x0 to ensure x0 has the lowest value
//            std::swap(x0, x1);
//            std::swap(y0, y1);
//        }
//        double m = ((double)y1 - (double)y0) / ((double)x1 - (double)x0);
//        if (-1.0 <= m && m <= 1.0)
//        {
//            for (int i = (int) (x1 - x0); i >= 0; i--)
//            {
//                //(*this)(x0 + i, (unsigned int)round(y0 + m * i)) = color;
//                currentPoint.x = x0 + i;
//                currentPoint.y = (unsigned int)round(y0 + m * i);
//
//                points.push_back(currentPoint);
//            }
//        }
//        else if (m > 1.0)
//        {
//            for (int i = (int) (y1 - y0); i >= 0; i--)
//            {
//                //(*this)((unsigned int)round(x0 + (i / m)), y0 + i) = color;
//
//                currentPoint.x = (unsigned int)round(x0 + (i / m));
//                currentPoint.y = y0 + i;
//
//                points.push_back(currentPoint);
//            }
//        }
//        else if (m < -1.0)
//        {
//            for (int i = (int) (y0 - y1); i >= 0; i--)
//            {
//                //(*this)((unsigned int)round(x0 - (i / m)), y0 - i) = color;
//                currentPoint.x = (unsigned int)round(x0 - (i / m));
//                currentPoint.y = y0 - i;
//
//                points.push_back(currentPoint);
//            }
//        }
//    }
//
//
//    // Hij reversed die lijst soms(wrs compleet normaal door de logica die ik gebruik)
//    // Maar ik wil in het begin de laagste y-waarde hebben en op het einde de grootste, dus ik doe effe een checkje
//
//    Vector3D firstElem = points[0];
//    Vector3D lastElem = points[points.size()-1];
//
//    if (lastElem.y <= firstElem.y){
//        std::reverse(points.begin() ,points.end());
//    }
//
//
//
//    return points;
//}

//
//std::vector<Vector3D> ZBuffer::getLinePoints(const Vector3D& startPoint, const Vector3D& endPoint) {
//    std::vector<Vector3D> points;
//
//    int x0 = static_cast<int>(round(startPoint.x));
//    int y0 = static_cast<int>(round(startPoint.y));
//    int x1 = static_cast<int>(round(endPoint.x));
//    int y1 = static_cast<int>(round(endPoint.y));
//
////    double x0 = startPoint.x;
////    double y0 = startPoint.y;
////    double x1 = endPoint.x;
////    double y1 = endPoint.y;
//
//    int dx = abs(x1 - x0);
//    int dy = abs(y1 - y0);
//    int sx = (x0 < x1) ? 1 : -1;
//    int sy = (y0 < y1) ? 1 : -1;
//
//
//    double err = dx - dy;
//
//    while (true) {
//        Vector3D p;
//        p.x = x0;
//        p.y = y0;
//        points.push_back(p);
//
//        if (abs(x0) == abs(x1) && abs(y0) == abs(y1))
//            break;
//
//        double e2 = 2.0 * err;
//
//        if (e2 > -dy) {
//            err -= dy;
//            x0 += sx;
//        }
//
//        if (e2 < dx) {
//            err += dx;
//            y0 += sy;
//        }
//    }
//
//    // Optioneel: bepaal of we de volgorde willen aanpassen zodat y oplopend is
//    if (!points.empty() && points.front().y > points.back().y) {
//        std::reverse(points.begin(), points.end());
//    }
//
//    return points;
//
////        std::vector<Vector3D> points;
////
////        // Behoud de originele double waarden
////        double x0 = startPoint.x;
////        double y0 = startPoint.y;
////        double x1 = endPoint.x;
////        double y1 = endPoint.y;
////
////        int dx = abs(static_cast<int>(round(x1)) - static_cast<int>(round(x0)));
////        int dy = abs(static_cast<int>(round(y1)) - static_cast<int>(round(y0)));
////
////        int sx = (x0 < x1) ? 1 : -1;
////        int sy = (y0 < y1) ? 1 : -1;
////
////        int err = dx - dy;
////
////        while (true) {
////            Vector3D p;
////            // Gebruik de originele double waarden voor de punt coördinaten
////            p.x = x0;
////            p.y = y0;
////            points.push_back(p);
////
////            if (round(x0) == round(x1) && round(y0) == round(y1))
////                break;
////
////            int e2 = 2 * err;
////
////            if (e2 > -dy) {
////                err -= dy;
////                x0 += sx;
////            }
////
////            if (e2 < dx) {
////                err += dx;
////                y0 += sy;
////            }
////        }
////
////        if (!points.empty() && points.front().y > points.back().y) {
////            std::reverse(points.begin(), points.end());
////        }
////
////        return points;
//
//
//}

std::vector<Vector3D> ZBuffer::getLinePoints(const Vector3D& startPoint, const Vector3D& endPoint) {
    std::vector<Vector3D> points;

    double x0 = startPoint.x;
    double y0 = startPoint.y;
    double x1 = endPoint.x;
    double y1 = endPoint.y;

    double dx = x1 - x0;
    double dy = y1 - y0;

    double length = std::sqrt(dx * dx + dy * dy);
    if (length == 0.0) {
        points.push_back(startPoint);
        return points;
    }

    double steps = std::ceil(length);  // aantal tussenpunten gebaseerd op afstand
    double xStep = dx / steps;
    double yStep = dy / steps;

    for (int i = 0; i <= steps; ++i) {
        Vector3D p;
        p.x = x0 + i * xStep;
        p.y = y0 + i * yStep;
        points.push_back(p);
    }

    if (!points.empty() && points.front().y > points.back().y) {
        std::reverse(points.begin(), points.end());
    }

    return points;
}

double ZBuffer::calcZ(Vector3D& point1, Vector3D& point2, int i, int a){
    double dz = point2.z-point1.z;

    Vector3D groundPoint = point1;

    double p2 = (static_cast<double>(i)/static_cast<double>(a-1));
    double p1 = dz;

    //double currentZ = groundPoint.z -(0.2/a) + p1*p2;
    double currentZ = groundPoint.z + p1*p2;

    return currentZ;

//    double p = static_cast<double>(i) / static_cast<double>(a-1);
//
//    double oneOverZ1 = 1.0 / point1.z;
//    double oneOverZ2 = 1.0 / point2.z;
//
//    double currentZ = 1.0 / ((1.0 - p) * oneOverZ1 + p * oneOverZ2);
//
//    return currentZ;
}

// Voor doubles naar pixels om te zetten gebruik ik gewoon int()

void ZBuffer::generateBuffer() {
    for (auto& line: lines){
        Vector3D startPoint = line.p1;
        Vector3D endPoint = line.p2;


        // Gevaarlijk dat ik dit schrijf, want het is laat(2 uur)
        // doe ik wel morgen verder anders, gwn functie van easyImage kopieren om die punten te krijgen :)

        // Edit: toch niet, ik heb een beetje naar die foto's zitten kijken en die pixels zitten perfect
        // als je een lijn trekt die 3 hoog is en 20 breed, heb je altijd precies 23 pixels nodig
        // met deze kennis ga ik het is zelf proberen

//        int xPixels = abs(startPoint.x - endPoint.x);
//        int yPixels = abs(startPoint.y - endPoint.y);
//
//        int a = xPixels + yPixels;

        std::vector<Vector3D> linePoints = ZBuffer::getLinePoints(startPoint, endPoint);

        int a = linePoints.size();

        for(int i=0; i<a; i++){
            // Dit is ook 2D
            Vector3D pos = linePoints[i];

//            double p = (static_cast<double>(a) - static_cast<double>(i)) / static_cast<double>(a);
//            double currentZ = 1.0/((p/startPoint.z)+((1.0-p)/endPoint.z));

            double currentZ = ZBuffer::calcZ(startPoint, endPoint, i, a);



            int x = static_cast<int>(round(pos.x));
            int y = static_cast<int>(round(pos.y));

            double prevValue = zBuf[y][x];

            if (1/currentZ < prevValue) {
 //               std::cout <<std::fixed << std::setprecision(20) <<  1/currentZ << std::endl;
                zBuf[y][x] = 1/currentZ;

                // Nu voeg ik het punt ook nog toe aan points, met z coordinaat: 1/z
                // Of ik zou ook gewoon z kunnen opslaan. Misschien is dat logischer

                Vector3D currentPoint;
                currentPoint.x = pos.x;
                currentPoint.y = pos.y;
                currentPoint.z = currentZ; // Nu wordt het weer de normale z coordinaat

                ZBufPoint bufPoint;
                bufPoint.point = currentPoint;
                bufPoint.color = line.color;

                points.push_back(bufPoint);
            }



        }


    }
}


void ZBuffer::generateBufferTriangle(){

//    std::vector<Triangle> better;
//    better.push_back(triangles[3]);
//    triangles = better;


    triangles[0].A.print(std::cout << std::endl);
    triangles[0].B.print(std::cout << std::endl);
    triangles[0].C.print(std::cout << std::endl);

    int triaCount =0;
    for(auto& triangle : triangles){
        triaCount++;
        if (triaCount >0){

            Vector3D topPoint;
            Vector3D downPoint;
            Vector3D middlePoint;

            if (triangle.A.y >= triangle.B.y and triangle.A.y >= triangle.C.y){
                topPoint = triangle.A;
            } else if(triangle.B.y >= triangle.A.y and triangle.B.y >= triangle.C.y){
                topPoint = triangle.B;
            }else{
                topPoint = triangle.C;
            }

            if (triangle.A.y <= triangle.B.y and triangle.A.y <= triangle.C.y){
                downPoint = triangle.A;
            } else if(triangle.B.y <= triangle.A.y and triangle.B.y <= triangle.C.y){
                downPoint = triangle.B;
            }else{
                downPoint = triangle.C;
            }


            if(triangle.A.y <= triangle.B.y  and triangle.B.y <= triangle.C.y or triangle.A.y >= triangle.B.y  and triangle.B.y >= triangle.C.y){
                middlePoint = triangle.B;
            } else if(triangle.B.y <= triangle.A.y  and triangle.A.y <= triangle.C.y or triangle.B.y >= triangle.A.y  and triangle.A.y >= triangle.C.y){
                middlePoint = triangle.A;
            }else {
                middlePoint = triangle.C;
            }

            // Haalt alle punten van de omtrek van de driehoek
            // Dus lijntjes AB, BC, AC

            //std::cout << downPoint.z << std::endl;

            // Ik reverse die lineLijsten omdat mijn functie getLinePoints de alle punten schijnbaar
            // van de hoogste y-waarde naar de laagste y-waarde teruggeeft, en ik tel van onder naar boven
            // (is dan ook iets makkelijker met for-loopjes enzo

            std::vector<Vector3D> linePoints1 = ZBuffer::getLinePoints(downPoint, topPoint);
            //std::reverse(linePoints1.begin(), linePoints1.end());

            std::vector<Vector3D> linePoints2 = ZBuffer::getLinePoints(downPoint, middlePoint);
            //std::reverse(linePoints2.begin(), linePoints2.end());

            // Om een of andere duistere reden draait hij linePoints3 net niet om?
            std::vector<Vector3D> linePoints3 = ZBuffer::getLinePoints(middlePoint, topPoint);
            //std::reverse(linePoints3.begin(), linePoints3.end());


            // Maar de punten hebben nog geen z waarden dus die zal ik ze is geven :)

            int a = linePoints1.size();

            for (int i=0; i< a; i++){
                //double currentZ = 1/((p/downPoint.z)+((1.0-p)/topPoint.z));
                double currentZ = ZBuffer::calcZ(downPoint, topPoint, i, a);
                linePoints1[i].z = currentZ;
      //          std::cout <<std::fixed << std::setprecision(20) <<  1/currentZ << std::endl;

            }

            a = linePoints2.size();
            for (int i=0; i< a; i++){
                //double p = static_cast<double>(i) / static_cast<double>(a);


                //double currentZ = 1/((p/downPoint.z)+((1.0-p)/middlePoint.z));
                double currentZ = ZBuffer::calcZ(downPoint, middlePoint, i, a);
                linePoints2[i].z = currentZ;
            }

            a = linePoints3.size();
            for (int i=0; i< a; i++){
//                double p = static_cast<double>(i) / static_cast<double>(a);
//
//
//                double currentZ = 1/((p/middlePoint.z)+((1.0-p)/topPoint.z));
                double currentZ = ZBuffer::calcZ(middlePoint, topPoint, i, a);
                linePoints3[i].z = currentZ;
            }

            // Maakt de twee lijntjes in 1 soort van lijn (dus linePoints3 gebruiken we niet meer)
            linePoints2.insert(linePoints2.end(), linePoints3.begin(), linePoints3.end());


            //weet niet zeker of het hier goed is om int te gebruiken, de coordinaten van de punten blijven floats,
            //misschien geeft het wel problemen

            //std::cout << (unsigned int)round(topPoint.y-downPoint.y) << std::endl;

    //        std::cout << topPoint.y << std::endl;
    //        std::cout << middlePoint.y << std::endl;
    //        std::cout << downPoint.y << std::endl;
    //
    //        middlePoint.print(std::cout << std::endl);
    //        downPoint.print(std::cout << std::endl);

            int i = 0;

            //std::cout << "linePoints2 size: " << linePoints2.size() << std::endl;
            for(int j=0; j<linePoints2.size()-0; j++){
                //weet je, ik maak wel gewoon een hoop lijntjes van die driehoeken :), niet helemaal volgens hun regels maar ja


                // Verschrikkelijk lelijke code
                Vector3D firstPoint = linePoints1[i];
                Vector3D secondPoint = linePoints2[j];

    //            while (round(secondPoint.y) != height and j <= linePoints2.size()){
    //                j++;
    //                secondPoint = linePoints2[j];
    //            }

                while (round(firstPoint.y) < round(secondPoint.y) and i<= linePoints1.size()){
                    i++;
                    firstPoint = linePoints1[i];
                }

    //            firstPoint.print(std::cout << std::endl);
    //            secondPoint.print(std::cout << std::endl);

//                firstPoint.x = round(firstPoint.x);
//                firstPoint.y = round(firstPoint.y);
//
//                secondPoint.x = round(secondPoint.x);
//                secondPoint.y = round(secondPoint.y);

                Line2D currentLine = Line2D(firstPoint, secondPoint, triangle.color);

    //            //Dit zijn de horizontale lijntjes die je trekt van onder naar boven
    //            std::vector<Vector3D> horPoints = ZBuffer::getLinePoints(firstPoint, secondPoint);
    //
    //            // Nog effe die z-waarden er weer bijgooien
    //            int a = horPoints.size();
    //            for(int i=0; i<a; i++){
    //                double currentZ = ((i/a)/firstPoint.z)+((1-i/a)/secondPoint.z);
    //                horPoints[i].z = currentZ;
    //            }
    //
                lines.push_back(currentLine);




            }


        }
    }
}

void ZBuffer::bufSetup() {



    // Dit is enkel om de width en height te vinden, maakt dus niet uit of er kopietjes of niet worden gemaakt
    // en met pointers enzo

//    std::vector<Vector3D*> pointst;
//
//    for(auto& line : lines){
//        pointst.push_back(&line.p1);
//        pointst.push_back(&line.p2);
//    }

    // effe tijdelijk omdat hij moeite heeft met de extrema
    double width = 1024;//Figure2DFunctions::getImageWidth(points);
    double height = 1024;//Figure2DFunctions::getImageHeight(points);

    double posInf = std::numeric_limits<double>::infinity();

    for(int i=0; i<height; i++){
        zBuf.push_back({});
        for(int j=0; j<width; j++){
            zBuf[i].push_back(posInf);
        }
        pointsMap.push_back({});
    }



}


// Convert triangles naar lineList :)
// (op zich kan ik ook meteen naar points omzetten maar dan moet ik meer code veranderen enzo, ik ben lui)

void ZBuffer::varInit() {

    if(triangles.empty() && shapes.empty()){
        std::cout << "constructor of zbuffer has to be given lineList or triangleList"<< std::endl;
    }else if(!triangles.empty()){
        for(auto& triangle : triangles){
            //triangle.A.print(std::cout << std::endl);
            Line2D AB = Line2D(triangle.A, triangle.B, triangle.color);
            Line2D BC = Line2D(triangle.B, triangle.C, triangle.color);
            Line2D AC = Line2D(triangle.A, triangle.C, triangle.color);
            lines.push_back(AB);
            lines.push_back(BC);
            lines.push_back(AC);

            // Beetje kut dat hij weer een andere functie in zichzelf aanroept maar heb geen zin om vandaag
            // een perfectionist te zijn.


        }

        // DIT IS VOOR GEVULDE DRIEHOEKEN!!!
        ZBuffer::generateBufferTriangle();

    // Allemaal scuffed gedaan met het omzetten maar ik voel me een beetje lui vandaag.
    } else if(!shapes.empty()){
        std::cout << "bufferwireframes detected..." << std::endl;
        std::cout << shapes.size() << std::endl;
        shapes[0].lines[0].p1.print(std::cout << std::endl);
        for(auto& shape : shapes){

            lines.insert(lines.begin(), shape.lines.begin(), shape.lines.end());
            //std::cout << "bufferwireframes detected..." << std::endl;
        }
        std::cout << "done" << std::endl;
    }
}

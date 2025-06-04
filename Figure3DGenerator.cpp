////
//// Created by adria on 12-3-2025.
////
//
//#include "Figure3DGenerator.h"
//
//static void addEdge(std::vector<std::pair<int,int>> &edges, int i, int j) {
//    if (j < i) std::swap(i,j);
//    edges.emplace_back(i, j);
//}
//
//img::EasyImage Figure3DGenerator::generate(const ini::Configuration& config) {
//    int size = config["General"]["size"].as_int_or_die();
//    ini::DoubleTuple bgColor = config["General"]["backgroundcolor"].as_double_tuple_or_die();
//    Vector3D eye = Vector3D::point(
//            config["General"]["eye"].as_double_tuple_or_die()[0],
//            config["General"]["eye"].as_double_tuple_or_die()[1],
//            config["General"]["eye"].as_double_tuple_or_die()[2]
//    );
//
//    int nrFigures = config["General"]["nrFigures"].as_int_or_die();
//    std::vector<Figure3D> figures;
//
//    for (int i = 0; i < nrFigures; i++) {
//        std::string figureKey = "Figure" + std::to_string(i);
//        std::string type = config[figureKey]["type"].as_string_or_die();
//
//        double rotX = config[figureKey]["rotateX"].as_double_or_default(0);
//        double rotY = config[figureKey]["rotateY"].as_double_or_default(0);
//        double rotZ = config[figureKey]["rotateZ"].as_double_or_default(0);
//        double scaling = config[figureKey]["scale"].as_double_or_default(1.0);
//        ini::DoubleTuple centerTup = config[figureKey]["center"].as_double_tuple_or_default({0, 0, 0});
//        Vector3D center = Vector3D::point(centerTup[0], centerTup[1], centerTup[2]);
//        ini::DoubleTuple colorTup = config[figureKey]["color"].as_double_tuple_or_default({1, 1, 1});
//        Vector3D colorVec = Vector3D::vector(colorTup[0], colorTup[1], colorTup[2]);
//
//        Figure3D figure;
//        figure = createLineDrawing(config, figureKey);
//
//
//        Matrix M = translateMatrix(center)
//                   * rotateXMatrix(rotX)
//                     * rotateYMatrix(rotY)
//                   * rotateZMatrix(rotZ)
//
//                   * scaleMatrix(scaling);
//        figure.color = colorVec;
//
//
//        for (auto &p: figure.points) {
//            p *= M;
//        }
//
//        figures.push_back(std::move(figure));
//    }
//    if (figures.size() == 0) {
//        std::cerr << "Not generating image, figures.size() == 0, ";
//        return img::EasyImage();
//    }
//
//    Matrix projectionMatrix = eyePointTrans(eye);
//    double d = -sqrt(eye.x * eye.x + eye.y * eye.y + eye.z * eye.z);
//
//    for (Figure3D &figure : figures) {
//        applyTransformation(figure.points, projectionMatrix);
//        for (Vector3D &point : figure.points) {
//            point = doProjection(point, d);
//        }
//    }
//
//    double minX = figures[0].points[0].x, maxX = figures[0].points[0].x;
//    double minY = figures[0].points[0].y, maxY = figures[0].points[0].y;
//
//    for (const Figure3D &figure : figures) {
//        for (const Vector3D &point : figure.points) {
//            minX = std::min(minX, point.x);
//            maxX = std::max(maxX, point.x);
//            minY = std::min(minY, point.y);
//            maxY = std::max(maxY, point.y);
//        }
//    }
//
//    double width = maxX - minX;
//    double height = maxY - minY;
//    bool isWidthLargest = (width >= height);
//
//    double scaleFactor;
//    if (isWidthLargest) {
//        scaleFactor = (0.95 * size) / width;
//    } else {
//        scaleFactor = (0.95 * size) / height;
//    }
//
//    double finalWidth, finalHeight;
//    if (isWidthLargest) {
//        finalWidth = size;
//        finalHeight = (height * scaleFactor) / 0.95;
//    } else {
//        finalHeight = size;
//        finalWidth = (width * scaleFactor) / 0.95;
//    }
//
//    int imageWidth  = static_cast<int>(std::floor(finalWidth));
//    int imageHeight = static_cast<int>(std::floor(finalHeight));
//
//    // Compute offsets so that the drawing is centered:
//    double offsetX = (imageWidth - scaleFactor * width) / 2;
//    double offsetY = (imageHeight - scaleFactor * height) / 2;
//
//    img::EasyImage image(imageWidth, imageHeight, img::Color(bgColor[0] * 255, bgColor[1] * 255, bgColor[2] * 255));
//
//    for (const Figure3D &figure : figures) {
//        img::Color color(figure.color.x * 255, figure.color.y * 255, figure.color.z * 255);
//        for (const auto &line : figure.lines) {
//            int x0 = static_cast<int>(scaleFactor * (figure.points[line.first].x - minX) + offsetX);
//            int y0 = static_cast<int>(scaleFactor * (figure.points[line.first].y - minY) + offsetY);
//            int x1 = static_cast<int>(scaleFactor * (figure.points[line.second].x - minX) + offsetX);
//            int y1 = static_cast<int>(scaleFactor * (figure.points[line.second].y - minY) + offsetY);
//            image.draw_line(x0, y0, x1, y1, color);
//        }
//    }
//
//    return image;
//}
//
//Matrix Figure3DGenerator::scaleMatrix(double scale) {
//    Matrix m;
//    m(1, 1) = scale;
//    m(2, 2) = scale;
//    m(3, 3) = scale;
//    return m;
//}
//
//Matrix Figure3DGenerator::rotateXMatrix(double angle) {
//    Matrix m;
//    double rad = angle * M_PI / 180;
//    m(2, 2) = cos(rad);
//    m(2, 3) = sin(rad);
//    m(3, 2) = -sin(rad);
//    m(3, 3) = cos(rad);
//    return m;
//}
//
//Matrix Figure3DGenerator::rotateYMatrix(double angle) {
//    Matrix m;
//    double rad = angle * M_PI / 180;
//    m(1, 1) = cos(rad);
//    m(1, 3) = -sin(rad);
//    m(3, 1) = sin(rad);
//    m(3, 3) = cos(rad);
//    return m;
//}
//
//Matrix Figure3DGenerator::rotateZMatrix(double angle) {
//    Matrix m;
//    double rad = angle * M_PI / 180;
//    m(1, 1) = cos(rad);
//    m(1, 2) = sin(rad);
//    m(2, 1) = -sin(rad);
//    m(2, 2) = cos(rad);
//    return m;
//}
//
//Matrix Figure3DGenerator::translateMatrix(const Vector3D &translation) {
//    Matrix m;
//    m(4, 1) = translation.x;
//    m(4, 2) = translation.y;
//    m(4, 3) = translation.z;
//    return m;
//}
//
//Matrix Figure3DGenerator::eyePointTrans(const Vector3D &eye) {
//    double r = sqrt(eye.x * eye.x + eye.y * eye.y + eye.z * eye.z);
//    double theta = atan2(eye.y, eye.x);
//    double phi = acos(eye.z / r);
//    Matrix m;
//
//    // Row 1 (right vector)
//    m(1,1) = -sin(theta);
//    m(1,2) = -cos(theta) * cos(phi);
//    m(1,3) =  cos(theta) * sin(phi);
//    m(1,4) = 0;
//
//    // Row 2 (up vector)
//    m(2,1) =  cos(theta);
//    m(2,2) = -sin(theta) * cos(phi);
//    m(2,3) =  sin(theta) * sin(phi);
//    m(2,4) = 0;
//
//    // Row 3 (forward vector) -- flip its sign so the camera looks from the front
//    m(3,1) = 0;
//    m(3,2) = sin(phi);
//    m(3,3) = cos(phi);
//    m(3,4) = 0;
//
//    // Translation row: also flip the sign on the z component
//    m(4,1) = 0;
//    m(4,2) = 0;
//    m(4,3) = -r;
//    m(4,4) = 1;
//
//    return m;
//}
//
//Vector3D Figure3DGenerator::doProjection(const Vector3D &point, double d) {
//    double safe_z = (std::abs(point.z) < 1e-6) ? 1e-6 : point.z;
//    return Vector3D::point((d * point.x) / safe_z, (d * point.y) / safe_z, 1);
//}
//
//void Figure3DGenerator::applyTransformation(std::vector<Vector3D> &points, const Matrix &m) {
//    for (auto &point : points) {
//        point *= m;
//    }
//}
//
//int Figure3DGenerator::getMiddlePoint(int i1, int i2, std::vector<Vector3D> &points, std::map<long long,int> &middlePointCache) {
//    if (i1>i2) std::swap(i1,i2);
//    long long key = ((long long)i1 << 32) + i2;
//
//    auto it = middlePointCache.find(key);
//    if (it != middlePointCache.end()){
//        return it->second;
//    }
//
//    Vector3D p1 = points[i1];
//    Vector3D p2 = points[i2];
//    Vector3D mid = Vector3D::point(
//            0.5*(p1.x + p2.x),
//            0.5*(p1.y + p2.y),
//            0.5*(p1.z + p2.z)
//    );
//    int index = (int)points.size();
//    points.push_back(mid);
//    middlePointCache[key] = index;
//    return index;
//}
//
//
//Figure3DGenerator::Figure3D Figure3DGenerator::createLineDrawing(const ini::Configuration &config, const std::string &figureKey)
//{
//    Figure3D figure;
//
//    int nrPoints = config[figureKey]["nrPoints"].as_int_or_die();
//    figure.points.reserve(nrPoints);
//
//    for (int j = 0; j < nrPoints; j++) {
//        std::string pointKey = "point" + std::to_string(j);
//        auto pointValues = config[figureKey][pointKey].as_double_tuple_or_die();
//        figure.points.push_back(Vector3D::point(
//                pointValues[0],
//                pointValues[1],
//                pointValues[2]
//        ));
//    }
//
//    int nrLines = config[figureKey]["nrLines"].as_int_or_die();
//
//    figure.lines.reserve(nrLines);
//    for (int j = 0; j < nrLines; j++) {
//        std::string lineKey = "line" + std::to_string(j);
//        auto lineIdx = config[figureKey][lineKey].as_int_tuple_or_die();
//        figure.lines.emplace_back(lineIdx[0], lineIdx[1]);
//    }
//
//    return figure;
//}
//
//

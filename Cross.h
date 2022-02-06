//
// Created by bryan on 06/02/22.
//

#ifndef CSCI251A2_CROSS_H
#define CSCI251A2_CROSS_H

#include "ShapeTwoD.h"
#include <vector>

using namespace std;

class Cross : public ShapeTwoD{

private:
    static const int CROSSVERTICES = 12;
    int id;

    int xVertices[CROSSVERTICES];
    int yVertices[CROSSVERTICES];

    vector<int> xPerimeterPoints;
    vector<int> yPerimeterPoints;
    vector<int> xShapePoints;
    vector<int> yShapePoints;

    double area = 0;
    int xMin;
    int xMax;
    int yMin;
    int yMax;

    // Private Class method
    int pnpoly(int nvert, int *vertx, int *verty, int testx, int testy);
    bool isPointAVertex(int x , int y);

public:

    // Public constructor
    Cross(string name, bool containsWarpSpace, int id);

    // Public Class method
    void storeVertices();

    // Overriden methods
    string toString() override;
    double computeArea() override;
    bool isPointInShape(int x, int y) override;
    bool isPointOnShape(int x, int y) override;
    double getArea() override;
};
#endif //CSCI251A2_CROSS_H

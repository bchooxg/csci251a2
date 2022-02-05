//
// Created by bryan on 06/02/22.
//

#ifndef CSCI251A2_RECTANGLE_H
#define CSCI251A2_RECTANGLE_H

#include "ShapeTwoD.h"
#include <vector>

using namespace std;

class Rectangle : public ShapeTwoD{
private:
    static const int RECTANGLEVERTICES = 4;
    int id;

    int xVertices[RECTANGLEVERTICES];
    int yVertices[RECTANGLEVERTICES];

    vector<int> xPerimeterPoints;
    vector<int> yPerimeterPoints;
    vector<int> xShapePoints;
    vector<int> yShapePoints;

    int height ;
    int width ;

    double area;

    int xMin;
    int yMin;
    int xMax;
    int yMax;

public:
    Rectangle(string name, bool containsWarpSpace, int id);
    void storeVertices();
    bool isPointInShape(int x, int y) override;
    bool isPointOnShape(int x, int y) override;
    string toString() override;
    double computeArea() override ;
    double getArea() override;

};

#endif //CSCI251A2_RECTANGLE_H

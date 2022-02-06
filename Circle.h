//
// Created by bryan on 06/02/22.
//

#ifndef CSCI251A2_CIRCLE_H
#define CSCI251A2_CIRCLE_H

#include "ShapeTwoD.h"
#include <vector>

using namespace std;

class Circle : public ShapeTwoD{
private:
    static const int CIRCLEVERTICES = 1;
    const double PI  =3.141592653589793238463;
    int id;

    int xVertices[CIRCLEVERTICES];
    int yVertices[CIRCLEVERTICES];

    vector<int> xPerimeterPoints;
    vector<int> yPerimeterPoints;
    vector<int> xShapePoints;
    vector<int> yShapePoints;

    double radius;

    double area = 0;

    int xMin;
    int yMin;
    int xMax;
    int yMax;


public:
    // Public Constructor
    Circle(string name, bool containsWarpSpace, int id);

    // Class methods
    void storeVertices();

    // Overriden methods
    bool isPointInShape(int x, int y) override;
    bool isPointOnShape(int x, int y) override;
    double computeArea() override;
    string toString() override;
    double getArea() override;

};

#endif //CSCI251A2_CIRCLE_H

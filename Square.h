//
// Created by bryan on 06/02/22.
//

#ifndef CSCI251A2_SQUARE_H
#define CSCI251A2_SQUARE_H

#include "ShapeTwoD.h"
#include <vector>

using namespace std;

class Square : public ShapeTwoD{
private:
    static const int SQUAREVERTICES = 4;
    int id;

    int xVertices[SQUAREVERTICES];
    int yVertices[SQUAREVERTICES];

    vector<int> xPerimeterPoints;
    vector<int> yPerimeterPoints;
    vector<int> xShapePoints;
    vector<int> yShapePoints;

    int height ;
    int width ;

    double area = 0;

    int xMin;
    int yMin;
    int xMax;
    int yMax;

public:

    // Public Constructor
    Square(string name, bool containsWarpSpace, int id);

    // Class methods
    void storeVertices();

    // Overridden methods
    bool isPointInShape(int x, int y) override;
    bool isPointOnShape(int x, int y) override;
    string toString() override;
    double computeArea() override;
    double getArea() override;

};

#endif //CSCI251A2_SQUARE_H

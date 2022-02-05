//
// Created by bryan on 05/02/22.
//

#ifndef CSCI251A2_SHAPETWOD_H
#define CSCI251A2_SHAPETWOD_H

#include <iostream>
using namespace std;


class ShapeTwoD{
protected:
    string name;
    bool containsWarpSpace;

public:
    // Public Constructors
    ShapeTwoD(string name, bool containsWarpSpace);

    // Getter Methods
    string getName();
    bool getContainsWarpSpace();

    // Setter Methods
    void setName(string name);
    void setContainsWarpSpace(bool containsWarpSpace);

    // Virtual Methods
    virtual string toString()=0;
    virtual double computeArea()=0;
    virtual bool isPointInShape(int x, int y)=0;
    virtual bool isPointOnShape(int x, int y)=0;
    virtual double getArea() = 0;

};

#endif //CSCI251A2_SHAPETWOD_H

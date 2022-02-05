//
// Created by bryan on 06/02/22.
//
#include "ShapeTwoD.h"
#include <iostream>
using namespace std;

ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace) {
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
}

string ShapeTwoD::getName() {
    return name;
}

bool ShapeTwoD::getContainsWarpSpace() {
    return containsWarpSpace;
}

void ShapeTwoD::setName(string name) {
    this->name = name;
}

void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace) {
    this->containsWarpSpace = containsWarpSpace;
}
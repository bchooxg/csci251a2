//
// Created by bryan on 06/02/22.
//

#include "Rectangle.h"
#include <sstream>



Rectangle::Rectangle(string name, bool containsWarpSpace, int id) : ShapeTwoD(name, containsWarpSpace) {
    this-> id = id;
}

void Rectangle::storeVertices(){

    xMin = xVertices[0];
    xMax = xVertices[0];
    yMin = yVertices[0];
    yMax = yVertices[0];

    for(int i = 0; i < RECTANGLEVERTICES ; i++){
        int x_ord;
        int y_ord;

        // TODO add exception handling for non int values inserted
        cout <<"Please enter x-ordinate of pt. " << i + 1 << " : ";
        cin >> x_ord;
        cout <<"Please enter y-ordinate of pt. " << i + 1 << " : " ;
        cin >> y_ord;
        cout << endl;
        // To find the min max xy values of the inputs;
        if(i == 0){
            xMin = x_ord;
            xMax = x_ord;
            yMin = y_ord;
            yMax = y_ord; }
        else{
            if(x_ord > xMax){xMax = x_ord;}
            if(x_ord < xMin){xMin = x_ord;}
            if(y_ord > yMax){yMax = y_ord;}
            if(y_ord < yMin){yMin = y_ord;}
        }

        this->xVertices[i] = x_ord;
        this->yVertices[i] = y_ord;
    }

    // Populating points that lie on perimeter & shape
    for(int i = yMin ; i <= yMax; i++){
        for(int j = xMin ; j <= xMax; j++){

            if( isPointOnShape(j, i) ){
                xPerimeterPoints.push_back(j);
                yPerimeterPoints.push_back(i);
            }else if(isPointInShape(j,i)){
                xShapePoints.push_back(j);
                yShapePoints.push_back(i);
            }

        }
    }
}

bool Rectangle::isPointInShape(int x, int y)  {
    if( x != xMin &&  x != xMax && y != yMin && y != yMax){
        return true;
    }else{
        return false;
    }
}

bool Rectangle::isPointOnShape(int x, int y)  {

    // To check if point is a vertex
    if( (x == xMin || x == xMax) && (y == yMin || y == yMax)){
        return false;
    }

    //  To check if points is along the width
    if(y == yMin || y == yMax){
        return true;
    }
        // To check if point is along the height
    else if( x == xMin || x == xMax){
        return true;
    }
    else{
        return false;
    }
}

string Rectangle::toString()  {
    stringstream ss;
    ss << endl;
    ss << "Shape [" << to_string(id) << "]" << endl;
    ss << "Name   : " << name << endl;
    ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
    if(area > 0){
        ss << "Area : " << area << " units square" << endl;
    }else{
        ss << "Area : " <<  "Not Computed yet" << endl;
    }
    ss << "Vertices : "<< endl;

    for(int i = 0; i < RECTANGLEVERTICES; i++){
        ss << "Point [" << i << "] : (" << xVertices[i] << ", "<< yVertices[i] <<")" << endl;
    }
    ss << "Points on perimeter : ";
    if(xPerimeterPoints.size() == 0){ ss << "none!";}
    for(int i = 0; i < xPerimeterPoints.size(); i++){
        if(i != 0){
            ss << ", ";
        }
        ss << "(" << xPerimeterPoints.at(i) << ", " << yPerimeterPoints.at(i) << ")";
    }

    ss << endl << "Points within shape : ";
    if(xShapePoints.size() == 0){ ss << "none!";}
    for(int i = 0; i < xShapePoints.size(); i++){
        if(i != 0){
            ss << ", ";
        }
        ss << "(" << xShapePoints.at(i) << ", " << yShapePoints.at(i) << ")";
    }

    return ss.str();
}

double Rectangle::computeArea()  {

    // Populating area
    this->width = xMax - xMin;
    this->height = yMax - yMin;

    double area = height * width;
    this->area = area;

    return area;
}

double Rectangle::getArea() {
    return area;
}

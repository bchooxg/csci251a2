//
// Created by bryan on 06/02/22.
//

#include "Circle.h"
#include <math.h>
#include <sstream>

Circle::Circle(string name, bool containsWarpSpace, int id) : ShapeTwoD(name, containsWarpSpace) {
    this->id = id;
}

void Circle::storeVertices(){
    for(int i = 0; i < CIRCLEVERTICES ; i++){
        int x_ord;
        int y_ord;

        // TODO add exception handling for non int values inserted
        cout << "Please enter x-ordinate of center : ";
        cin >> x_ord ;
        cout << "Please enter y-ordinate of center : ";
        cin >> y_ord;
        cout << "Please enter radius (units) : " ;
        cin >> radius;

        this->xVertices[i] = x_ord;
        this->yVertices[i] = y_ord;
    }

    // To get points within the circle
    // Creates a square surrounding the circle and checks each point if its in the circle.

    // To compute the points of the circle
    xMin = xVertices[0] - radius;
    yMin = yVertices[0] - radius;

    xMax = xVertices[0] + radius;
    yMax = yVertices[0] + radius;

    for(int i = yMin; i <= yMax; i++){
        for(int j = xMin; j <= xMax;j++){

            // To ignore center
            if(i == yVertices[0] && j == xVertices[0]){
                continue;
            }else{
                if(isPointOnShape(j,i)){
                    xPerimeterPoints.push_back(j);
                    yPerimeterPoints.push_back(i);
                }
                else if(isPointInShape(j,i)){
                    xShapePoints.push_back(j);
                    yShapePoints.push_back(i);
                }

            }

        }
    }
}

bool Circle::isPointInShape(int x, int y) {
    // Uses pythagoras theorem to find distance from the center
    // a^2  + b^2 = c^2
    // If c < radius , point is in shape
    double result = sqrt( pow((x - xVertices[0]),2.0) + pow((y - yVertices[0]),2.0 ) )  ;
    return result < radius;
}

bool Circle::isPointOnShape(int x, int y)  {
    // Uses pythagoras theorem to find distance from the center
    // a^2  + b^2 = c^2
    // If c = radius , point is on shape
    double result = sqrt( pow((x - xVertices[0]),2.0) + pow((y - yVertices[0]),2.0 ) )  ;
    return result == radius;
}

double Circle::computeArea()  {

    // To compute the area of the circle and store it in
    double area = PI * radius * radius;
    this->area = area;
    return area ;
}

string Circle::toString()  {
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

    for(int i = 0; i < CIRCLEVERTICES; i++){
        ss << "Point [" << i << "] : (" << xVertices[i] << ", "<< yVertices[i] <<")" << endl;
    }
    ss << endl;

    ss  << "Points on perimeter : ";
    if(xPerimeterPoints.size() == 0){ ss << "none!";}
    for(int i = 0; i < xPerimeterPoints.size(); i++){
        if(i != 0){
            ss << ", ";
        }
        ss << "(" << xPerimeterPoints.at(i) << ", " << yPerimeterPoints.at(i) << ")";
    }
    ss << endl;

    ss << "Points within shape : ";
    if(xShapePoints.size() == 0){ ss << "none!";}
    for(int i = 0; i < xShapePoints.size(); i++){
        if(i != 0){
            ss << ", ";
        }
        ss << "(" << xShapePoints.at(i) << ", " << yShapePoints.at(i) << ")";
    }
    ss << endl;

    return ss.str();
}

double Circle::getArea() {
    return area;
}

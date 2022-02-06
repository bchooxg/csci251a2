//
// Created by bryan on 06/02/22.
//

#include <sstream>
#include "Cross.h"

int Cross::pnpoly(int nvert, int *vertx, int *verty, int testx, int testy) {
    // Helper function using ray tracing algorithm to find if the point lies within a polygon
    // c value switches between 1 and 0 based on how many times it crosses a line
    // If it is 1 it means that it is within the shape
    int i, j, c = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((verty[i]>testy) != (verty[j]>testy)) &&
             (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
            c = !c;
    }
    return c;
}

bool Cross::isPointAVertex(int x , int y){
    // Loops through all vertices and checks if a given point is a vertex
    for(int i = 0; i < CROSSVERTICES; i++){
        if(x == xVertices[i] && y == yVertices[i]){
            return true;
        }
    }
    return false;
}

Cross::Cross(string name, bool containsWarpSpace, int id) : ShapeTwoD(name, containsWarpSpace) {
    this->id = id;
}

void Cross::storeVertices(){

    xMin = xVertices[0];
    xMax = xVertices[0];
    yMin = yVertices[0];
    yMax = yVertices[0];

    for(int i = 0; i < CROSSVERTICES ; i++){
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

    // Populates perimeter points and shape points
    for(int i = yMin; i < yMax; i++){
        for(int j = xMin; j < xMax; j++){
            if(isPointAVertex(j,i)){
                continue;
            }else if(isPointOnShape(j,i)){
                xPerimeterPoints.push_back(j);
                yPerimeterPoints.push_back(i);
            }else if(isPointInShape(j,i)){
                xShapePoints.push_back(j);
                yShapePoints.push_back(i);
            }
        }
    }
}

string Cross::toString() {
    stringstream ss;
    ss << endl;
    ss << "Shape [" << to_string(id) << "]" << endl;
    ss << "Name   : " << name << endl;
    ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;

    if(area > 0){
        ss << "Area : " << area << " units square" << endl;
    }else{
        ss << "Area : " <<  "Not Computed yet" << endl;
    }        ss << "Vertices : "<< endl;

    for(int i = 0; i < CROSSVERTICES; i++){
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

double Cross::computeArea() {
    // Using shoelace formula in order to determine the area of any polygon

    // Initialize area
    double area = 0.0;

    // Calculate value of shoelace formula
    int j = CROSSVERTICES - 1;
    for (int i = 0; i < CROSSVERTICES; i++)
    {
        area += (xVertices[j] + xVertices[i]) * (yVertices[j] - yVertices[i]);
        j = i;  // j is previous vertex to i
    }

    // Return absolute value
    area = abs(area / 2.0);
    this->area = area;

    return area;
}

bool Cross::isPointInShape(int x, int y) {
    // If the result = 1 , it means that the point is in the shape since it only passes an edge once

    int result = pnpoly(CROSSVERTICES, xVertices, yVertices, x, y);

    if(result == 1){
        return true;
    }

    return false;
}

bool Cross::isPointOnShape(int x, int y) {
    // Loop through all vertices
    // Compare if the point lies between the two vertices

    for(int i = 1; i < CROSSVERTICES; i++){
        // Get the first point
        int x1 = xVertices[i-1];
        int y1 = yVertices[i-1];

        // Get the second point
        int x2 = xVertices[i];
        int y2 = yVertices[i];

        // Value of the distance between two vertices;
        int distance;

        if(x1 == x2){
            int tempY1;
            int tempY2;

            if(y1 > y2){
                tempY1 = y2;
                tempY2 = y1;
            }else{
                tempY1 = y1;
                tempY2 = y2;
            }

            distance = tempY2 - tempY1;

            if(distance > 1){

                for(int j = tempY1 + 1; j < tempY2; j++){
                    if(x == x1 && y == j){
                        return true;
                    }
                }
            }

        }else if(y1 == y2){
            int tempX1;
            int tempX2;

            if(x1 > x2){
                tempX1 = x2;
                tempX2 = x1;
            }else{
                tempX1 = x1;
                tempX2 = x2;
            }

            distance = tempX2 - tempX1;

            if(distance > 1){

                for(int j = tempX1 + 1; j < tempX2; j++){
                    if(y == y1 && x == j){
                        return true;
                    }
                }
            }

        }
    }
    return false;
}

double Cross::getArea() {
    return area;
}

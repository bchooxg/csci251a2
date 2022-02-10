#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

#include "ShapeTwoD.h"
#include "Cross.h"
#include "Square.h"
#include "Circle.h"
#include "Rectangle.h"


using namespace std;


int displayMenu(){

    /*
        Function Displays the relevant menu to the user in terminal
        And returns the value of the choice that they have entered
    */

    const int headingWidth = 15;
    const int optionWidth = 5;

    cout << endl;
    cout << left << setw(headingWidth) << "Student ID ";
    cout << ": " << "7060452" << endl ;

    cout << setw(headingWidth) << "Student Name ";
    cout << ": " << "Bryan Choo" << endl ;

    cout << "-----------------------------------------" << endl;


    cout << "Welcome to Assn2 program!" << endl << endl;

    for(int i = 1; i <= 5; i ++){
        cout << left << setw(optionWidth) << to_string(i) + ")";
        switch (i){
            case 1:
                cout << "Input sensor data";
                break;
            case 2:
                cout << "Compute area (for all records)";
                break;
            case 3:
                cout << "Print shapes report";
                break;
            case 4:
                cout << "Sort shapes data";
                break;
            case 5:
                cout << "Exit Program";
        }
        cout << endl;
    }

    cout << endl ;
    cout << "Please enter your choice : ";
    int choice ;

    cin >> choice;
    while( !(choice >= 1 && choice <= 5) ){
        cout << "Invalid Value, Please select value within 1-5" << endl;
        cin.clear();
        cin.ignore(100,'\n');
        cin >> choice;
    }

    cout << endl;
    return choice;

}

int getShapeInput(ShapeTwoD* allShapes[], int &shapesCount){

    // Gets input from user

    cout << "[ Input sensor data ]" << endl;

    string shapeType;
    string specialType;
    ShapeTwoD* temp;

    cout << "Please enter name of shape : ";
    cin >> shapeType;

    cout << "Please enter special type : ";
    cin >> specialType;
    cout << endl;

    bool containsWarpSpace ;

    // Checks for valid warp space text
    if(specialType == "WS"){
        containsWarpSpace = true;
    }else if(specialType == "NS") {
        containsWarpSpace = false;
    }else{
        cout << "Invalid special type. Please enter [WS/NS]" << endl;
        return 1;
    }

    // Checks the shape that user has entered and calls the relevant constructor
    if(shapeType == "Circle"){
        Circle * c = new Circle(shapeType, containsWarpSpace, shapesCount);
        c->storeVertices();
        temp = c;

    }else if(shapeType == "Square"){
        Square * s = new Square(shapeType, containsWarpSpace, shapesCount);
        s->storeVertices();
        temp = s;

    }else if(shapeType == "Rectangle"){
        Rectangle * r = new Rectangle(shapeType , containsWarpSpace, shapesCount);
        r->storeVertices();
        temp = r;
    }else if(shapeType == "Cross") {
        Cross *c = new Cross(shapeType, containsWarpSpace, shapesCount);
        c->storeVertices();
        temp = c;
    }else{
        cout << endl << "Invalid Shape Name. Please try again" << endl;
        return 1;
    }

    // Adds the shape to the vector
//    v.push_back(temp);
    allShapes[shapesCount++] = temp;
    cout << endl << "Record successfully stored. Going back to main menu ..." << endl;
    return 0;

}

void printShapesReport(ShapeTwoD* a[], int &shapesCount){

    cout << "Total no. of records available : " << shapesCount << endl;

    double sum=0;
    for(int i = 0; i < shapesCount; i++){
        cout << endl;
        cout << a[i]->toString();
        sum += a[i]->getArea();
    }

    // Additional Feature
    if(shapesCount > 2 && sum > 0){
        cout << endl << endl << "Average size of shapes : " << sum/shapesCount << " units square" << endl;
    }


    cout << endl << endl << "All shapes displayed. Going back to main menu ... " << endl;



}

void computeShapes(ShapeTwoD* a[], int shapesCount, int & computedShapes){
    // Loops through all shapes
    int updatedShapes = 0;

    for(int i = 0; i < shapesCount; i++){
        if(a[i]->getArea() == 0){
            a[i]->computeArea();
            updatedShapes++;
        }
    }

    // Updates external variable
    computedShapes = shapesCount;

    if(updatedShapes == 0){
        cout << "All shape areas are already computed! [" << computedShapes << " shapes]"<<  endl;
    }else{
        cout << "Computation Completed! ( " <<  updatedShapes << " records were updated )" << endl;
    }
}

int sortShapes(const string& sortType, ShapeTwoD* allShapes[], int &shapesCount){

    // Special handling for special sort that will exit function early

    if(sortType == "SPECIAL"){

        // Initialize separate vectors for Warp Space and normal space
        vector<ShapeTwoD * > tempWSVec;
        vector<ShapeTwoD * > tempNSVec;

        // Populates the WS and NS vectors above
        for(int i = 0; i < shapesCount; i ++){
            if(allShapes[i]->getContainsWarpSpace()){
                tempWSVec.push_back(allShapes[i]);
            }else{
                tempNSVec.push_back(allShapes[i]);
            }
        }

        // Sort the both vectors in desc order
        sort(tempWSVec.begin(), tempWSVec.end(),
             [](ShapeTwoD * shape1 , ShapeTwoD * shape2){
                 return shape1->getArea() > shape2->getArea();
             });

        sort(tempNSVec.begin(), tempNSVec.end(),
             [](ShapeTwoD * shape1 , ShapeTwoD * shape2){
                 return shape1->getArea()  > shape2->getArea();
             });

        // Prints warp space vectors first followed by normal space
        for(int i = 0; i < tempWSVec.size(); i++){
            cout << endl << tempWSVec.at(i)->toString();
        }
        for(int i = 0; i < tempNSVec.size(); i++){
            cout << endl << tempNSVec.at(i)->toString();
        }
        return 0;
    }

    // Initialize temp vector that will be rearranged according to the sort
    vector<ShapeTwoD * > tempVec;

    // Populates the temporary vector
    for(int i = 0; i < shapesCount; i++){
        tempVec.push_back(allShapes[i]);
    }

    if(sortType == "ASC"){
        // Sorts temp vec in ascending order
        sort(tempVec.begin(), tempVec.end(),
             [](ShapeTwoD * shape1 , ShapeTwoD * shape2){
                 return shape1->getArea() < shape2->getArea();
             });

    }else if(sortType == "DSC"){
        // Sorts temp vec in descending order
        sort(tempVec.begin(), tempVec.end(),
             [](ShapeTwoD * shape1 , ShapeTwoD * shape2){
                 return shape1->getArea() > shape2->getArea();
             });
    }

    // Prints out temp vec
    for(int i = 0; i < tempVec.size(); i ++){
        cout << endl << tempVec.at(i)->toString();
    }
    return 0;
}

int sortShapesData(ShapeTwoD* a[], int &shapesCount, int & computedShapes ){

    // Check the size of the vector to make sure there is enough shapes to sort

    if(shapesCount < 2){
        cout << endl;
        cout << "Please add at least 2 shapes before attempting to sort" << endl;
        return 1;
    }
    if(computedShapes != shapesCount){
        cout << "Please compute the areas of all shapes before performing sort operations" << endl;
        return 1;
    }

    cout << "\ta)\tSort by area (ascending)" << endl;
    cout << "\tb)\tSort by area (descending)" << endl;
    cout << "\tc)\tSort by special type and area" << endl;

    cout << endl;

    while(true){

        // Prompt for user input
        cout << "Please select sort option ('q' to go back to main menu) : ";
        char choice;

        cin >> choice;

        if(choice == 'q'){
            break;
        }else if(choice == 'a'){
            sortShapes("ASC", a, shapesCount);
            break;
        }else if(choice == 'b'){
            sortShapes("DSC", a , shapesCount);
            break;
        }else if(choice == 'c'){
            sortShapes("SPECIAL", a, shapesCount);
            break;
        }else{
            cout << endl << "Choice is invalid please try again" << endl << endl;
        }
    }
    cout << endl << endl << "Going back to main menu ... " << endl;
    return 0;
}



int main() {
    vector<ShapeTwoD* > allShapes;
    ShapeTwoD *shapeArr[100];

    bool running = true;
    int shapesCount = 0;
    int computedShapes = 0;

    while(running){
        int choice = displayMenu();
        switch (choice) {
            case 1:
                getShapeInput(shapeArr, shapesCount);
                break;
            case 2:
                computeShapes(shapeArr, shapesCount, computedShapes);
                break;
            case 3:
                printShapesReport(shapeArr, shapesCount);
                break;
            case 4:
                sortShapesData(shapeArr,shapesCount, computedShapes);
                break;
            case 5:
                for (auto v : allShapes)
                {
                    delete v;
                }
                cout << "Exiting Program ... " << endl;
                running = false;
                break;
            default:
                cout << endl << "Invalid choice. Please enter a num [1-5]" << endl;
                break;
        }
    }
}

#include <iostream>
#include <numbers>
#include <vector>

using namespace std;

class ShapeTwoD{
protected:
    string name;
    bool containsWarpSpace;
public:
    // Public Constructors
    ShapeTwoD(string name, bool containsWarpSpace){
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
    }
    // Getter Methods
    string getName() const {
        return name;
    }

    bool isContainsWarpSpace() const {
        return containsWarpSpace;
    }

    // Setter Methods
    void setName(string name) {
        this->name = name;
    }

    void setContainsWarpSpace(bool containsWarpSpace) {
        this->containsWarpSpace = containsWarpSpace;
    }
    // Virtual Methods
    virtual string toString()=0;
    virtual double computeArea()=0;
    virtual bool isPointInShape(int x, int y)=0;
    virtual bool isPointOnShape(int x, int y)=0;


};

class Cross : ShapeTwoD{
protected:
    static const int CROSSVERTICES = 12;
    int x_ords[CROSSVERTICES];
    int y_ords[CROSSVERTICES];
    int xyVertices[CROSSVERTICES * 2];
    // [x, y, x, y, x, y]
    double area;

public:
    Cross(string name, bool containsWarpSpace) : ShapeTwoD(name, containsWarpSpace) {

    }

    void setXYords(){
        for(int i = 1; i < CROSSVERTICES * 2; i += 2){
            int x_ord;
            int y_ord;

            cout << "Please enter x-ordinate of pt. " << i + 1 << endl;
            cin >> x_ord;
            cout << "Please enter y-ordinate of pt. " << i + 1 << endl;
            cin >> y_ord;

            this->xyVertices[i-1] = x_ord; // Sets x vertice
            this->xyVertices[i] = y_ord;
        }
    }
    string toString() override {
        return std::string();
    }

    double computeArea() override {
        return 0;
    }

    bool isPointInShape(int x, int y) override {
        return false;
    }

    bool isPointOnShape(int x, int y) override {
        return false;
    }

};

class Square : ShapeTwoD{
private:
    static const int SQUAREVERTICES = 4;
    int vertices[SQUAREVERTICES * 2];
    int x_ords[SQUAREVERTICES];
    int y_ords[SQUAREVERTICES];
};

class Circle : ShapeTwoD{
private:
    static const int CIRCLEVERTICES = 1;
    int xVertices[CIRCLEVERTICES];
    int yVertices[CIRCLEVERTICES];
    int x_ords[CIRCLEVERTICES];
    int y_ords[CIRCLEVERTICES];
    double area;
    int radius;
    const int pi = 3.14159265358979323846;
public:
    Circle(const string &name, bool containsWarpSpace) : ShapeTwoD(name, containsWarpSpace) {

    }

    void storeVertices(){
        for(int i = 0; i < CIRCLEVERTICES ; i++){
            int x_ord;
            int y_ord;

            // TODO add exception handling for non int values inserted
            cout << "\nPlease enter x-ordinate of center : ";
            cin >> x_ord ;
            cout << "\nPlease enter y-ordinate of center : ";
            cin >> y_ord;
            cout << "Please enter radius (units) :" << endl;
            cin >> radius;

            this->xVertices[i] = x_ord;
            this->yVertices[i] = y_ord;
        }
    }

    void storeArea() {
        this->area = computeArea();
    }

    double computeArea() override {
        return pi * radius * radius;
    }

};

class Rectangle : ShapeTwoD{
private:
    static const int RECTANGLEVERTICES = 4;

    int xVertices[RECTANGLEVERTICES];
    int yVertices[RECTANGLEVERTICES];

    vector<int> xPerimeterPoints;
    vector<int> yPerimeterPoints;
    vector<int> xShapePoints;
    vector<int> yShapePoints;

    int height ;
    int width ;

    int xMin;
    int yMin;
    int xMax;
    int yMax;

    double area;
    int x_ords[RECTANGLEVERTICES];
    int y_ords[RECTANGLEVERTICES];
public:

    void storeVertices(){

        xMin = xVertices[0];
        xMax = xVertices[0];
        yMin = yVertices[0];
        yMax = yVertices[0];

        for(int i = 0; i < RECTANGLEVERTICES ; i++){
            int x_ord;
            int y_ord;

            // TODO add exception handling for non int values inserted
            cout << "\nPlease enter x-ordinate of pt. " << i + 1 << ": ";
            cin >> x_ord ;
            cout << "\nPlease enter y-ordinate of pt. " << i + 1 << ": ";
            cin >> y_ord;

            // To find the min max xy values of the inputs;
            if(i == 0){
                xMin = x_ord;
                xMax = x_ord;
                yMin = y_ord;
                yMax = y_ord;            }
            else{
                if(x_ord > xMax){xMax = x_ord;}
                if(x_ord < xMin){xMin = x_ord;}
                if(y_ord > yMax){yMax = y_ord;}
                if(y_ord < yMin){yMax = y_ord;}
            }

            this->xVertices[i] = x_ord;
            this->yVertices[i] = y_ord;
        }
    }

    void computePerimeter(){

        // Bottom left vertex
        int x = xMin;
        int y = yMin;

        // Need to implement point on shape ?
        // Change to compute points
        // Loop through all points in the array
        // Check if they are surface or points

        for(int i = yMin; i < yMax; i++){
            for(int j = xMin; j < xMax; j++){

                // Identify if this point is a vertex
                if( (i == yMin || i == yMax) && (j != xMin && j != xMax) ){
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


//        // Find points along the width of the rectangle
//        for(int i = xMin; i < xMax; i++){
//            if(i != xMin ){
//
//                xPerimeterPoints.push_back(i);
//                yPerimeterPoints.push_back(yMin);
//
//                xPerimeterPoints.push_back(i);
//                yPerimeterPoints.push_back(yMax);
//
//            }
//        }
//        // Find points along the height of the rectangle
//        for(int i = yMin; i < yMax; i++){
//            if(i != yMin ){
//
//                yPerimeterPoints.push_back(i);
//                xPerimeterPoints.push_back(xMin);
//
//                yPerimeterPoints.push_back(i);
//                xPerimeterPoints.push_back(xMax);
//            }
//        }


    }

    void computeInternal(){

    }

    bool isPointInShape(int x, int y) override {
        if( x != xMin &&  x != xMax && y != yMin && y != yMax){
            return true;
        }else{
            return false;
        }
    }

    bool isPointOnShape(int x, int y) override {
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

public:

    void computeLengthWidth(){
        this->width = abs(xVertices[0] - xVertices[3]); // Maybe refactor to use xmin xmax
        this->height = abs(yVertices[0] - yVertices[3]);

    }

    double computeArea() override {
        return height * width;
    }

    void storeArea(){
        this->area = computeArea();
    }
};

int main() {
    cout << "Hello, World!" << std::endl;
    return 0;
}

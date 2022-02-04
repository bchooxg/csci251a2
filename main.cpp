#include <iostream>
#include <iomanip>
#include <numbers>
#include <vector>
#include <sstream>
#include <cmath>


using namespace std;

class ShapeTwoD{
protected:
    string name;
    bool containsWarpSpace;
    int counter = 0;
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

class Cross : public ShapeTwoD{
private:
    static const int CROSSVERTICES = 12;
    int id;

    int xVertices[CROSSVERTICES];
    int yVertices[CROSSVERTICES];

    vector<int> xPerimeterPoints;
    vector<int> yPerimeterPoints;
    vector<int> xShapePoints;
    vector<int> yShapePoints;

    // [x, y, x, y, x, y]
    double area;
    int xMin;
    int xMax;
    int yMin;
    int yMax;

public:
    Cross(string name, bool containsWarpSpace, int id) : ShapeTwoD(name, containsWarpSpace) {
        this->id = id;
    }

    void storeVertices(){

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

    string toString() override {
        stringstream ss;
        string temp = "";
        ss << "Shape [" << to_string(id) << "]" << endl;
        ss << "Name   : " << name << endl;
        ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
        if(area > 0){
            ss << "Area : " << area << " units sqaure" << endl;
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

    double computeArea() override {
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

private: int pnpoly(int nvert, int *vertx, int *verty, int testx, int testy){
        // Helper function using ray tracing algorithm to find if the point lies within a polygon
        // c value switches between 1 and 0 based on how many times it crosses a vertice
        // If it is 1 it means that it is within the shape
        int i, j, c = 0;
        for (i = 0, j = nvert-1; i < nvert; j = i++) {
            if ( ((verty[i]>testy) != (verty[j]>testy)) &&
                 (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
                c = !c;
        }
        return c;
    }

    bool isPointAVertex(int x , int y){
        for(int i = 0; i < CROSSVERTICES; i++){
            if(x == xVertices[i] && y == yVertices[i]){
                return true;
            }
        }
        return false;
    }

    bool isPointInShape(int x, int y) override {

        int result = pnpoly(CROSSVERTICES, xVertices, yVertices, x, y);

        if(result == 1){
            return true;
        }

        return false;
    }

    bool isPointOnShape(int x, int y) override {
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

};

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

    double area;

    int xMin;
    int yMin;
    int xMax;
    int yMax;

public:

    Square(string name, bool containsWarpSpace, int id) : ShapeTwoD(name, containsWarpSpace) {
        this-> id = id;
    }

    void storeVertices(){

        xMin = xVertices[0];
        xMax = xVertices[0];
        yMin = yVertices[0];
        yMax = yVertices[0];

        for(int i = 0; i < SQUAREVERTICES ; i++){
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

    bool isPointInShape(int x, int y) override {
        if( x != xMin &&  x != xMax && y != yMin && y != yMax){
            return true;
        }else{
            return false;
        }
    }

    bool isPointOnShape(int x, int y) override {

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

    string toString() override {
        stringstream ss;
        string temp = "";
        ss << "Shape [" << to_string(id) << "]" << endl;
        ss << "Name   : " << name << endl;
        ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
        if(area > 0){
            ss << "Area : " << area << " units sqaure" << endl;
        }else{
            ss << "Area : " <<  "Not Computed yet" << endl;
        }
        ss << "Vertices : "<< endl;

        for(int i = 0; i < SQUAREVERTICES; i++){
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

    double computeArea() override {


        // Populating area
        this->width = xMax - xMin;
        this->height = yMax - yMin;

        double area = height * width;
        this->area = area;

        return area;
    }

};

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

    double area;

    int xMin;
    int yMin;
    int xMax;
    int yMax;


public:
    Circle(string name, bool containsWarpSpace, int id) : ShapeTwoD(name, containsWarpSpace) {
        this->id = id;
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

    bool isPointInShape(int x, int y) override {
        // Uses pythagoras theorem to find distance from the center
        // a^2  + b^2 = c^2
        double result = sqrt( pow((x - xVertices[0]),2.0) + pow((y - yVertices[0]),2.0 ) )  ;
        return result < radius;
    }

    bool isPointOnShape(int x, int y) override {
        double result = sqrt( pow((x - xVertices[0]),2.0) + pow((y - yVertices[0]),2.0 ) )  ;
        return result == radius;
    }

    double computeArea() override {

        // To compute the area of the circle and store it in
        double area = PI * radius * radius;
        this->area = area;
        return area ;
    }

    string toString() override {
        stringstream ss;
        string temp = "";
        ss << "Shape [" << to_string(id) << "]" << endl;
        ss << "Name   : " << name << endl;
        ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
        if(area > 0){
            ss << "Area : " << area << " units sqaure" << endl;
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

};

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

    Rectangle(string name, bool containsWarpSpace, int id) : ShapeTwoD(name, containsWarpSpace) {
        this-> id = id;
    }

    void storeVertices(){

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

    bool isPointInShape(int x, int y) override {
        if( x != xMin &&  x != xMax && y != yMin && y != yMax){
            return true;
        }else{
            return false;
        }
    }

    bool isPointOnShape(int x, int y) override {

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

    string toString() override {
        stringstream ss;
        string temp = "";
        ss << "Shape [" << to_string(id) << "]" << endl;
        ss << "Name   : " << name << endl;
        ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
        if(area > 0){
            ss << "Area : " << area << " units sqaure" << endl;
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

    double computeArea() override {

        // Populating area
        this->width = xMax - xMin;
        this->height = yMax - yMin;

        double area = height * width;
        this->area = area;

        return area;
    }

};

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

    for(int i = 1; i <= 4; i ++){
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
        }
        cout << endl;
    }

    cout << endl ;
    cout << "Please enter your choice : ";
    int choice ;

    cin >> choice;
    while( !(choice >= 1 && choice <= 4) ){
        cout << "Invalid Value, Please select value within 1-4" << endl;
        cin.clear();
        cin.ignore(100,'\n');
        cin >> choice;
    }

    cout << endl;
    return choice;

}

int getShapeInput(vector<ShapeTwoD*> &v, int &shapesCount){
    cout << endl;
    cout << "[ Input sensor data ]" << endl;

    string shapeType;
    string specialType;
    ShapeTwoD* temp;

    cout << "Please enter name of shape : ";
    cin >> shapeType;
    cout << "Please enter special type : ";
    cin >> specialType;

    bool containsWarpSpace = specialType == "WS";

    if(shapeType == "Circle"){
        Circle * c = new Circle(shapeType, containsWarpSpace, shapesCount++);
        c->storeVertices();
        temp = c;

    }else if(shapeType == "Square"){
        Square * s = new Square(shapeType, containsWarpSpace, shapesCount++);
        s->storeVertices();
        temp = s;

    }else if(shapeType == "Rectangle"){
        Rectangle * r = new Rectangle(shapeType , containsWarpSpace, shapesCount++);
        r->storeVertices();
        temp = r;
    }else if(shapeType == "Cross") {
        Cross *c = new Cross(shapeType, containsWarpSpace, shapesCount++);
        c->storeVertices();
        temp = c;
    }else{
        cout << endl << "Invalid Shape Name. Please try again" << endl;
        return 1;
    }

    v.push_back(temp);
    cout << endl << "Record successfully stored. Going back to main menu ..." << endl;
    return 0;

}

void printShapesReport(vector<ShapeTwoD*> &v){

    cout << "Total no. of records available : " << v.size() << endl;

    for(int i = 0; i < v.size(); i++){
        cout << endl;
        cout << v.at(i)->toString();
    }

    cout << endl << endl << "All shapes displayed. Going back to main menu ... " << endl;



}

void computeShapes(vector<ShapeTwoD*> &v){
    for(int i = 0; i < v.size(); i++){
        v.at(i)->computeArea();
    }

    cout << "Computation Completed! ( " <<  v.size() << " records were updated )" << endl;
}


int main() {
    vector<ShapeTwoD* > allShapes;
    bool running = true;
    int shapesCount = 0;

    while(running){
        int choice = displayMenu();
        switch (choice) {
            case 1:
                getShapeInput(allShapes, shapesCount);
                break;
            case 2:
                computeShapes(allShapes);
                break;
            case 3:
                printShapesReport(allShapes);
                break;
            case 4:
                break;
        }
    }

//    Rectangle r = Rectangle("Rectangle", false);
//    cout << r.toString();
//    allShapes.push_back(&r);

    return 0;
}

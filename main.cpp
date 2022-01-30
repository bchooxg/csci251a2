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

    Square(string name, bool containsWarpSpace) : ShapeTwoD(name, containsWarpSpace) {
        this-> id = counter;
        counter++;
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
        ss << "Area : " << area << " units sqaure" << endl;
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

        // Bottom left vertex
        int x = xMin;
        int y = yMin;

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
    Circle(string name, bool containsWarpSpace) : ShapeTwoD(name, containsWarpSpace) {
        this->id = counter;
        counter++;
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

    bool isPointInShape(int x, int y) override {
        // Uses pythagoras theorem to find distance from the center
        // a^2  + b^2 = c^2
        double result = sqrt( pow((x - xVertices[0]),2.0) + pow((y - yVertices[0]),2.0 ) )  ;
        cout << "IS POINT IN SHAPE ? " << endl;
        cout << "X : " << x << ", Y : " << y << endl;
        cout << "Radius : " << radius << endl;
        cout << "Result : " << result << endl;
        cout << "T OR F : " << ((result < radius)?"T": "F") << endl;
        return result < radius;
    }

    bool isPointOnShape(int x, int y) override {
        double result = sqrt( pow((x - xVertices[0]),2.0) + pow((y - yVertices[0]),2.0 ) )  ;
        cout << "IS POINT ON SHAPE ? " << endl;
        cout << "X : " << x << ", Y : " << y << endl;
        cout << "Radius : " << radius << endl;
        cout << "Result : " << result << endl;
        cout << "T OR F : " << ((result == radius)?"T": "F") << endl;
        return result == radius;
    }

    double computeArea() override {

        // To compute the points of the circle
        xMin = xVertices[0] - radius;
        yMin = yVertices[0] - radius;

        xMax = xVertices[0] + radius;
        yMax = yVertices[0] + radius;

//        // To get the points on the perimeter [ North south east west ]
//        const int m = 4;
//        int radiusToInt = int(radius);
//        int xMovements[m] ={0,0,radiusToInt,-radiusToInt};
//        int yMovements[m] ={radiusToInt,-radiusToInt,0,0};
//
//        for(int i = 0; i < m; i++){
//            xPerimeterPoints.push_back(xVertices[0] + xMovements[i]);
//            yPerimeterPoints.push_back(yVertices[0] + yMovements[i]);
//        }


        // To get points within the circle
        // Creates a square surrounding the circle and checks each point if its in the circle.
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
        ss << "Area : " << area << " units sqaure" << endl;
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

    Rectangle(string name, bool containsWarpSpace) : ShapeTwoD(name, containsWarpSpace) {
        this-> id = counter;
        counter++;
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
        ss << "Area : " << area << " units sqaure" << endl;
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

        // Bottom left vertex
        int x = xMin;
        int y = yMin;

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

void getShapeInput(vector<ShapeTwoD*> &v){
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

    if(shapeType == "Cross"){
        ;
    }else if(shapeType == "Circle"){
        Circle * c = new Circle(shapeType, containsWarpSpace);
        c->storeVertices();
        temp = c;

    }else if(shapeType == "Square"){
        Square * s = new Square(shapeType, containsWarpSpace);
        s->storeVertices();
        temp = s;

    }else if(shapeType == "Rectangle"){
        Rectangle * r = new Rectangle(shapeType , containsWarpSpace );
        r->storeVertices();
        temp = r;
    }

    v.push_back(temp);
    cout << endl << "Record successfully stored. Going back to main menu ..." << endl;

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
    bool computed = false;

    while(running){
        int choice = displayMenu();
        switch (choice) {
            case 1:
                getShapeInput(allShapes);
                computed = false;
                break;
            case 2:
                computeShapes(allShapes);
                computed = true;
                break;
            case 3:
                if(computed){
                    printShapesReport(allShapes);
                }else{
                    cout << "Please compute area before generating report" << endl ;
                }
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

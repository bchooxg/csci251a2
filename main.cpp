#include <iostream>

using namespace std;

class ShapeTwoD{
private:
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
            cin >> y_ord;

            this->xVertices[i] = x_ord;
            this->yVertices[i] = y_ord;
        }
    }

    double computeArea() override {
        // get pi and compute area and store
    }

};

class Rectangle : ShapeTwoD{
private:
    static const int RECTANGLEVERTICES = 4;
    int vertices[RECTANGLEVERTICES * 2];
    int x_ords[RECTANGLEVERTICES];
    int y_ords[RECTANGLEVERTICES];
};

int main() {
    cout << "Hello, World!" << std::endl;
    return 0;
}

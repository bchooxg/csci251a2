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

    virtual string toString(){
        return "";
    }
    // Setter Methods
    void setName(string name) {
        this->name = name;
    }

    void setContainsWarpSpace(bool containsWarpSpace) {
        this->containsWarpSpace = containsWarpSpace;
    }
    // Virtual Methods
    virtual double computeArea()=0;
    virtual bool isPointInShape(int x, int y)=0;
    virtual bool isPointOnShape(int x, int y)=0;


};

class Cross{

};

class Square{

};

class Circle{

};

class Rectangle{

};

int main() {
    cout << "Hello, World!" << std::endl;
    return 0;
}

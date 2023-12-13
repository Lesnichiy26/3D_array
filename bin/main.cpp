#include "lib/Cube.h"
#include <iostream>
#include <fstream>

//using namespace std;
int main() {
    Cube cube = Cube::MakeArray(3, 3, 3);
    cube[0][1][2] = 123;
    cube[0][1][1] = 555;
    std::cout << cube;
    return 0;
}

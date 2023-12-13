#include "lib/Cube.h"
#include <gtest/gtest.h>
#include <fstream>


TEST(Collect, Test1) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    cube[1][2][3] = 26;
    int a = (int)cube[1][2][3];
    int b = 26;
    ASSERT_EQ(b, a);
}


TEST(Collect, Test2) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    cube[1][2][3] = 100500;
    int a = (int)cube[1][2][3];
    int b = 100500;
    ASSERT_EQ(b, a);
}


TEST(Collect, Test3) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    cube[1][2][3] = 100500;
    cube[1][2][3] = 8;
    int a = (int)cube[1][2][3];
    int b = 8;
    ASSERT_EQ(b, a);
}


TEST(Sum, Test4) {
    Cube cube1(10, 10, 10);
    Cube cube2(10, 10, 10);
    cube1[1][2][3] = 123;
    cube2[1][2][3] = 123;
    cube1[4][5][6] = 100000;
    cube2[4][5][6] = 500;
    int a = 123 + 123;
    int b = 100000 + 500;
    Cube cube3 = cube1 + cube2;
    int c = (int)cube3[1][2][3];
    int d = (int)cube3[4][5][6];
    int e = (int)cube3[0][0][0];
    ASSERT_EQ(a, c);
    ASSERT_EQ(b, d);
    ASSERT_EQ(0, e);
}


TEST(Sub, Test5) {
    Cube cube1 = Cube::MakeArray(10, 10, 10);
    Cube cube2 = Cube::MakeArray(10, 10, 10);
    cube1[1][2][3] = 123;
    cube2[1][2][3] = 123;
    cube1[4][5][6] = 100000;
    cube2[4][5][6] = 500;
    int a = 123 - 123;
    int b = 100000 - 500;
    Cube cube3 = cube1 - cube2;
    ASSERT_EQ(a, (int)cube3[1][2][3]);
    ASSERT_EQ(b, (int)cube3[4][5][6]);
    ASSERT_EQ(0, (int)cube3[0][0][0]);
}


TEST(Mult, Test6) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    cube[1][2][3] = 50250;
    cube[0][0][0] = 8;
    cube = 2 * cube;
    ASSERT_EQ(100500, (int)cube[1][2][3]);
    ASSERT_EQ(16, (int)cube[0][0][0]);
}



TEST(Mult, Test7) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    cube[1][2][3] = 50250;
    cube[0][0][0] = 8;
    cube = cube * 2;
    ASSERT_EQ(100500, (int)cube[1][2][3]);
    ASSERT_EQ(16, (int)cube[0][0][0]);
}


TEST(Err, Test8) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    ASSERT_ANY_THROW(cube[11][0][0] = 10);
}


TEST(Err, Test9) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    ASSERT_ANY_THROW(cube[0][10][0] = 10);
}


TEST(Err, Test10) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    ASSERT_ANY_THROW(cube[0][0][101] = 10);
}


TEST(Err, Test11) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    Cube cube1 = Cube::MakeArray(1, 2, 3);
    ASSERT_ANY_THROW(cube + cube1);
}


TEST(Err, Test12) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    Cube cube1 = Cube::MakeArray(10, 2, 10);
    ASSERT_ANY_THROW(cube - cube1);
}


TEST(Cin, Test13) {
    Cube cube = Cube::MakeArray(10, 10, 10);
    std::ifstream file("/home/nikita/CLionProjects/labwork5-Lesnichiy26/tests/test.txt");
    file >> cube[1][2][3];
    int a = (int)cube[1][2][3];
    ASSERT_EQ(100500, a);
}

#include <iostream>
#include "Matrix.cpp"
using namespace std;




int main() {
    Matrix m1;
    cout << "Matrix m1:\n" <<m1;
    Matrix m2(1.,0.,0.,0.,
              1.,1.,0.,0.,
              0.,0.,2.,0.,
              0.,3.,0.,1.
             );
    cout << "Matrix m2:\n" << m2;
    Matrix m3 = m1+m2;
    cout << "Matrix m3:\n" << m3;
    Matrix m4 = m3*m2;
    cout << "Matrix m4:\n" << m4;
}

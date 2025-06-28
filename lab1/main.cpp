#include "header.hpp"

double ask_cord(char name){
    cout << "please enter " << name << ": ";
    double ret = 0;
    cin >> ret;
    return ret;
}

int main(void){
    double x,y,z;
    x = ask_cord('x');
    y = ask_cord('y');
    z = ask_cord('z');
    cout << "a: " << calc_a(x, y) << endl; 
    cout << "b: " << calc_b(x, y, z) << endl;
    return 0;
}

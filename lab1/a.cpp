#include "a.hpp"

double calc_a(double x = 1.0, double y = 1.0){
    return (pow(y, x + 1) / pow(fmod(fabs(y - 2), 3) + 3, 1.0 / 3)) + ((x + 0.5 * y) / (2 * fmod(fabs(x + y), 1e9)));
} 

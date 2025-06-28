#include "b.hpp"

double calc_b(long double x = 1.0, long double y = 1.0, long double z = 1.0){
   return pow(x+1, -y * sin(z)); 
}

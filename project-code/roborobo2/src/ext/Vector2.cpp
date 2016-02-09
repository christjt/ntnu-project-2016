#include "Utilities/Vector2.h"
std::ostream& operator<<(std::ostream &strm, const Vector2<double> vec){
    return strm << "(" << vec.x <<"," << vec.y <<  ")";
}
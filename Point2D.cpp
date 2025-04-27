#include "Point2D.h"

std::string Point2D::string()
{
    std::string res = "";
    res += std::to_string(x);
    res += "\t";
    res += std::to_string(y);
    return res;
}

#include "cl_obj_gruz.h"

cl_obj_gruz::cl_obj_gruz(cl_base * pheadObject, std::string type, double length, double width, double height): cl_base(pheadObject, type, 6){
    this->length = length;
    this->height = height;
    this->width = width;
}
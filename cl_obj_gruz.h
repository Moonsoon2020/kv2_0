#ifndef __CL_OBJ_GRUZ__H
#define __CL_OBJ_GRUZ__H

#include "cl_base.h"
class cl_obj_gruz: public cl_base{
public:
    string type;
    double length, width, height;
    cl_obj_gruz(cl_base * pheadObject, std::string type, double length, double width, double height);

};

#endif

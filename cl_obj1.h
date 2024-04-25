#ifndef __CL_OBJ1__H
#define __CL_OBJ1__H

#include "cl_base.h"
class cl_obj1: public cl_base{
public:
    cl_obj1(cl_base * pheadObject, std::string name);
    void signal(string&);
    void handler(string);
};


#endif

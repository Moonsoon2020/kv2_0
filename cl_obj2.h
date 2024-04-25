#ifndef __CL_OBJ2__H
#define __CL_OBJ2__H

#include "cl_base.h"
class cl_obj2: public cl_base{
public:
    cl_obj2(cl_base * pheadObject, std::string name);
    void signal(std::string&);
    void handler(string);
};

#endif

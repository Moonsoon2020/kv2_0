#ifndef __CL_OBJ_OUT__H
#define __CL_OBJ_OUT__H

#include "cl_base.h"
class cl_obj_out: public cl_base{
public:
    cl_obj_out(cl_base * pheadObject, std::string name);
    void signal(string &);
};

#endif

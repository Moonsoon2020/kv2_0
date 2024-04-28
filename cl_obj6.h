#ifndef __CL_OBJ6__H
#define __CL_OBJ6__H

#include "cl_base.h"
class cl_obj6: public cl_base{
public:
    cl_obj6(cl_base * pheadObject, std::string name);
    void signal(string &);
    void handler(string );
};

#endif

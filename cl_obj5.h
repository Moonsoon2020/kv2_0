#ifndef __CL_OBJ5__H
#define __CL_OBJ5__H

#include "cl_base.h"
class cl_obj5: public cl_base{
public:
    cl_obj5(cl_base * pheadObject, std::string name);
    void signal(string &);
    void handler(string );
};

#endif

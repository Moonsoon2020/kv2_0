#ifndef __CL_OBJ4__H
#define __CL_OBJ4__H

#include "cl_base.h"
class cl_obj4: public cl_base{
public:
    cl_obj4(cl_base * pheadObject, std::string name);
    void signal(string &);
    void handler(string );
};

#endif

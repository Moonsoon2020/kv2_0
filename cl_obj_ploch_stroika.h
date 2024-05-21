#ifndef __CL_OBJ_PLOCH_STROIKA__H
#define __CL_OBJ_PLOCH_STROIKA__H

#include "cl_base.h"
class cl_obj_ploch_stroika: public cl_base{
public:
    int n, m;
    vector<vector<string >> razm;
    cl_obj_ploch_stroika(cl_base * pheadObject, std::string name, int n, int m);
};

#endif

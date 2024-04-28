#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "cl_base.h"
#include "cl_obj2.h"
#include "cl_obj3.h"
#include "cl_obj4.h"
#include "cl_obj5.h"
#include "cl_obj6.h"


class cl_application: public cl_base{
public:
    cl_application(cl_application * element);
    void build_tree_objects();
    int exec_app();
    TYPE_SIGNAL get_signal(cl_base*);
    TYPE_HANDLER get_handler(cl_base*);
};


#endif

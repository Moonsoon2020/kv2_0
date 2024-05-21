#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "cl_base.h"
#include "cl_obj_inp.h"
#include "cl_obj_control.h"
#include "cl_obj_ploch_stroika.h"
#include "cl_obj_gruz.h"
#include "cl_obj_ploch_razm.h"
#include "cl_obj_out.h"


class cl_application: public cl_base{
public:
    string input;
    int n, m, e;
    cl_obj_ploch_stroika *stroika;
    cl_obj_control *control;
    cl_obj_out *out;
    cl_base *inp;
    cl_application(cl_application * element);
    void build_tree_objects();
    int exec_app();


    void signal(string &d);

    int update(int takt, string text);
};


#endif

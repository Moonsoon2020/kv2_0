#ifndef __CL_OBJ_CONTROL__H
#define __CL_OBJ_CONTROL__H
#include "cl_obj_ploch_razm.h"
#include "cl_obj_ploch_stroika.h"
#include "cl_base.h"
class cl_obj_control: public cl_base{
public:
    cl_obj_control(cl_base *pheadObject, string text, int e, cl_obj_ploch_stroika *stroika, int n, int m);

    int status = 0;
    cl_base * obj;
    int square, n, m, h = 0, e;
    cl_obj_ploch_razm * platform;
    int length = 1, angle = 0;
    cl_obj_ploch_stroika* stroika;
    void update();

    pair<int, int> getCoordinates(int cell_number, string platform);

    int calculateDistance(int cell_number, string platform);

    int calculateAngle(int cell_number, string platform);
};

#endif

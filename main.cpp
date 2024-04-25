#include <sstream>
#include "cl_application.h"
using namespace std;
int main()
{
    istringstream oss("appls_root\n"
                      "/ object_s1 3\n"
                      "/ object_s2 2\n"
                      "/object_s2 object_s4 4\n"
                      "/ object_s13 5\n"
                      "/object_s2 object_s6 6\n"
                      "/object_s1 object_s7 2\n"
                      "endtree\n"
                      "/object_s2/object_s4 /object_s2/object_s6\n"
                      "/object_s2 /object_s1/object_s7\n"
                      "/ /object_s2/object_s4\n"
                      "/object_s2/object_s4 /\n"
                      "end_of_connections\n"
                      "EMIT /object_s2/object_s4 Send message 1\n"
                      "EMIT /object_s2/object_s4 Send message 2\n"
                      "EMIT /object_s2/object_s4 Send message 3\n"
                      "EMIT /object_s1 Send message 4\n"
                      "END");
    cin.rdbuf(oss.rdbuf());
    cl_application ob_cl_application(nullptr);
    ob_cl_application.build_tree_objects();
    return ob_cl_application.exec_app();
}

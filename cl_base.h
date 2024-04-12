#ifndef __ELEMENT__H
#define __ELEMENT__H
#include "string"
#include "vector"
#include "iostream"
using namespace std;
class cl_base{
protected:
    cl_base * head;
    string name;
    int state{};
    vector <cl_base *> objects;
public:
    cl_base(cl_base * head_object, string text_n = "Object_root");

    cl_base * get_head();
    cl_base * get_child_by_name(string text_);
    cl_base * find_on_tree(string name);
    cl_base * find_on_branch(string name);
    cl_base* get_object_by_coordinate(std::string = "/");

    string get_name();
    bool modify_text(string text_n);
    void set_state(int state);
    bool change_head_object(cl_base*);

    void delete_sub_object_by_name(std::string name);

    void print_state();
    void print();
};

#endif

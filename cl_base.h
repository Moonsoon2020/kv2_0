#ifndef __CL_BASE__H
#define __CL_BASE__H
#include "string"
#include "vector"
#include "iostream"
using namespace std;
class cl_base;
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f)
typedef void (cl_base ::* TYPE_SIGNAL)(string&);
typedef void (cl_base ::* TYPE_HANDLER)(string);
using namespace std;
class cl_base{
protected:
    cl_base * head;
    string name;
    int state;
    vector <cl_base *> objects;
    struct o_sh {
        TYPE_SIGNAL p_signal;
        cl_base* p_cl_base;
        TYPE_HANDLER p_handler;
    };
public:
    int cl_n;
    cl_base(cl_base * head_object, string name = "Object_root", int cl_n= 1);
    cl_base * get_head();
    cl_base * get_child_by_name(string name);
    cl_base * find_on_tree(string name);
    cl_base * find_on_branch(string name);
    cl_base * get_object_by_coordinate(string s_object_coordinate= "/");
    string get_name();
    bool modify_text(string name);
    void set_state(int state);
    bool change_head_object(cl_base*);
    void delete_sub_object_by_name(string name);
    void print_state();
    void print();
    string path();
    // Вектор для хранения установленных связей
    vector < o_sh* > connects;
    // Метод установи связи
    void set_connect(TYPE_SIGNAL, cl_base*, TYPE_HANDLER);
    // Метод выдачи сигнала и отработки соответствующих обработчиков
    void emit_signal(TYPE_SIGNAL, string&);
    // Метод удаления (разрыва) связи между сигналом текущего объекта и
    void break_connection(TYPE_SIGNAL, cl_base*, TYPE_HANDLER);
    // Получение состояния
    int get_state();
    // Получение номера класса
    int get_cl_n();
    // Установка готовности дереву объектов
    void set_ready_branch();
    void signal(std::string &);
    void handler(string );
};

#endif
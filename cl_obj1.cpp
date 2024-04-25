#include "cl_obj1.h"

cl_obj1::cl_obj1(cl_base * pheadObject, std::string text):cl_base(pheadObject, text, 1){

}
// Метод сигнала
void cl_obj1::signal(string& d) {
    cout << endl << "Signal from " << path();
    d += " (class: 6)";
}
// Метод обработчика
void cl_obj1::handler(string d) {
    cout << endl << "Signal to " << path() << " Text: " << d;
}
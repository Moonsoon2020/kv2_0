#include "cl_obj2.h"

cl_obj2::cl_obj2(cl_base * pheadObject, std::string text):cl_base(pheadObject, text, 2){

}
// Метод сигнала
void cl_obj2::signal(string& d) {
    cout << "Signal from " << path() << endl;
    d += " (class: 2)";
}
// Метод обработчика
void cl_obj2::handler(string d) {
    cout << "Signal to " << path() << " Text: " << d<< endl;
}
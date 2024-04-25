#include "cl_obj3.h"

cl_obj3::cl_obj3(cl_base * pheadObject, std::string text):cl_base(pheadObject, text, 3){

}
// Метод сигнала
void cl_obj3::signal(string& d) {
    cout << endl << "Signal from " << path();
    d += " (class: 6)";
}
// Метод обработчика
void cl_obj3::handler(string d) {
    cout << endl << "Signal to " << path() << " Text: " << d;
}
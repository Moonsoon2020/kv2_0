#include "cl_obj3.h"

cl_obj3::cl_obj3(cl_base * pheadObject, std::string text):cl_base(pheadObject, text, 3){

}
// Метод сигнала
void cl_obj3::signal(string& d) {
    cout << "Signal from " << path()<< endl;
    d += " (class: 3)";
}
// Метод обработчика
void cl_obj3::handler(string d) {
    cout << "Signal to " << path() << " Text: " << d<< endl;
}
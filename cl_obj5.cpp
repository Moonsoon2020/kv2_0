#include "cl_obj5.h"

cl_obj5::cl_obj5(cl_base * pheadObject, std::string text):cl_base(pheadObject, text, 5){

}
// Метод сигнала
void cl_obj5::signal(string& d) {
    cout << "Signal from " << path()<< endl;
    d += " (class: 5)";
}
// Метод обработчика
void cl_obj5::handler(string d) {
    cout << "Signal to " << path() << " Text: " << d<< endl;
}
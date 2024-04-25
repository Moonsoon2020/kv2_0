#include "cl_obj6.h"

cl_obj6::cl_obj6(cl_base * pheadObject, std::string text):cl_base(pheadObject, text, 6){

}
// Метод сигнала
void cl_obj6::signal(string& d) {
    cout << endl << "Signal from " << path();
    d += " (class: 6)";
}
// Метод обработчика
void cl_obj6::handler(string d) {
    cout << endl << "Signal to " << path() << " Text: " << d;
}
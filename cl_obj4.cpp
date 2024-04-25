#include "cl_obj4.h"

cl_obj4::cl_obj4(cl_base * pheadObject, std::string text):cl_base(pheadObject, text, 4){

}
// Метод сигнала
void cl_obj4::signal(string& d) {
    cout << endl << "Signal from " << path();
    d += " (class: 6)";
}
// Метод обработчика
void cl_obj4::handler(string d) {
    cout << endl << "Signal to " << path() << " Text: " << d;
}
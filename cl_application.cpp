#include "cl_application.h"
#include <iostream>
#include <sstream>
#include <string>

cl_application::cl_application(cl_application *element)
        : cl_base(element, "Object tree") {
}

// Метод сигнала
void cl_application::signal(string &d) {
    input = d;
}

void cl_application::build_tree_objects() {
    string sub;
    cin >> n >> m >> e;
    inp = new cl_obj_inp(this);
    set_connect(SIGNAL_D(cl_obj_inp::signal), inp, HANDLER_D(cl_application::handler));
    inp->set_connect(SIGNAL_D(cl_application::signal), this, HANDLER_D(cl_obj_inp::handler));
    out = new cl_obj_out(this, "out");
    set_connect(SIGNAL_D(cl_obj_out::signal), out, HANDLER_D(cl_application::handler));
    stroika = new cl_obj_ploch_stroika(this, "s", n, m);
    control =new cl_obj_control(this, "control", e, stroika, n, m);
    new cl_obj_ploch_razm(this, "1", 9);
    new cl_obj_ploch_razm(this, "2", 9);
    new cl_obj_ploch_razm(this, "3", 9);
    string msg = "build";
    emit_signal(SIGNAL_D(cl_obj_inp::signal), msg);
    set_ready_branch();
    while (true) {
        emit_signal(SIGNAL_D(cl_obj_inp::signal), msg);
        // Проверка на конец ввода грузов
        if (input == "End of cargos") {
            break;
        }

        // Создаем поток для чтения данных из строки
        std::istringstream iss(input);
        int platform, square;
        std::string cargo_type;
        double length, width, height;
        // Считываем данные о грузе из строки
        iss >> platform >> square >> cargo_type >> length >> width >> height;
        string st = "/" + to_string(platform);
        cl_obj_ploch_razm *obj = static_cast<cl_obj_ploch_razm *>(get_object_by_coordinate(st));
        if (!obj->get_child_by_name(cargo_type)) {
            new cl_obj_gruz(obj, cargo_type, length, width, height);
            obj->razm[square - 1].emplace_back(cargo_type);
        }

    }
    set_ready_branch();
}

int cl_application::exec_app() {
    int takt = 0;
    // print();
    inp = static_cast<cl_obj_inp *>(get_object_by_coordinate("/inp"));
    cl_obj_ploch_stroika *p_s = static_cast<cl_obj_ploch_stroika *>(get_object_by_coordinate("/s"));

    string text_msg = "Ready to work\n";
    emit_signal(SIGNAL_D(cl_obj_out::signal), text_msg);
    string command, args, msg = "exec";
    while (true) {
        text_msg = "";
        emit_signal(SIGNAL_D(cl_obj_inp::signal), msg);
        if (input == "Turn off the system") break;
        if (input == "SHOWTREE"){
            print();
        }
        if (input == "Condition of the tower crane") {
            text_msg = "Tower crane " + to_string(control->angle) + " " + to_string(control->length) + "\n";
        } else if (input == "Floor construction") {
            text_msg = "Floor condition";
            for (int i = 0; i < n * m / 16; i++){
                if (!p_s->razm[i].empty()) {
                    text_msg += " s " + to_string(i + 1) + ":";
                    for (int j = p_s->razm[i].size()-1; j >= 0; j -- ){
                        text_msg += " " + p_s->razm[i][j];
                    }
                }
            }
            text_msg += "\n";
        } else if (input.find("Submit the cargo") != string::npos) {
            input = input.erase(0, 16);
            std::istringstream iss(input);
            int square;
            std::string cargo_type;
            // Считываем данные о грузе из строки
            iss >> cargo_type >> square;
            cl_base *base = find_on_tree(cargo_type);
            if (!base) {
                text_msg = "Cargo " + cargo_type + " not found\n";
                takt = update(takt, text_msg);
                continue;
            }
            cl_obj_ploch_razm *platform = static_cast<cl_obj_ploch_razm *>(base->get_head());
            bool flag = false;
            int n = 0;
            for (vector<string> stek: platform->razm) {
                n++;
                if (stek.size() == 0)
                    continue;
                if (stek.back() == base->get_name()) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                text_msg = "The cargo" + cargo_type + " is not available\n";
                takt = update(takt, text_msg);
                continue;
            }
            control->obj = base;
            control->status = 6;
            control->square = square;
            control->platform = platform;
        } else if (input.find("Condition of the cargo area") != string::npos) {
            input = input.erase(0, 28);
            cl_obj_ploch_razm * platform = static_cast<cl_obj_ploch_razm *>(get_object_by_coordinate("/" + input));
            text_msg = "Condition of the cargo area " + input + " --";
            for (int i = 0; i < 9; i++){
                if (!platform->razm[i].empty()){
                    text_msg += " s " + to_string(i + 1) + ":";
                    for (int j = platform->razm[i].size()-1; j >= 0; j -- ){
                        text_msg +=  " " + platform->razm[i][j];
                    }
                }
            }
            text_msg += "\n";
        } else if (input.find("Cargo condition") != string::npos) {
            input = input.erase(0, 16);
            cl_base * base = find_on_tree(input);
            if (base == nullptr){
                text_msg = "Cargo " + input + " not found\n";
            } else if (base->get_head()->get_name() == "control"){
                text_msg = "Cargo condition " + input + ": in hook\n";
            } else if (base->get_head()->get_name() == "s"){
                int pos = -1;
                for (int i = 0; i < n * m / 16; i++){
                    if (p_s->razm[i].empty()){
                        continue;
                    }
                    for (string obs : p_s->razm[i]){
                        if (obs == base->get_name()){
                            pos = i + 1;
                            break;
                        }}
                }
                text_msg = "Cargo condition " + input + ": in floor square " + to_string(pos) + "\n";
            } else {
                cl_obj_ploch_razm *obj = static_cast <cl_obj_ploch_razm*>(base->get_head());
                int pos = -1;
                for (int i = 0; i < 9; i++){
                    if (obj->razm[i].empty()){
                        continue;
                    }
                    for (string obs : obj->razm[i]){
                        if (obs == base->get_name()){
                            pos = i + 1;
                            break;
                        }}
                }
                text_msg = "Cargo condition " + input + ": in area " + obj->get_name()+ ", square "+ to_string(pos) + "\n";
            }
        }
        takt = update(takt, text_msg);
    }
    text_msg = "Turn off the system\n";
    emit_signal(SIGNAL_D(cl_obj_out::signal), text_msg);
    return 0;
}
int cl_application::update(int takt, string text){
    emit_signal(SIGNAL_D(cl_obj_out::signal), text);
    control->update();
    return takt + 1;
}

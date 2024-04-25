#include "cl_base.h"

cl_base *cl_base::get_head() {
    return head;
}
cl_base *cl_base::get_child_by_name(string name) {
    for(cl_base* i : objects){
        if (i->get_name() == name){
            return i;
        }
    }
    return nullptr;
}

cl_base *cl_base::find_on_branch(string name) {
    if (this->name == name)
        return this;
    cl_base *found_object = nullptr;
    bool found = false;
    for (cl_base *subordinate_object: objects) {
        cl_base *temp_object = subordinate_object->find_on_branch(name);
        if (temp_object) {
            if (found)
                return nullptr;
            found_object = temp_object;
            found = true;
        }
    }
    return found_object;
}

cl_base *cl_base::find_on_tree(string name) {
    if (!name.empty()) {
        cl_base *found_object = nullptr;
        bool found = false;
        for (auto &object: objects) {
            if (object->get_name() == name) {
                if (found)
                    return nullptr;
                found_object = object;
                found = true;
            }
            cl_base *temp_object = object->find_on_tree(name);
            if (temp_object) {
                found_object = temp_object;
                found = true;
            }
        }
        return found_object;
    }
    return nullptr;
}


cl_base *cl_base::get_object_by_coordinate(string s_object_coordinate) {
    if (!s_object_coordinate.empty()) {
        cl_base *base = this;
        if (s_object_coordinate.at(0) == '.') {
            if (s_object_coordinate.length() == 1)
                return this;
            return find_on_branch(s_object_coordinate.substr(1));
        } else if (s_object_coordinate.at(0) == '/') {
            while (true) {
                if (base->get_head())
                    base = base->get_head();
                else{
                    break;
                }
            }
            if (s_object_coordinate == "/"){
                return base;
            }
            bool fl = s_object_coordinate.length() >= 2&& s_object_coordinate.at(1) != '/';
            if (fl) {
                s_object_coordinate = s_object_coordinate.substr(1);}
            else {
                s_object_coordinate = s_object_coordinate.substr(2);
            }
            std::vector<std::string> names;
            while (s_object_coordinate.length() > 0) {
                if (s_object_coordinate.find('/') != std::string::npos) {
                    names.push_back(s_object_coordinate.substr(0, s_object_coordinate.find('/')));
                    s_object_coordinate = s_object_coordinate.substr(s_object_coordinate.find('/') + 1);
                } else {
                    names.push_back(s_object_coordinate);
                    break;
                }
            }
            while (true){
                bool flag = false;
                if (names.empty())
                    return base;
                for (auto  i : base->objects){
                    if (names[0] == i->get_name()){
                        names.erase(names.begin());
                        base = i;
                        flag = true;
                        break;
                    }
                }
                if (!flag)
                    return nullptr;
            }
        } else {
            std::vector<std::string> names;
            while (s_object_coordinate.length() > 0) {
                if (s_object_coordinate.find('/') != std::string::npos) {
                    names.push_back(s_object_coordinate.substr(0, s_object_coordinate.find('/')));
                    s_object_coordinate = s_object_coordinate.substr(s_object_coordinate.find('/') + 1);
                } else {
                    names.push_back(s_object_coordinate);
                    break;
                }
            }
            for (std::string name: names) {
                base = base->find_on_tree(name);
                if (!base) break;
            }
            return base;
        }}
    return nullptr;
}

std::string cl_base::get_name() {
    return name;
}

bool cl_base::modify_text(string name) {
    if (name.empty())
        return false;
    for (cl_base *subordinate_object: objects)
        if (subordinate_object->get_name() == name)
            return false;
    this->name = name;
    return true;
}

void cl_base::set_state(int state) {
    if (head && head->state == 0) {
        this->state = 0;
    }
    else {
        this->state = state;
    }
    if (state == 0) {
        for (cl_base* child : objects) {
            child->set_state(0);
        }
    }
}

bool cl_base::change_head_object(cl_base *head) {
    if (this->head==nullptr || head == nullptr) return false;
    if (head->get_child_by_name(get_name())) return false;
    cl_base* current = head;
    while (current->get_head()){
        if (current == this) return false;
        current = current->get_head();
    }
    for (auto i = (this->head->objects).begin(); i !=
                                                                (this->head->objects).end();i++){
        if (*i == this){
            (this->head->objects).erase(i);
            break;
        }
    }
    this->head = head;
    (this->head->objects).push_back(this);
    return true;
}

void cl_base::delete_sub_object_by_name(string name) {
    if (name.empty()) return;
    for (int i = 0; i < objects.size(); i++)
        if (objects.at(i)->get_name() == name)
            objects.erase(objects.begin() + i);
}

void cl_base::print() {
    cout << this->name << endl;
    int tab = 1;
    cl_base *par = this;
    while (par->get_head()) {
        par = par->get_head();
        tab += 1;
    }
    if (!objects.empty()) {
        for (cl_base *ch: objects) {
            for (int i = 0; i < tab; i++)
                cout << "    ";
            ch->print();
        }
    }
}

void cl_base::print_state() {
    cout << this->name;
    if (this->state == 0)
        cout << " is not ready\n";
    else
        cout << " is ready\n";
    int tab = 1;
    cl_base *par = this;
    while (par->get_head()) {
        par = par->get_head();
        tab += 1;
    }
    if (!objects.empty()) {
        for (cl_base *ch: objects) {
            for (int i = 0; i < tab; i++)
                cout << "    ";
            ch->print_state();
        }
    }
}

// КВ4
// Метод получения абсолютного пути
string cl_base::path() {
    if (!get_head()) {
        return "/";
    }
    string p = get_name();
    cl_base* current = get_head();
    while (current&&current->get_head()) {
        p = current->get_name() + "/" + p;
        current = current->get_head();
    }
    return "/" + p;
}
// Метод установи связи между сигналом текущего объекта и обработчиком
void cl_base::set_connect(TYPE_SIGNAL p_signal, cl_base* p_object,
                          TYPE_HANDLER p_ob_handler){
    o_sh* p_value;
    for (unsigned int i = 0; i < connects.size(); i++)
    {
        if (connects[i]->p_signal == p_signal &&
            connects[i]->p_cl_base == p_object &&
            connects[i]->p_handler == p_ob_handler)
        {
            return;
        }
    }
    p_value = new o_sh(); // создание объекта структуры для
// хранения информации о новой связи
    p_value->p_signal = p_signal;
    p_value->p_cl_base = p_object;
    p_value->p_handler = p_ob_handler;
    connects.push_back(p_value); // добавление новой связи
}
// Метод выдачи сигнала от текущего объекта с передачей строковой переменной
void cl_base::emit_signal(TYPE_SIGNAL p_signal, string & s_command){
    TYPE_HANDLER p_handler;
    cl_base* p_object;
// если отключен
    if (this->state == 0) return;
    (this->*p_signal) (s_command); // вызов метода сигнала
    for (unsigned int i = 0; i < connects.size(); i++) // цикл по всем
    {
        if (connects[i]->p_signal == p_signal) // определение допустимого
        {
            p_object = connects[i]->p_cl_base;
            if (p_object->state == 0) continue;
            p_handler = connects[i]->p_handler;
            (p_object->*p_handler) (s_command); // вызов метода обработчика
        }
    }
}
// Метод удаления (разрыва) связи между сигналом текущего объекта и обработчиком целевого объекта
void cl_base::break_connection(TYPE_SIGNAL p_signal, cl_base* p_object,
                               TYPE_HANDLER p_ob_handler) {
    for (auto i = connects.begin(); i != connects.end(); i++) {
        o_sh* c = *i;
        if (c->p_cl_base == p_object &&
            c->p_handler == p_ob_handler &&
            c->p_signal == p_signal) {
            connects.erase(i);
            delete c;
            return;
        }
    }
}

cl_base::cl_base(cl_base* p_head_object, string s_object_name, int cl_n) {
    this->head = p_head_object;
    this->name = s_object_name;
    this->cl_n = cl_n;
    if (p_head_object) {
        p_head_object->objects.push_back(this);
    }
}
// Получение состояния
int cl_base::get_state() {
    return state;
}
// Получение номера класса
int cl_base::get_cl_n() {
    return cl_n;
}
// Установка готовности дереву объектов
void cl_base::set_ready_branch() {
    this->set_state(1);
    for (auto child : objects) {
        child->set_ready_branch();
    }
}
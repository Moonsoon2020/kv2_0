#include "cl_base.h"

cl_base::cl_base(cl_base *head, std::string name) {
    this->head = head;
    this->name = name;
    if (head) head->objects.push_back(this);
}

cl_base *cl_base::get_head() {
    return head;
}

cl_base *cl_base::get_child_by_name(std::string name) {
    cl_base *base = this;
    while (true)
        if (base->get_head()) base = base->get_head();
        else break;

    if (base->find_on_branch(name)) return base->find_on_branch(name);
    return nullptr;
}

cl_base *cl_base::find_on_branch(std::string name) {
    if (this->name == name) return this;

    cl_base *found_object = nullptr;
    bool found = false;
    for (cl_base *subordinate_object: objects) {
        cl_base *temp_object = subordinate_object->find_on_branch(name);
        if (temp_object) {
            if (found) // Если элемент уже был найден в другом подчиненном объекте, возвращаем nullptr
                return nullptr;
            found_object = temp_object;
            found = true;
        }
    }

    return found_object;
}

cl_base *cl_base::find_on_tree(std::string name) {
    if (!name.empty()) {
        cl_base *found_object = nullptr;
        bool found = false;
        for (auto &object: objects) {
            if (object->get_name() == name) {
                if (found) // Если элемент уже был найден в другом объекте, возвращаем nullptr
                    return nullptr;
                found_object = object;
                found = true;
            }

            cl_base *temp_object = object->find_on_tree(name);
            if (temp_object) {
                if (found) // Если элемент уже был найден в другом объекте, возвращаем nullptr
                    return nullptr;
                found_object = temp_object;
                found = true;
            }
        }

        return found_object;
    }

    return nullptr;
}

cl_base *cl_base::get_object_by_coordinate(std::string s_object_coordinate) {
    if (!s_object_coordinate.empty()) {
        cl_base *base = this;
        if (s_object_coordinate.at(0) == '.') {
            if (s_object_coordinate.length() == 1)
                return this;
            return find_on_branch(s_object_coordinate.substr(1));
        } else if (s_object_coordinate.at(0) == '/') {
            if (s_object_coordinate == "/"){
                while (true) {
                    if (base->get_head())
                        base = base->get_head();
                    else{
                        break;
                    }
                }
                return base;while (true) {
                    if (base->get_head())
                        base = base->get_head();
                    else{
                        break;
                    }
                }
            }
            if (s_object_coordinate.length() > 2&& s_object_coordinate.at(1) != '/') {
                while (true) {
                    if (base->get_head())
                        base = base->get_head();
                    else{
                        break;
                    }
                }while (true) {
                    if (base->get_head())
                        base = base->get_head();
                    else{
                        break;
                    }
                }
                s_object_coordinate = s_object_coordinate.substr(1);
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
                    if (names.empty())
                        return base;
                    for (auto  i : base->objects
                            ){
                        if (names[0] == i->get_name()){
                            names.erase(names.begin());
                            base = i;
                            break;
                        }
                    }
                }
//                return base->find_on_tree(s_object_coordinate.substr(1));
            } else {
                while (true) {
                    if (base->get_head())
                        base = base->get_head();
                    else{
                        break;
                    }
                }
                s_object_coordinate = s_object_coordinate.substr(2);
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


            }
        } else if (s_object_coordinate == ".")
            return this;

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
    }
    return nullptr;
}

std::string cl_base::get_name() {
    return name;
}

bool cl_base::modify_text(std::string name) {
    if (name.empty()) return false;
    for (cl_base *subordinate_object: objects) if (subordinate_object->get_name() == name) return false;

    this->name = name;
    return true;
}

void cl_base::set_state(int state) {
    this->state = state;
    if (this->state == 0)
        for (cl_base *subordinate_object: objects)
            subordinate_object->set_state(state);

    cl_base *base = this;
    while (true) {
        if (base->get_head()) {
            base = base->get_head();
            if (state == 0) base->set_state(0);
        } else break;
    }
}

bool cl_base::change_head_object(cl_base *head) {
    if (!head || !get_head()) return false;

    get_head()->delete_sub_object_by_name(get_name());
    this->head = head;
    this->head->objects.push_back(this);
    return true;
}

void cl_base::delete_sub_object_by_name(string name) {
    if (name.empty()) return;
    for (size_t i = 0; i < objects.size(); i++)
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
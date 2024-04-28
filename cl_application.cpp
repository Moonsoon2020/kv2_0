#include "cl_application.h"

cl_application::cl_application(cl_application *element)
        : cl_base(element, "Object tree") {
}

void cl_application::build_tree_objects() {
    int id;
    std::string head, sub;
    std::cin >> head;
    modify_text(head);
    while (true) {
        std::cin >> head;
        if (head == "endtree") break;
        cl_base *obj = get_object_by_coordinate(head);
        if (!obj) {
            cout << "Object tree" << endl;
            print();
            cout << endl << "The head object " << head << " is not found";
            exit(1);
        }
        std::cin >> sub >> id;
        if (!obj->get_child_by_name(sub)) {
            if (id == 1) new cl_base(obj, sub, 1);
            else if (id == 2) new cl_obj2(obj, sub);
            else if (id == 3) new cl_obj3(obj, sub);
            else if (id == 4) new cl_obj4(obj, sub);
            else if (id == 5) new cl_obj5(obj, sub);
            else if (id == 6) new cl_obj6(obj, sub);
        } else
            std::cout << head << " Dubbing the names of subordinate objects" << endl;

    }
    cin >> sub;
    while (sub != "end_of_connections") {
        cl_base *obj1 = get_object_by_coordinate(sub);
        cin >> sub;
        cl_base *obj2 = get_object_by_coordinate(sub);
        obj1->set_connect(get_signal(obj1), obj2, get_handler(obj2));
        cin >> sub;
    }
}

int cl_application::exec_app() {
    set_ready_branch();
    std::cout << "Object tree\n";
    print();
    std::string command, args, msg;
    cl_base *target = this, *from = nullptr;
    std::getline(std::cin, command, '\n');
    while (true) {
        cin >> command;
        if (command == "END") break;
        cin >> args;
        cl_base *from = target->get_object_by_coordinate(args);
        getline(cin, msg);
        if (command == "SET") {
            if (from) {
                target = from;
                cout << ("Object is set: " + target->get_name()) << endl;
            } else cout << ("The object was not found at the specified coordinate: " + args) << endl;
        } else if (command == "FIND") {
            if (from)
                cout << (args + " Object name: " + from->get_name()) << endl;
            else
                cout << (args + " Object is not found") << endl;
        } else if (command == "MOVE") {
            if (from) {
                if (target->find_on_branch(from->get_name()) == from)
                    cout << (args + " Redefining the head object failed") << endl;
                else {
                    if (from->find_on_tree(target->get_name()))
                        cout << (args + " Dubbing the names of subordinate objects") << endl;
                    else if (target->change_head_object(from))
                        cout << ("New head object: " + target->get_head()->get_name()) << endl;

                }
            } else cout << (args + " Head object is not found") << endl;
        } else if (command == "MOVE") {
            if (!from) {
                cout << args << " Head object is not found" << endl;
            } else if (from->get_head() != target->get_head() && target->find_on_branch(from->get_name())) {
                cout << args << " Redefining the head fromect failed" << endl;
            } else if (from->get_child_by_name(target->get_name())) {
                cout << args << " Dubbing the names of subordinate objects" << endl;
            } else if (!target->change_head_object(from)) {
                cout << args << " Redefining the head object failed" << endl;
            } else {
                cout << "New head object: " << from->get_name() << endl;
            }
        } else if (command == "DELETE") {
            if (from) {
                cl_base *to = from->get_head();
                if (to) {
                    std::string absolute = from->get_name();
                    to->delete_sub_object_by_name(absolute);
                    while (to->get_head()) {
                        absolute = to->get_name() + "/" + absolute;
                        to = to->get_head();
                    }
                    cout << ("The object /" + absolute + " has been deleted") << endl;
                }
            }
        } else if (command == "EMIT") {
            if (!from) {
                cout << "Object " << args << " not found" << endl;
                continue;
            }
            if (from->get_state()) {
                from->emit_signal(get_signal(from), msg);
            }
        } else if (command == "SET_CONDITION") {
            from->set_state(stoi(msg));
        } else {
            if (!from) {
                cout << "Object " << args << " not found" << endl;
                continue;
            }
            cl_base *obj2 = get_object_by_coordinate(msg.substr(1));
            if (obj2 == nullptr) {
                cout << "Handler object " << msg << " not found" << endl;
                continue;
            }
            if (command == "SET_CONNECT") {
                from->set_connect(get_signal(from), obj2, get_handler(obj2));
            } else if (command == "DELETE_CONNECT") {
                from->break_connection(get_signal(from), obj2, get_handler(obj2));
            }
        }
    }
    //cout << ("Current object hierarchy tree") << endl;
    //print();
    return 0;
}

// Метод получения сигнала
TYPE_SIGNAL cl_application::get_signal(cl_base *obj) {
    switch (obj->get_cl_n()) {
        case 1:
            return SIGNAL_D(cl_base::signal);
        case 2:
            return SIGNAL_D(cl_obj2::signal);
        case 3:
            return SIGNAL_D(cl_obj3::signal);
        case 4:
            return SIGNAL_D(cl_obj4::signal);
        case 5:
            return SIGNAL_D(cl_obj5::signal);
        case 6:
            return SIGNAL_D(cl_obj6::signal);
    }
    return nullptr;
}

// Метод получения обработчика
TYPE_HANDLER cl_application::get_handler(cl_base *obj) {
    switch (obj->get_cl_n()) {
        case 1:
            return HANDLER_D(cl_base::handler);
        case 2:
            return HANDLER_D(cl_obj2::handler);
        case 3:
            return HANDLER_D(cl_obj3::handler);
        case 4:
            return HANDLER_D(cl_obj4::handler);
        case 5:
            return HANDLER_D(cl_obj5::handler);
        case 6:
            return HANDLER_D(cl_obj6::handler);
    }
    return nullptr;
}
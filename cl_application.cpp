#include "cl_application.h"

cl_application::cl_application(cl_application *p_head_object)
        : cl_base(p_head_object, "Object tree") {
}

void cl_application::build_tree_objects() {
    int id;
    std::string head, sub;

    std::cin >> head;
    modify_text(head);
    while (true) {
        std::cin >> head;
        if (head == "endtree") break;

        std::cin >> sub >> id;
        if (get_object_by_coordinate(head)) {
            if (get_object_by_coordinate(head)->find_on_tree(sub)) {
                std::cout << head << "     Dubbing the names of subordinate objects" << std::endl;
                continue;
            }

            if (id == 2) new cl_obj2(get_object_by_coordinate(head), sub);
            else if (id == 3) new cl_obj3(get_object_by_coordinate(head), sub);
            else if (id == 4) new cl_obj4(get_object_by_coordinate(head), sub);
            else if (id == 5) new cl_obj5(get_object_by_coordinate(head), sub);
            else if (id == 6) new cl_obj6(get_object_by_coordinate(head), sub);
        } else {
            modify_text(get_name() + "_" + head + "_broken");
            return;
        }
    }
}

int cl_application::exec_app() {
    if (get_name().find("_broken") != std::string::npos) {
        std::string origin_object_name = get_name().substr(0, get_name().find_last_of("_broken"));
        std::string error_coordinate = origin_object_name.substr(origin_object_name.find_last_of('_') + 1);
        origin_object_name = origin_object_name.substr(0, origin_object_name.find_last_of('_'));

        modify_text(origin_object_name);
        std::cout << "Object tree\n";
        print();
        std::cout << std::endl << "The head object " << error_coordinate << " is not found";
        return 1;
    }
    std::cout << "Object tree\n";
    print();

    std::string command, args;
    std::vector<std::string> commands;
    cl_base *target = this, *from = nullptr;

    std::getline(std::cin, command, '\n');
    while (true) {
        std::getline(std::cin, command, '\n');
        if (command == "END")
            break;
        args = command.substr(command.find(' ') + 1);
        command = command.substr(0, command.find(' '));
        from = target->get_object_by_coordinate(args);
        if (command == "SET") {
            if (from) {
                target = from;
                cout << ("Object is set: " + target->get_name()) << endl;
            } else cout << ("The object was not found at the specified coordinate: " + args) << endl;
        } else if (command == "FIND") {
            if (from) cout << (args + "     Object name: " + from->get_name()) << endl;
            else cout << (args + "     Object is not found") << endl;
        } else if (command == "MOVE") {
            if (from) {
                if (target->find_on_branch(from->get_name()) &&
                    target->find_on_branch(from->get_name()) == from)
                    cout << (args + "     Redefining the head object failed") << endl;
                else {
                    if (from->find_on_tree(target->get_name()))
                        cout << (args + "     Dubbing the names of subordinate objects") << endl;
                    else if (target->change_head_object(from))
                        cout << ("New head object: " + target->get_head()->get_name()) << endl;
                }
            } else cout << (args + "     Head object is not found") << endl;
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
        }
    }

    cout << ("Current object hierarchy tree") << endl;
    print();

    return 0;
}
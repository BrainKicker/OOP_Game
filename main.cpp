#include <iostream>
#include <getopt.h>

#include "lib/containers/vector/Vector.h"

#include "lib/containers/pair/Pair.h"

#include "lib/containers/string/String.h"

#include "prog/field/field.h"
#include "prog/adapters/sfml/sfml_adapter.h"

int main(int argc, char** argv) {

    std::srand(std::time(nullptr));

    const char* short_options = "l::";

    const option long_options[] = {
            { "log", optional_argument, nullptr, 'l'},
            {nullptr, 0, nullptr, 0 }
    };

    std::shared_ptr<Logger> logger;

    int opchar;
    int option_index;

    while ((opchar = getopt_long_only(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (opchar) {
            case 'l':
                if (optarg == nullptr)
                    logger = std::shared_ptr<Logger>(new StreamLogger(std::cout));
                else
                    logger = std::shared_ptr<Logger>(new FileLogger(optarg));
                break;
            default:
                break;
        }
    }

    sfml_adapter<5> adapter;
    adapter.get_field()->set_logger(logger);
    adapter.start();

//    character c;
//    character c1;
//
//    std::cout << "c: " << c.max_hp() << ' ' << c.hp() << ' ' << c.damage() << '\n';
//
//    artifact* art0 = new artifact(0);
//    artifact* art1 = new artifact(1);
//    artifact* art2 = new artifact(2);
//    artifact* art2_1 = new artifact(2);
//    artifact* art2_2 = new artifact(2);
//    artifact* art2_3 = new artifact(2);
//
//    c.get_artifact(art0);
//    art0 = nullptr;
//
//    std::cout << "c: " << c.max_hp() << ' ' << c.hp() << ' ' << c.damage() << '\n';
//
//    c.delete_artifact(0);
//
//    std::cout << "c: " << c.max_hp() << ' ' << c.hp() << ' ' << c.damage() << '\n';
//
//    c.get_artifact(art1);
//    art1 = nullptr;
//
//    std::cout << "c: " << c.max_hp() << ' ' << c.hp() << ' ' << c.damage() << '\n';
//
//    c.get_artifact(art2);
//    art2 = nullptr;
//
//    std::cout << "c: " << c.max_hp() << ' ' << c.hp() << ' ' << c.damage() << '\n';
//
//    c.get_artifact(art2_1);
//    art2_1 = nullptr;
//    c.get_artifact(art2_2);
//    art2_2 = nullptr;
//    c.get_artifact(art2_3);
//    art2_3 = nullptr;
//
//    std::cout << "c: " << c.max_hp() << ' ' << c.hp() << ' ' << c.damage() << '\n';
//    std::cout << "c1: " << c1.max_hp() << ' ' << c1.hp() << ' ' << c1.damage() << '\n';
//
//    c.attack(&c1);
//
//    std::cout << "c: " << c.max_hp() << ' ' << c.hp() << ' ' << c.damage() << '\n';
//    std::cout << "c1: " << c1.max_hp() << ' ' << c1.hp() << ' ' << c1.damage() << '\n';
//
//    c.attack(&c1);
//
//    std::cout << "c: " << c.max_hp() << ' ' << c.hp() << ' ' << c.damage() << '\n';
//    std::cout << "c1: " << c1.max_hp() << ' ' << c1.hp() << ' ' << c1.damage() << '\n';
//
//    c.attack(&c1);
//
//    std::cout << "c: " << c.max_hp() << ' ' << c.hp() << ' ' << c.damage() << '\n';
//    std::cout << "c1: " << c1.max_hp() << ' ' << c1.hp() << ' ' << c1.damage() << '\n';
//
//    std::cout << c1.alive() << '\n';
//
//    delete art0;
//    delete art1;
//    delete art2;
}
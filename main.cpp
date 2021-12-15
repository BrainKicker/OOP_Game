#include <iostream>

#include "lib/containers/vector/vector.h"

#include "lib/containers/pair/pair.h"

#include "lib/containers/string/string.h"

#include "prog/field/field.h"
#include "prog/adapters/sfml/sfml_adapter.h"

int main() {

    sfml_adapter adapter(3);
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
// Treeningkava funktsionaalsus

#include "../include/treeningkava.h"
#include <iostream>

Treeningkava::Treeningkava(const std::vector<std::string>& treeningpaevad) : treeningpaevad(treeningpaevad) {}

void Treeningkava::kuva_treeningkava() {
    std::cout << "Treeningpäevad: ";
    for (const auto& paev : treeningpaevad) {
        std::cout << paev << " ";
    }
    std::cout << std::endl;
}


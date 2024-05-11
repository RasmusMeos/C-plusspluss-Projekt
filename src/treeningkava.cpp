// Treeningkava funktsionaalsus

/* #include "../include/treeningkava.h"
#include <iostream>

Treeningkava::Treeningkava(const std::vector<std::string>& treeningpaevad) : treeningpaevad(treeningpaevad) {}

void Treeningkava::kuva_treeningkava() {
    std::cout << "Treeningpäevad: ";
    for (const auto& paev : treeningpaevad) {
        std::cout << paev << " ";
    }
    std::cout << std::endl;
} */

#include "../include/treeningkava.h"
#include <iostream>

Treeningkava::Treeningkava(std::map<std::string,std::string> &kava) : kava(kava) {};



void Treeningkava::kuva_treeningkava() {
    std::cout << "Treeningpaevad: \n";
    for (const auto& pair : kava) {
        std::cout << pair.first << ": \n" << pair.second << std::endl;
    }
    std::cout << std::endl;
}
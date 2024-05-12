// Treeningkava funktsionaalsus
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
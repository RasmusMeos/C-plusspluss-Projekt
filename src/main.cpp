#include <iostream>
#include "../include/kasutaja.h"
#include "../include/treeningkava.h"
#include "../lib/json.hpp"
#include <fstream>
#include <vector>

int main() {
    std::string nimi;
    int vanus;
    float kaal;
    std::string eesmark;

    std::cout << "Sisesta oma nimi: ";
    std::cin >> nimi;
    std::cout << "Sisesta oma vanus: ";
    std::cin >> vanus;
    std::cout << "Sisesta oma kaal (kg): ";
    std::cin >> kaal;
    std::cout << "Sisesta oma fitness eesmärk: ";
    std::cin >> eesmark;

    Kasutaja kasutaja(nimi, vanus, kaal, eesmark);
    kasutaja.kuva_andmed();

    std::vector<std::string> paevad = {"esmaspäev", "kolmapäev", "reede"};
    Treeningkava kava(paevad);
    kava.kuva_treeningkava();

    nlohmann::json j;
    j["kasutaja"] = {{"nimi", nimi}, {"vanus", vanus}, {"kaal", kaal}, {"eesmärk", eesmark}};
    j["treeningkava"] = {"treeningpäevad", paevad};

    std::ofstream file("data/kavad.json");
    file << j.dump(4);
    file.close();

    return 0;
}


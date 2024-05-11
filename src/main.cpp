#include <iostream>
#include <fstream>
#include <map>
#include "../include/kasutaja.h"
#include "../include/treeningkava.h"
#include "../lib/json.hpp"


/**
 * Kogub kasutaja andmed standardse sisendi kaudu.
 * @param nimi Kasutaja nimi.
 * @param vanus Kasutaja vanus.
 * @param kaal Kasutaja kaal kilogrammides.
 * @param eesmark Kasutaja fitness eesmärk.
 */
void koguKasutajaAndmed(std::string& nimi, int& vanus, float& kaal, std::string& eesmark) {
    std::cout << "Sisesta oma nimi: ";
    std::cin >> nimi;
    std::cout << "Sisesta oma vanus: ";
    std::cin >> vanus;
    if (vanus < 0) {
        std::cerr << "Error: Vanus peab olema positiivne!\n";
        exit(1);
    }
    std::cout << "Sisesta oma kaal (kg): ";
    std::cin >> kaal;
    if (kaal <= 0) {
        std::cerr << "Error: Kaal peab olema suurem kui 0!\n";
        exit(1);
    }
    std::cout << "Sisesta oma fitness eesmärk: ";
    std::cin >> eesmark;
}


/**
 * Initsialiseerib Kasutaja objekti ja kuvab andmed.
 * @param nimi Kasutaja nimi.
 * @param vanus Kasutaja vanus.
 * @param kaal Kasutaja kaal kilogrammides.
 * @param eesmark Kasutaja fitness eesmärk.
 */
void initsialiseeriKasutaja(const std::string& nimi, int vanus, float kaal, const std::string& eesmark) {
    Kasutaja kasutaja(nimi, vanus, kaal, eesmark);
    kasutaja.kuva_andmed();
}


//Loob ja kuvab treeningkava.
void initsialiseeriTreeningkava() {
    std::map<std::string, std::string> treeningKava = {
            {"esmaspäev", "30 min kardiotreening"},
            {"kolmapäev", "Jõutrenn - 'Pushday': Rind ja käed"},
            {"reede", "Jõutrenn - 'Pullday': Selg ja käed"}
    };
    Treeningkava kava(treeningKava);
    kava.kuva_treeningkava();
}


/**
 * Laeb või initsialiseerib JSON objekti failist.
 * @param failiTee Tee JSON failini.
 * @return Initsialiseeritud või olemasolev JSON objekt.
 */
nlohmann::json initsialiseeriJson(const std::string& failiTee) {
    std::ifstream inputFile(failiTee);
    nlohmann::json j;

    // Vaatab, et fail eksisteerib ega oleks tühi
    if (inputFile.peek() != std::ifstream::traits_type::eof()) {
        inputFile >> j;  // Loeme olemasoleva JSON'i sisse
    } else {
        // Kui faili ei eksisteeri või on tühi, loome uue JSON'i struktuuri
        j = {{"kasutaja", nlohmann::json::array()}};
    }
    inputFile.close();
    return j;
}


/**
 * Uuendab JSON objekti uue kasutaja või olemasoleva kasutaja andmetega ja kirjutab muudatused faili.
 * @param j Viide JSON objektile.
 * @param failiTee Tee JSON failini.
 * @param nimi Kasutaja nimi.
 * @param vanus Kasutaja vanus.
 * @param kaal Kasutaja kaal.
 * @param eesmark Kasutaja eesmärk.
 */
void uuendaJson(nlohmann::json& j, const std::string& failiTee, const std::string& nimi, int vanus, float kaal, const std::string& eesmark) {
    nlohmann::json uusSissekanne = {
            {"vanus", vanus},
            {"kaal", kaal},
            {"eesmärk", eesmark},
            {"treeningkava", {
                              {"esmaspäev", "30 min kardiotreening"},
                              {"kolmapäev", "Jõutrenn - 'Pushday': Rind ja käed"},
                              {"reede", "Jõutrenn - 'Pullday': Selg ja käed"}
                      }}
    };

    bool kasutajaLeitud = false;
    for (auto& user : j["kasutaja"]) {
        if (user["nimi"] == nimi) {
            user["sissekanded"].push_back(uusSissekanne);
            kasutajaLeitud = true;
            break;
        }
    }

    if (!kasutajaLeitud) {
        nlohmann::json uusKasutaja = {
                {"nimi", nimi},
                {"sissekanded", nlohmann::json::array({uusSissekanne})}
        };
        j["kasutaja"].push_back(uusKasutaja);
    }

    std::ofstream outputFile(failiTee);
    if (!outputFile) {
        std::cerr << "Error: Pole võimalik JSON'i faili kirjutamiseks avada!";
        return;
    }
    outputFile << j.dump(4);
    outputFile.close();
}


/**
 * Käitleb kogu JSONiga seotud protsessi alates laadimisest kuni uuendamiseni.
 * @param failiTee Tee JSON failini.
 * @param nimi Kasutaja nimi.
 * @param vanus Kasutaja vanus.
 * @param kaal Kasutaja kaal.
 * @param eesmark Kasutaja eesmärk.
 */
void kaitleJson(const std::string& failiTee, const std::string& nimi, int vanus, float kaal, const std::string& eesmark) {
    nlohmann::json j = initsialiseeriJson(failiTee);
    uuendaJson(j, failiTee, nimi, vanus, kaal, eesmark);
}

int main() {
    std::string failiTee = "../data/kavad.json";
    std::string nimi;
    int vanus;
    float kaal;
    std::string eesmark;

    koguKasutajaAndmed(nimi, vanus, kaal, eesmark);
    initsialiseeriKasutaja(nimi, vanus, kaal, eesmark);
    initsialiseeriTreeningkava();
    kaitleJson(failiTee, nimi, vanus, kaal, eesmark);

    return 0;
}

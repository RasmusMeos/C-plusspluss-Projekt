#include "../include/jsonHaldaja.h"
#include <fstream>
#include <iostream>
#include <limits>

std::vector<std::string> laeTreeningPlaan(const std::string& failiTee, int& valik) {
    std::ifstream inputFile(failiTee);
    json j;
    if (inputFile) {
        inputFile >> j;
        inputFile.close();
    } else {
        std::cerr << "Error: Ei saa avada plaanid.json faili.\n";
        exit(1);
    }

    std::vector<std::string> plaan;
    switch (valik) {
        case 1:
            plaan = j["kavad"]["iga_teine_päev"].get<std::vector<std::string>>();
            break;
        case 2:
            plaan = j["kavad"]["iga_kolmas_päev"].get<std::vector<std::string>>();
            break;
        case 3:
            plaan = j["kavad"]["ainult_nädalavahetused"].get<std::vector<std::string>>();
            break;
    }
    return plaan;
}

std::map<std::string, std::vector<std::pair<std::string, std::string>>> laeHarjutused(const std::string& failiTee) {
    std::ifstream inputFile(failiTee);
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> harjutused;

    if (inputFile) {
        json j;
        inputFile >> j;
        inputFile.close();

        for (auto& element : j.items()) {
            std::string kategooria = element.key();
            for (auto& harjutus : element.value()) {
                std::string nimetus = harjutus["harjutus"];
                std::string detailid = harjutus.contains("kordused") ? harjutus["kordused"] : harjutus["kestvus"];
                harjutused[kategooria].emplace_back(nimetus, detailid);
            }
        }
    } else {
        std::cerr << "Error: Pole võimalik JSON'i faili avada! " << failiTee << std::endl;
    }

    return harjutused;
}

/**
 * Laeb või initsialiseerib JSON objekti failist.
 * @param failiTee Tee JSON failini.
 * @return Initsialiseeritud või olemasolev JSON objekt.
 */
json initsialiseeriJson(const std::string& failiTee) {
    std::ifstream inputFile(failiTee);
    json j;

    // Vaatab, et fail eksisteerib ega oleks tühi
    if (inputFile.peek() != std::ifstream::traits_type::eof()) {
        inputFile >> j;  // Loeme olemasoleva JSON'i sisse
    } else {
        // Kui faili ei eksisteeri või on tühi, loome uue JSON'i struktuuri
        j = {{"kasutaja", json::array()}};
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
    json uusSissekanne = {
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
        json uusKasutaja = {
                {"nimi", nimi},
                {"sissekanded", json::array({uusSissekanne})}
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
    json j = initsialiseeriJson(failiTee);
    uuendaJson(j, failiTee, nimi, vanus, kaal, eesmark);
}
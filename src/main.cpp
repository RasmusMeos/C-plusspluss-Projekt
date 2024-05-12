#include <iostream>
#include <fstream>
#include <vector>
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

    while (true) {
        std::cout << "Sisesta oma vanus: ";
        std::cin >> vanus;
        if (std::cin.fail() || vanus < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Vanus peab olema positiivne ja numbriline. Proovi uuesti.\n";
            continue;
        }
        if (vanus < 17) {
            std::cout << "Hoiatus: Oled alla 17 aasta vanune. Palun konsulteeri treeneriga enne treeningprogrammi alustamist. (Vajuta sisestusklahvi jätkamiseks)\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
        break;
    }

    while (true) {
        std::cout << "Sisesta oma kaal (kg): ";
        std::cin >> kaal;
        if (std::cin.fail() || kaal <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Kaal peab olema suurem kui 0 ja numbriline. Proovi uuesti.\n";
            continue;
        }
        break;
    }

    std::cout << "Sisesta oma fitness eesmärk: ";
    std::cin >> eesmark;
}


std::vector<std::string> laeTreeningPlaan(const std::string& failiTee, int& valik) {
    std::ifstream inputFile(failiTee);
    nlohmann::json j;
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

int kasutajaValik(const std::string& teade) {
    int valik;
    do {
        std::cout << teade;
        std::cin >> valik;
        if (std::cin.fail() || valik < 1 || valik > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Palun sisesta korrektne valik (1, 2 või 3).\n";
            continue;
        }
        break;
    } while (true);
    return valik;
}

//Abimeetod info kuvamiseks
void kuvaInfot(const std::vector<std::string>& list) {
    for (const auto& yksus : list) {
        std::cout << yksus << std::endl;
    }
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
    /* std::string failiTeeKavad = "../data/kavad.json";
     * std::string failiTeeHarjutused = "../data/harjutused.json"; */


    std::string failiTeePlaanid = "../data/plaanid.json";
    std::string nimi;
    int vanus, plaaniValik;
    float kaal;
    std::string eesmark;

    koguKasutajaAndmed(nimi, vanus, kaal, eesmark);

    plaaniValik = kasutajaValik("Vali oma treeningplaan (1: iga teine päev, 2: iga kolmas päev, 3: ainult nädalavahetused): ");
    auto treeningPlaan = laeTreeningPlaan(failiTeePlaanid, plaaniValik);
    kuvaInfot(treeningPlaan);

    int rutiiniValik = kasutajaValik("Vali oma treenimistüüp (1: ainult jõusaal, 2: ainult kardio, 3: kombinatsioon mõlemast): ");


    std::vector<std::vector<std::string>> genereeritudKavad;

    for (int i = 0; i < genereeritudKavad.size(); i++) {
        std::cout << "Kava " << i+1 << ":\n";
        kuvaInfot(genereeritudKavad[i]);
    }

    int kavaValik = kasutajaValik("Vali endale sobiv treeningkava: (treeningkava number)");
    std::cout << "Teie valitud treeningkava:\n";
    kuvaInfot(genereeritudKavad[kavaValik -1]);


   /* koguKasutajaAndmed(nimi, vanus, kaal, eesmark);
    initsialiseeriKasutaja(nimi, vanus, kaal, eesmark);
    initsialiseeriTreeningkava();
    kaitleJson(failiTeePlaanid, nimi, vanus, kaal, eesmark); */

    return 0;

}

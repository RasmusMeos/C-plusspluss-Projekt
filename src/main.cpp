#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <limits>
#include <chrono>
#include <thread>
#include <ctime>
#include "../include/kasutaja.h"
#include "../include/treeningkava.h"
#include "../lib/json.hpp"

using json = nlohmann::json;


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
            std::cout << "Hoiatus: Oled alla 17 aasta vanune. Palun konsulteeri treeneriga enne treeningprogrammi alustamist. (Vajuta 'Enter' jätkamiseks)\n";
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

void taastaHarjutusteList(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
                          const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal) {
    harjutused = harjutusedOriginaal;
}



std::vector<std::pair<std::string, std::string>> genereeriTreeningSessioon(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        const std::vector<std::string>& kategooriad, int mituHarjutust, bool lahtesta) {

    if (lahtesta) {
        taastaHarjutusteList(harjutused, harjutusedOriginaal);
    }

    std::vector<std::pair<std::string, std::string>> treeningSessioon;
    for (int i = 0; i < mituHarjutust; ++i) {
        const auto& kategooria = kategooriad[rand() % kategooriad.size()];
        auto& harjutusteList = harjutused[kategooria];
        if (!harjutusteList.empty()) {
            int idx = rand() % harjutusteList.size();
            treeningSessioon.push_back(harjutusteList[idx]);
            harjutusteList.erase(harjutusteList.begin() + idx);
        }
    }
    return treeningSessioon;
}

std::vector<std::vector<std::pair<std::string, std::string>>> genereeriIgaKolmasPaevKavad(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        int rutiiniValik) {

    std::vector<std::string> jousaalKategooriad = {"push", "pull", "jalad", "core"};
    std::vector<std::string> kardioKategooriad = {"cardio"};
    std::vector<std::vector<std::pair<std::string, std::string>>> kavad;
    bool jousaaliPaev;

    for (int paev = 1; paev <= 7; ++paev) {
        if (rutiiniValik == 1) {  // ainult jõusaal
            kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, jousaalKategooriad, 8, paev % 2 != 0));
        } else if (rutiiniValik == 2) {  // ainult kardio
            kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, kardioKategooriad, 4, true));
        } else if (rutiiniValik == 3) {  // kombinatsioon mõlemast
            jousaaliPaev = (paev % 2 != 0);  // Alustades jõusaaliga
            if (jousaaliPaev) {
                kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, jousaalKategooriad, 8, true));
            } else {
                kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, kardioKategooriad, 4, true));
            }
        }
    }

    taastaHarjutusteList(harjutused, harjutusedOriginaal);
    return kavad;
}


std::vector<std::vector<std::pair<std::string, std::string>>> genereeriIgaTeinePaevKavad(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        int rutiiniValik) {

    std::vector<std::string> jousaalKategooriad1 = {"push", "jalad"};
    std::vector<std::string> jousaalKategooriad2 = {"pull", "core"};
    std::vector<std::string> jousaalKategooriad = {"push", "pull", "jalad", "core"};
    std::vector<std::string> kardioKategooriad = {"cardio"};
    std::vector<std::vector<std::pair<std::string, std::string>>> kavad;
    bool jousaaliPaev;

    for (int paev = 1; paev <= 6; ++paev) {
        if (rutiiniValik == 1) {  // ainult jõusaal
            std::vector<std::string>& valitudKategooriad = (paev % 2 != 0) ? jousaalKategooriad1 : jousaalKategooriad2;
            kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, valitudKategooriad, 6, true));
        } else if (rutiiniValik == 2) {  // ainult kardio
            kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, kardioKategooriad, 3, true));
        } else if (rutiiniValik == 3) {  // kombinatsioon mõlemast
            jousaaliPaev = (paev % 2 != 0);  // Alustades jõusaaliga
            if (jousaaliPaev) {
                kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, jousaalKategooriad, 6, true));
            } else {
                kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, kardioKategooriad, 3, true));
            }
        }
    }

    taastaHarjutusteList(harjutused, harjutusedOriginaal);
    return kavad;
}




std::vector<std::vector<std::pair<std::string, std::string>>> genereeriNadalavahetuseKavad(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        int rutiiniValik) {

    std::vector<std::vector<std::pair<std::string, std::string>>> kavad;
    std::vector<std::string> jousaalKategooriad = {"push", "pull", "jalad", "core"};
    std::vector<std::string> kardioKategooriad = {"cardio"};

    if (rutiiniValik == 1) { // Ainult jõusaal
        kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, jousaalKategooriad, 10, false));
        kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, jousaalKategooriad, 10, false));
    } else if (rutiiniValik == 2) { // Ainult kardio
        kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, kardioKategooriad, 5, true));
        kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, kardioKategooriad, 5, true));
    } else if (rutiiniValik == 3) { // Kombinatsioon mõlemast
        kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, jousaalKategooriad, 10, false));
        kavad.push_back(genereeriTreeningSessioon(harjutused, harjutusedOriginaal, kardioKategooriad, 5, true));
    }

    taastaHarjutusteList(harjutused, harjutusedOriginaal);
    return kavad;
}




void kuvaNadalavahetuseKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad) {
    std::cout << "Laupäev:\n";
    for (const auto& harjutus : kavad[0]) {
        std::cout << harjutus.first << " - " << harjutus.second << std::endl;
    }
    std::cout << "----------------------\n";
    std::cout << "Pühapäev:\n";
    for (const auto& harjutus : kavad[1]) {
        std::cout << harjutus.first << " - " << harjutus.second << std::endl;
    }
    std::cout << "----------------------\n";
}

void kuvaIgaKolmasPaevKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad, const std::vector<std::string>& paevad) {
    for (size_t i = 0; i < kavad.size(); ++i) {
        std::cout << paevad[i] << ":\n";
        for (const auto& harjutus : kavad[i]) {
            std::cout << harjutus.first << " - " << harjutus.second << std::endl;
        }
        std::cout << "----------------------\n";
    }
}

void kuvaIgaTeinePaevKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad, const std::vector<std::string>& paevad) {
    for (size_t i = 0; i < kavad.size(); ++i) {
        std::cout << paevad[i] << ":\n";
        for (const auto& harjutus : kavad[i]) {
            std::cout << harjutus.first << " - " << harjutus.second << std::endl;
        }
        std::cout << "----------------------\n";
    }
}


void genereeriKasutajaKavad(const int plaaniValik, const int rutiiniValik,
                             std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
                             std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
                             std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>>& genereeritudKavad) {


    for (int i = 0; i < 3; i++) {
        switch (plaaniValik) {
            case 1:
                genereeritudKavad.push_back(genereeriIgaTeinePaevKavad(harjutused, harjutusedOriginaal, rutiiniValik));
                break;
            case 2:
                genereeritudKavad.push_back(genereeriIgaKolmasPaevKavad(harjutused, harjutusedOriginaal, rutiiniValik));
                break;
            case 3:
                genereeritudKavad.push_back(genereeriNadalavahetuseKavad(harjutused, harjutusedOriginaal, rutiiniValik));
                break;
        }
    }

}

void peataValjund(const std::string& teade) {
    std::cout << teade;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void kuvaKasutajaKavad(int plaaniValik, std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad,
                       std::vector<std::string>& igaTeineKuvamiseks, std::vector<std::string>& igaKolmasKuvamiseks) {

    for (int i = 0; i < genereeritudKavad.size(); i++) {
        std::cout << "Kava " << (i + 1) << ":\n";
        switch (plaaniValik) {
            case 1:
                kuvaIgaTeinePaevKava(genereeritudKavad[i], igaTeineKuvamiseks);
                break;
            case 2:
                kuvaIgaKolmasPaevKava(genereeritudKavad[i], igaKolmasKuvamiseks);
                break;
            case 3:
                kuvaNadalavahetuseKava(genereeritudKavad[i]);
                break;
        }
        if (i < genereeritudKavad.size() - 1) {
            peataValjund("Vajuta 'Enter', et näha järgmist kava...\n");
        }
    }
}

void kuvaKasutajaValitudKava(int plaaniValik, int kavaValik, std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad,
                             std::vector<std::string>& igaTeineKuvamiseks, std::vector<std::string>& igaKolmasKuvamiseks) {

    std::cout << "\nTeie valitud treeningkava:\n";
    switch (plaaniValik) {
        case 1:
            kuvaIgaTeinePaevKava(genereeritudKavad[kavaValik - 1], igaTeineKuvamiseks);
            break;
        case 2:
            kuvaIgaKolmasPaevKava(genereeritudKavad[kavaValik - 1], igaKolmasKuvamiseks);
            break;
        case 3:
            kuvaNadalavahetuseKava(genereeritudKavad[kavaValik - 1]);
            break;
    }
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

//Abimeetod info kuvamiseks
void kuvaJsonPlaan(const std::vector<std::string>& list) {
    for (const auto& yksus : list) {
        std::cout << yksus << std::endl;
    }
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


void viivitaValjund(const std::string& teade, int sek) {
    std::cout << teade << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(sek));
}

int main() {
    // std::string failiTeeKavad = "../data/kavad.json";

    std::string failiTeeHarjutused = "../data/harjutused.json";
    std::string failiTeePlaanid = "../data/plaanid.json";
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> harjutused, harjutusedOriginaal;
    std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad;
    std::string nimi;
    int vanus, plaaniValik, rutiiniValik, kavaValik;
    float kaal;
    std::string eesmark;
    std::vector<std::string> igaTeineKuvamiseks = {
            "Nädal 1 - esmaspäev", "Nädal 1 - kolmapäev", "Nädal 1 - reede",
            "Nädal 1 - pühapäev", "Nädal 2 - teisipäev", "Nädal 2 - laupäev"
    };
    std::vector<std::string> igaKolmasKuvamiseks = {
            "Nädal 1 - esmaspäev", "Nädal 1 - neljapäev", "Nädal 1 - pühapäev",
            "Nädal 2 - kolmapäev", "Nädal 2 - laupäev", "Nädal 3 - teisipäev",
            "Nädal 3 - reede"
    };



    koguKasutajaAndmed(nimi, vanus, kaal, eesmark);

    plaaniValik = kasutajaValik("Vali oma treeningplaan (1: iga teine päev, 2: iga kolmas päev, 3: ainult nädalavahetused): ");

    harjutused = laeHarjutused(failiTeeHarjutused);
    harjutusedOriginaal = harjutused;
    auto treeningPlaan = laeTreeningPlaan(failiTeePlaanid, plaaniValik);
    kuvaJsonPlaan(treeningPlaan);

    rutiiniValik = kasutajaValik("Vali oma treenimistüüp (1: ainult jõusaal, 2: ainult kardio, 3: kombinatsioon mõlemast): ");

    genereeriKasutajaKavad(plaaniValik, rutiiniValik, harjutused, harjutusedOriginaal, genereeritudKavad);
    viivitaValjund("Genereerime teile 3 treeningkava, mille hulgast saate endale sobiva valida. Palun oodake!\n", 3);
    kuvaKasutajaKavad(plaaniValik, genereeritudKavad, igaTeineKuvamiseks, igaKolmasKuvamiseks);

    kavaValik = kasutajaValik("Vali endale sobiv treeningkava (treeningkava number): ");
    kuvaKasutajaValitudKava(plaaniValik, kavaValik, genereeritudKavad, igaTeineKuvamiseks, igaKolmasKuvamiseks);


    /* koguKasutajaAndmed(nimi, vanus, kaal, eesmark);
     initsialiseeriKasutaja(nimi, vanus, kaal, eesmark);
     initsialiseeriTreeningkava();
     kaitleJson(failiTeePlaanid, nimi, vanus, kaal, eesmark); */

    return 0;

}


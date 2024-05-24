#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <thread>
#include "../include/infoKuvaja.h"
#include "../include/jsonHaldaja.h"
#include "../include/trenniGeneraator.h"
#include "../include/kasutaja.h"

bool kasutajaKinnitus(Kasutaja& kasutaja) {
    kasutaja.kuva_andmed();
    std::cout << "Kinnita andmed (Y/N): ";
    char kinnita;
    std::cin >> kinnita;
    return (kinnita == 'Y' || kinnita == 'y');
}

Kasutaja koguKasutajaAndmed(std::string& failiTee, int kordiProovitud) {
    if (kordiProovitud > 2) {
        std::cerr << "Liiga palju uuesti proovitud. Programm sulgub...\n";
        return Kasutaja();
    }
    std::string nimi;
    int vanus;
    float kaal;
    std::string eesmark;

    std::cout << "Sisesta oma nimi: ";
    std::cin >> nimi;

    while (true) {
        std::cout << "Sisesta oma vanus: ";
        std::cin >> vanus;
        if (std::cin.fail() || vanus < 0 || vanus > 125) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Vanus peab olema positiivne, numbriline ja usutav. Proovi uuesti.\n";
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
        if (std::cin.fail() || kaal <= 0 || kaal > 650) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Kaal peab olema suurem kui 0, numbriline ja usutav. Proovi uuesti.\n";
            continue;
        }
        break;
    }

    std::cout << "Sisesta oma fitness eesmärk: ";
    std::cin >> eesmark;

    Kasutaja kasutaja(nimi, vanus, kaal, eesmark);
    if (kasutajaKinnitus(kasutaja)) {
        salvestaKasutaja(failiTee, kasutaja);
    } else {
        std::cout << "Sisesta andmed uuesti.\n";
        koguKasutajaAndmed(failiTee, kordiProovitud+1);
    }
    return kasutaja;
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

void viivitaValjund(const std::string& teade, int sek) {
    std::cout << teade << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(sek));
}

int main() {
    std::string failiTeeKasutajad = "../data/kasutajad.json";
    std::string failiTeeKavad = "../data/kavad.json";
    std::string failiTeeHarjutused = "../data/harjutused.json";
    std::string failiTeePlaanid = "../data/plaanid.json";
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> harjutused, harjutusedOriginaal;
    std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad;
    int plaaniValik, rutiiniValik, kavaValik;
    std::vector<std::string> igaTeineKuvamiseks = {
            "Nädal 1 - esmaspäev", "Nädal 1 - kolmapäev", "Nädal 1 - reede",
            "Nädal 1 - pühapäev", "Nädal 2 - teisipäev", "Nädal 2 - laupäev"
    };
    std::vector<std::string> igaKolmasKuvamiseks = {
            "Nädal 1 - esmaspäev", "Nädal 1 - neljapäev", "Nädal 1 - pühapäev",
            "Nädal 2 - kolmapäev", "Nädal 2 - laupäev", "Nädal 3 - teisipäev",
            "Nädal 3 - reede"
    };



    Kasutaja kasutaja = koguKasutajaAndmed(failiTeeKasutajad,0);

    if (!kasutaja.kasSobiv()) {
        return 1;
    }


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
    salvestaTreeningkava(failiTeeKavad, kasutaja, genereeritudKavad[kavaValik - 1]);
    viivitaValjund("Salvestame teie valitud kava. Palun oodake!\n", 2);
    kuvaKasutajaValitudKava(plaaniValik, kavaValik, genereeritudKavad, igaTeineKuvamiseks, igaKolmasKuvamiseks);
    std::cout << "Teie kava on edukalt salvestatud!" << std::endl;



    return 0;

}


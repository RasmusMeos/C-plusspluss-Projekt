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


/**
 * Kinnitab kasutaja andmed konsooli sisendi kaudu.
 * @param kasutaja Viide Kasutaja objektile, mis sisaldab kasutaja andmeid.
 * @return Tagastab true, kui kasutaja kinnitab andmed sisestades 'Y' või 'y'; vastasel juhul tagastab false.
 */
bool kasutajaKinnitus(Kasutaja& kasutaja) {
    std::cout << "\nÜlevaade: " << std::endl;
    kasutaja.kuva_andmed();
    std::cout << "Kinnita andmed (Y/N): ";
    char kinnita;
    std::cin >> kinnita;
    return (kinnita == 'Y' || kinnita == 'y');
}

/**
 * Valideerib numbrilisi sisendeid määratud piiridega.
 * @param vaartus Viide muutujale, kuhu sisend salvestatakse.
 * @param teade Kasutajale kuvatava küsimuse sõnum.
 * @param veateade Veasõnum, mis kuvatakse sisendi valideerimise ebaõnnestumisel.
 * @param min Minimaalne aktsepteeritav väärtus.
 * @param max Maksimaalne aktsepteeritav väärtus.
 * @return Tagastab true, kui sisend on edukalt valideeritud ja salvestatud.
 */
template<typename T>
bool valideeriNumbrilineSisend(T& vaartus, const std::string& teade, const std::string& veateade, T min, T max) {
    while (true) {
        std::cout << teade;
        std::cin >> vaartus;
        if (std::cin.fail() || vaartus < min || vaartus > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << veateade << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }
}

/**
 * Valideerib sõne sisendeid, tagades, et need ei ole tühjad.
 * @param vaartus Viide string muutujale, kuhu sisend salvestatakse.
 * @param teade Kasutajale kuvatava küsimuse sõnum.
 * @param veateade Vea sõnum, mis kuvatakse kui sisend on sobimatu.
 * @return Tagastab true, kui sisend on edukalt valideeritud ja salvestatud.
 */
bool valideeriSoneSisend(std::string& vaartus, const std::string& teade, const std::string& veateade) {
    while (true) {
        std::cout << teade;
        std::getline(std::cin, vaartus);
        if (vaartus.empty()) {
            std::cerr << veateade << std::endl;
            continue;
        }
        return true;
    }
}

/**
 * Kogub kasutaja andmed ja valideerib neid.
 * @param failiTee Faili tee, kuhu kasutaja andmed salvestatakse.
 * @param kordiProovitud Arv, mis näitab, mitu korda kasutaja on andmeid sisestanud.
 * @return Tagastab Kasutaja objekti, kui andmed on edukalt kogutud ja valideeritud; vastasel juhul tagastab tühja objekti.
 */
Kasutaja koguKasutajaAndmed(std::string& failiTee, int kordiProovitud) {
    if (kordiProovitud > 2) {
        std::cerr << "Liiga palju uuesti proovitud. Programm sulgub...\n";
        return {}; //saaks kohe ka 'exit(1)' kasutada
    }
    std::string nimi, eesmark;
    int vanus;
    float kaal;

    valideeriSoneSisend(nimi, "Sisesta oma nimi: ", "Nimi ei tohi olla tühi. Proovi uuesti!");
    valideeriNumbrilineSisend(vanus, "Sisesta oma vanus: ", "Error: Vanus peab olema positiivne, numbriline ja vahemikus 0-125. Proovi uuesti!",0,125);

        if (vanus < 17) {
            std::cout << "Hoiatus: Oled alla 17 aasta vanune. Palun konsulteeri treeneriga enne treeningprogrammi alustamist. (Vajuta 'Enter' jätkamiseks)\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    valideeriNumbrilineSisend(kaal, "Sisesta oma kaal (kg): ", "Error: Kaal peab olema suurem kui 0, numbriline ja vahemikus 0-650 (kg). Proovi uuesti!", 0.1f, 650.0f);
    valideeriSoneSisend(eesmark,"Sisesta oma fitness eesmärk: ", "Fitness eesmärk ei tohi olla tühi. Proovi uuesti!");

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
 * Küsib kasutajalt valikut konkreetse küsimuse alusel.
 * @param teade Sõnum, mis esitatakse kasutajale.
 * @return Tagastab kasutaja sisestatud valiku numbrina.
 */
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

/**
 * Viivitab teatud aja ja kuvab seejärel teate.
 * @param teade Sõnum, mida kuvada.
 * @param sek Sekundid, kui kaua viivitamine kestab.
 */
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

    if (!kasutaja.kasSobiv()) { // täiendav kontroll
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


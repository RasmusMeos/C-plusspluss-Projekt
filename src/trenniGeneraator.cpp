#include "../include/trenniGeneraator.h"
#include <cstdlib>
#include <ctime>

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

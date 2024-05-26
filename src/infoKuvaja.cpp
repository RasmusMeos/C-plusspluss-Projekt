#include "../include/infoKuvaja.h"
#include <iostream>

void peataValjund(const std::string& teade) {
    std::cout << teade;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void kuvaJsonPlaan(const std::vector<std::string>& list) {
    for (const auto& yksus : list) {
        std::cout << yksus << std::endl;
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

void kuvaIgaKolmasPaevKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad, const std::vector<std::string>& paevad) {
    for (size_t i = 0; i < kavad.size(); ++i) {
        std::cout << paevad[i] << ":\n";
        for (const auto& harjutus : kavad[i]) {
            std::cout << harjutus.first << " - " << harjutus.second << std::endl;
        }
        std::cout << "----------------------\n";
    }
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
            peataValjund("Vajuta 'Enter' (vajadusel 2 korda), et näha järgmist kava...\n");
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
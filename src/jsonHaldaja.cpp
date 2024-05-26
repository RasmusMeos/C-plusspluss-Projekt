#include "../include/jsonHaldaja.h"

void salvestaKasutaja(const std::string& failiTee, const Kasutaja& kasutaja) {
    json j;
    std::ifstream inputFile(failiTee);

    if (inputFile.peek() != std::ifstream::traits_type::eof()) {
        inputFile >> j;
    } else {
        j = {{"kasutajad", json::array()}};
    }
    inputFile.close();

    json uusKasutaja = {
            {"nimi", kasutaja.getNimi()},
            {"vanus", kasutaja.getVanus()},
            {"kaal", kasutaja.getKaal()},
            {"eesmärk", kasutaja.getEesmark()}
    };

    j["kasutajad"].push_back(uusKasutaja);

    std::ofstream outputFile(failiTee);
    if (!outputFile) {
        std::cerr << "Error: Pole võimalik JSON'i faili kirjutamiseks avada!\n";
        exit(1);
    }
    outputFile << j.dump(4);
    outputFile.close();
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
        std::cerr << "Error: Pole võimalik JSON'i faili avada!\n" << failiTee << std::endl;
        exit(1);
    }

    return harjutused;
}

void salvestaTreeningkava(const std::string& failiTee, const Kasutaja& kasutaja, const std::vector<std::vector<std::pair<std::string, std::string>>>& valitudKava) {
    std::string nimi = kasutaja.getNimi();
    std::ifstream inputFile(failiTee);
    nlohmann::json j;
    if (inputFile.peek() != std::ifstream::traits_type::eof()) {
        inputFile >> j;
    } else {
        j = nlohmann::json::object();
    }
    inputFile.close();

    nlohmann::json kavaJson;
    for (const auto& sessioon : valitudKava) {
        nlohmann::json sessioonJson;
        for (const auto& trenn : sessioon) {
            sessioonJson["treeningsessioon"].push_back({{"harjutus", trenn.first}, {"detailid", trenn.second}});
        }
        kavaJson["sessioonid"].push_back(sessioonJson);
    }

    j[nimi]["treeningkavad"].push_back({{"kava", kavaJson}});

    std::ofstream outputFile(failiTee);
    if (!outputFile) {
        std::cerr << "Error: Pole võimalik JSON'i faili kirjutamiseks avada!\n";
        exit(1);
    }
    outputFile << j.dump(4);
    outputFile.close();
}
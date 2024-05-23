#ifndef C_PLUSSPLUSS_PROJEKT_TRENNIGENERAATOR_H
#define C_PLUSSPLUSS_PROJEKT_TRENNIGENERAATOR_H

#include <vector>
#include <map>
#include <string>
#include <utility>

void taastaHarjutusteList(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
                          const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal);

std::vector<std::pair<std::string, std::string>> genereeriTreeningSessioon(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        const std::vector<std::string>& kategooriad, int mituHarjutust, bool lahtesta);

std::vector<std::vector<std::pair<std::string, std::string>>> genereeriIgaTeinePaevKavad(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        int rutiiniValik);

std::vector<std::vector<std::pair<std::string, std::string>>> genereeriIgaKolmasPaevKavad(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        int rutiiniValik);

std::vector<std::vector<std::pair<std::string, std::string>>> genereeriNadalavahetuseKavad(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        int rutiiniValik);

void genereeriKasutajaKavad(const int plaaniValik, const int rutiiniValik,
                            std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
                            std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
                            std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>>& genereeritudKavad);




#endif //C_PLUSSPLUSS_PROJEKT_TRENNIGENERAATOR_H

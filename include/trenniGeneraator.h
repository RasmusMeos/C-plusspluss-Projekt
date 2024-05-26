#ifndef C_PLUSSPLUSS_PROJEKT_TRENNIGENERAATOR_H
#define C_PLUSSPLUSS_PROJEKT_TRENNIGENERAATOR_H

#include <vector>
#include <map>
#include <string>
#include <utility>

/**
 * Taastab harjutuste nimekirja algseisundisse.
 * @param harjutused Harjutuste nimekiri, mida taastada.
 * @param harjutusedOriginaal Algne harjutuste nimekiri.
 */
void taastaHarjutusteList(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
                          const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal);

/**
 * Genereerib treeningsessiooni.
 * @param harjutused Harjutuste nimekiri.
 * @param harjutusedOriginaal Algne harjutuste nimekiri.
 * @param kategooriad Harjutuste kategooriad.
 * @param mituHarjutust Harjutuste arv.
 * @param lahtesta Kui tõene, taastatakse harjutuste nimekiri enne genereerimist.
 * @return Vektor treeningsessiooni harjutustest.
 */
std::vector<std::pair<std::string, std::string>> genereeriTreeningSessioon(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        const std::vector<std::string>& kategooriad, int mituHarjutust, bool lahtesta);

/**
 * Genereerib iga-teine-päev kavad.
 * @param harjutused Harjutuste nimekiri.
 * @param harjutusedOriginaal Algne harjutuste nimekiri.
 * @param rutiiniValik Kasutaja rutiini valik.
 * @return Vektor iga-teine-päev kavadest.
 */
std::vector<std::vector<std::pair<std::string, std::string>>> genereeriIgaTeinePaevKavad(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        int rutiiniValik);

/**
 * Genereerib iga-kolmas-päev kavad.
 * @param harjutused Harjutuste nimekiri.
 * @param harjutusedOriginaal Algne harjutuste nimekiri.
 * @param rutiiniValik Kasutaja rutiini valik.
 * @return Vektor-iga-kolmas päev kavadest.
 */
std::vector<std::vector<std::pair<std::string, std::string>>> genereeriIgaKolmasPaevKavad(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        int rutiiniValik);

/**
 * Genereerib nädalavahetuse kavad.
 * @param harjutused Harjutuste nimekiri.
 * @param harjutusedOriginaal Algne harjutuste nimekiri.
 * @param rutiiniValik Kasutaja rutiini valik.
 * @return Vektor nädalavahetuse kavadest.
 */
std::vector<std::vector<std::pair<std::string, std::string>>> genereeriNadalavahetuseKavad(
        std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
        const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
        int rutiiniValik);

/**
 * Genereerib kasutaja kavad vastavalt plaani ja rutiini valikule.
 * @param plaaniValik Kasutaja plaani valik.
 * @param rutiiniValik Kasutaja rutiini valik.
 * @param harjutused Harjutuste nimekiri.
 * @param harjutusedOriginaal Algne harjutuste nimekiri.
 * @param genereeritudKavad Genereeritud kavad.
 */
void genereeriKasutajaKavad(const int plaaniValik, const int rutiiniValik,
                            std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused,
                            std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal,
                            std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>>& genereeritudKavad);

#endif //C_PLUSSPLUSS_PROJEKT_TRENNIGENERAATOR_H

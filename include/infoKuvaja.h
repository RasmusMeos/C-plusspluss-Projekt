#ifndef C_PLUSSPLUSS_PROJEKT_INFOKUVAJA_H
#define C_PLUSSPLUSS_PROJEKT_INFOKUVAJA_H

#include <vector>
#include <string>
#include <utility> // std::pair jaoks
#include <limits>

/**
 * Peatab väljundi ja ootab kasutaja sisendit.
 * @param teade Teade, mida kuvada.
 */
void peataValjund(const std::string& teade);

/**
 * Kuvab JSON (päevade) plaani.
 * @param list Vektor plaani üksustest.
 */
void kuvaJsonPlaan(const std::vector<std::string>& list);

/**
 * Kuvab iga-teine-päev kava.
 * @param kavad Vektor kavast.
 * @param paevad Vektor päevadest.
 */
void kuvaIgaTeinePaevKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad, const std::vector<std::string>& paevad);

/**
 * Kuvab iga-kolmas-päev kava.
 * @param kavad Vektor kavast.
 * @param paevad Vektor päevadest.
 */
void kuvaIgaKolmasPaevKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad, const std::vector<std::string>& paevad);

/**
 * Kuvab nädalavahetuse kava.
 * @param kavad Vektor kavast.
 */
void kuvaNadalavahetuseKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad);

/**
 * Kuvab kasutaja kavad vastavalt plaani valikule.
 * @param plaaniValik Kasutaja plaani valik.
 * @param genereeritudKavad Genereeritud kavad.
 * @param igaTeineKuvamiseks Päevad iga-teine-päev kava kuvamiseks.
 * @param igaKolmasKuvamiseks Päevad iga-kolmas-päev kava kuvamiseks.
 */
void kuvaKasutajaKavad(int plaaniValik, std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad,
                       std::vector<std::string>& igaTeineKuvamiseks, std::vector<std::string>& igaKolmasKuvamiseks);

/**
 * Kuvab kasutaja valitud kava vastavalt plaani ja kava valikule.
 * @param plaaniValik Kasutaja plaani valik.
 * @param kavaValik Kasutaja kava valik.
 * @param genereeritudKavad Genereeritud kavad.
 * @param igaTeineKuvamiseks Päevad iga-teine-päev kava kuvamiseks.
 * @param igaKolmasKuvamiseks Päevad iga-kolmas-päev kava kuvamiseks.
 */
void kuvaKasutajaValitudKava(int plaaniValik, int kavaValik, std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad,
                             std::vector<std::string>& igaTeineKuvamiseks, std::vector<std::string>& igaKolmasKuvamiseks);

#endif //C_PLUSSPLUSS_PROJEKT_INFOKUVAJA_H

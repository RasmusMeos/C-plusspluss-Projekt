#ifndef C_PLUSSPLUSS_PROJEKT_INFOKUVAJA_H
#define C_PLUSSPLUSS_PROJEKT_INFOKUVAJA_H

#include <vector>
#include <string>
#include <utility> // std::pair jaoks

void peataValjund(const std::string& teade);
void kuvaJsonPlaan(const std::vector<std::string>& list);
void kuvaIgaTeinePaevKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad, const std::vector<std::string>& paevad);
void kuvaIgaKolmasPaevKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad, const std::vector<std::string>& paevad);
void kuvaNadalavahetuseKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad);

void kuvaKasutajaKavad(int plaaniValik, std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad,
                       std::vector<std::string>& igaTeineKuvamiseks, std::vector<std::string>& igaKolmasKuvamiseks);

void kuvaKasutajaValitudKava(int plaaniValik, int kavaValik, std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad,
                             std::vector<std::string>& igaTeineKuvamiseks, std::vector<std::string>& igaKolmasKuvamiseks);

#endif //C_PLUSSPLUSS_PROJEKT_INFOKUVAJA_H

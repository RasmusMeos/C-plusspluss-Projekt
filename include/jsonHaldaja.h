#ifndef C_PLUSSPLUSS_PROJEKT_JSONHALDAJA_H
#define C_PLUSSPLUSS_PROJEKT_JSONHALDAJA_H

#include <vector>
#include <map>
#include <string>
#include "../lib/json.hpp"

using json = nlohmann::json;

std::vector<std::string> laeTreeningPlaan(const std::string& failiTee, int& valik);
std::map<std::string, std::vector<std::pair<std::string, std::string>>> laeHarjutused(const std::string& failiTee);
json initsialiseeriJson(const std::string& failiTee);
void uuendaJson(nlohmann::json& j, const std::string& failiTee, const std::string& nimi, int vanus, float kaal, const std::string& eesmark);
void kaitleJson(const std::string& failiTee, const std::string& nimi, int vanus, float kaal, const std::string& eesmark);

#endif //C_PLUSSPLUSS_PROJEKT_JSONHALDAJA_H

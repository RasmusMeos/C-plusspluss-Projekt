#ifndef C_PLUSSPLUSS_PROJEKT_JSONHALDAJA_H
#define C_PLUSSPLUSS_PROJEKT_JSONHALDAJA_H

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "../lib/json.hpp"
#include "../include/kasutaja.h"

using json = nlohmann::json;

void salvestaKasutaja(const std::string& failiTee, const Kasutaja& kasutaja);
std::vector<std::string> laeTreeningPlaan(const std::string& failiTee, int& valik);
std::map<std::string, std::vector<std::pair<std::string, std::string>>> laeHarjutused(const std::string& failiTee);
void salvestaTreeningkava(const std::string& failiTee, const Kasutaja& kasutaja, const std::vector<std::vector<std::pair<std::string, std::string>>>& valitudKava);

#endif //C_PLUSSPLUSS_PROJEKT_JSONHALDAJA_H

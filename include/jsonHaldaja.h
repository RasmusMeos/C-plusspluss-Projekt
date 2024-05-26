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

/**
 * Salvestab Kasutaja andmed JSON faili.
 * @param failiTee JSON faili tee.
 * @param kasutaja Kasutaja objekt.
 */
void salvestaKasutaja(const std::string& failiTee, const Kasutaja& kasutaja);

/**
 * Laeb treeningplaani JSON failist.
 * @param failiTee JSON faili tee.
 * @param valik Kasutaja treeningplaani valik.
 * @return Vektor treeningplaani üksustest.
 */
std::vector<std::string> laeTreeningPlaan(const std::string& failiTee, int& valik);

/**
 * Laeb harjutused JSON failist.
 * @param failiTee JSON faili tee.
 * @return 'Map' harjutuste kategooriatest ja harjutustest.
 */
std::map<std::string, std::vector<std::pair<std::string, std::string>>> laeHarjutused(const std::string& failiTee);

/**
 * Salvestab treeningkava JSON faili.
 * @param failiTee JSON faili tee.
 * @param kasutaja Kasutaja objekt.
 * @param valitudKava Vektor valitud treeningkavast.
 */
void salvestaTreeningkava(const std::string& failiTee, const Kasutaja& kasutaja, const std::vector<std::vector<std::pair<std::string, std::string>>>& valitudKava);

#endif //C_PLUSSPLUSS_PROJEKT_JSONHALDAJA_H

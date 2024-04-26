// Kasutaja profiili funktsionaalsus

#include "../include/kasutaja.h"
#include <iostream>

Kasutaja::Kasutaja(std::string nimi, int vanus, float kaal, std::string eesmärk)
        : nimi(nimi), vanus(vanus), kaal(kaal), eesmark(eesmark) {}

void Kasutaja::kuva_andmed() {
    std::cout << "Nimi: " << nimi << "\nVanus: " << vanus << "\nKaal: " << kaal << " kg\nEesmärk: " << eesmark << std::endl;
}


// Kasutaja profiili funktsionaalsus

#include "../include/kasutaja.h"
#include <iostream>

Kasutaja::Kasutaja() {}

Kasutaja::Kasutaja(std::string nimi, int vanus, float kaal, std::string eesmark)
        : nimi(nimi), vanus(vanus), kaal(kaal), eesmark(eesmark) {}

void Kasutaja::kuva_andmed() {
    std::cout << "Nimi: " << nimi << "\nVanus: " << vanus << "\nKaal: " << kaal << " kg\nEesmärk: " << eesmark << std::endl;
}

bool Kasutaja::kasSobiv() const {
    return !nimi.empty() && vanus > 0 && vanus < 125 && kaal > 0 && kaal < 650 && !eesmark.empty();
}

const std::string &Kasutaja::getNimi() const {return nimi;}

int Kasutaja::getVanus() const {return vanus;}

float Kasutaja::getKaal() const {return kaal;}

const std::string &Kasutaja::getEesmark() const {return eesmark;}




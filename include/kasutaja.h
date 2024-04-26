#ifndef KASUTAJA_H
#define KASUTAJA_H

#include <string>

class Kasutaja {
public:
    std::string nimi;
    int vanus;
    float kaal;
    std::string eesmark;

    Kasutaja(std::string nimi, int vanus, float kaal, std::string eesmark);
    void kuva_andmed();
};

#endif


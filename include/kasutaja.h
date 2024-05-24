#ifndef KASUTAJA_H
#define KASUTAJA_H

#include <string>

class Kasutaja {
private:
    std::string nimi;
    int vanus;
    float kaal;
    std::string eesmark;
public:
    Kasutaja();

    Kasutaja(std::string nimi, int vanus, float kaal, std::string eesmark);
    void kuva_andmed();

    bool kasSobiv() const;

    const std::string &getNimi() const;

    int getVanus() const;

    float getKaal() const;

    const std::string &getEesmark() const;
};

#endif


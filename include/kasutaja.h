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
    /**
     * Initsialiseerib Kasutaja objekti vaikimisi konstruktoriga.
     */
    Kasutaja();

    /**
     * Initsialiseerib Kasutaja objekti antud parameetritega.
     * @param nimi Kasutaja nimi.
     * @param vanus Kasutaja vanus.
     * @param kaal Kasutaja kaal kilogrammides.
     * @param eesmark Kasutaja fitness eesmärk.
     */
    Kasutaja(std::string nimi, int vanus, float kaal, std::string eesmark);

    /**
     * Kuvab Kasutaja andmed konsoolile.
     */
    void kuva_andmed();

    /**
     * Kontrollib, kas Kasutaja andmed on sobivad.
     * @return Tõene, kui andmed on sobivad, vastasel juhul väär.
     */
    bool kasSobiv() const;

    /**
     * Tagastab Kasutaja nime.
     * @return Kasutaja nimi.
     */
    const std::string &getNimi() const;

    /**
     * Tagastab Kasutaja vanuse.
     * @return Kasutaja vanus.
     */
    int getVanus() const;

    /**
     * Tagastab Kasutaja kaalu.
     * @return Kasutaja kaal kilogrammides.
     */
    float getKaal() const;

    /**
     * Tagastab Kasutaja fitness eesmärgi.
     * @return Kasutaja fitness eesmärk.
     */
    const std::string &getEesmark() const;
};

#endif



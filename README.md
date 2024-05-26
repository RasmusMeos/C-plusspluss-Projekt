# Treeningkava Generaator

## Ülevaade
Treeningkava Generaator on C++-is kirjutatud rakendus, mis võimaldab kasutajatel luua personaliseeritud treeningkavasid. Rakendus kogub kasutaja andmed ja nende treeningeesmärgid, genereerib treeningkavad ning salvestab need JSON-failidesse.

## Eeldused
- C++11 või uuem versioon
- JSON for Modern C++ (nlohmann/json) teek

## Projektistruktuur
Projekt sisaldab järgmisi faile:
- `main.cpp`: Põhiprogrammi fail, mis koordineerib kogu rakenduse tööd.
- `kasutaja.cpp` ja `kasutaja.h`: Kasutaja klass, mis haldab kasutaja andmeid.
- `jsonHaldaja.cpp` ja `jsonHaldaja.h`: Funktsioonid JSON failidega töötamiseks (andmete salvestamine ja laadimine).
- `infoKuvaja.cpp` ja `infoKuvaja.h`: Funktsioonid, mis kuvavad informatsiooni kasutajale.
- `trenniGeneraator.cpp` ja `trenniGeneraator.h`: Funktsioonid, mis genereerivad treeningkavasid.

## Kasutamine
### Käivitamine
Kompileeri ja käivita projekt järgmiste käskudega:
```bash
g++ -o treeningkava main.cpp kasutaja.cpp jsonHaldaja.cpp infoKuvaja.cpp trenniGeneraator.cpp -I ../lib/json.hpp
./treeningkava

## Sisendfailid

- `../data/kasutajad.json`: Kasutajate andmed
- `../data/kavad.json`: Treeningkavad
- `../data/harjutused.json`: Treeningharjutused
- `../data/plaanid.json`: Treeningplaanid

## Kasutaja Andmete Kogumine

Rakendus küsib kasutajalt tema nimi, vanus, kaal ja treeningeesmärk. Andmete kogumisel kasutatakse valideerimisfunktsioone, mis tagavad, et sisestatud andmed on korrektsed ja usutavad. Näiteks:
- **Nimi** ja **eesmärk** peavad olema sõnestrandid, mis ei ole tühjad.
- **Vanus** peab olema numbriline, positiivne ja jääma vahemikku 0 kuni 125 aastat.
- **Kaal** peab olema numbriline ja jääma vahemikku 0.1 kuni 650 kg.

Kui andmed on kinnitatud, salvestab programm need `kasutajad.json` faili. Kasutaja andmeid on võimalik kinnitada või uuesti sisestada, sõltuvalt kasutaja valikust kinnitusetapis.

## Treeningkava Genererimine

Kasutaja valib treeningplaani (iga teine päev, iga kolmas päev, ainult nädalavahetused) ja treeningtüübi (ainult jõusaal, ainult kardio, kombinatsioon mõlemast). Rakendus genereerib vastavalt valikule treeningkavad ja kuvab need kasutajale.

## Treeningkava Salvestamine

Kasutaja valitud treeningkava salvestatakse JSON-faili.

## Näide

```plaintext
Sisesta oma nimi: John Doe
Sisesta oma vanus: 25
Sisesta oma kaal (kg): 70
Sisesta oma fitness eesmärk: Kaalu kaotus
Vali oma treeningplaan (1: iga teine päev, 2: iga kolmas päev, 3: ainult nädalavahetused): 1
Vali oma treenimistüüp (1: ainult jõusaal, 2: ainult kardio, 3: kombinatsioon mõlemast): 3


## Funktsioonide Ülevaade

### `kasutaja.h` ja `kasutaja.cpp`
Kasutaja klass, mis sisaldab järgmisi meetodeid:
- Konstruktorid: `Kasutaja()`, `Kasutaja(std::string nimi, int vanus, float kaal, std::string eesmark)`
- Andmete kuvamine: `void kuva_andmed()`
- Sobivuse kontroll: `bool kasSobiv() const`
- Getterid: `const std::string &getNimi() const`, `int getVanus() const`, `float getKaal() const`, `const std::string &getEesmark() const`

### `jsonHaldaja.h` ja `jsonHaldaja.cpp`
Funktsioonid JSON failidega töötamiseks:
- `void salvestaKasutaja(const std::string& failiTee, const Kasutaja& kasutaja)`
- `std::vector<std::string> laeTreeningPlaan(const std::string& failiTee, int& valik)`
- `std::map<std::string, std::vector<std::pair<std::string, std::string>>> laeHarjutused(const std::string& failiTee)`
- `void salvestaTreeningkava(const std::string& failiTee, const Kasutaja& kasutaja, const std::vector<std::vector<std::pair<std::string, std::string>>>& valitudKava)`

### `infoKuvaja.h` ja `infoKuvaja.cpp`
Funktsioonid informatsiooni kuvamiseks:
- `void peataValjund(const std::string& teade)`
- `void kuvaJsonPlaan(const std::vector<std::string>& list)`
- `void kuvaIgaTeinePaevKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad, const std::vector<std::string>& paevad)`
- `void kuvaIgaKolmasPaevKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad, const std::vector<std::string>& paevad)`
- `void kuvaNadalavahetuseKava(const std::vector<std::vector<std::pair<std::string, std::string>>>& kavad)`
- `void kuvaKasutajaKavad(int plaaniValik, std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad, std::vector<std::string>& igaTeineKuvamiseks, std::vector<std::string>& igaKolmasKuvamiseks)`
- `void kuvaKasutajaValitudKava(int plaaniValik, int kavaValik, std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>> genereeritudKavad, std::vector<std::string>& igaTeineKuvamiseks, std::vector<std::string& igaKolmasKuvamiseks)`

### `trenniGeneraator.h` ja `trenniGeneraator.cpp`
Funktsioonid treeningkavade genereerimiseks:
- `void taastaHarjutusteList(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused, const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal)`
- `std::vector<std::pair<std::string, std::string>> genereeriTreeningSessioon(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused, const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal, const std::vector<std::string>& kategooriad, int mituHarjutust, bool lahtesta)`
- `std::vector<std::vector<std::pair<std::string, std::string>>> genereeriIgaTeinePaevKavad(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused, const std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal, int rutiiniValik)`
- `std::vector<std::vector<std::pair<std::string, std::string>>> genereeriIgaKolmasPaevKavad(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused, the std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal, int rutiiniValik)`
- `std::vector<std::vector<std::pair<std::string, std::string>>> genereeriNadalavahetuseKavad(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused, the std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal, int rutiiniValik)`
- `void genereeriKasutajaKavad(const int plaaniValik, the int rutiiniValik, std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutused, std::map<std::string, std::vector<std::pair<std::string, std::string>>>& harjutusedOriginaal, std::vector<std::vector<std::vector<std::pair<std::string, std::string>>>>& genereeritudKavad)`

## Autorid
Projekti on loonud Rasmus Meos ja Nikita Chernov.

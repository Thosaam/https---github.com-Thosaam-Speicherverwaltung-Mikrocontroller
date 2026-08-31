#ifndef SPEICHERMANAGER_H
#define SPEICHERMANAGER_H
#include <cstdint>
#include <deque>
#include "Speicherblock.h"

// Verwaltet einen zusammenhängenden Hauptspeicherbereich für alle Sensoren die Speicherblöcke werden fortlaufend ohne
// Lücken vergeben, eine Freigabe verkleinert den belegten Bereich nicht.
class Speichermanager{
    private:
    uint8_t* gesamtspeicher; 
    int gesamtGroesseBytes;

    //wird benötigt um zu wissen wo der nächste Speicher-Block beginnen darf
    int naechsterFreierByteIndex;

    // Sammlung aller erstellten Blöcke. deque statt vector, da Speicherblock& aus reserviereSpeicher() referenzstabil 
    // bleiben muss (kein Reallocation-Problem wie bei vector bei weiteren emplace_back()-Aufrufen)
    std::deque<Speicherblock> speicherbloecke;

    public:
    // Reserviert gesamtGroesseBytes Bytes auf dem Heap.
    // Wirft std::invalid_argument, falls gesamtGroesseBytes <= 0 ist.
    Speichermanager( int gesamtGroesseBytes);
    
    // Gibt den in new[] reservierten Speicher wieder frei, Wird automatisch beim Verlassen 
    // des Gültigkeitsbereichs von speichermanager in main() aufgerufen
    ~Speichermanager();

    // Kopieren verboten, da gesamtspeicher exklusiv von genau einem Speichermanager-Objekt besessen wird (verhindert Double-Free)
    Speichermanager(const Speichermanager&) = delete;
    Speichermanager& operator=(const Speichermanager&) = delete;

    uint8_t* getGesamtspeicher()const;

    // Prüft, ob für anzahlDatenwerte (je sizeof(double) Bytes) noch genug zusammenhängender Platz ab nächsterFreierByteIndex frei ist
    bool pruefeReservierung(int anzahlDatenwerte);

    // Reserviert Platz für anzahlDatenwerte double-Werte und liefert eine Referenz auf den neu erstellten Speicherblock (bleibt gültig für
    // die Lebensdauer des Speichermanagers, siehe deque-Kommentar oben).
    // Wirft std::runtime_error, falls nicht genug freier Speicher vorhanden ist.
    Speicherblock& reserviereSpeicher(int anzahlDatenwerte);

    const std::deque<Speicherblock>& getSpeicherbloecke() const;

    int getFreierSpeicher() const;
    int getGesamtGroesseBytes() const;

};
#endif

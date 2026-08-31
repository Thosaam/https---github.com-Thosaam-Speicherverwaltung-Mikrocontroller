#ifndef RINGPUFFER_H
#define RINGPUFFER_H
#include "Speicherblock.h"
#include <vector>
#include <cstdint>


// Ringpuffer für Messwerte eines einzelnen Sensors. Nutzt einen vorreservierten Speicherbereich (Speicherblock) 
// und überschreibt bei vollem Puffer automatisch den ältesten Wert.
class RingPuffer{
    private:
    // Referenz auf den Speicherblock, der Größe & Position dieses Ringpuffers im Hauptspeicher beschreibt
    const Speicherblock& speicherblock; 

    // Zeiger auf den Beginn des gesamten Hauptspeicherbereichs (nicht auf den Blockanfang selbst - Offset kommt aus speicherblock)
    uint8_t *    basisAdresse; 

    int         anzahlaktuelleDatenwerte;  // wie viele Datenwerte aktuell im Ringpuffer gespeichert sind
    int            schreibIndex;  // Index an dem der nächste Datenwert gespeichert wird
    int            leseIndex; // Index an dem der nächste Datenwert gelesen wird
    
    // Berechnet die tatsaechliche Speicheradresse fuer einen relativen 
    // Index innerhalb des Blocks (0 <= relativerIndex < getKapazitaet())
    double * berechneAdresse(int relativerIndex)const;

    public:
    // Erstellt einen Ringpuffer auf Basis des angegebenen Speicherblocks.
    // Wirft std::invalid_argument, falls basisAdresse nullptr ist oder
    // der Speicherblock kleiner als ein einzelner double-Wert ist.
    RingPuffer( const Speicherblock& speicherblock, uint8_t * basisAdresse);

    const Speicherblock& getSpeicherblock()const;
    int getAnzahlAktuelleDatenwerte()const;
    int getSchreibIndex()const;
    int getLeseIndex()const;

    // Liefert die maximale Anzahl an double-Werten, die dieser Ringpuffer basierend auf der Speicherblock-Größe fassen kann
    int getKapazitaet()const;

    // Speichert einen neuen Datenwert im Ringpuffer. Überschreibt automatisch den ältesten Wert, wenn der Puffer voll ist.
    void pushDatenwert(double datenwert);

    // Liefert alle aktuell gespeicherten Werte in chronologischer Reihenfolge (ältester Wert zuerst)
    std::vector<double> getAlleDatenwerte()const;

    bool istVoll() const;

    bool istLeer() const;

};

#endif

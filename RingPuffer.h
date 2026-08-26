#include "Speicherblock.h"
#include <vector>

class RingPuffer{
    private:
    const Speicherblock& speicherblock; //Referenz auf den Speicherblock, in dem die Datenwerte gespeichert werden (wird für die Ausgabe der Datenwerte benötigt)
    double *    IndexSpeicherplatz; //Zeiger auf den Hauptspeicher- Anfangsadresse des Speicherblocks, in dem die Datenwerte gespeichert werden (wird für das Schreiben der Datenwerte benötigt)
    int         anzahlaktuelleDatenwerte,  // wie viele Datenwerte aktuell im Ringpuffer gespeichert sind
                schreibIndex,  // Index an dem der nächste Datenwert gespeichert wird
                leseIndex; // Index an dem der nächste Datenwert gelesen wird
    // Berechnet die tatsächliche Speicheradresse für einen relativen Index innerhalb des Blocks
    double * berechneAdresse(int relativerIndex)const;

public:
// Konstruktoraufruf 
RingPuffer( const Speicherblock& speicherblock, double * IndexSpeicherplatz);





//Daten in Ringpuffer speichern, Schreibindex erhöhen, anzahlaktuelleDatenwerte erhöhen, wenn Ringpuffer voll, dann ältesten Datenwert überschreiben
void pushDatenwert(double datenwert);

std::vector<double>  getAlleDatenwerte()const;
};



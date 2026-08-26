#include "RingPuffer.h"


// Konstruktoraufruf
RingPuffer::RingPuffer(const Speicherblock& speicherblock, double * IndexSpeicherplatz)

// Initialisierungsliste der Variablen (default Konstruktoren der Variablen werden aufgerufen)
    :   speicherblock(speicherblock),
        IndexSpeicherplatz(IndexSpeicherplatz),
        anzahlaktuelleDatenwerte(0), 
        schreibIndex(0), 
        leseIndex(0) {}




double * RingPuffer::berechneAdresse(int relativerIndex)const {
    return IndexSpeicherplatz + speicherblock.getStartIndex() + relativerIndex;
}

void RingPuffer::pushDatenwert(double datenwert)
{
    *(berechneAdresse(schreibIndex)) = datenwert;
    schreibIndex =(schreibIndex +1) % speicherblock.getLaenge();
    if (anzahlaktuelleDatenwerte < speicherblock.getLaenge()) {
        anzahlaktuelleDatenwerte++;} else{
            leseIndex=(leseIndex+1)% speicherblock.getLaenge();
        }
    }

std::vector<double> RingPuffer::getAlleDatenwerte() const {
    std::vector<double> datenwerte;
    int index = leseIndex;
    for (int i=0; i<anzahlaktuelleDatenwerte; i++) {
       datenwerte.push_back(*(berechneAdresse(index)));
       index= (index+1)% speicherblock.getLaenge();
    }
    return datenwerte;
}
  
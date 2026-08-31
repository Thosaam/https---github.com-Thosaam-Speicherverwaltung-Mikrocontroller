#include "RingPuffer.h"
#include <stdexcept>
#include <cstdint>


// Konstruktoraufruf
RingPuffer::RingPuffer(const Speicherblock& speicherblock, uint8_t * basisAdresse)

    :   speicherblock(speicherblock),
        basisAdresse(basisAdresse),
        anzahlaktuelleDatenwerte(0), 
        schreibIndex(0), 
        leseIndex(0)
{
    if (basisAdresse == nullptr)
    {
        throw std::invalid_argument("Speicheradresse darf nicht null sein.");
    }
    if (speicherblock.getLaenge() < sizeof(double))
    {
        throw std::invalid_argument("Speicherblock zu klein fuer mindestens einen Datenwert.");
    }
}

double * RingPuffer::berechneAdresse(int relativerIndex)const 
{
    // reinterpret_cast ist hier sicher, da der Speichermanager Blöcke ausschließlich in Vielfachen von sizeof(double) reserviert und
    // getStartIndex() damit immer 8-byte-aligned ist (siehe Speichermanager::reserviereSpeicher). relativerIndex liegt zudem durch das Modulo in
    // pushDatenwert/getAlleDatenwerte immer im gueltigen Bereich [0,
    double * alsDouble = reinterpret_cast<double*>(basisAdresse + speicherblock.getStartIndex());
    return alsDouble + relativerIndex;
}

const Speicherblock& RingPuffer::getSpeicherblock()const {
    
    return speicherblock;
}

int RingPuffer::getAnzahlAktuelleDatenwerte()const {
    return anzahlaktuelleDatenwerte;
}

int RingPuffer::getSchreibIndex()const {
    return schreibIndex;
}

int RingPuffer::getLeseIndex()const {
    return leseIndex;
}

int RingPuffer::getKapazitaet ()const {
    int kapazitaet= speicherblock.getLaenge()/sizeof(double);
    return kapazitaet;
}

void RingPuffer::pushDatenwert(double datenwert)
{
    *(berechneAdresse(schreibIndex)) = datenwert;
    schreibIndex =(schreibIndex +1) % getKapazitaet();
    if (anzahlaktuelleDatenwerte < getKapazitaet()) {
        anzahlaktuelleDatenwerte++;} else{
            leseIndex=(leseIndex+1)% getKapazitaet();
        }
    }

std::vector<double> RingPuffer::getAlleDatenwerte() const {
    std::vector<double> datenwerte;
    int index = leseIndex;
    for (int i=0; i<anzahlaktuelleDatenwerte; i++) {
       datenwerte.push_back(*(berechneAdresse(index)));
       index= (index+1)% getKapazitaet();
    }
    return datenwerte;
}

bool RingPuffer::istVoll() const {
        return anzahlaktuelleDatenwerte == getKapazitaet();
    }

bool RingPuffer::istLeer() const {
        return anzahlaktuelleDatenwerte == 0;
    }
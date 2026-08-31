#include "Speicherblock.h"
#include <stdexcept>



// Konstruktoraufruf 
Speicherblock::Speicherblock( int startIndex, int laenge)
// mit Präfix-Inkrementierung der statischen Variable nextBlockID wird jedem Speicherblock eine eindeutige BlockID zugewiesen (BlockID start bei 1 ...)
    : blockID(++nextBlockID),
    startIndex(startIndex),
    laenge(laenge),
    belegt(true)
{
    if (startIndex < 0)
    {
        throw std::invalid_argument("startIndex darf nicht negativ sein.");
    }
    if (laenge <= 0)
    {
        throw std::invalid_argument("laenge muss positiv sein.");
    }
}


int Speicherblock::getBlockID()const {
    return blockID;
}
// statische Methode um die nächste BlockID abzufragen, ohne dass ein Objekt der Klasse Speicherblock erzeugt werden muss
 int Speicherblock::getNextBlockID() {
    return nextBlockID;
}
    
int Speicherblock::getStartIndex()const {
    return startIndex;
}

int Speicherblock::getLaenge()const {
    return laenge;
}

bool Speicherblock::istBelegt()const {
    return belegt;
}
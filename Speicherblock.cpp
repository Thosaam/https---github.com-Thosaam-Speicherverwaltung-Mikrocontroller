#include "Speicherblock.h"


// Konstruktoraufruf 
Speicherblock::Speicherblock( int startIndex, int laenge)
// mit Präfix-Inkrementierung der statischen Variable nextBlockID wird jedem Speicherblock eine eindeutige BlockID zugewiesen (BlockID start bei 1 ...)
    : blockID(++nextBlockID),
    startIndex(startIndex),
    laenge(laenge),
    belegt(true) {}

// Getter-Methoden um die privaten Variablen abzufragen
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

bool Speicherblock::getBelegt()const {
    return belegt;
}

// Methode um Speicherblock freizugeben bzw. zu belegen, d.h. belegt auf false/true zu setzen
void Speicherblock::freigeben() {
    belegt = false;
}
void Speicherblock::belegen() {
    belegt = true;
}
// Methode um die Länge des Speicherblocks dynamisch anzupassen
void Speicherblock::setLaenge(int neueLaenge) {
        laenge = neueLaenge;
}
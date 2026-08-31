#ifndef SPEICHERBLOCK_H
#define SPEICHERBLOCK_H

// Repräsentiert einen einzelnen reservierten Speicherbereich (nur Metadaten)
// Hält selbst keinen Speicher, sondern nur Position/Größe/Belegungsstatus -
// die eigentliche Speicherverwaltung übernimmt der Speichermanager

class Speicherblock{
    private:
    int    blockID;

    // statische Variable zur Generierung eindeutiger BlockIDs, 
    // Sorgt für eindeutige IDs über alle Speicherblöcke hinweg, unabhängig vom Speichermanager
    static inline int nextBlockID = 0; 

    int startIndex;
    int laenge;
    bool belegt;
   
    public:
    // Erstellt einen Speicherblock an der angegebenen Startadresse mit der angegebenen Laenge (in Bytes). 
    // Der Block ist initial belegt. Wirft std::invalid_argument, falls startIndex negativ oder
    // länge kleiner/gleich 0 ist.
    Speicherblock( int startIndex, int laenge);

    int getBlockID()const;

    // Liefert die nächste zu vergebende BlockID, ohne dass ein Objekt der Klasse Speicherblock erzeugt werden muss
    static int getNextBlockID();

    int getStartIndex()const;
    int getLaenge()const;

    // Markiert den Block als belegt
    bool istBelegt()const;
};
#endif
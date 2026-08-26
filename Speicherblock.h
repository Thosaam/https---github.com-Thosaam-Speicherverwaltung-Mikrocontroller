

class Speicherblock{
    private:
    int    blockID;
    static inline int nextBlockID = 0; // statische Variable zur Generierung eindeutiger BlockIDs, Sorgt für eindeutige IDs über alle Speicherblöcke hinweg, unabhängig vom Speichermanager
    int startIndex;
    int laenge;
    bool belegt;
   
    public:
    //Konstruktoraufruf
    Speicherblock( int startIndex, int laenge);
    // Getter-Methoden um die privaten Variablen abzufragen
    int getBlockID()const;
    // statische Methode um die nächste BlockID abzufragen, ohne dass ein Objekt der Klasse Speicherblock erzeugt werden muss
    static int getNextBlockID();
    int getStartIndex()const;
    int getLaenge()const;
    bool getBelegt()const;
    //Methode um Speicherblock freizugeben bzw. zu belegen, d.h. belegt auf false/true zu setzen
    void freigeben();
    void belegen();
    //Vorbereitung für dynamische Anpassung der Blocklänge
    void setLaenge(int neueLaenge);

};



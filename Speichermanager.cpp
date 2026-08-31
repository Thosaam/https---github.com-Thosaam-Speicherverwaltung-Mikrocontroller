#include "Speichermanager.h"
#include <stdexcept>

Speichermanager::Speichermanager(int gesamtGroesseBytes)
    // gesamtspeicher wird vorab auf nullptr gesetzt (Absicherung, falls der Konstruktor später erweitert wird)
    :   gesamtspeicher(nullptr),
        gesamtGroesseBytes(gesamtGroesseBytes),
        naechsterFreierByteIndex(0)
      
{
    if (gesamtGroesseBytes <= 0)
    {
        throw std::invalid_argument(
            "Gesamtgroesse Hauptspeicher muss positiv sein."
        );
    }

    gesamtspeicher = new uint8_t[gesamtGroesseBytes];
}

Speichermanager::~Speichermanager(){
        delete[] gesamtspeicher;
    }

uint8_t* Speichermanager::getGesamtspeicher()const {
    return gesamtspeicher;
}

bool Speichermanager::pruefeReservierung(int anzahlDatenwerte) {
    // Kontrolle für Werte die negativ oder kleiner sind.. weil dann unter Umständen fälschicherweise auch true zurückgegeben werden könnte
    if (anzahlDatenwerte<=0){
        return false;
    } else {
        //Berechnung für Bereichskontrolle (Menge an Bytes + nächster freier ByteIndex)
          int benoetigteBytes= anzahlDatenwerte* sizeof(double);
    int bereichsPruefung= benoetigteBytes + naechsterFreierByteIndex;
    return bereichsPruefung<=gesamtGroesseBytes;
    }
  
}

Speicherblock& Speichermanager::reserviereSpeicher(int anzahlDatenwerte) {
    if(pruefeReservierung(anzahlDatenwerte)){
        int benoetigteBytes= anzahlDatenwerte* sizeof(double);
        // Referenz bleibt gültig, da speicherbloecke ein deque ist (siehe Header)
        speicherbloecke.emplace_back(naechsterFreierByteIndex, benoetigteBytes);
        Speicherblock& blockRef= speicherbloecke.back();
        naechsterFreierByteIndex += benoetigteBytes;
        return blockRef;
    } else {
        // throw Exception... methode wird direkt verlassen!
       throw std::runtime_error("Nicht genügend Speicher vorhanden");
    }

}

const std::deque<Speicherblock>& Speichermanager::getSpeicherbloecke() const
{
    return speicherbloecke;
}

int Speichermanager::getFreierSpeicher() const
{
    return gesamtGroesseBytes - naechsterFreierByteIndex;
}

int Speichermanager::getGesamtGroesseBytes() const {
    return gesamtGroesseBytes;
}
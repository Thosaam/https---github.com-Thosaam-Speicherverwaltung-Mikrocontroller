#include "Sensor.h"


Sensor::Sensor(
    const std::string& name, 
    const std::string& einheit, 
    int abtastrate, 
    double mittelwert, 
    double rauschen)

    //Initialisierungsliste der Variablen (default Konstruktoren der Variablen werden aufgerufen)
    : name(name), 
    einheit(einheit), 
    abtastrate(abtastrate), 
    //Initialisierung mit 0.0 weil noch kein wert gemessen wurde
    messwert(0.0), 
    mittelwert(mittelwert), 
    rauschen(rauschen),
    letzteMessung{},
    // Generator wird mit einer zufälligen Startzahl initialisiert
    zufallszahlgenerator(std::random_device{}()) 
{
    if (rauschen < 0.0)
    {
        throw std::invalid_argument(
            "Rauschen darf nicht negativ sein."
        );
    }

    if (abtastrate <= 0)
    {
        throw std::invalid_argument(
            "Abtastrate muss positiv sein."
        );
    }
}


    std::string Sensor::getName()const {
        return name;
    }

    std::string Sensor::getEinheit()const {
        return einheit;
    }

    int Sensor::getAbtastrate()const {
        return abtastrate;
    }

    double Sensor::getMesswert()const {
        return messwert;
    }

    double Sensor::getMittelwert()const {
        return mittelwert;
    }

    double Sensor::getRauschen() const{

        return rauschen;
    }

    // steady_clock statt system_clock, da monoton steigend und unabhaengig
    // wichtig fuer korrekte Intervallmessung in messungFaellig()
    std::chrono::steady_clock::time_point Sensor::getLetzteMessung() const {
        return letzteMessung;
    }

   void Sensor::setLetzteMessung(std::chrono::steady_clock::time_point zeitwert){
        letzteMessung= zeitwert;
    }

    bool Sensor::messungFaellig() const
    {
    auto jetzt = std::chrono::steady_clock::now();

    auto vergangeneZeit =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            jetzt - letzteMessung
        ).count();

    return vergangeneZeit >= abtastrate;
    }

    double Sensor::messwertErzeugen() {
        // Gleichverteilte Abweichung innerhalb des definierten Rauschbereichs
        std::uniform_real_distribution<double> verteilung(-rauschen, rauschen);
        return mittelwert + verteilung(zufallszahlgenerator);
    }

     void Sensor::triggerMessung(){
        messwert = messwertErzeugen();
     }

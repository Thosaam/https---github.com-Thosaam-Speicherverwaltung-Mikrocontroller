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
    // Generator wird mit einer zufälligen Startzahl initialisiert
    Zufallszahlgenerator(std::random_device{}()) {}

// Getter-Methoden um die privaten Variablen abzufragen
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

    // Methode zum Erzeugen eines zufälligen Messwerts
    double Sensor::messwertErzeugen() {
        // Gleichverteilte Abweichung innerhalb des definierten Rauschbereichs
        std::uniform_real_distribution<double> verteilung(-rauschen, rauschen);
        return mittelwert + verteilung(Zufallszahlgenerator);
    }

    // Methode zum Auslösen einer Messung, die den Messwert später anhand der Abtastrate aktualisiert
     void Sensor::triggerMessung(){
        messwert = messwertErzeugen();
     }

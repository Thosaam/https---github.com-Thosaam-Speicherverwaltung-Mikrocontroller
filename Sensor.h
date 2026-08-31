#ifndef SENSOR_H
#define SENSOR_H
#include <random>
#include <string>
#include <chrono>


// Simuliert einen einzelnen Sensor (z. B. Temperatur, Druck, Helligkeit).
// Erzeugt Messwerte als Zufallsrauschen um einen konfigurierten Mittelwert
// und verwaltet den Zeitpunkt der letzten Messung fuer die Abtastraten-Steuerung.
class Sensor {
private:
    std::string name, einheit;

    int abtastrate;
    double messwert, mittelwert, rauschen;
    std::chrono::steady_clock::time_point letzteMessung;

    // Eigener zufallszahlgenerator pro Sensor, um voneinander unabhängige Messwertfolgen zu simulieren
    std::mt19937 zufallszahlgenerator;

    

public:
    // Erstellt einen Sensor mit den angegebenen Parametern.
    // Wirft std::invalid_argument, falls rauschen negativ oder
    // abtastrate kleiner/gleich 0 ist.
    Sensor(const std::string& name, const std::string& einheit, int abtastrate, double mittelwert, double rauschen);

    // Getter fuer die Konfigurationsdaten des Sensors (unveraenderlich nach der Konstruktion)
    std::string getName()const;
    std::string getEinheit()const;
    int getAbtastrate()const;
    double getMesswert()const;
    double getMittelwert()const;
    double getRauschen() const;
    std::chrono::steady_clock::time_point getLetzteMessung() const;
    void setLetzteMessung(std::chrono::steady_clock::time_point zeit);

    // Prueft, ob seit der letzten Messung mindestens die Abtastrate (in Millisekunden) vergangen ist
    bool messungFaellig() const;

    // Erzeugt und liefert einen neuen Zufallswert (mittelwert +/- rauschen), ohne den internen Zustand (messwert) zu veraendern
    double messwertErzeugen();
    
    // Aktualisiert den internen Messwert durch Aufruf von messwertErzeugen()
    void triggerMessung();
};

#endif
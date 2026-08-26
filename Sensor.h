#ifndef SENSOR_H
#define SENSOR_H
#include <random>
#include <string>

class Sensor {
private:
//Variablen 
    std::string name, einheit;

    int abtastrate;
    double messwert, mittelwert, rauschen;

// Eigener Zufallsgenerator pro Sensor, um voneinander unabhängige Messwertfolgen zu simulieren
    std::mt19937 Zufallszahlgenerator;

public:
// Konstruktoraufruf
    Sensor(const std::string& name, const std::string& einheit, int abtastrate, double mittelwert, double rauschen);

//Getter für private Variablen: Name, Einheit, Abtastrate, Messwert, Mittelwert und Rauschen (um von außen auf die Werte zugreifen zu können)
    std::string getName()const;
    std::string getEinheit()const;
    int getAbtastrate()const;
    double getMesswert()const;
    double getMittelwert()const;
    double getRauschen() const;

// Messwert erzeugen
    double messwertErzeugen();
// Messung auslösen
    void triggerMessung();
};

#endif
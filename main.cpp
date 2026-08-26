#include <iostream>
#include <string>
#include "Sensor.h"
#include "Speicherblock.h"
using namespace std;

    int main() {
/* 
//Test für Sensor Klasse
Sensor TemperaturSensor= Sensor ("Temperatur", "Celsius", 1, 20.0, 0.5); 

std::cout<< "Test Ausgabe der Get Methoden: " << TemperaturSensor.getName() << " " << TemperaturSensor.getEinheit() << " " << TemperaturSensor.getAbtastrate() << " "<< TemperaturSensor.getMesswert() << " "<< TemperaturSensor.getMittelwert() << " " << TemperaturSensor.getRauschen() << std::endl;

std::cout << "Und hier einige Werte die der Sensor erzeugt: " << std::endl;
for (int i = 0; i < 4; i++) {
    TemperaturSensor.triggerMessung();
    std::cout << "Messwert " << i + 1 << ": " << TemperaturSensor.getMesswert() << std::endl;
}

//Test für Speicherblock Klasse
Speicherblock Block1= Speicherblock(0, 10);
std::cout<< "Test Ausgabe der Get Methoden Block1: " << Block1.getBlockID() << " "<< Speicherblock::getNextBlockID() << " " << Block1.getStartIndex() << " " << Block1.getLaenge() << " "<< Block1.getBelegt() << std::endl;
std::cout<< "Test Block1 neue Länge setzen: " << std::endl;
Block1.setLaenge(15);
std::cout<< "Test Ausgabe von Block1: " << Block1.getBlockID() << " "<< Speicherblock::getNextBlockID() << " " << Block1.getStartIndex() << " " << Block1.getLaenge() << " "<< Block1.getBelegt() << std::endl;
Speicherblock Block2= Speicherblock(10, 20);
std::cout<< "Test Ausgabe der Get Methoden Block2: " << Block2.getBlockID() << " "<< Speicherblock::getNextBlockID() << " " << Block2.getStartIndex() << " " << Block2.getLaenge() << " "<< Block2.getBelegt() << std::endl;
std::cout<< "Test Block 2 neue Länge setzen: " << std::endl;
Block2.setLaenge(25);
std::cout<< "Test Ausgabe von Block2: " << Block2.getBlockID() << " "<< Speicherblock::getNextBlockID() << " " << Block2.getStartIndex() << " " << Block2.getLaenge() << " "<< Block2.getBelegt() << std::endl;
*/
return 0;
}

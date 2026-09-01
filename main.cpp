#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>

#include "Sensor.h"
#include "RingPuffer.h"
#include "Speicherblock.h"
#include "Speichermanager.h"


// Gemeinsamer Mutex (Um beidseitigen Zugriff parallel zu verhindern)
std::mutex ringpufferMutex;


// Mess-Steuerung, weil Sensoren unterschiedliche Abtastraten haben,
// parallele Messwerterfassung zum Hauptmenü-Programm 
// Schleife geht nach dem durchlaufen in "sleep" um die Auslastung zu schonen  
void messSteuerung(
    std::vector<Sensor>& sammlungSensoren,
    std::deque<RingPuffer>& sammlungRingpuffer,
    bool& programmLaeuft)
{
    while (programmLaeuft)
    {
        for (size_t i = 0; i < sammlungSensoren.size(); i++)
        {
            if (sammlungSensoren[i].messungFaellig())
            {
                sammlungSensoren[i].triggerMessung();

                // Ringpuffer gegen Beidseitigen Zugriff kurz sperren
                {
                    std::lock_guard<std::mutex> sperre(ringpufferMutex);

                    sammlungRingpuffer[i].pushDatenwert(
                        sammlungSensoren[i].getMesswert()
                    );
                }

                sammlungSensoren[i].setLetzteMessung(
                    std::chrono::steady_clock::now()
                );
            }
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );
    }
}

// Methode um Sensordaten im Terminal anzuzeigen,
// Code Duplikate in Case Aufrufen werden dadurch aufgehoben
void zeigeSensordaten(
    size_t index,
    const std::vector<Sensor>& sammlungSensoren,
    std::deque<RingPuffer>& sammlungRingpuffer,
    std::mutex& sperreObjekt)
{
    // Bounds-Check: verhindert Out-of-Bounds-Zugriff bei ungültigem Index,
    // z. B. falls die Sensoranzahl sich später ändert oder ein Aufrufer
    // versehentlich einen falschen Index übergibt
    if (index >= sammlungSensoren.size() || index >= sammlungRingpuffer.size())
    {
        std::cerr << "Fehler: Ungueltiger Sensor-Index (" << index << ")\n";
    }

    std::vector<double> daten;
    {
        // Sperre nur so lange wie nötig halten,
        // damit der Mess-Thread nicht unnötig lange blockiert wird
        std::lock_guard<std::mutex> sperre(sperreObjekt);
        daten = sammlungRingpuffer[index].getAlleDatenwerte();
    }

    const Sensor& sensor = sammlungSensoren[index];

    std::cout << "\n--- " << sensor.getName() << " ---\n";

    for (double wert : daten)
    {
        std::cout << wert << " " << sensor.getEinheit() << "\n";
    }

    std::cout << "\n- Abtastrate: " << sensor.getAbtastrate() << " ms -\n";

}

// Methode für das Menü, 
// parallele Umsetzung während Messsteuerung durch Threads umgesetzt
void zeigeMenue(
    std::vector<Sensor>& sammlungSensoren,
    std::deque<RingPuffer>& sammlungRingpuffer,
    Speichermanager& speichermanager,
    bool& programmLaeuft)
{
    int auswahl;

    std::cout << "\n";
    std::cout << "====================================\n";
    std::cout << "          SPEICHERVERWALTUNG\n";
    std::cout << "====================================\n";
    std::cout << "1: Messwerte Temperatur anzeigen\n";
    std::cout << "2: Messwerte Luftfeuchtigkeit anzeigen\n";
    std::cout << "3: Messwerte Luftdruck anzeigen\n";
    std::cout << "4: Speicherzustand anzeigen\n";
    std::cout << "5: Ringpuffer-Status anzeigen\n";
    std::cout << "6: Programm beenden\n";
    std::cout << "====================================\n";
    std::cout << "Auswahl: ";

    // Kontrolle für fehlerhafter Eingabe (wenn es keine int Werte sind)
    if (!(std::cin >> auswahl))
    {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ungueltige Eingabe!\n";
    return; 
    }

    //Hauptmenü mit switch case Auswah erstellt, 
    //Lässt sich felxibel und schnell erweitern
    switch (auswahl)
    {
        
        // Messwerte Sensor 1 anzeigen
        case 1:
       {
            zeigeSensordaten(
                0,
                sammlungSensoren, 
                sammlungRingpuffer, 
                ringpufferMutex);
    break;
}
        // Messwerte Sensor 2 anzeigen
        case 2:
        {
            zeigeSensordaten(
                1,
                sammlungSensoren, 
                sammlungRingpuffer, 
                ringpufferMutex);
            break;
        }
        // Messwerte Sensor 3 anzeigen
        case 3:
        {
            zeigeSensordaten(
                2,
                sammlungSensoren, 
                sammlungRingpuffer, 
                ringpufferMutex);
            break;
        }
        // Speicherzustand anzeigen
        case 4:
        {
            
    std::cout << "\n";
    std::cout << "====================================\n";
    std::cout << "          SPEICHERZUSTAND\n";
    std::cout << "====================================\n";

    const auto& bloecke =
        speichermanager.getSpeicherbloecke();

    for (const auto& block : bloecke)
    {
        std::cout << "\n";
        std::cout << "Block-ID: "
                  << block.getBlockID()
                  << "\n";

        std::cout << "Startadresse: "
                  << block.getStartIndex()
                  << "\n";

        std::cout << "Groesse: "
                  << block.getLaenge()
                  << " Bytes\n";

        if (block.istBelegt())
        {
            std::cout << "Status: BELEGT\n";
        }
        else
        {
            std::cout << "Status: FREI\n";
        }
    }

    std::cout << "\n------------------------------------\n";

    std::cout << "Gesamtspeicher: "
              << speichermanager.getGesamtGroesseBytes() 
              << " Bytes\n";

    std::cout << "Freier Speicher: "
              << speichermanager.getFreierSpeicher()
              << " Bytes\n";

    std::cout << "====================================\n";

    break;
        }
        // Ringpuffer-Status anzeigen
        case 5:
            {
    std::lock_guard<std::mutex> sperre(ringpufferMutex);

    std::cout << "\n--- Ringpuffer-Status ---\n";

    for (size_t i = 0; i < sammlungRingpuffer.size(); i++)
    {
        std::cout << "Ringpuffer " << i + 1 << ": "
                  << sammlungRingpuffer[i].getAnzahlAktuelleDatenwerte()
                  << " / "
                  << sammlungRingpuffer[i].getKapazitaet()
                  << " Werte";

        if (sammlungRingpuffer[i].istVoll())
        {
            std::cout << " (VOLL)";
        }

        std::cout << std::endl;
    }

    break;
}
        // Programm beenden
        case 6: 
        {
            programmLaeuft = false;
            break;
        }
        
        // Kontrolle für fehlerhafter Eingabe (wenn Werte nicht zu den x - Cases passen)
        default:
            std::cout << "Ungueltige Auswahl!\n";
            break;
    }
}

int main()
{ 
    // Kontrolle um gezielte Fehler während der Initialisierung abzufangen
    try
    {
    std::vector<Sensor> sammlungSensoren;
    std::deque<RingPuffer> sammlungRingpuffer;

    // Speicher mit Größe von 150 Bytes wird erstellt
    Speichermanager speichermanager(150);


    // Sensor 1
    Sensor Sensor1(
        "Temperatur",
        "Grad Celsius",
        9000,
        23,
        0.5
    );

    sammlungSensoren.push_back(Sensor1);

    // Speicherblock mit 5 Datenplätzen wird reserviert
    Speicherblock& Speicherblock1 =
        speichermanager.reserviereSpeicher(5);

    sammlungRingpuffer.emplace_back(
        Speicherblock1,
        speichermanager.getGesamtspeicher()
    );


    // Sensor 2
    Sensor Sensor2(
        "Luftfeuchtigkeit",
        "% relative Feuchte",
        3000,
        55.0,
        3.0
    );

    sammlungSensoren.push_back(Sensor2);

    // Speicherblock mit 10 Datenplätzen wird reserviert
    Speicherblock& Speicherblock2 =
        speichermanager.reserviereSpeicher(10);

    sammlungRingpuffer.emplace_back(
        Speicherblock2,
        speichermanager.getGesamtspeicher()
    );


    // Sensor 3
    Sensor Sensor3(
        "Luftdruck",
        "hPa",
        5000,
        1013.0,
        0.02
    );

    sammlungSensoren.push_back(Sensor3);

    // Speicherblock mit 3 Datenplätzen wird reserviert
    Speicherblock& Speicherblock3 =
        speichermanager.reserviereSpeicher(3);

    sammlungRingpuffer.emplace_back(
        Speicherblock3,
        speichermanager.getGesamtspeicher()
    );

// ======== Ab hier Programmstart ========
    bool programmLaeuft = true;


    // Mess-Thread läuft parallel zum Menü, damit Sensoren im Hintergrund
    // unabhaengig von Benutzereingaben in ihrer jeweiligen Abtastrate messen.
    // std::ref() noetig, da std::thread Parameter sonst per Kopie übergibt
    // (Sensoren/Ringpuffer müssen aber dieselben Instanzen bleiben).
    std::thread messThread(
        messSteuerung,
        std::ref(sammlungSensoren),
        std::ref(sammlungRingpuffer),
        std::ref(programmLaeuft)
    );

    // Programmschleife 
    while (programmLaeuft)
    {
        zeigeMenue( sammlungSensoren,
                    sammlungRingpuffer,
                    speichermanager,
                    programmLaeuft
        );
    }


   // Thread wird hier beendet
    messThread.join();

    
}   
    // Ungültige Konstruktor Parameter werden abgefangen (z.B. negative Werte..)
    catch (const std::invalid_argument& fehler)
    {
        std::cerr << "Ungueltige Konfiguration beim Start: " << fehler.what() << "\n";
        return 1;
    }
    //  Fängt fehlgeschlagene Speicherreservierung ab, wenn nicht genug
    // freier Platz im Hauptspeicher für einen weiteren Sensor vorhanden ist
    catch (const std::runtime_error& fehler)
    {
        std::cerr << "Fehler bei der Speicherreservierung: " << fehler.what() << "\n";
        return 1;
    }
    // Fängt echten Systemspeichermangel ab (new[] konnte keinen
    // Speicher vom Betriebssystem bekommen) - separat behandelt,
    // da dies kein Logikfehler im Programm, sondern ein Umgebungsproblem ist
    catch (const std::bad_alloc& fehler)
    {
        std::cerr << "Nicht genug Arbeitsspeicher verfuegbar: " << fehler.what() << "\n";
        return 1;
    }
    // Auffangnetz für alle anderen Fehler Ableitungen 
    catch (const std::exception& fehler)
    {
        
        std::cerr << "Unerwarteter Fehler: " << fehler.what() << "\n";
        return 1;
    }

    return 0;
}
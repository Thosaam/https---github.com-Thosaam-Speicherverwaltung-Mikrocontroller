#include <iostream>
#include <string>
using namespace std;

int main() {

    goto ende;
char c;
    while (cin >> c , c!=',') cout << c;

/*
double zahl1, zahl2, zahl3,zahl4, zahl5, mittelwert;

string name,vorname, Personalien;
int Kennnummer;


std::cout<<"Personalwesen, Bitte Name, Vorname und Kennummer angeben" <<std::endl;
std::cin>> name>> vorname>> Kennnummer;
Personalien= std::to_string(Kennnummer) + " "+ vorname + " "+name;
std::cout<<"Personalien" << Personalien << std::endl;


std::cout<<"Mittelwertberechnung: Bitte Zahl1 & zahl2 eingeben" <<std::endl;
std::cin>> zahl1>> zahl2;
std::cout<<"Bitte Zahl3 eingeben" <<std::endl;
std::cin>> zahl3;
std::cout<<"Bitte Zahl4 eingeben" <<std::endl;
std::cin>> zahl4;
std::cout<<"Bitte Zahl5 eingeben" <<std::endl;
std::cin>> zahl5;

mittelwert= (zahl1+zahl2+zahl3+zahl4+zahl5)/5;

std::cout<<"Mittelwert der angegebenen Zahlen ist:" << mittelwert <<std::endl;




    double a=11.1, b=5.784, c;
    c= a+b;

    std::cout << "Hello Lina" << std::endl;
    std::cout <<std::right << "... viel Erfolg ..."<< '\n' << std::flush;
    std::cout <<std::left << "... mit C++! Hier eine Rechnung:" << '\n' << std::flush
    << a<< '+' << b<< '=' << c << std::endl;

    int i = 10;
for (i=0; i<4; i++)
switch (i) {
case 0: std::cout << 1;
default: std::cout << i;
}
*/
ende:
    return 0;
}
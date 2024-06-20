/*

Napisati na jeziku C++ sledeći sistem klasa. Klase opremiti onim konstruktorima, destruktoromi 
operatorima dodelekoji su potrebni za bezbedno i efikasno korišćenje klasa. 
Greške prijavljivati izuzecima tipa jednostavnih klasa koje su opremljene pisanjem teksta poruke.


Implementirajte program koji modeluje Sunčev sistem sa planetama i Suncem. 
Svaki entitet u Sunčevom sistemu ima ime, prečnik i gravitaciju. 
Program treba da podržava sledeće funkcionalnosti: 
Definisati klasu "SuncevSistem" koja sadrži niz planeta i objekat Sunce. 
Klasa "SuncevSistem" treba da ima metodu "dodajPlanetu" koja dodaje planetu u niz planeta.
Definisati apstraktnu klasu "Entitet" koja sadrži polja ime, prečnik i gravitacija. 
Ova klasa treba da ima virtuelnu metodu "prikazilnformacije" koja prikazuje osnovne informacije o entitetu
na standardnom izlazu Izvesti klasu "Planeta" koja nasleduje klasu "Entitet". 

Klasa "Planeta" treba da ima dodatno polje "brojStanovnika" i da preklopi virtuelnu metodu 
"prikazilnformacije" kako bi prikazala informacije specifične za planetu. 
Izvesti klasu "Sunce" koja nasleđuje klasu "Entitet". Klasa "Sunce" treba da preklopi
virtuelnu metodu "prikazilnformacije" kako bi prikazala informacije specifične za Sunce. 
U klasi "SuncevSistem" implementirati operator koji vrača pokazivač na entitet na određenoj 
poziciji u nizu planeta. 
Preklapati operator + koji omogućava dodavanje planete u Sunčev sistem putem operatora
Implementirati prijateljsku funkciju "prikazilnformacije koja prikazuje informacije 
o entitetu na standardnom izlazu.
Kreirati objekat "suncevSistem" tipa "SuncevSistem".
Dodati nekoliko planeta u sunčev sistem pomoću operatora.
Prolaziti kroz niz planeta korišćenjem petlje i pozvati metodu "prikazilnformacije" za svaku planetu
Koristiti preklapanje operatora [] za pristupanje određenoj planeti u nizu 

i pozvati funkciju "prikazilnformacije" za tu planetu.*/

#include <iostream>
#include <string>
#include <vector>

class Entitet
{
public:
    Entitet(const std::string &ime, double precnik, double gravitacija)
        : ime(ime), precnik(precnik), gravitacija(gravitacija) {}

    virtual void prikaziInformacije() const
    {
        std::cout << "Ime: " << ime << ", Precnik: " << precnik << ", Gravitacija: " << gravitacija << std::endl;
    }

    std::string ime;
    double precnik;
    double gravitacija;
};

class Planeta : public Entitet
{
public:
    Planeta(const std::string &ime, double precnik, double gravitacija, int brojStanovnika)
        : Entitet(ime, precnik, gravitacija), brojStanovnika(brojStanovnika) {}

    void prikaziInformacije() const override
    {
        std::cout << "Planeta: ";
        Entitet::prikaziInformacije();
        std::cout << "Broj stanovnika: " << brojStanovnika << std::endl;
    }

    int brojStanovnika;
};






void prikaziInformacijeEntiteta(const Entitet &entitet)
{
    entitet.prikaziInformacije();
}



int main()
{
    Planeta zemlja("Zemlja", 6371, 9.81, 7.8e9);
    prikaziInformacijeEntiteta(zemlja);

    return 0;
}

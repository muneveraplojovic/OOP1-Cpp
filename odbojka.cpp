/*

Napisati sistem klasa u jeziku C++ koji modelira interakciju između odbojkaša, timova,
privilegovanih timova, parova i takmičenja unutar odbojkaške lige.
Klase treba opremiti odgovarajućim konstruktorima, destruktorima i operatorima dodele radi
sigume i efikasne upotrebe.
Klasa Odbojkaš: Ova klasa predstavlja odbojkaša i stvara se zadatim imenom i celobrojnom vrednošću
koja predstavlja početnu vrednost odbojkaša (podrazumevano 1000). Moguće je povečati
ili smanjiti vrednost odbojkaša za određeni procenat Odbojkaši se mogu uporediti na jednakost
(odbojkaš1 == odbojkaš2), a jednaki su ukoliko su im svi atributi jednaki. Odbojkaš se ispisuje
u izlazni tok u obliku

"ime#vrednost".

 Klasa Tim: Ova klasa predstavlja odbojkaški tim i stvara se zadatim nazivom i maksimalnim brojem
 odbojkaša koje je moguće priključiti timu. Moguće je priključiti odbojkaša na zadatu poziciju u
 timu Takode, moguće je dohvatiti trenutni broj odbojkaša u timu, dohvatiti odbojkaša sa određene
 pozicije i dohvatiti srednju vrednost vrednosti svih priključenih odbojkaša.
 Timovi se mogu uporediti na jednakost (tim1 ==  tim2), a jednaki su ukoliko su im nazivi,
 maksimaan broj odbojkaša i svi priključeni odbojkaši na odgovarajućim pozicijama jednaki.
 Tim se ispisuje u izlazni tok u formatu
"naziv [odbojkaš 1, odbojkaš2,...]".

Klasa PrivilegovaniTim: Ova klasa predstavlja privilegovani odbojkaški tiim i stvara se dodatnom
minimalnom vrednošću odbojkasa potrebnom da se odbojkas prikljuco timu.  Prilikom priključivanja
odbojkaša u privilegovani tim, greska se javlja ukoliko  je vrednost odbojkaša manja od minimalne
vrednosti potrebne za priključenje ekipe Privilegovani tim se ispisuje nakon naziva, dodatno
ispisujuci minimalnu vrednost odbojkaša potrebnu da se odbojkas prikljuci timu unutar običnih zagrada
Klasa Par: Ova klasa predstavlja uredeni par od dva pokazivača na podatke nekog koji se
zadaju pri stvaranju. Par se može uporediti na jednakost (par1== par2) upoređivanjem
odgovarajućih pokazivanih podataka. Par se ispisuje u izlazni tok u formatu "[podatak 1-podatak2]"

Klasa Takmičenje: Ova klasa predstavija odbojkaško takmičenje i sadrži par timova
(domačin i gost) koje se zadaju pri stvaramu, kao i ishod takmičenja.
Ishod takmičenja može biti POBEDA_DOMACIN, NERESENO ili POBEDA_GOST.
Ukoliko je takmičenje odigrano, odbojkašima obe ekipe se ažuriraju vrednosti u
zavisnosti od ishoda. Greška se javlja ukoliko takmičenje nije odigrano.
Takmičenje se ispisuje u izlazni tok tako što se ispisuje par timova,
 a zatim ishod takmičenja, ukoliko je takmičenje odigrano.

Napišite glavnu funkciju koja kreira nekoliko odbojkaša, dodaje ih u timove,
a potom kreira nekoliko takmičenja, odigrava ih i ispisuje rezultate*/

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Odbojkas
{
public:
    string ime;
    int vrednost;

    Odbojkas(string ime, int vrednost = 1000) : ime(ime), vrednost(vrednost) {}

    void promeniVrednost(float procenat)
    {
        vrednost += vrednost * procenat / 100;
    }

    bool operator==(const Odbojkas &drugi) const
    {
        return ime == drugi.ime && vrednost == drugi.vrednost;
    }

    void ispisi() const
    {
        cout << ime << "#" << vrednost;
    }
};

class Tim
{
public:
    string naziv;
    int maxBrojOdbojkasa;
    vector<Odbojkas> odbojkasi;

    Tim(string naziv, int maxBrojOdbojkasa) : naziv(naziv), maxBrojOdbojkasa(maxBrojOdbojkasa) {}

    void dodajOdbojkasa(const Odbojkas &odbojkas)
    {
        if (odbojkasi.size() >= maxBrojOdbojkasa)
        {
            cout << "Tim je pun." << endl;
            return;
        }
        odbojkasi.push_back(odbojkas);
    }

    int brojOdbojkasa() const
    {
        return odbojkasi.size();
    }

    Odbojkas &getOdbojkasa(int pozicija)
    {
        if (pozicija < 0 || pozicija >= odbojkasi.size())
        {
            cout << "Neispravna pozicija." << endl;
            exit(1);
        }
        return odbojkasi[pozicija];
    }

    float srednjaVrednost() const
    {
        int suma = 0;
        for (const auto &odbojkas : odbojkasi)
        {
            suma += odbojkas.vrednost;
        }
        return odbojkasi.empty() ? 0 : suma / odbojkasi.size();
    }

    bool operator==(const Tim &drugi) const
    {
        return naziv == drugi.naziv && maxBrojOdbojkasa == drugi.maxBrojOdbojkasa && odbojkasi == drugi.odbojkasi;
    }

    void ispisi() const
    {
        cout << naziv << " [";
        for (size_t i = 0; i < odbojkasi.size(); ++i)
        {
            odbojkasi[i].ispisi();
            if (i != odbojkasi.size() - 1)
                cout << ", ";
        }
        cout << "]";
    }
};

class PrivilegovaniTim : public Tim
{
public:
    int minimalnaVrednost;

    PrivilegovaniTim(string naziv, int maxBrojOdbojkasa, int minimalnaVrednost)
        : Tim(naziv, maxBrojOdbojkasa), minimalnaVrednost(minimalnaVrednost) {}

    void dodajOdbojkasa(const Odbojkas &odbojkas)
    {
        if (odbojkas.vrednost < minimalnaVrednost)
        {
            cout << "Odbojkas nema dovoljnu vrednost za prikljucenje timu." << endl;
            return;
        }
        Tim::dodajOdbojkasa(odbojkas);
    }

    void ispisi() const
    {
        Tim::ispisi();
        cout << " (Minimalna vrednost: " << minimalnaVrednost << ")";
    }
};

class Par
{
public:
    Odbojkas *domacin;
    Odbojkas *gost;

    Par(Odbojkas *domacin, Odbojkas *gost) : domacin(domacin), gost(gost) {}

    bool operator==(const Par &drugi) const
    {
        return *domacin == *drugi.domacin && *gost == *drugi.gost;
    }

    void ispisi() const
    {
        cout << "[" << domacin->ime << "-" << gost->ime << "]";
    }
};

enum class Ishod
{
    POBEDA_DOMACIN,
    NERESENO,
    POBEDA_GOST
};

class Takmicenje
{
public:
    Par timovi;
    Ishod ishod;
    bool odigrano;

    Takmicenje(const Par &par) : timovi(par), odigrano(false) {}

    void odigraj(Ishod rezultat)
    {
        ishod = rezultat;
        odigrano = true;
        // Ažuriraj vrednosti odbojkaša na osnovu ishoda
        switch (rezultat)
        {
        case Ishod::POBEDA_DOMACIN:
            timovi.domacin->promeniVrednost(10);
            timovi.gost->promeniVrednost(-5);
            break;
        case Ishod::NERESENO:
            timovi.domacin->promeniVrednost(0);
            timovi.gost->promeniVrednost(0);
            break;
        case Ishod::POBEDA_GOST:
            timovi.domacin->promeniVrednost(-5);
            timovi.gost->promeniVrednost(10);
            break;
        }
    }

    void ispisi() const
    {
        timovi.ispisi();
        if (odigrano)
        {
            switch (ishod)
            {
            case Ishod::POBEDA_DOMACIN:
                cout << " POBEDA DOMACIN";
                break;
            case Ishod::NERESENO:
                cout << " NERESENO";
                break;
            case Ishod::POBEDA_GOST:
                cout << " POBEDA GOST";
                break;
            }
        }
        else
        {
            cout << " TAKMICENJE NIJE ODIGRANO";
        }
    }
};

int main()
{
    // Kreiraj odbojkaše
    Odbojkas odbojkas1("Marko", 1100);
    Odbojkas odbojkas2("Milos", 1000);
    Odbojkas odbojkas3("Nikola", 1050);

    // Kreiraj timove
    Tim tim1("Crvena zvezda", 5);
    tim1.dodajOdbojkasa(odbojkas1);
    tim1.dodajOdbojkasa(odbojkas2);
    tim1.dodajOdbojkasa(odbojkas3);

    Tim tim2("Partizan", 5);
    tim2.dodajOdbojkasa(odbojkas2);
    tim2.dodajOdbojkasa(odbojkas1);
    tim2.dodajOdbojkasa(odbojkas3);

    // Kreiraj takmičenje
    Takmicenje takmicenje(Par(&odbojkas1, &odbojkas2));
    takmicenje.odigraj(Ishod::POBEDA_DOMACIN);

    // Ispis rezultata takmičenja
    cout << "Rezultati takmicenja: ";
    takmicenje.ispisi();
    cout << endl;

    return 0;
}

/*
Napisati na jeziku C++ sledeći sistem klasa.
Klase opremiti onim konstruktorima, destruktoromi operatorima dodele koji su potrebni
za bezbedno i efikasno korišćenje klasa.
Greške prijavljivati izuzecima tipa jednostavnih klasa koje su opremljene pisanjem teksta
poruke.

Glumac ima zadato ime i zadati filmski žanr. Žanr može biti AKCIJA, DRAMA ili KOMEDIJA
i može da se dohvati. Na glavnom izlazu se ispisuje u obliku ime (žanr).

Film ima naziv, trajanje izraženo brojem minuta i brojem sekundi i maksimalni broj glumaca.
Svi podaci se zadaju prilikom stvaranja. Može se dohvatiti broj minuta i broj sekundi
trajanja filma, može se proveriti koji od dva data filma traje duže, kao i da se dodaju
pojedinačni glumci (dodavanje ne uspeva u slučaju prekoračenja kapaciteta).
Film se ne može kopirati ni na koji način. Na glavnom izlazu se ispisuje u obliku
F(naziv minuti: sekunde), a zatim se pojedinačni glumci ispisuju u zasebnim redovima.


Filmski repertoar ima ukupno trajanje izraženo brojem minuta i brojem sekundi
i sadrži proizvoljan broj filmova. Stvara se prazan serijal,
nakon čega se filmovi dodaju pojedinačno uz ažuriranje ukupnog trajanja repertoara.
Repertoar može da se uredi po rastućim vremenima trajanja njegovih filmova.
Prilikom uništavanja repertoara ne uništavaju se njegovi filmovi,
Na glavnom izlazu se ispisuje u obliku Repertoar trajanje: minuti
sekundi , a zatim se u svakom redu ispisuje po jedan film.


Priložena je glavna funkcija koja stvara jedan repertoar filmova
i u njega dodaje nekoliko filmova sa nekoliko glumaca.
Nakon toga se stvara novi serijal filmova kao kopija prethodnog,
uređuje se novi serijal filmova, a zatim se originalni
i novi serijal filmova ispisuju na glavnom izlazu
*/

/*
Sta se trazi od nas u zadatku:
1. klasa glumac(ime, zanr)
2. klasa ili niz zanr(akcija, drama, komedija)
3.treba ispisati ime i zanr
4. klasa film(naziv, trajanje u min, trajanje u sek, max br glumaca)
5. podatke o filmu zadajemo mi
6. podatke o glumcima dodajemo mi, ukoliko se dodje do prekoracenje ne mozemo dodati glumca
7. uporedjivanje koji je film duzi
8. ispisuje se naziv_filma + trajanje u min: trajanje u sek i pored se ispisuju glumci
9. postoji repertoar odredjene duzine i koji je prazan, u njemu se redjaju filmovi po duzini trajanja
10.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Za sortiranje

using namespace std;

// Izuzetak za prekoračenje kapaciteta
class PrekoracenjeKapacitetaException : public exception
{
    virtual const char *what() const throw()
    {
        return "Prekoracenje kapaciteta!";
    }
};

// Enumeracija za žanrove
enum Zanr
{
    AKCIJA,
    DRAMA,
    KOMEDIJA
};

// Klasa Glumac
class Glumac
{
private:
    string ime;
    Zanr zanr;

public:
    // Konstruktor
    Glumac(string ime, Zanr zanr) : ime(ime), zanr(zanr) {}

    // Metoda za ispis
    void ispisi() const
    {
        cout << ime << " (" << zanr << ")" << endl;
    }
};





// Klasa Film
class Film
{
private:
    string naziv;
    int trajanjeMin;
    int trajanjeSec;
    int maxBrojGlumaca;
    vector<Glumac> glumci;

public:
    // Konstruktor
    Film(string naziv, int trajanjeMin, int trajanjeSec, int maxBrojGlumaca)
        : naziv(naziv), trajanjeMin(trajanjeMin), trajanjeSec(trajanjeSec), maxBrojGlumaca(maxBrojGlumaca) {}

    // Metode za dohvatanje trajanja filma
    int getTrajanjeMin() const { return trajanjeMin; }
    int getTrajanjeSec() const { return trajanjeSec; }

    // Metoda za dodavanje glumca
    void dodajGlumca(const Glumac &glumac)
    {
        if (glumci.size() < maxBrojGlumaca)
        {
            glumci.push_back(glumac);
        }
        else
        {
            throw PrekoracenjeKapacitetaException();
        }
    }

    // Metoda za ispis filma
    void ispisi() const
    {
        cout << "F(" << naziv << " " << trajanjeMin << ":" << trajanjeSec << ")" << endl;
        for (const auto &glumac : glumci)
        {
            glumac.ispisi();
        }
    }
};










// Klasa FilmskiRepertoar
class FilmskiRepertoar
{
private:
    vector<Film> filmovi;

public:
    // Konstruktor
    FilmskiRepertoar() {}

    // Metoda za dodavanje filma
    void dodajFilm(const Film &film)
    {
        filmovi.push_back(film);
    }

    // Metoda za sortiranje repertoara po trajanju
    void sortirajPoTrajanju()
    {
        sort(filmovi.begin(), filmovi.end(), [](const Film &f1, const Film &f2)
             { return f1.getTrajanjeMin() < f2.getTrajanjeMin(); });
    }

    // Metoda za ispis repertoara
    void ispisi() const
    {
        int ukupnoMin = 0;
        int ukupnoSec = 0;

        for (const auto &film : filmovi)
        {
            film.ispisi();
            ukupnoMin += film.getTrajanjeMin();
            ukupnoSec += film.getTrajanjeSec();
        }

        // Pretvaranje sekundi u minute ako je potrebno
        if (ukupnoSec >= 60)
        {
            ukupnoMin += ukupnoSec / 60;
            ukupnoSec %= 60;
        }

        cout << "Repertoar trajanje: " << ukupnoMin << " minuta " << ukupnoSec << " sekundi" << endl;
    }
};










int main()
{
    // Kreiranje glumaca
    Glumac glumac1("Robert De Niro", DRAMA);
    Glumac glumac2("Tom Hanks", DRAMA);
    Glumac glumac3("Bruce Willis", AKCIJA);
    Glumac glumac4("Jim Carrey", KOMEDIJA);

    // Kreiranje filmova
    Film film1("The Shawshank Redemption", 142, 0, 2);
    Film film2("Forrest Gump", 142, 30, 2);
    Film film3("Die Hard", 131, 15, 1);
    Film film4("Ace Ventura: Pet Detective", 86, 0, 1);

    // Dodavanje glumaca filmovima
    film1.dodajGlumca(glumac1);
    film1.dodajGlumca(glumac2);
    film2.dodajGlumca(glumac2);
    film2.dodajGlumca(glumac4);
    film3.dodajGlumca(glumac3);
    film4.dodajGlumca(glumac4);

    // Kreiranje repertoara i dodavanje filmova
    FilmskiRepertoar repertoar;
    repertoar.dodajFilm(film1);
    repertoar.dodajFilm(film2);
    repertoar.dodajFilm(film3);
    repertoar.dodajFilm(film4);

    // Kopiranje repertoara
    FilmskiRepertoar kopijaRepertoara = repertoar;

    // Sortiranje kopije repertoara po trajanju
    kopijaRepertoara.sortirajPoTrajanju();

    // Ispis originalnog repertoara
    cout << "Originalni repertoar:" << endl;
    repertoar.ispisi();

    cout << endl;

    // Ispis kopije repertoara
    cout << "Kopija repertoara sortirana po trajanju:" << endl;
    kopijaRepertoara.ispisi();

    return 0;
}

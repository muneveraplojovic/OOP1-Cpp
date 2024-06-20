/*


Napisite sistem klasa u jeziku c++ koji modelira interakciju izmedju knjiga, 
Clanova biblioteke i samog bibliotekara. Klase treba opremiti
odgovarajučim konstruktorima, destruktorima i operatorima dodele radi sigurne i efikasne upotrebe.

Klasa Knjiga: Ova klasa predstavlia knigu i sadrži informacije o naslova, 
autoru i godini izdanja. Prilikom kreiranja knjige, postavljaju se naslov, autor i godina izdanja
Informacije o knjizi mogu se dohvatiti.
Klasa Clan: Ova klasa predstavija člana biblioteke i sadrži informacije 
o imenu prezimenu, adresi i listi iznajmljenih knjiga. Prilikom kreiranja člana,
 postavljaju se ime. prezime i adresa. Knjige se dodaju ili uklanjaju iz liste iznajmljenih. 
 Informacije o članu i njegovim iznajmljenim knjigama mogu se ispisati.
Klasa Bibliotekar: Ova klasa predstavlja bibliotekara i sadrži informacije
o imenu i prezimenu. Bibliotekar može iznajmljivati i vraćati knjige članovima biblioteke.

 Informacije o bibliotekaru mogu se ispisati*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Knjiga
{
public:
    string naslov;
    string autor;
    int godinaIzdanja;

    Knjiga(const string &naslov, const string &autor, int godinaIzdanja)
        : naslov(naslov), autor(autor), godinaIzdanja(godinaIzdanja) {}
};

class Clan
{
public:
    string ime;
    string prezime;
    string adresa;
    vector<Knjiga> iznajmljeneKnjige;

    Clan(const string &ime, const string &prezime, const string &adresa)
        : ime(ime), prezime(prezime), adresa(adresa) {}

    void iznajmiKnjigu(const Knjiga &knjiga)
    {
        iznajmljeneKnjige.push_back(knjiga);
    }

    // void vratiKnjigu(const Knjiga &knjiga)
    // {
    //     for (auto it = iznajmljeneKnjige.begin(); it != iznajmljeneKnjige.end(); ++it)
    //     {
    //         if (it->naslov == knjiga.naslov && it->autor == knjiga.autor && it->godinaIzdanja == knjiga.godinaIzdanja)
    //         {
    //             iznajmljeneKnjige.erase(it);
    //             return;
    //         }
    //     }
    // }

    void ispisiInformacije() const
    {
        cout << "Ime: " << ime << endl;
        cout << "Prezime: " << prezime << endl;
        cout << "Adresa: " << adresa << endl;
        cout << "Iznajmljene knjige:" << endl;
        for (const auto &knjiga : iznajmljeneKnjige)
        {
            cout << "- " << knjiga.naslov << " (" << knjiga.autor << ", "
                 << knjiga.godinaIzdanja << ")" << endl;
        }
    }
};

class Bibliotekar
{
public:
    string ime;
    string prezime;

    Bibliotekar(const string &ime, const string &prezime)
        : ime(ime), prezime(prezime) {}

    void iznajmiKnjigu(Clan &clan, const Knjiga &knjiga)
    {
        clan.iznajmiKnjigu(knjiga);
    }

    // void vratiKnjigu(Clan &clan, const Knjiga &knjiga)
    // {
    //     clan.vratiKnjigu(knjiga);
    // }

    void ispisiInformacije() const
    {
        cout << "Ime: " << ime << endl;
        cout << "Prezime: " << prezime << endl;
    }
};

int main()
{
    Knjiga knjiga1("Naslov knjige 1", "Autor 1", 2000);
    Knjiga knjiga2("Naslov knjige 2", "Autor 2", 2010);

    Clan clan1("Marko", "Markovic", "Adresa 1");
    Clan clan2("Ana", "Anic", "Adresa 2");

    Bibliotekar bibliotekar("Jovan", "Jovanovic");

    bibliotekar.iznajmiKnjigu(clan1, knjiga1);
    bibliotekar.iznajmiKnjigu(clan2, knjiga2);

    cout << "Informacije o clanu 1:" << endl;
    clan1.ispisiInformacije();

    cout << endl;

    cout << "Informacije o clanu 2:" << endl;
    clan2.ispisiInformacije();

    cout << endl;

    cout << "Informacije o bibliotekaru:" << endl;
    bibliotekar.ispisiInformacije();

    return 0;
}

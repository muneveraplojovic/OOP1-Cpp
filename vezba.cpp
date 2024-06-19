#include <iostream>
using namespace std;

class Automobil
{
public:
    void zvukAutomobila()
    {
        cout << "Moje auto se cuje:  \n";
    }
};
//polimorfizam - vise nacina jedne klase
class Mercedes : public Automobil
{
public:
    void zvukAutomobila()
    {
        cout << "Mercedes: vrum vrum";
    }
};

class Audi : public Automobil
{
public:
    void zvukAutomobila()
    {
        cout << "Audi: brum brum \n";
    }
};

int main()
{
    Automobil autic;
    Audi audic;
    Mercedes mercedescic;

    string imePredmeta = "Objektno orjentisano programiranje";
    cout << "Hej ja vezbam " << imePredmeta << "\n";

    autic.zvukAutomobila();
    audic.zvukAutomobila();
    mercedescic.zvukAutomobila();
    return 0;
}
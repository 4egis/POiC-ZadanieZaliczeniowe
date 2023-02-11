#include <iostream>
#include <vector>

using namespace std;

class Pozycja{
private :
    int x;
    int y;

public:
    Pozycja(int x, int y){
        this->x = x;
        this->y = y;
    }

    double odleglosc(Pozycja p) {
        return sqrt(pow(this->x - p.x, 2) + pow(this->y - p.y, 2));
    }
};

class Przedmiot{
private:
    string nazwa;

public:
    Przedmiot(string nazwa){
        this->nazwa = nazwa;
    }

    string getNazwa(){
        return this->nazwa;
    }
};

class Towar : public Przedmiot{
private:
    int cena;
    int ilosc;

public:
    Towar(string nazwa, int cena, int ilosc) : Przedmiot(nazwa){
        this->cena = cena;
        this->ilosc = ilosc;
    }

    int getCena(){
        return this->cena;
    }

    int getIlosc(){
        return this->ilosc;
    }

    void zmniejszIlosc(){
        this->ilosc--;
    }
};

class Sklep{
private:
    Pozycja pozycja;
    vector<Towar> towary;

public:
    Sklep(int x, int y) : pozycja(x, y) {}

    void dodajTowar(Towar towar){
        towary.push_back(towar);
    }

    Towar sprawdzDostepnosc(string nazwa){
        for (int i = 0; i < towary.size(); i++){
            if (towary[i].getNazwa() == nazwa){
                return towary[i]; //specjalnie nie zwracam wskaźnika, bo klient nie powinien mieć możliwości modyfikacji towaru
            }
        }
        return Towar("brak", 0, 0);
    }
};

class ZwyklySklep : public Sklep{
public:
    ZwyklySklep(int x, int y) : Sklep(x, y) {}

    bool sprzedajTowar(string nazwa){
        Towar towar = sprawdzDostepnosc(nazwa);
        if (towar.getNazwa() == "brak"){
            return false;
        }

        if (towar.getIlosc() > 0){
            towar.zmniejszIlosc();
            return true;
        }

    }
};

class SiecSklepow{
private:
    vector<Sklep> sklepy;
    int marza;

public:
    SiecSklepow(int marza){
        this->marza = marza;
    }

    void dodajSklep(Sklep sklep){
        sklepy.push_back(sklep);
    }



}



int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

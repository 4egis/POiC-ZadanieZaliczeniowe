#include <iostream>
#include <vector>
#include <cmath>

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
protected:
    vector<Towar> towary;
    bool wSieci;

public:
    void dodajDoSieci(){
        wSieci = true;
    }

    bool czyWSieci(){
        return wSieci;
    }

    void dodajTowar(Przedmiot * przedmiot, int cena, int ilosc){
        Towar towar(przedmiot->getNazwa(), cena, ilosc);
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
private:
    Pozycja pozycja;
public:
    ZwyklySklep(int x, int y) : pozycja(x, y) {
        this->wSieci = false;
    }

    void sprzedajTowar(string nazwa){
        Towar towar = sprawdzDostepnosc(nazwa);

        if (towar.getIlosc() > 0){
            towar.zmniejszIlosc();
        }
    }

    Pozycja getPozycja(){
        return this->pozycja;
    }

    Towar najdrozszyTowar(int maksymalnaCena){
        Towar najdrozszyTowar("brak", 0, 0);
        for (int i = 0; i < towary.size(); i++){
            if (towary[i].getCena() > najdrozszyTowar.getCena() && towary[i].getCena() <= maksymalnaCena){
                najdrozszyTowar = towary[i];
            }
        }
        return najdrozszyTowar;
    }

    Towar najtanszyTowar(){
        Towar najtanszyTowar("brak", 0, 0);
        for (int i = 0; i < towary.size(); i++){
            if (towary[i].getCena() < najtanszyTowar.getCena() || najtanszyTowar.getNazwa() == "brak"){
                najtanszyTowar = towary[i];
            }
        }
        return najtanszyTowar;
    }

    Towar zaproponujLosowy(){
        int losowaLiczba = rand() % towary.size();
        return towary[losowaLiczba];
    }
};

class SiecSklepow{
private:
    vector<Sklep *> sklepy;
    int marza;

public:
    SiecSklepow(int marza){
        this->marza = marza;
    }

    void dodajSklep(Sklep * sklep){
        if(sklep->czyWSieci() == false){
            sklepy.push_back(sklep);
            sklep->dodajDoSieci();
        }
    }

    void przejmijSiec(SiecSklepow siec);

    void przejmijSklep(ZwyklySklep sklep);

    void utrataSklepu(Sklep sklep);

    Towar sprawdzDostepnosc(string nazwa){
        for (int i = 0; i < sklepy.size(); i++){
            Towar towar = sklepy[i]->sprawdzDostepnosc(nazwa);
            if (towar.getNazwa() != "brak"){
                return Towar(towar.getNazwa(), towar.getCena() * (100+marza)/100, towar.getIlosc());
            }
        }
        return Towar("brak", 0, 0);
    }


};

class Miasto;

class Klient{
protected:
    Miasto * miasto;
    int portfel;
    string imie;
    string nazwisko;
    Pozycja pozycja;
    vector<Przedmiot> listaZakupowZrealizowanych;

public:
    Klient(int portfel, string imie, string nazwisko, int x, int y) : pozycja(x, y) {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->portfel = portfel;
    }

    void dodajDoListyZakupowZrealizowanych(Przedmiot przedmiot){
        listaZakupowZrealizowanych.push_back(przedmiot);
    }

    virtual void kup() = 0;
};

class Miasto{
private:
    vector<Klient *> klienci;
    vector<ZwyklySklep> zwykleSklepy;
    vector<SiecSklepow> sieciSklepow;

public:
    void dodajKlienta(Klient * klient){
        klienci.push_back(klient);
    }

    void dodajZwyklySklep(ZwyklySklep sklep){
        zwykleSklepy.push_back(sklep);
    }

    void dodajSiecSklepow(SiecSklepow siec){
        sieciSklepow.push_back(siec);
    }

    void kupujcieDrodzyRodacy(){
        for (int i = 0; i < klienci.size(); i++){
            klienci[i]->kup();
        }
    }

    vector<ZwyklySklep> * getZwykleSklepy(){
        return &zwykleSklepy;
    }

    vector<SiecSklepow> * getSieciSklepow(){
        return &sieciSklepow;
    }
};

class WUlubionymSklepe : public Klient{
protected:
    ZwyklySklep * ulubionySklep;

public:
    WUlubionymSklepe(int portfel, string imie, string nazwisko, int x, int y, ZwyklySklep * ulubionySklep) : Klient(portfel, imie, nazwisko, x, y) {
        this->ulubionySklep = ulubionySklep;
    }

    virtual void kup() = 0;
};

class Maksymalista : public WUlubionymSklepe{
public:
    Maksymalista(int portfel, string imie, string nazwisko, int x, int y, ZwyklySklep * ulubionySklep) : WUlubionymSklepe(portfel, imie, nazwisko, x, y, ulubionySklep) {}

    void kup(){
        Towar towar = ulubionySklep->najdrozszyTowar(portfel);
        if (towar.getNazwa() != "brak"){
            portfel -= towar.getCena();
            dodajDoListyZakupowZrealizowanych(Przedmiot(towar.getNazwa()));
            ulubionySklep->sprzedajTowar(towar.getNazwa());
        }
    }
};

class Minimalista : public WUlubionymSklepe{
public:
    Minimalista(int portfel, string imie, string nazwisko, int x, int y, ZwyklySklep * ulubionySklep) : WUlubionymSklepe(portfel, imie, nazwisko, x, y, ulubionySklep) {}

    void kup(){
        Towar towar = ulubionySklep->najtanszyTowar();
        if (towar.getNazwa() != "brak"){
            portfel -= towar.getCena();
            dodajDoListyZakupowZrealizowanych(Przedmiot(towar.getNazwa()));
            ulubionySklep->sprzedajTowar(towar.getNazwa());
        }
    }
};

class Losowy : public WUlubionymSklepe{
private:
    int iloscProb;

public:
    Losowy(int portfel, string imie, string nazwisko, int x, int y, ZwyklySklep * ulubionySklep, int iloscProb) : WUlubionymSklepe(portfel, imie, nazwisko, x, y, ulubionySklep) {
        this->iloscProb = iloscProb;
    }

    void kup(){
        for(int i = 0; i < iloscProb; i++){
            Towar towar = ulubionySklep->zaproponujLosowy();
            if (towar.getNazwa() != "brak" && towar.getCena() <= portfel){
                portfel -= towar.getCena();
                dodajDoListyZakupowZrealizowanych(Przedmiot(towar.getNazwa()));
                ulubionySklep->sprzedajTowar(towar.getNazwa());
                break;
            }
        }
    }

};

class ZKonkretnymProduktem : public Klient{
protected:
    vector<Przedmiot> listaZakupow;

public:
    ZKonkretnymProduktem(int portfel, string imie, string nazwisko, int x, int y) : Klient(portfel, imie, nazwisko, x, y) {}

    virtual void kup() = 0;

    void dodajDoListyZakupow(Przedmiot przedmiot){
        listaZakupow.push_back(przedmiot);
    }
};

class Oszczedny : public ZKonkretnymProduktem{
public:
    Oszczedny(int portfel, string imie, string nazwisko, int x, int y) : ZKonkretnymProduktem(portfel, imie, nazwisko, x, y) {}

    void kup(){

        if(listaZakupow.size() == 0){
            return;
        }

        vector<ZwyklySklep> * zwykleSklepy = miasto->getZwykleSklepy();
        vector<SiecSklepow> * sieciSklepow = miasto->getSieciSklepow();

        Towar najtanszy = Towar("brak", 0, 0);

        Przedmiot planowanyZakup = listaZakupow[0];

        for(int i = 0; i < zwykleSklepy->size(); i++){
            Towar towar = zwykleSklepy->at(i).sprawdzDostepnosc(planowanyZakup.getNazwa());
            if (towar.getNazwa() != "brak" && (najtanszy.getNazwa() == "brak" || towar.getCena() < najtanszy.getCena())){
                najtanszy = towar;
            }
        }
        for(int i = 0; i < sieciSklepow->size(); i++){
            Towar towar = sieciSklepow->at(i).sprawdzDostepnosc(planowanyZakup.getNazwa());
            if (towar.getNazwa() != "brak" && (najtanszy.getNazwa() == "brak" || towar.getCena() < najtanszy.getCena())){
                najtanszy = towar;
            }
        }

        if (najtanszy.getNazwa() != "brak" && najtanszy.getCena() <= portfel){
            portfel -= najtanszy.getCena();
            dodajDoListyZakupowZrealizowanych(planowanyZakup);
            listaZakupow.erase(listaZakupow.begin());
        }

    }
};

class Tradycjonalista : public ZKonkretnymProduktem{
public:
    Tradycjonalista(int portfel, string imie, string nazwisko, int x, int y) : ZKonkretnymProduktem(portfel, imie, nazwisko, x, y) {}

    void kup(){

        if(listaZakupow.size() == 0){
            return;
        }

        vector<ZwyklySklep> * zwykleSklepy = miasto->getZwykleSklepy();

        Przedmiot planowanyZakup = listaZakupow[0];

        ZwyklySklep * najblizszySklep = nullptr;

        for (int i = 0; i < zwykleSklepy->size(); i++){
            Towar towar = zwykleSklepy->at(i).sprawdzDostepnosc(planowanyZakup.getNazwa());
            if(towar.getNazwa() != "brak" && towar.getCena() <= portfel){
                if(najblizszySklep == nullptr){
                    najblizszySklep = &zwykleSklepy->at(i);
                } else {
                    if (pozycja.odleglosc(najblizszySklep->getPozycja()) > pozycja.odleglosc(zwykleSklepy->at(i).getPozycja())){
                        najblizszySklep = &zwykleSklepy->at(i);
                    }

                }
            }
        }
        if(najblizszySklep != nullptr){
            Towar towar = najblizszySklep->sprawdzDostepnosc(planowanyZakup.getNazwa());
            portfel -= towar.getCena();
            dodajDoListyZakupowZrealizowanych(planowanyZakup);
            listaZakupow.erase(listaZakupow.begin());
        }

    }
};

int main() {
    Przedmiot przedmiot1 = Przedmiot("hulajnoga");
    Przedmiot przedmiot2 = Przedmiot("deskorolka");
    Przedmiot przedmiot3 = Przedmiot("rolki");
    Przedmiot przedmiot4 = Przedmiot("lyzwy");
//    Przedmiot przedmiot5 = Przedmiot("perfumy");
//    Przedmiot przedmiot6 = Przedmiot("Playstation");
//    Przedmiot przedmiot7 = Przedmiot("Xbox");


    ZwyklySklep zwyklySklep1 = ZwyklySklep(4, 2);
    zwyklySklep1.dodajTowar(&przedmiot1, 78, 2);
    zwyklySklep1.dodajTowar(&przedmiot2, 65, 1);

    ZwyklySklep zwyklySklep2 = ZwyklySklep(13, 5);
    zwyklySklep2.dodajTowar(&przedmiot1, 81, 1);
    zwyklySklep2.dodajTowar(&przedmiot2, 76, 2);

    ZwyklySklep zwyklySklep3 = ZwyklySklep(3, 21);
    zwyklySklep3.dodajTowar(&przedmiot3, 84, 3);
    zwyklySklep3.dodajTowar(&przedmiot4, 120, 3);

    Sklep sklep1 = Sklep();
    sklep1.dodajTowar(&przedmiot1, 81, 1);
    sklep1.dodajTowar(&przedmiot4, 119, 2);

    Sklep sklep2 = Sklep();
    sklep2.dodajTowar(&przedmiot2, 71, 4);
    sklep2.dodajTowar(&przedmiot4, 116, 1);

    Sklep sklep3 = Sklep();
    sklep3.dodajTowar(&przedmiot3, 81, 1);
    sklep3.dodajTowar(&przedmiot2, 85, 5);

    SiecSklepow siecSklepow1 = SiecSklepow(8);
    siecSklepow1.dodajSklep(&zwyklySklep1);
    siecSklepow1.dodajSklep(&zwyklySklep2);
    siecSklepow1.dodajSklep(&zwyklySklep3);

    Sklep sklep4 = Sklep();
    sklep4.dodajTowar(&przedmiot2, 81, 2);
    sklep4.dodajTowar(&przedmiot3, 79, 3);

    Sklep sklep5 = Sklep();
    sklep5.dodajTowar(&przedmiot1, 86, 2);
    sklep5.dodajTowar(&przedmiot4, 124, 3);
    sklep5.dodajTowar(&przedmiot3, 69, 1);

    SiecSklepow siecSklepow2 = SiecSklepow(14);
    siecSklepow2.dodajSklep(&sklep4);
    siecSklepow2.dodajSklep(&sklep5);


    Maksymalista maksymalista1 = Maksymalista(100, "Jan", "Kowalski", 5, 10, &zwyklySklep1);
    Minimalista minimalista1 = Minimalista(80, "Tomasz", "Niecik", 2, 2, &zwyklySklep2);
    Losowy losowy1 = Losowy(90, "Krzysztof", "Kolumb", 1050, 2500, &zwyklySklep3, 3);

    Oszczedny oszczedny1 = Oszczedny(94, "Janusz", "Tracz", 8, 2);
    oszczedny1.dodajDoListyZakupow(przedmiot1);
    oszczedny1.dodajDoListyZakupow(przedmiot2);

    Tradycjonalista tradycjonalista1 = Tradycjonalista(100, "Jedrzej", "Rymnsza", 7, 1);
    tradycjonalista1.dodajDoListyZakupow(przedmiot3);

    Miasto naszePiekneMiasto;

    naszePiekneMiasto.dodajZwyklySklep(zwyklySklep1);
    naszePiekneMiasto.dodajZwyklySklep(zwyklySklep2);
    naszePiekneMiasto.dodajZwyklySklep(zwyklySklep3);
    naszePiekneMiasto.dodajSiecSklepow(siecSklepow1);
    naszePiekneMiasto.dodajSiecSklepow(siecSklepow2);
    naszePiekneMiasto.dodajKlienta(&maksymalista1);
    naszePiekneMiasto.dodajKlienta(&minimalista1);
    naszePiekneMiasto.dodajKlienta(&losowy1);
    naszePiekneMiasto.dodajKlienta(&oszczedny1);
    naszePiekneMiasto.dodajKlienta(&tradycjonalista1);

    naszePiekneMiasto.kupujcieDrodzyRodacy();

    cout<<"asd";
    return 0;
}

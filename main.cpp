#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Pozycja{
private :
    int x;
    int y;



public:

    ~Pozycja() = default;
    Pozycja(const Pozycja&) = default;
    Pozycja& operator=(const Pozycja&) = delete;

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

    Przedmiot(const Przedmiot&) = default;
    Przedmiot& operator=(const Przedmiot&) = default;
    ~Przedmiot() = default;

    Przedmiot(string nazwa){
        this->nazwa = nazwa;
    }

    string getNazwa() const {
        return this->nazwa;
    }
};

class Towar : public Przedmiot{
private:
    int cena;
    int ilosc;

public:

    Towar(const Towar&) = default;
    Towar& operator=(const Towar&) = default;
    ~Towar() = default;

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

    friend ostream& operator<<(ostream& os, Towar towar){
        os << "nazwa towaru: " << towar.getNazwa() << ", cena: " << towar.getCena() << ", ilosc: " << towar.getIlosc();
        return os;
    }
};

class SiecSklepow;

class Sklep{
protected:
    string nazwa;
    vector<Towar> towary;
    bool wSieci;
    SiecSklepow * siec = nullptr;

public:

    Sklep(const Sklep&) = default;
    Sklep& operator=(const Sklep&) = delete;
    ~Sklep() {
        towary.clear();
    };

    Sklep(string nazwa) : nazwa(nazwa) {
        this->wSieci = false;
    }

    string getNazwa(){
        return this->nazwa;
    }

    void dodajDoSieci(SiecSklepow * siec){
        wSieci = true;
        this->siec = siec;
    }

    bool czyWSieci() const{
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

    friend ostream& operator<<(ostream& os, Sklep sklep){
        os << "nazwa sklepu: " << sklep.getNazwa() << ", towary: " << endl;
        for (int i = 0; i < sklep.towary.size(); i++){
            os << sklep.towary[i] << endl;
        }
        return os;
    }
};

class ZwyklySklep : public Sklep{
private:
    Pozycja pozycja;
public:

    ZwyklySklep(const ZwyklySklep&) = default;
    ZwyklySklep& operator=(const ZwyklySklep&) = delete;
    ~ZwyklySklep() = default;

    ZwyklySklep(int x, int y, string nazwa) : Sklep(nazwa), pozycja(x, y) {}

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
    string nazwa;
    vector<Sklep *> sklepy;
    int marza;

public:

    SiecSklepow(const SiecSklepow&) = default;
    SiecSklepow& operator=(const SiecSklepow&) = delete;
    ~SiecSklepow() {
        sklepy.clear();
    };

    SiecSklepow(int marza, string nazwa){
        this->marza = marza;
        this->nazwa = nazwa;
    }

    void dodajSklep(Sklep * sklep){
        if(!sklep->czyWSieci()){
            sklepy.push_back(sklep);
            sklep->dodajDoSieci(this);
        }
    }

    void przejmijSiec(SiecSklepow * siec){
        for (int i = 0; i < siec->sklepy.size(); i++){
            dodajSklep(siec->sklepy[i]);
        }
        delete siec;
    };

    void przejmijSklep(ZwyklySklep * sklep){
        sklep->dodajDoSieci(this);
        dodajSklep(sklep);
    }

    void przejmijSklep(Sklep * sklep){
        dodajSklep(sklep);
    }

    void utrataSklepu(Sklep * sklep){
        vector<Sklep *>::iterator it = find(sklepy.begin(), sklepy.end(), sklep);
        if(it != sklepy.end())
            sklepy.erase(it);
    }

    Towar sprawdzDostepnosc(string nazwa){
        for (int i = 0; i < sklepy.size(); i++){
            Towar towar = sklepy[i]->sprawdzDostepnosc(nazwa);
            if (towar.getNazwa() != "brak"){
                return Towar(towar.getNazwa(), towar.getCena() * (100+marza)/100, towar.getIlosc());
            }
        }
        return Towar("brak", 0, 0);
    }

    friend ostream& operator<<(ostream& os, SiecSklepow siec){
        os << "nazwa sieci: " << siec.nazwa << endl;
        os << "marza: " << siec.marza << "%" << endl;
        os << "sklepy nalezace do tej sieci: " << endl;
        for (int i = 0; i < siec.sklepy.size(); i++){
            os << * siec.sklepy[i] << endl;
        }
        return os;
    }

};

class Miasto;

class Klient{
protected:
    int portfel;
    string imie;
    string nazwisko;
    Pozycja pozycja;
    vector<Przedmiot> listaZakupowZrealizowanych;

public:

    Klient(const Klient&) = delete;
    Klient& operator=(const Klient&) = delete;
    virtual ~Klient() {
        listaZakupowZrealizowanych.clear();
    };


    Klient(int portfel, string imie, string nazwisko, int x, int y) : pozycja(x, y) {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->portfel = portfel;
    }

    void wypisz_info(){
        cout<<"Imie: "<<imie<<" przechodzi do robienia zakupow"<<endl;
    }

    void dodajDoListyZakupowZrealizowanych(Przedmiot przedmiot){
        listaZakupowZrealizowanych.push_back(przedmiot);
    }

    virtual ostream& wypisz(ostream& os) const = 0;

    friend ostream& operator<<(ostream& os, const Klient& klient){
        return klient.wypisz(os);
    }

    virtual void kup() = 0;
};

class Miasto{
private:
    vector<Klient *> klienci;
    vector<ZwyklySklep> zwykleSklepy;
    vector<SiecSklepow> sieciSklepow;

public:

    Miasto() = default;
    Miasto(const Miasto&) = delete;
    Miasto& operator=(const Miasto&) = delete;
    ~Miasto() {
        klienci.clear();
        zwykleSklepy.clear();
        sieciSklepow.clear();
    };

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

    friend ostream& operator<<(ostream& os, const Miasto& miasto){
        os << "Zwykle sklepy:" << endl;
        for (int i = 0; i < miasto.zwykleSklepy.size(); i++){
            os << miasto.zwykleSklepy[i] << endl;
        }
        os << "Sieci sklepow:" << endl;
        for (int i = 0; i < miasto.sieciSklepow.size(); i++){
            os << miasto.sieciSklepow[i] << endl;
        }
        os<<"Klienci:"<<endl;
        for (int i = 0; i < miasto.klienci.size(); i++){
            os<<*miasto.klienci[i]<<endl;
        }
        return os;
    }
};

class WUlubionymSklepe : public Klient{
protected:
    ZwyklySklep * ulubionySklep;

public:

    WUlubionymSklepe(const WUlubionymSklepe&) = delete;
    WUlubionymSklepe& operator=(const WUlubionymSklepe&) = delete;
    ~WUlubionymSklepe() override = default;

    WUlubionymSklepe(int portfel, string imie, string nazwisko, int x, int y, ZwyklySklep * ulubionySklep) : Klient(portfel, imie, nazwisko, x, y) {
        this->ulubionySklep = ulubionySklep;
    }

    ostream& wypisz(ostream& os) const override{
        os<<"Imie: "<<imie<<endl;
        os<<"Nazwisko: "<<nazwisko<<endl;
        os<<"Portfel: "<<portfel<<endl;
        os<<"Ulubiony sklep: "<<ulubionySklep->getNazwa()<<endl;
        os<<"Lista zakupow zrealizowanych: "<<endl;
        for (int i = 0; i < listaZakupowZrealizowanych.size(); i++){
            os<<listaZakupowZrealizowanych[i].getNazwa()<<endl;
        }
        return os;
    }

    virtual void kup() = 0;
};

class Maksymalista : public WUlubionymSklepe{
public:

    Maksymalista(const Maksymalista&) = delete;
    Maksymalista& operator=(const Maksymalista&) = delete;
    ~Maksymalista() override = default;

    Maksymalista(int portfel, string imie, string nazwisko, int x, int y, ZwyklySklep * ulubionySklep) : WUlubionymSklepe(portfel, imie, nazwisko, x, y, ulubionySklep) {}

    void kup(){
        wypisz_info();
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

    Minimalista(const Minimalista&) = delete;
    Minimalista& operator=(const Minimalista&) = delete;
    ~Minimalista() override = default;

    Minimalista(int portfel, string imie, string nazwisko, int x, int y, ZwyklySklep * ulubionySklep) : WUlubionymSklepe(portfel, imie, nazwisko, x, y, ulubionySklep) {}

    void kup(){
        wypisz_info();
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

    Losowy(const Losowy&) = delete;
    Losowy& operator=(const Losowy&) = delete;
    ~Losowy() override = default;

    Losowy(int portfel, string imie, string nazwisko, int x, int y, ZwyklySklep * ulubionySklep, int iloscProb) : WUlubionymSklepe(portfel, imie, nazwisko, x, y, ulubionySklep) {
        this->iloscProb = iloscProb;
    }

    void kup(){
        wypisz_info();
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
    Miasto * miasto;

public:

    ZKonkretnymProduktem(const ZKonkretnymProduktem&) = delete;
    ZKonkretnymProduktem& operator=(const ZKonkretnymProduktem&) = delete;
    ~ZKonkretnymProduktem() override {
        listaZakupow.clear();
    };

    ZKonkretnymProduktem(int portfel, string imie, string nazwisko, int x, int y, Miasto * miasto) : Klient(portfel, imie, nazwisko, x, y) {this->miasto = miasto;}

    virtual void kup() = 0;

    ostream& wypisz(ostream& os) const override{
        os<<"Imie: "<<imie<<endl;
        os<<"Nazwisko: "<<nazwisko<<endl;
        os<<"Portfel: "<<portfel<<endl;
        os<<"Lista zakupow: "<<endl;
        for (int i = 0; i < listaZakupow.size(); i++){
            os<<listaZakupow[i].getNazwa()<<endl;
        }
        os<<"Lista zakupow zrealizowanych: "<<endl;
        for (int i=0; i<listaZakupowZrealizowanych.size(); i++){
            os<<listaZakupowZrealizowanych[i].getNazwa()<<endl;
        }
        return os;
    }

    void dodajDoListyZakupow(Przedmiot przedmiot){
        listaZakupow.push_back(przedmiot);
    }
};

class Oszczedny : public ZKonkretnymProduktem{
public:

    Oszczedny(const Oszczedny&) = delete;
    Oszczedny& operator=(const Oszczedny&) = delete;
    ~Oszczedny() override = default;

    Oszczedny(int portfel, string imie, string nazwisko, int x, int y, Miasto * miasto) : ZKonkretnymProduktem(portfel, imie, nazwisko, x, y, miasto) {}

    void kup(){
        wypisz_info();

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

    Tradycjonalista(const Tradycjonalista&) = delete;
    Tradycjonalista& operator=(const Tradycjonalista&) = delete;
    ~Tradycjonalista() override = default;

    Tradycjonalista(int portfel, string imie, string nazwisko, int x, int y, Miasto * miasto) : ZKonkretnymProduktem(portfel, imie, nazwisko, x, y, miasto) {}

    void kup(){
        wypisz_info();

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
    Miasto naszePiekneMiasto;
    cout<<"Obiekt miasto utworzony"<<endl;

    Przedmiot przedmiot1 = Przedmiot("hulajnoga");
    Przedmiot przedmiot2 = Przedmiot("deskorolka");
    Przedmiot przedmiot3 = Przedmiot("rolki");
    Przedmiot przedmiot4 = Przedmiot("lyzwy");
//    Przedmiot przedmiot5 = Przedmiot("perfumy");
//    Przedmiot przedmiot6 = Przedmiot("Playstation");
//    Przedmiot przedmiot7 = Przedmiot("Xbox");


    ZwyklySklep zwyklySklep1 = ZwyklySklep(4, 2, "zwyklySklep1");
    zwyklySklep1.dodajTowar(&przedmiot1, 78, 2);
    zwyklySklep1.dodajTowar(&przedmiot2, 65, 1);

    ZwyklySklep zwyklySklep2 = ZwyklySklep(13, 5, "zwyklySklep2");
    zwyklySklep2.dodajTowar(&przedmiot1, 81, 1);
    zwyklySklep2.dodajTowar(&przedmiot2, 76, 2);

    ZwyklySklep zwyklySklep3 = ZwyklySklep(3, 21, "zwyklySklep3");
    zwyklySklep3.dodajTowar(&przedmiot3, 84, 3);
    zwyklySklep3.dodajTowar(&przedmiot4, 120, 3);

    Sklep sklep1 = Sklep("sklep1");
    sklep1.dodajTowar(&przedmiot1, 81, 1);
    sklep1.dodajTowar(&przedmiot4, 119, 2);

    Sklep sklep2 = Sklep("sklep2");
    sklep2.dodajTowar(&przedmiot2, 71, 4);
    sklep2.dodajTowar(&przedmiot4, 116, 1);

    Sklep sklep3 = Sklep("sklep3");
    sklep3.dodajTowar(&przedmiot3, 81, 1);
    sklep3.dodajTowar(&przedmiot2, 85, 5);

    SiecSklepow siecSklepow1 = SiecSklepow(8, "siecSklepow1");
    siecSklepow1.dodajSklep(&sklep1);
    siecSklepow1.dodajSklep(&sklep2);
    siecSklepow1.dodajSklep(&sklep3);

    Sklep sklep4 = Sklep("sklep4");
    sklep4.dodajTowar(&przedmiot2, 81, 2);
    sklep4.dodajTowar(&przedmiot3, 79, 3);

    Sklep sklep5 = Sklep("sklep5");
    sklep5.dodajTowar(&przedmiot1, 86, 2);
    sklep5.dodajTowar(&przedmiot4, 124, 3);
    sklep5.dodajTowar(&przedmiot3, 69, 1);

    SiecSklepow siecSklepow2 = SiecSklepow(14, "siecSklepow2");
    siecSklepow2.dodajSklep(&sklep4);
    siecSklepow2.dodajSklep(&sklep5);

    Maksymalista maksymalista1 = Maksymalista(100, "Jan", "Kowalski", 5, 10, &zwyklySklep1);
    Minimalista minimalista1 = Minimalista(80, "Tomasz", "Niecik", 2, 2, &zwyklySklep2);
    Losowy losowy1 = Losowy(90, "Krzysztof", "Kolumb", 1050, 2500, &zwyklySklep3, 3);


    Oszczedny oszczedny1 = Oszczedny(94, "Janusz", "Tracz", 8, 2, &naszePiekneMiasto);
    oszczedny1.dodajDoListyZakupow(przedmiot1);
    oszczedny1.dodajDoListyZakupow(przedmiot2);

    Tradycjonalista tradycjonalista1 = Tradycjonalista(100, "Jedrzej", "Rymsza", 7, 1, &naszePiekneMiasto);
    tradycjonalista1.dodajDoListyZakupow(przedmiot3);


    naszePiekneMiasto.dodajZwyklySklep(zwyklySklep1);
    naszePiekneMiasto.dodajZwyklySklep(zwyklySklep2);
    naszePiekneMiasto.dodajZwyklySklep(zwyklySklep3);
    cout<<"Dodano zwykle sklepy"<<endl;
    naszePiekneMiasto.dodajSiecSklepow(siecSklepow1);
    naszePiekneMiasto.dodajSiecSklepow(siecSklepow2);
    cout<<"Dodano sieci sklepow"<<endl;
    naszePiekneMiasto.dodajKlienta(&maksymalista1);
    naszePiekneMiasto.dodajKlienta(&minimalista1);
    naszePiekneMiasto.dodajKlienta(&losowy1);
    naszePiekneMiasto.dodajKlienta(&oszczedny1);
    naszePiekneMiasto.dodajKlienta(&tradycjonalista1);
    cout<<"Dodano klientow"<<endl;

    cout<<"wypisz miasto:"<<endl;
    cout<<naszePiekneMiasto<<endl;


    cout<<"rozpoczynam symulacje"<<endl;
    naszePiekneMiasto.kupujcieDrodzyRodacy();

    cout<<"symulacja zakonczona"<<endl;

    cout<<"wypisz miasto:"<<endl;
    cout<<naszePiekneMiasto<<endl;
    return 0;
}

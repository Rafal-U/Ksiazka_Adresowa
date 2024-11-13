#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

string wczytajLinie()
{
    string input;
    getline(cin, input);
    return input;
}
struct Uzytkownik
{
    int idUzytkownika = 0;
    string login, haslo;
};

struct Adresat
{
    int id = 0;
    string imie, nazwisko, nrTel, email, adres;
};


void wczytajUzytkownikow(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik osoba;
    int numerLinii = 1, pozycja = 0, dlugoscLinii = 0;
    string linia = "", slowo = "";
    string daneOsoby[3];
    fstream plik;

    plik.open("Uzytkownicy.txt", ios::in);
    if (plik.good())
    {
        while(getline(plik, linia))
        {
            dlugoscLinii = linia.length();
            if (dlugoscLinii != 0)
            {
                for (int i = 0; i < dlugoscLinii; i++)
                {
                    if (linia[i] == '|')
                    {
                        slowo = "";
                        pozycja++;
                    }
                    else
                    {
                        slowo += linia[i];
                        daneOsoby[pozycja] = slowo;
                    }
                }
                osoba.idUzytkownika = stoi(daneOsoby[0]);
                osoba.login = daneOsoby[1];
                osoba.haslo = daneOsoby[2];
                uzytkownicy.push_back(osoba);
                numerLinii++;
                pozycja = 0;
            }
        }
    }
    plik.close();
}

void aktualizujListeUzytkownikow(vector<Uzytkownik> &uzytkownicy)
{
    fstream plik;
    Uzytkownik osoba;
    plik.open("Uzytkownicy.txt", ios::out);
    for (Uzytkownik osoba : uzytkownicy)
    {
        plik << osoba.idUzytkownika << '|' << osoba.login << '|' << osoba.haslo << '|' << endl;
    }
    plik.close();
}

bool sprawdzCzyLoginLubHasloIstnieja(vector <Uzytkownik> uzytkownicy, string wpisanyLogin, string wpisaneHaslo)
{
    bool czyZnaleziono = false;
    for (Uzytkownik osoba : uzytkownicy)
    {
        if (osoba.login == wpisanyLogin || osoba.haslo == wpisaneHaslo)
        {
            czyZnaleziono = true;
        }
    }
    return czyZnaleziono;
}

void zarejestrujUzytkownika(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik osoba;
    fstream plik;
    bool uzytkownikIstnieje;
    string potwierdzenie = "tak";

    while (uzytkownikIstnieje && potwierdzenie == "tak")
    {
        system("cls");
        if (uzytkownicy.empty())
        {
            osoba.idUzytkownika = 1;
        }
        else
        {
            osoba.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
        }
        cout << "Utworz login" << endl;
        osoba.login = wczytajLinie();
        cout << "Utworz haslo" << endl;
        osoba.haslo = wczytajLinie();
        uzytkownikIstnieje = sprawdzCzyLoginLubHasloIstnieja(uzytkownicy, osoba.login, osoba.haslo);
        if (uzytkownikIstnieje)
        {
            cout << "Podane haslo lub login sa juz zajete, jesli chcesz sprobowac ponownie wpisz 'tak', nastepnie zatwierdz klawiszem Enter." << endl;
            potwierdzenie = wczytajLinie();
        }
    }
    if (!uzytkownikIstnieje)
    {
        uzytkownicy.push_back(osoba);
        plik.open("Uzytkownicy.txt", ios::out | ios::app);
        plik << osoba.idUzytkownika << '|' << osoba.login << '|' << osoba.haslo << '|' << endl;
        plik.close();
        system("cls");
        cout << "Rejestracja pomyslna! Przekierowuje do menu glownego." << endl;
        Sleep(2000);
    }
}

bool znajdzUzytkownika(vector <Uzytkownik> uzytkownicy, string wpisanyLogin, string wpisaneHaslo)
{
    bool czyZnaleziono = false;
    for (Uzytkownik osoba : uzytkownicy)
    {
         if (osoba.login == wpisanyLogin && osoba.haslo == wpisaneHaslo)
        {
            czyZnaleziono = true;
        }
    }
    return czyZnaleziono;
}

int zalogujUzytkownika(vector<Uzytkownik> uzytkownicy)
{
    system("cls");
    string login = "", haslo = "";
    int identyfikator = 0;
    bool znaleziono;

    cout << "Podaj login" << endl;
    login = wczytajLinie();
    cout << "Podaj haslo" << endl;
    haslo = wczytajLinie();
    znaleziono = znajdzUzytkownika(uzytkownicy, login, haslo);

    if (znaleziono)
    {
        for (size_t i = 0; i < uzytkownicy.size(); i++)
        {
            if (uzytkownicy[i].login == login && uzytkownicy[i].haslo == haslo)
            {
                identyfikator = uzytkownicy[i].idUzytkownika;
            }
        }
    }
    else
    {
        cout << "Niepoprawny login lub haslo!" << endl;
        Sleep(2000);
    }
    return identyfikator;
}

void edytujUzytkownika(vector<Uzytkownik> &uzytkownicy)
{
    system("cls");
    char wyborOpcji;
    int obecnyUzytkownik = 0;
    string nowyLogin = "", noweHaslo = "";
    bool nazwaIstnieje;

    obecnyUzytkownik = zalogujUzytkownika(uzytkownicy);
    if (obecnyUzytkownik != 0)
    {
        system("cls");
        cout << "Wybierz jaka dana chcesz edytowac:" << endl << "a. Zmien login" << endl << "b. Zmien haslo" << endl << endl;
        cout << "Wcisnij litere stojaca przy danej opcji i zatwierdz Enter. Wcisnij kazdy inny znak, aby wrocic do menu glownego." << endl;
        cin >> wyborOpcji;
        cin.sync();
        for (size_t i = 0; i < uzytkownicy.size(); i++)
        {
            if (obecnyUzytkownik == uzytkownicy[i].idUzytkownika)
            {
                if (wyborOpcji == 'a')
                {
                    system("cls");
                    cout << "Wpisz nowy login:    " << endl;
                    cin >> nowyLogin;
                    cin.sync();
                    nazwaIstnieje = sprawdzCzyLoginLubHasloIstnieja(uzytkownicy, nowyLogin, noweHaslo);
                    if (!nazwaIstnieje)
                    {
                        uzytkownicy[i].login = nowyLogin;
                        aktualizujListeUzytkownikow(uzytkownicy);
                        system("cls");
                        cout << "Pomyslnie zmieniono login. Przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                    }
                    else
                    {
                        cout << "Login juz istnieje! Przekierowanie do menu glownego" << endl;
                        Sleep(2000);
                    }
                }
                if (wyborOpcji == 'b')
                {
                    system("cls");
                    cout << "Wpisz nowe haslo:    " << endl;
                    cin >> noweHaslo;
                    cin.sync();
                    nazwaIstnieje = sprawdzCzyLoginLubHasloIstnieja(uzytkownicy, nowyLogin, noweHaslo);
                    if (!nazwaIstnieje)
                    {
                        uzytkownicy[i].haslo = noweHaslo;
                        aktualizujListeUzytkownikow(uzytkownicy);
                        system("cls");
                        cout << "Pomyslnie zmieniono haslo. Przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                    }
                    else
                    {
                        cout << "Haslo juz istnieje! Przekierowanie do menu glownego" << endl;
                        Sleep(2000);
                    }
                }
            }
        }
    }
}

void zamknijProgram()
{
    system("cls");
    cout << "Trwa zamykanie programu" << endl;
    Sleep(2000);
    exit(0);
}

int wczytajAdresatowZPliku(vector <Adresat> &adresaci, int obecnyUzytkownik)
{
    Adresat osoba;
    int numerLinii = 1, pozycja = 0, dlugoscLinii = 0, ostatnieID = 0;
    string linia = "", slowo = "";
    string daneOsoby[7];
    fstream plik;

    plik.open("Adresaci.txt", ios::in);
    if (plik.good())
    {
        while(getline(plik, linia))
        {
            dlugoscLinii = linia.length();
            if (dlugoscLinii != 0)
            {
                for (int i = 0; i < dlugoscLinii; i++)
                {
                    if (linia[i] == '|')
                    {
                        slowo = "";
                        pozycja++;
                    }
                    else
                    {
                        slowo += linia[i];
                        daneOsoby[pozycja] = slowo;
                    }
                }
                if (stoi(daneOsoby[1]) == obecnyUzytkownik)
                {
                    osoba.id = stoi(daneOsoby[0]);
                    osoba.imie = daneOsoby[2];
                    osoba.nazwisko = daneOsoby[3];
                    osoba.nrTel = daneOsoby[4];
                    osoba.email = daneOsoby[5];
                    osoba.adres = daneOsoby[6];
                    adresaci.push_back(osoba);
                }
                numerLinii++;
                pozycja = 0;
            }
        }
        ostatnieID = stoi(daneOsoby[0]);
    }
    plik.close();
    return ostatnieID;
}

char wyswietlWszystkichAdresatow(vector <Adresat> osoby)
{
    Adresat osoba;
    system("cls");
    cout << "Nacisnij dowolny klawisz, aby wrocic do menu glowengo." << endl << endl << endl;
    for (Adresat osoba : osoby)
    {
        cout << "ID:             " << osoba.id << endl;
        cout << "Imie:           " << osoba.imie << endl;
        cout << "Nazwisko:       " << osoba.nazwisko << endl;
        cout << "Nr telefonu:    " << osoba.nrTel << endl;
        cout << "Email:          " << osoba.email << endl;
        cout << "Adres:          " << osoba.adres << endl << endl;
    }
    system("pause");
    return '0';
}

bool wyszukajImiona(vector <Adresat> osoby, string wpisaneImie)
{
    bool czyZnaleziono = false;
    for (Adresat osoba : osoby)
    {
        if (wpisaneImie == osoba.imie)
        {
            czyZnaleziono = true;
        }
    }
    return czyZnaleziono;
}

char wyswietlAdresatowPoImieniu(vector <Adresat> osoby)
{
    char wyborOgolny;
    string szukaneImie = "";
    bool znaleziono;
    system("cls");
    cout << "Wprowadz imie adresata, ktorego chcesz znalezc." << endl;
    szukaneImie = wczytajLinie();
    system("cls");
    znaleziono = wyszukajImiona(osoby, szukaneImie);
    if (znaleziono)
    {
        for (Adresat osoba : osoby)
        {
            if (szukaneImie == osoba.imie )
            {
                cout << osoba.id << endl;
                cout << osoba.imie << endl;
                cout << osoba.nazwisko << endl;
                cout << osoba.nrTel << endl;
                cout << osoba.email << endl;
                cout << osoba.adres << endl << endl;
            }
        }
        cout << "Wcisnij dowolny przycisk, aby wrocic do menu glownego." << endl;
        system("pause");
        wyborOgolny = '0';
    }
    else
    {
        cout << "Nie znaleziono adresatow o imieniu " << szukaneImie << endl;
        Sleep(2000);
        wyborOgolny = '2';
    }

    return wyborOgolny;
}


bool wyszukajNazwiska(vector <Adresat> osoby, string wpisaneNazwisko)
{
    bool czyZnaleziono = false;
    for (Adresat osoba : osoby)
    {
        if (wpisaneNazwisko == osoba.nazwisko)
        {
            czyZnaleziono = true;
        }
    }
    return czyZnaleziono;
}

char wyswietlAdresatowPoNazwisku(vector <Adresat> osoby)
{
    char wyborOgolny;
    string szukaneNazwisko = "";
    bool znaleziono;

    system("cls");
    cout << "Wprowadz nazwisko adresata, ktorego chcesz znalezc." << endl;
    szukaneNazwisko = wczytajLinie();
    system("cls");
    znaleziono = wyszukajNazwiska(osoby, szukaneNazwisko);
    if (znaleziono)
    {
        for (Adresat osoba : osoby)
        {
            if (szukaneNazwisko == osoba.nazwisko)
            {
                cout << osoba.id << endl;
                cout << osoba.imie << endl;
                cout << osoba.nazwisko << endl;
                cout << osoba.nrTel << endl;
                cout << osoba.email << endl;
                cout << osoba.adres << endl << endl;
            }
        }
        cout << "Wcisnij dowolny przycisk, aby wrocic do menu glownego." << endl;
        system("pause");
        wyborOgolny = '0';
    }
    else
    {
        cout << "Nie znaleziono adresatow o nazwisku " << szukaneNazwisko << endl;
        Sleep(2000);
        wyborOgolny = '2';
    }
    return wyborOgolny;
}

int dodajAdresata(vector <Adresat> &adresaci, int ostatniIdentyfikator, int zalogowaneID)
{
    Adresat osoba;
    fstream plik;
    system("cls");

    osoba.id = ostatniIdentyfikator + 1;

    cout << "Wpisz imie adresata:   ";
    osoba.imie = wczytajLinie();
    cout << "Wpisz nazwisko adresata:   ";
    osoba.nazwisko = wczytajLinie();
    cout << "Wpisz numer telefonu adresata:   ";
    osoba.nrTel = wczytajLinie();
    cout << "Wpisz email adresata:   ";
    osoba.email = wczytajLinie();
    cout << "Wpisz adres zamieszkania adresata:   ";
    osoba.adres = wczytajLinie();
    adresaci.push_back(osoba);

    plik.open("Adresaci.txt", ios::out | ios::app);
    plik << osoba.id << '|' << zalogowaneID << '|' << osoba.imie << '|' << osoba.nazwisko << '|' << osoba.nrTel << '|' << osoba.email << '|' << osoba.adres << '|' << endl;
    plik.close();

    system("cls");
    cout << "Dodales adresata do Twojej ksiazki adresowej! Zaraz zostaniesz przeniesiony do menu glownego." << endl;
    Sleep(2000);
    return osoba.id;
}
void operacjeNaPlikachPodczasUsuwaniaAdresata(vector <Adresat> &adresaci, int aktualnyUzytkownik, int idAdresataUsunietego)
{
    fstream plik, plikTymczasowy;
    int numerLinii = 1, dlugoscLinii = 0;
    string linia = "";
    plikTymczasowy.open("Adresaci_Tymczasowi.txt", ios::out);
    plik.open("Adresaci.txt", ios::in);
    if (plik.good() && plikTymczasowy.good())
    {
        while(getline(plik, linia))
        {
            dlugoscLinii = linia.length();
            if (idAdresataUsunietego != stoi(linia) && dlugoscLinii != 0)
            {
                plikTymczasowy << linia << endl;
                numerLinii++;
            }
        }
    }
    plikTymczasowy.close();
    plik.close();
}

void operacjeNaPlikachPodczasEdytowaniaAdresata(vector <Adresat> &adresaci, int aktualnyUzytkownik, int idAdresataZmienionego)
{
    fstream plik, plikTymczasowy;
    int numerLinii = 1, dlugoscLinii = 0;
    string linia = "";
    plikTymczasowy.open("Adresaci_Tymczasowi.txt", ios::out);
    plik.open("Adresaci.txt", ios::in);
    if (plik.good() && plikTymczasowy.good())
    {
        while(getline(plik, linia))
        {
            dlugoscLinii = linia.length();
            if (idAdresataZmienionego != stoi(linia) && dlugoscLinii != 0)
            {
                plikTymczasowy << linia << endl;
                numerLinii++;
            }
            else
            {
                for (size_t i = 0; i < adresaci.size(); i++)
                {
                    if (idAdresataZmienionego == adresaci[i].id)
                    {
                        plikTymczasowy << adresaci[i].id << '|' << aktualnyUzytkownik << '|' << adresaci[i].imie << '|' << adresaci[i].nazwisko << '|'
                        << adresaci[i].nrTel << '|' << adresaci[i].email << '|' << adresaci[i].adres << '|' << endl;
                    }
                }
            }
        }
    }
    plikTymczasowy.close();
    plik.close();
}

void uaktualnijPlikiZAdresatami()
{
    remove("Adresaci.txt");
    rename("Adresaci_Tymczasowi.txt", "Adresaci.txt");
}

char usunAdresata(vector <Adresat> &adresaci, int obecnyUzytkownik)
{
    int identyfikator = 1;
    char potwierdzenie;
    bool znalezionoID = false;

    while(identyfikator != 0)
    {
        system("cls");
        cout << "Wprowadz numer ID osoby, ktora chcesz usunac lub wcisnij 0, aby wrocic do menu glownego. Zatwierdz klawiszem Enter." << endl;
        cin >> identyfikator; cin.sync();
        if (identyfikator == 0) {;}
        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr -> id == identyfikator)
            {
                znalezionoID = true;
                cout << "Czy jestes pewien, ze chcesz usunac adresata?" << endl;
                cout << "Aby potwierdzic wcisnij t." << endl << "Aby anulowac i wybrac ponownie wcisnij inny dowolny znak" << endl;
                cin >> potwierdzenie; cin.sync();
                if (potwierdzenie == 't')
                {
                    adresaci.erase(itr);
                    system("cls");
                    cout << "Usunieto adresata. Nastapi przekierowanie do menu glownego." << endl;
                    operacjeNaPlikachPodczasUsuwaniaAdresata(adresaci, obecnyUzytkownik, identyfikator);
                    Sleep(2000); identyfikator = 0;
                    if (itr == adresaci.end())
                    {
                        break;
                    }
                }
            }
        }
        if (!znalezionoID)
        {
            if (identyfikator != 0)
            {
                system("cls");
                cout << "Zaden adresat nie ma takiego ID. Wybierz ponownie." << endl;
                Sleep(2000);
            }
        }
    }
    return '0';
}

char edytujAdresata(vector <Adresat> &adresaci, int aktualnyUzytkownik)
{
    char wyborOpcji;
    int wyborAdresataID = 1;
    bool znalezionoID = false;
    string noweDane = "";

    cout << "Wpisz numer ID osoby do edycji lub 0, aby wrocic do menu zarzadzania i zatwierdz klawiszem Enter." << endl << endl;
    cin >> wyborAdresataID; cin.sync();
    while (wyborAdresataID != 0)
    {
        for (size_t i = 0; i < adresaci.size(); i++)
        {
            if (adresaci[i].id == wyborAdresataID)
            {
                znalezionoID = true;
                while(wyborOpcji != '6')
                {
                    system("cls");
                    cout << "Wybierz jaka dana chcesz edytowac: " << endl;
                    cout << "1. Edytuj imie adresata" << endl;
                    cout << "2. Edytuj nazwisko adresata" << endl;
                    cout << "3. Edytuj numer telefonu adresata" << endl;
                    cout << "4. Edytuj email adresata" << endl;
                    cout << "5. Edytuj adres adresata" << endl;
                    cout << "6. Anuluj i wroc do menu glownego." << endl << endl;
                    cout << "Wcisnij cyfre stojaca przy danej opcji i zatwierdz klawiszem Enter." << endl;
                    cin >> wyborOpcji; cin.sync();
                    system("cls");
                    switch(wyborOpcji)
                    {
                    case '1':
                        cout << "Wpisz nowe imie adresata:   " << endl;
                        noweDane = wczytajLinie();
                        adresaci[i].imie = noweDane;
                        system("cls");
                        cout <<  "Zmieniono imie adresata. Nastapi przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                        operacjeNaPlikachPodczasEdytowaniaAdresata(adresaci, aktualnyUzytkownik, wyborAdresataID);
                        wyborOpcji = '6'; wyborAdresataID = 0;
                        break;
                    case '2':
                        cout << "Wpisz nowe nazwisko adresata:   " << endl;
                        noweDane = wczytajLinie();
                        adresaci[i].nazwisko = noweDane;
                        system("cls");
                        cout <<  "Zmieniono nazwisko adresata. Nastapi przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                        operacjeNaPlikachPodczasEdytowaniaAdresata(adresaci, aktualnyUzytkownik, wyborAdresataID);
                        wyborOpcji = '6'; wyborAdresataID = 0;
                        break;
                    case '3':
                        cout << "Wpisz nowy numer telefonu adresata:   " << endl;
                        noweDane = wczytajLinie();
                        adresaci[i].nrTel = noweDane;
                        system("cls");
                        cout <<  "Zmieniono numer telefonu adresata. Nastapi przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                        operacjeNaPlikachPodczasEdytowaniaAdresata(adresaci, aktualnyUzytkownik, wyborAdresataID);
                        wyborOpcji = '6'; wyborAdresataID = 0;
                        break;
                    case '4':
                        cout << "Wpisz nowy email adresata:   " << endl;
                        noweDane = wczytajLinie();
                        adresaci[i].email = noweDane;
                        system("cls");
                        cout <<  "Zmieniono email adresata. Nastapi przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                        operacjeNaPlikachPodczasEdytowaniaAdresata(adresaci, aktualnyUzytkownik, wyborAdresataID);
                        wyborOpcji = '6'; wyborAdresataID = 0;
                        break;
                    case '5':
                        cout << "Wpisz adres zamieszkania adresata:   " << endl;
                        noweDane = wczytajLinie();
                        adresaci[i].adres = noweDane;
                        system("cls");
                        cout <<  "Zmieniono adres adresata. Nastapi przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                        operacjeNaPlikachPodczasEdytowaniaAdresata(adresaci, aktualnyUzytkownik, wyborAdresataID);
                        wyborOpcji = '6'; wyborAdresataID = 0;
                        break;
                    case '6':
                        wyborAdresataID = 0;
                        break;
                    default:
                        cout << "Bledny wybor. Wybierz ponownie." << endl;
                        Sleep(1500); system("cls");
                    }
                }
            }
        }
        if (znalezionoID == false)
        {
            system("cls");
            cout << "Nie znaleziono osoby z takim ID. Nastapi przekiwrowanie do menu glownego." << endl;
            Sleep(2000);
            wyborAdresataID = 0;
        }
    }
    return '0';
}

void zarzadzajAdresatami(vector<Uzytkownik> uzytkownicy, int zalogowanyUzytkownik)
{
    char wybor = '0', wyborWOpcjiDrugiej = '0';
    int koncoweID = 0;
    vector <Adresat> adresaci;

    koncoweID = wczytajAdresatowZPliku(adresaci, zalogowanyUzytkownik);

    while (zalogowanyUzytkownik != 0)
    {
        system("cls");
        switch(wybor)
        {
        case '0':
        {
            cout << "Menu zarzadzania adresatami:" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj adresata" << endl;
            cout << "3. Wyswietl wszystkich adresatow" << endl;
            cout << "4. Edytuj adresata" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Wyloguj sie" << endl;
            cout << "7. Zamknij program" << endl << endl;
            cout << "Wcisnij cyfre stojaca przy danej opcji, aby wybrac. Wcisnij Enter, aby zatwierdzac wprowadzane dane." << endl;
            cout << "UWAGA! Jesli wpiszesz wiecej niz jeden znak, pierwszy znak zostanie uznany za Twoj wybor!" << endl << endl;
            cin >> wybor; cin.sync(); break;
        }

        case'1':
            {
                system("cls");
                koncoweID = dodajAdresata(adresaci, koncoweID, zalogowanyUzytkownik);
                wybor = '0';
                break;
            }

        case '2':
        {
            system("cls");
            cout << "Wybierz znak stojacy przy opcji lub inny dowolny znak, aby wrocic do menu glownego i zatwierdz klawiszem Enter" << endl;
            cout << "a. Wyszukaj poprzez imie" << endl;
            cout << "b. Wyszukaj poprzez nazwisko" << endl << endl;
            cout << "UWAGA! Jesli wpiszesz wiecej niz jeden znak, pierwszy znak zostanie uznany za Twoj wybor!" << endl << endl;
            cin >> wyborWOpcjiDrugiej;
            cin.sync();
            if (wyborWOpcjiDrugiej == 'a')
            {
                wybor = wyswietlAdresatowPoImieniu(adresaci);
            }
            else if (wyborWOpcjiDrugiej == 'b')
            {
                wybor = wyswietlAdresatowPoNazwisku(adresaci);
            }
            else
            {
                wybor = '0';
            }
            break;
        }

        case '3':
        {
            wybor = wyswietlWszystkichAdresatow(adresaci); break;
        }

        case '4':
        {
            system("cls");
            wybor = edytujAdresata(adresaci, zalogowanyUzytkownik);
            uaktualnijPlikiZAdresatami();
            break;
        }

        case '5':
        {
            wybor = usunAdresata(adresaci, zalogowanyUzytkownik);
            uaktualnijPlikiZAdresatami();
            adresaci.clear();
            koncoweID = wczytajAdresatowZPliku(adresaci, zalogowanyUzytkownik);
            break;
        }

        case '6':
        {
            zalogowanyUzytkownik = 0; break;
        }

        case '7':
        {
            zamknijProgram(); break;
        }

        default:
        {
            system("cls");
            cout << "Nie ma takiej opcji! Wybierz inny numer!" << endl << endl;
            Sleep(2000); wybor = '0';
            break;
        }
        }
    }
}


int main()
{
    char wyborGlowny = '0';
    int aktualnyUzytkownik = 0;
    vector<Uzytkownik> uzytkownicy;

    wczytajUzytkownikow(uzytkownicy);


    while(true)
    {
        system("cls");
        cout << "Wybierz numer stojacy przy danej opcji i potwierdz Enter." << endl << endl;
        cout << "1. Zaloguj sie" << endl << "2. Zarejestruj sie" << endl << "3. Edytuj login lub haslo" << endl << "4. Zamknij program" << endl << endl;
        cout << "UWAGA! Jesli wpiszesz wiecej niz jeden znak, pierwszy znak zostanie uznany za Twoj wybor!" << endl;
        cin >> wyborGlowny; cin.sync();

        switch(wyborGlowny)
        {
        case '1':
            aktualnyUzytkownik  = zalogujUzytkownika(uzytkownicy);
            if (aktualnyUzytkownik != 0)
            {
                zarzadzajAdresatami(uzytkownicy, aktualnyUzytkownik);
            }
            break;

        case '2': zarejestrujUzytkownika(uzytkownicy); break;
        case '3': edytujUzytkownika(uzytkownicy); break;
        case '4': zamknijProgram();
        default:
            system("cls");
            cout << "Nie ma takiej opcji, wybierz ponownie" << endl;
            Sleep(2000);
        }
    }
    return 0;
}

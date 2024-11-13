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

    while (uzytkownikIstnieje)
    {
        system("cls");
        if (uzytkownicy.empty()) {osoba.idUzytkownika = 1;}
        else {osoba.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;}
        cout << "Utworz login" << endl;
        osoba.login = wczytajLinie();
        cout << "Utworz haslo" << endl;
        osoba.haslo = wczytajLinie();
        uzytkownikIstnieje = sprawdzCzyLoginLubHasloIstnieja(uzytkownicy, osoba.login, osoba.haslo);
        if (uzytkownikIstnieje)
        {
            cout << "Podane haslo lub login sa juz zajete, wpisz inne dane!" << endl; Sleep(2000);
        }
    }
    uzytkownicy.push_back(osoba);

    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    plik << osoba.idUzytkownika << '|' << osoba.login << '|' << osoba.haslo << '|' << endl;
    plik.close();

    system("cls"); cout << "Rejestracja pomyslna! Przekierowuje do menu glownego." << endl; Sleep(2000);
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
            cout << "Wcisnij cyfre stojaca przy danej opcji, aby wybrac. Wcisnij Enter, aby zatwierdzac wprowadzane dane." << endl << endl << endl;
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
            cout << "b. Wyszukaj poprzez nazwisko" << endl;
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
/*
        case '4':
        {
            system("cls");
            edytujAdresata(adresaci);
            wybor = '0';
            break;
        }

        case '5':
        {
            system("cls");
            usunAdresata(adresaci);
            wybor = '0';
            break;
        }
*/
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
        cout << "Wybierz numer stojacy przy danej opcji i potwierdz Enter" << endl << endl;
        cout << "1. Zaloguj sie" << endl << "2. Zarejestruj sie" << endl << "3. Zamknij program" << endl;
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
        case '3': zamknijProgram();
        default:
            system("cls");
            cout << "Nie ma takiej opcji, wybierz ponownie" << endl;
            Sleep(2000);
        }
    }
    return 0;
}

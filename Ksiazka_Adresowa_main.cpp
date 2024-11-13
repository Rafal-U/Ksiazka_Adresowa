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
        for (Uzytkownik osoba : uzytkownicy)
        {
            if (osoba.login == login && osoba.haslo == haslo)
            {
                identyfikator = osoba.idUzytkownika;
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
            aktualnyUzytkownik  = zalogujUzytkownika(uzytkownicy); break;


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

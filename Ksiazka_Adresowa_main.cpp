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

struct Adresat
{
    int id = 0;
    string imie;
    string nazwisko;
    string nrTel;
    string email;
    string adres;
};


void wczytajLubStworzZapisanyPlik(vector <Adresat> &adresaci)
{
    Adresat osoba;
    int numerLinii = 1, pozycja = 0, dlugoscLinii = 0;
    string linia = "", slowo = "";
    string daneOsoby[6];
    fstream plik;

    plik.open("Ksiazka Adresowa.txt", ios::in);
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
                osoba.id = stoi(daneOsoby[0]);
                osoba.imie = daneOsoby[1];
                osoba.nazwisko = daneOsoby[2];
                osoba.nrTel = daneOsoby[3];
                osoba.email = daneOsoby[4];
                osoba.adres = daneOsoby[5];
                adresaci.push_back(osoba);
                numerLinii++;
                pozycja = 0;
            }
        }
    }
    plik.close();
}


void aktualizujPlik(vector <Adresat> &adresaci)
{
    fstream plik;
    Adresat osoba;
    plik.open("Ksiazka Adresowa.txt", ios::out);
    for (Adresat osoba : adresaci)
    {
        plik << osoba.id << '|' << osoba.imie << '|' << osoba.nazwisko << '|' << osoba.nrTel << '|' << osoba.email << '|' << osoba.adres << '|' << endl;
    }
    plik.close();
}


void dodajAdresata(vector <Adresat> &adresaci)
{
    Adresat osoba;
    fstream plik;

    if (adresaci.empty())
    {
        osoba.id = 1;
    }
    else
    {
        osoba.id = adresaci.back().id + 1;
    }

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

    plik.open("Ksiazka Adresowa.txt", ios::out | ios::app);
    plik << osoba.id << '|' << osoba.imie << '|' << osoba.nazwisko << '|' << osoba.nrTel << '|' << osoba.email << '|' << osoba.adres << '|' << endl;
    plik.close();

    system("cls");
    cout << "Dodales adresata do Twojej ksiazki adresowej! Zaraz zostaniesz przeniesiony do menu glownego." << endl;
    Sleep(2000);
}


void wyswietlWszystkichAdresatow(vector <Adresat> osoby)
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


void edytujAdresata(vector <Adresat> &adresaci)
{
    char wyborOpcji;
    int wyborAdresataID = 1;
    bool znalezionoID = false;
    string noweDane = "";

    cout << "Wpisz numer ID osoby do edycji lub 0, aby wrocic do menu glownego i zatwierdz klawiszem Enter." << endl << endl;
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
                        aktualizujPlik(adresaci);
                        wyborOpcji = '6'; wyborAdresataID = 0;
                        break;
                    case '2':
                        cout << "Wpisz nowe nazwisko adresata:   " << endl;
                        noweDane = wczytajLinie();
                        adresaci[i].nazwisko = noweDane;
                        system("cls");
                        cout <<  "Zmieniono nazwisko adresata. Nastapi przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                        aktualizujPlik(adresaci);
                        wyborOpcji = '6'; wyborAdresataID = 0;
                        break;
                    case '3':
                        cout << "Wpisz nowy numer telefonu adresata:   " << endl;
                        noweDane = wczytajLinie();
                        adresaci[i].nrTel = noweDane;
                        system("cls");
                        cout <<  "Zmieniono numer telefonu adresata. Nastapi przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                        aktualizujPlik(adresaci);
                        wyborOpcji = '6'; wyborAdresataID = 0;
                        break;
                    case '4':
                        cout << "Wpisz nowy email adresata:   " << endl;
                        noweDane = wczytajLinie();
                        adresaci[i].email = noweDane;
                        system("cls");
                        cout <<  "Zmieniono email adresata. Nastapi przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                        aktualizujPlik(adresaci);
                        wyborOpcji = '6'; wyborAdresataID = 0;
                        break;
                    case '5':
                        cout << "Wpisz adres zamieszkania adresata:   " << endl;
                        noweDane = wczytajLinie();
                        adresaci[i].adres = noweDane;
                        system("cls");
                        cout <<  "Zmieniono adres adresata. Nastapi przekierowanie do menu glownego." << endl;
                        Sleep(2000);
                        aktualizujPlik(adresaci);
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
}


void usunAdresata(vector <Adresat> &adresaci)
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
                    aktualizujPlik(adresaci);
                    Sleep(2000); identyfikator = 0;
                    if (itr == adresaci.end())
                    {
                        break;
                    }
                }
            }
        }
        if (znalezionoID == false)
        {
            if (identyfikator != 0)
            {
                system("cls");
                cout << "Zaden adresat nie ma takiego ID. Wybierz ponownie." << endl;
                Sleep(2000);
            }
        }
    }
}


int main()
{
    char wybor = '0', wyborWOpcjiDrugiej = '0';
    vector <Adresat> adresaci;

    wczytajLubStworzZapisanyPlik(adresaci);

    while (1)
    {
        if (wybor == '0')
        {
            system("cls");
            cout << "Menu glowne:" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj adresata" << endl;
            cout << "3. Wyswietl wszystkich adresatow" << endl;
            cout << "4. Edytuj adresata" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "9. Zamknij program" << endl << endl;
            cout << "Wcisnij cyfre stojaca przy danej opcji, aby wybrac. Wcisnij Enter, aby zatwierdzac wprowadzane dane." << endl << endl << endl;
            cin >> wybor; cin.sync();
        }

        else if (wybor == '1')
        {
            system("cls");
            dodajAdresata(adresaci);
            wybor = '0';
        }

        else if (wybor == '2')
        {
            system("cls");
            cout << "Wybierz znak stojacy przy opcji lub inny dowolny znak, aby wrocic do menu glownego i zatwierdz klawiszem Enter" << endl;
            cout << "a. Wyszukaj poprzez imie" << endl;
            cout << "b. Wyszukaj poprzez nazwisko" << endl;
            cin >> wyborWOpcjiDrugiej; cin.sync();
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
        }

        else if (wybor == '3')
        {
            wyswietlWszystkichAdresatow(adresaci);
            system("pause");
            wybor = '0';
        }

        else if (wybor == '4')
        {
            system("cls");
            edytujAdresata(adresaci);
            wybor = '0';
        }

        else if (wybor == '5')
        {
            system("cls");
            usunAdresata(adresaci);
            wybor = '0';
        }

        else if (wybor == '9')
        {
            system("cls");
            cout << "Trwa zamykanie programu" << endl;
            Sleep(2000);
            exit(0);
        }

        else
        {
            system("cls");
            cout << "Nie ma takiej opcji! Wybierz inny numer!" << endl << endl;
            Sleep(2000);
            wybor = '0';
        }
    }

    return 0;
}

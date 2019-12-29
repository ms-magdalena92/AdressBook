#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <iterator>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, nrTel, adres, email;
};
int odczytajKontaktyZPlikuTekstowego (vector<Kontakt> &kontakty);
int dodajKontakt (vector<Kontakt> &kontakty, int &iloscKontaktow);
void wyszukajPoImieniu(vector<Kontakt> kontakty, int iloscKontaktow);
void wyszukajPoNazwisku(vector<Kontakt> kontakty, int iloscKontaktow);
void wyswietlWszystkieKontakty(vector<Kontakt> kontakty, int iloscKontaktow);
void usunKontakt(vector<Kontakt> &kontakty, int &iloscKontaktow);
void edytujKontakt(vector<Kontakt> &kontakty, int iloscKontaktow);

int main()
{
    vector<Kontakt> kontakty;
    char wybor;

    int iloscKontaktow = odczytajKontaktyZPlikuTekstowego(kontakty);

    while (1)
    {
        system ("cls");
        cout << "KSIAZKA ADRESOWA" << endl << endl;
        cout << "1. Dodaj nowy kontakt" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie kontakty" << endl;
        cout << "5. Usun kontakt" << endl;
        cout << "6. Edytuj kontakt" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        //cout << "Ilosc kontaktow: " << iloscKontaktow << " " << "Ilosc el wektora: " << kontakty.size() <<  endl;
        cin >> wybor;

        if (!(wybor == '1' || wybor == '9') &&  iloscKontaktow==0)
        {
            cout << endl << "Ksiazka adresowa jest pusta! Dodaj kontakty." << endl;
            Sleep (3000);
        }
        else if (wybor == '1')
        {
            system ("cls");
            dodajKontakt(kontakty, iloscKontaktow);
        }

        else if (wybor == '2')
        {
            system ("cls");
            wyszukajPoImieniu(kontakty, iloscKontaktow);
        }

        else if (wybor == '3')
        {
            system ("cls");
            wyszukajPoNazwisku(kontakty, iloscKontaktow);
        }
        else if (wybor== '4')
        {
            system ("cls");
            wyswietlWszystkieKontakty(kontakty, iloscKontaktow);
        }
        else if (wybor== '5')
        {
            system ("cls");
            usunKontakt(kontakty, iloscKontaktow);
        }
        else if (wybor == '6')
        {
            system ("cls");
            edytujKontakt(kontakty, iloscKontaktow);
        }
        else if (wybor == '9')
            exit(0);
    }
    return 0;
}

int odczytajKontaktyZPlikuTekstowego (vector<Kontakt> &kontakty)
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if (plik.good() == false)
    {
        cout << "Ksiazka adresowa jest pusta!" << endl << "Dodaj plik \"ksiazkaAdresowa.txt\" lub dodaj nowe kontakty."<<endl;
        Sleep (4000);
        return 0;
    }
    string linia;
    int iloscKontaktow=0;

    while (!plik.eof())
    {
        getline(plik,linia,'|');
        if (linia != "")
        {
            kontakty.push_back(Kontakt());
            kontakty[iloscKontaktow].id = atoi(linia.c_str());
            getline(plik,linia,'|');
            kontakty[iloscKontaktow].imie = linia;
            getline(plik,linia,'|');
            kontakty[iloscKontaktow].nazwisko = linia;
            getline(plik,linia,'|');
            kontakty[iloscKontaktow].nrTel = linia;
            getline(plik,linia,'|');
            kontakty[iloscKontaktow].adres = linia;
            getline(plik,linia);
            kontakty[iloscKontaktow].email = linia;
            iloscKontaktow++;
        }
    }
    plik.close();
    return iloscKontaktow;
}

void dopiszKontaktDoPlikuTxt (vector<Kontakt> &kontakty, int iloscKontaktow)
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    if (iloscKontaktow == 0)
    {
        plik << kontakty[iloscKontaktow].id << "|";
    }
    else
        plik << endl << kontakty[iloscKontaktow].id << "|";
    plik << kontakty[iloscKontaktow].imie << "|";
    plik << kontakty[iloscKontaktow].nazwisko << "|";
    plik << kontakty[iloscKontaktow].nrTel << "|";
    plik << kontakty[iloscKontaktow].adres << "|";
    plik << kontakty[iloscKontaktow].email;
    plik.close();
}

void nadpiszPlikTxt (vector<Kontakt> &kontakty, int iloscKontaktow)
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out);
    for (int i = 0; i < iloscKontaktow; i++)
    {
        if (i == 0)
        {
            plik << kontakty[i].id << "|";
        }
        else
        {
            plik << endl << kontakty[i].id << "|";
        }
        plik << kontakty[i].imie << "|";
        plik << kontakty[i].nazwisko << "|";
        plik << kontakty[i].nrTel << "|";
        plik << kontakty[i].adres << "|";
        plik << kontakty[i].email;
    }
    plik.close();
}

int dodajKontakt (vector<Kontakt> &kontakty, int &iloscKontaktow)
{
    string imie, nazwisko, nrTel, adres, email;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj nr telefonu: ";
    cin.sync();
    getline(cin,nrTel);
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,adres);
    cout << "Podaj adres e-mail: ";
    cin >> email;

    kontakty.push_back(Kontakt());
    if (iloscKontaktow == 0)
    {
        kontakty[iloscKontaktow].id = 1;
    }
    else
    {
        kontakty[iloscKontaktow].id=kontakty[iloscKontaktow-1].id+1;
    }
    kontakty[iloscKontaktow].imie=imie;
    kontakty[iloscKontaktow].nazwisko=nazwisko;
    kontakty[iloscKontaktow].nrTel=nrTel;
    kontakty[iloscKontaktow].adres=adres;
    kontakty[iloscKontaktow].email=email;

    dopiszKontaktDoPlikuTxt(kontakty,iloscKontaktow);
    iloscKontaktow++;

    cout << endl << "Kontakt zostal dodany do ksiazki adresowej." << endl;
    Sleep(2000);
    return iloscKontaktow;
}

void wyswietlKontakt (vector<Kontakt> kontakty, vector<Kontakt>::iterator itr)
{
    cout << itr -> id << endl;
    cout << itr -> imie << endl;
    cout << itr -> nazwisko << endl;
    cout << itr -> nrTel << endl;
    cout << itr -> adres << endl;
    cout << itr -> email << endl << endl;
}

void wyszukajPoImieniu(vector<Kontakt> kontakty, int iloscKontaktow)
{
    string imie;
    cout << "Podaj imie wyszukiwanego kontaktu: ";
    cin >> imie;
    int iloscBrakuWystapienKontaktu=0;
    for (vector<Kontakt>::iterator itr = kontakty.begin(); itr != kontakty.end(); itr++)
    {
        if (itr -> imie == imie)
        {
            wyswietlKontakt(kontakty,itr);
        }
        else
        {
            iloscBrakuWystapienKontaktu++;
        }
    }
    if (iloscBrakuWystapienKontaktu == iloscKontaktow && iloscKontaktow != 0)
        cout << endl << "Nie ma takiego kontaktu!" << endl << endl;
    system ("pause");

}
void wyszukajPoNazwisku(vector<Kontakt> kontakty, int iloscKontaktow)
{
    string nazwisko;
    cout << "Podaj nazwisko wyszukiwanego kontaktu: ";
    cin >> nazwisko;

    int iloscBrakuWystapienKontaktu = 0;
    for (vector<Kontakt>::iterator itr = kontakty.begin(); itr != kontakty.end(); itr++)
    {
        if (itr -> nazwisko == nazwisko)
        {
            wyswietlKontakt(kontakty,itr);
        }
        else
        {
            iloscBrakuWystapienKontaktu++;
        }
    }
    if (iloscBrakuWystapienKontaktu == iloscKontaktow && iloscKontaktow != 0)
        cout << endl << "Nie ma takiego kontaktu!" << endl << endl;
    system ("pause");
}
void wyswietlWszystkieKontakty (vector<Kontakt> kontakty, int iloscKontaktow)
{
    vector<Kontakt>::iterator itr = kontakty.begin();
    while (itr != kontakty.end())
    {
        wyswietlKontakt(kontakty,itr);
        itr++;
    }
    system ("pause");
}

void usunKontakt(vector<Kontakt> &kontakty, int &iloscKontaktow)
{
    int id;
    int iloscBrakuWystapienKontaktu = 0;
    cout << "Wprowadz ID kontaktu do usuniecia: ";
    cin >> id;
    for (vector<Kontakt>::iterator itr = kontakty.begin(); itr < kontakty.end(); itr++)
    {
        if (itr -> id == id)
        {
            cout << "Kontakt do usuniecia: " << endl;
            wyswietlKontakt(kontakty,itr);
            cout << "Czy usunac kontakt? T/N" << endl;
            if (getch() == 't' || getch() == 'T')
            {
                kontakty.erase(itr);
                iloscKontaktow--;
                nadpiszPlikTxt (kontakty,iloscKontaktow);
                cout << endl << "Kontakt zostal usuniety" << endl;
                Sleep(3000);
            }
            else if ((getch() == 'n' || getch() == 'N'))
                break;
        }
        else
        {
            iloscBrakuWystapienKontaktu++;
        }
    }
    if (iloscBrakuWystapienKontaktu == iloscKontaktow && iloscKontaktow != 0)
    {
        cout << endl << "Nie ma kontaktu o takim ID" << endl << endl;
        Sleep (2000);
    }
}

void edytujKontakt(vector<Kontakt> &kontakty, int iloscKontaktow)
{
    int id;
    int iloscBrakuWystapienKontaktu = 0;
    char wybor;
    string noweDane;
    cout << "Wprowadz ID kontaktu do edycji: ";
    cin >> id;

    for (vector<Kontakt>::iterator itr = kontakty.begin(); itr != kontakty.end(); itr++)
    {
        if (itr->id == id)
        {
            while (1)
            {
                system ("cls");
                cout << "Kontakt do edycji: " << endl;
                wyswietlKontakt(kontakty,itr);
                cout << endl << "Wybierz dane do edycji: " << endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Nr telefonu" << endl;
                cout << "4. Adres" << endl;
                cout << "5. Email" << endl;
                cout << "6. Powrot do menu" << endl;
                wybor = getch();
                cin.sync();

                switch (wybor)
                {
                case '1':
                {
                    cout << "Wprowadz nowe dane: ";
                    cin >> noweDane;
                    itr -> imie = noweDane;
                    nadpiszPlikTxt(kontakty,iloscKontaktow);
                    cout << "Dane zostaly zaktualizowane." << endl;
                    Sleep (1000);
                    continue;
                }
                case '2':
                {
                    cout << "Wprowadz nowe dane: ";
                    getline(cin,noweDane);
                    itr -> nazwisko = noweDane;
                    nadpiszPlikTxt(kontakty,iloscKontaktow);
                    cout << "Dane zostaly zaktualizowane." << endl;
                    Sleep (1000);
                    continue;
                }
                case '3':
                {
                    cout << "Wprowadz nowe dane: ";
                    getline(cin,noweDane);
                    itr -> nrTel = noweDane;
                    nadpiszPlikTxt(kontakty,iloscKontaktow);
                    cout << "Dane zostaly zaktualizowane." << endl;
                    Sleep (1000);
                    continue;
                }
                case '4':
                {
                    cout << "Wprowadz nowe dane: ";
                    getline(cin,noweDane);
                    itr -> adres = noweDane;
                    nadpiszPlikTxt(kontakty,iloscKontaktow);
                    cout << "Dane zostaly zaktualizowane." << endl;
                    Sleep (1000);
                    continue;
                }
                case '5':
                {
                    cout << "Wprowadz nowe dane: ";
                    getline(cin,noweDane);
                    itr -> email = noweDane;
                    nadpiszPlikTxt(kontakty,iloscKontaktow);
                    cout << "Dane zostaly zaktualizowane." << endl;
                    Sleep (1000);
                    continue;
                }
                case '6':
                {
                    break;
                }
                default:
                {
                    cout << "Wybrano niepoprawna opcje" << endl;
                    Sleep (1000);
                    continue;
                }
                }
                break;
            }
        }
        else
        {
            iloscBrakuWystapienKontaktu++;
        }
    }
    if(iloscBrakuWystapienKontaktu == iloscKontaktow && iloscKontaktow != 0)
    {
        cout << endl << "Nie ma kontaktu o takim ID" << endl << endl;
        Sleep (2000);
    }
}



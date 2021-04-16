#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;


struct Kontakt {
    int id;
    string imie,nazwisko,nr_telefonu,email,adres;

};

struct Uzytkownik {
    int idUzytkownika;
    string nazwa,haslo;
};

string pozyskajOstatniaLinie(ifstream& in) {
    string linia;
    while (in >> ws && getline(in, linia));
    return linia;
}

int szukajOstaniegoId() {
    ifstream plik("ksiazka_adresowa.txt");
    int id;

    char znak;
    if(plik) {
        string linia = pozyskajOstatniaLinie(plik);
        for(int i=0; i<=linia.size(); i++) {
            znak=linia[i];
            if(znak=='|')
                linia=linia.substr(0,i);
            id=atoi(linia.c_str());
            return id;

        }
    }

    else
        return 0;


    return 0;
}

void zapisDoPliku(vector<Kontakt>adresaci,int iloscKontaktow,int idZalogowanego) {
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::out | ios::app);

    plik << adresaci[iloscKontaktow].id << "|";
    plik << idZalogowanego << "|";
    plik <<  adresaci[iloscKontaktow].imie << "|";
    plik << adresaci[iloscKontaktow].nazwisko << "|";
    plik <<  adresaci[iloscKontaktow].nr_telefonu << "|";
    plik <<  adresaci[iloscKontaktow].adres << "|";
    plik << adresaci[iloscKontaktow].email << "|" << endl;

    plik.close();
}

int dodajKontakt(vector<Kontakt>&adresaci, int iloscKontaktow, int idZalogowanego) {
    system("cls");
    int id;
    string imie,nazwisko,nr_telefonu,adres,email;

    id=szukajOstaniegoId()+1;

    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin >> nr_telefonu;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,adres);
    cout << "Podaj adres e-mail: ";
    cin >> email;

    Kontakt tmp;
    tmp.imie=imie;
    tmp.nazwisko=nazwisko;
    tmp.nr_telefonu=nr_telefonu;
    tmp.adres=adres;
    tmp.email=email;
    tmp.id=id;

    adresaci.push_back(Kontakt(tmp));

    zapisDoPliku(adresaci,iloscKontaktow,idZalogowanego);

    cout << "Dodano kontakt" << endl;
    Sleep(1000);
    return adresaci.size();


}

void wyszukajPoImieniu(vector<Kontakt>adresaci) {
    system("cls");
    string imie;
    cout << "Podaj imie po ktorym chcesz wyszukiwac: ";
    cin >> imie;
    int licznik=0;

    for(vector<Kontakt>::iterator itr=adresaci.begin(); itr!=adresaci.end(); ++itr) {
        if((*itr).imie==imie) {
            cout << "Znaleziono kontakt: " << endl;
            cout << (*itr).imie << " " << (*itr).nazwisko << " " <<(*itr).nr_telefonu;
            cout << " " << (*itr).adres << " " << (*itr).email << endl;
            licznik++;

        }
    }
    if(licznik>0) {


        cout << "Nacisnij dowolny klawisz aby kontynuowac" << endl;
        getch();
        return;
    } else {


        cout << "Nie ma osoby o takim imieniu";
        Sleep(2000);
        return;
    }
}

void wyszukajPoNazwisku(vector<Kontakt>adresaci) {
    system("cls");
    string nazwisko;
    cout << "Podaj nazwisko po ktorym chcesz wyszukiwac: ";
    cin >> nazwisko;
    int licznik=0;

    for(vector<Kontakt>::iterator itr=adresaci.begin(); itr!=adresaci.end(); ++itr) {
        if((*itr).nazwisko==nazwisko) {
            cout << "Znaleziono kontakt: " << endl;
            cout << (*itr).imie << " " << (*itr).nazwisko << " " <<(*itr).nr_telefonu;
            cout << " " << (*itr).adres << " " << (*itr).email << endl;
            licznik++;
        }

    }
    if(licznik>0) {


        cout << "Nacisnij dowolny klawisz aby kontynuowac" << endl;
        getch();
        return;
    } else {


        cout << "Nie ma osoby o takim nazwisku";
        Sleep(2000);
        return;
    }
}

void wyswietlWszystkieKontakty(vector<Kontakt>adresaci) {
    system("cls");

    for(vector<Kontakt>::iterator itr=adresaci.begin(); itr!=adresaci.end(); ++itr) {
        cout << (*itr).id << " "<<(*itr).imie << " " << (*itr).nazwisko << " " <<(*itr).nr_telefonu;
        cout << " " << (*itr).adres << " " << (*itr).email << endl;
    }


    cout << endl << "Wyswietlono wszystkie kontakty" << endl;
    cout << "Nacisnij dowolny klawisz aby kontynuowac" << endl;
    getch();

}


int odczytZPliku(vector<Kontakt>&adresaci,int idZalogowanego) {
    fstream plik;
    string linia,bufor;
    int dlugoscLinijki,aktualnaPozycjaZnaku,idOdczytane;
    int poprzedniaPozycjaZnaku=0;
    int licznik=0;
    adresaci.clear();
    Kontakt tmp;

    plik.open("ksiazka_adresowa.txt",ios::in| ios::app);

    if(plik.good()==false)
        return 0;
    else {
        while(getline(plik,linia)) {
            dlugoscLinijki=linia.length();
            char znak;

            for(int i=0; i<=dlugoscLinijki; i++) {
                znak=linia[i];
                if(znak=='|') {
                    licznik++;
                    aktualnaPozycjaZnaku=i;
                    bufor = linia.substr(poprzedniaPozycjaZnaku,aktualnaPozycjaZnaku-poprzedniaPozycjaZnaku);
                    switch(licznik) {
                    case 1:
                        tmp.id=atoi(bufor.c_str());
                        break;
                    case 2:
                        idOdczytane=atoi(bufor.c_str());
                        break;
                    case 3:
                        tmp.imie=bufor;
                        break;
                    case 4:
                        tmp.nazwisko=bufor;
                        break;
                    case 5:
                        tmp.nr_telefonu=bufor;
                        break;
                    case 6:
                        tmp.adres=bufor;
                        break;
                    case 7:
                        tmp.email=bufor;
                        break;
                    }
                    poprzedniaPozycjaZnaku = i+1;
                }


            }
            if(idOdczytane==idZalogowanego)
                adresaci.push_back(Kontakt(tmp));

            licznik=0;
            poprzedniaPozycjaZnaku=0;
        }

    }

    plik.close();

    return adresaci.size();
}

string utworzLinie(vector<Kontakt>::iterator itr,int idZalogowanego) {
    string linia,idString;
    int id =(*itr).id;
    idString = to_string(id);
    linia = idString + "|" + to_string(idZalogowanego) + "|"+ (*itr).imie + "|" + (*itr).nazwisko + "|" + (*itr).nr_telefonu +"|" + (*itr).adres +"|"+ (*itr).email +"|";
    return linia;

}

void usunAdresata(vector<Kontakt>&adresaci,int idZalogowanego) {
    system("cls");
    string usuwanaLinia,linia;
    ifstream plik;
    ofstream tymczasowyPlik;
    char znak;
    int id;
    cout << "Podaj id adresata, ktorego chcesz usunac: ";
    cin >> id;

    for(vector<Kontakt>::iterator itr=adresaci.begin(); itr!=adresaci.end(); ++itr) {
        if((*itr).id==id) {
            cout << endl << "Potwierdz ze chcesz usunac adresata klawiszem t" << endl;
            cin >> znak;
            if(znak=='t') {
                usuwanaLinia=utworzLinie(itr,idZalogowanego);
                plik.open("ksiazka_adresowa.txt");
                tymczasowyPlik.open("Adresaci_tymczasowy");
                while(getline(plik,linia)) {
                    if(linia!=usuwanaLinia)
                        tymczasowyPlik << linia << endl;
                }

                tymczasowyPlik.close();
                plik.close();
                remove("ksiazka_adresowa.txt");
                rename("Adresaci_tymczasowy","ksiazka_adresowa.txt");
                adresaci.erase(itr);
                cout << endl << "Usunieto adresata";
                Sleep(1500);
                return;
            } else
                return;
        }
    }
    cout << "Nie ma osoby o takim ID";
    Sleep(1500);
}

void edycjaInformacji(vector<Kontakt>::iterator itr,string zmienianiaLinia,int wybor,int idZalogowanego) {
    ifstream plik;
    ofstream tymczasowyPlik;
    string linia,nowaLinia,zmienianaInformacja;
    switch(wybor) {
    case 1:
        cout << "Podaj nowe imie: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("Adresaci_tymczasowy");
        (*itr).imie = zmienianaInformacja;
        nowaLinia = utworzLinie(itr,idZalogowanego);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("Adresaci_tymczasowy","ksiazka_adresowa.txt");

        return;

    case 2:
        cout << "Podaj nowe nazwisko: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("Adresaci_tymczasowy");
        (*itr).nazwisko = zmienianaInformacja;
        nowaLinia = utworzLinie(itr,idZalogowanego);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("Adresaci_tymczasowy","ksiazka_adresowa.txt");
        return;
    case 3:
        cout << "Podaj nowy numer telefonu: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("Adresaci_tymczasowy");
        (*itr).nr_telefonu = zmienianaInformacja;
        nowaLinia = utworzLinie(itr,idZalogowanego);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("Adresaci_tymczasowy","ksiazka_adresowa.txt");

        return;
    case 4:
        cout << "Podaj nowy email: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("Adresaci_tymczasowy");
        (*itr).email = zmienianaInformacja;
        nowaLinia = utworzLinie(itr,idZalogowanego);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("Adresaci_tymczasowy","ksiazka_adresowa.txt");
        return;
    case 5:
        cout << "Podaj nowe adres: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("Adresaci_tymczasowy");
        (*itr).adres= zmienianaInformacja;
        nowaLinia = utworzLinie(itr,idZalogowanego);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("Adresaci_tymczasowy","ksiazka_adresowa.txt");
        return;

    case 6:
        return;
    }

}

void edytujAdresata(vector<Kontakt>&adresaci,int idZalogowanego) {
    system("cls");
    int id,wyborId,wyborInformacji;
    cout << "Podaj id adresata ktorego chcesz edytowac :";
    cin >> wyborId;
    string zmienianaInformacja,zmienianiaLinia;


    for(vector<Kontakt>::iterator itr=adresaci.begin(); itr!=adresaci.end(); ++itr) {
        if((*itr).id==wyborId) {
            cout << "Wybierz informacje ktora chcesz zmienic: " << endl;
            cout << "1 - imie" << endl << "2 - nazwisko" << endl << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl << "5 - adres" << endl << "6 - Powrot do menu" << endl;
            cin >> wyborInformacji;
            zmienianiaLinia=utworzLinie(itr,idZalogowanego);
            edycjaInformacji(itr,zmienianiaLinia,wyborInformacji,idZalogowanego);
            cout << "Edytowano adresata" << endl;
            Sleep(2500);
            return;
        }

    }
    cout << "Nie ma osoby o takim ID" << endl;
    Sleep(1500);
    return;


}

void rejstracja(vector<Uzytkownik>&uzytkownicy) {
    fstream plik;
    Uzytkownik tmp;
    string nazwa,haslo;
    if(uzytkownicy.size()>=1)
        tmp=uzytkownicy.back();
    else
        tmp.idUzytkownika=0;
    tmp.idUzytkownika+=1;
    system("cls");
    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> nazwa;
    for(vector<Uzytkownik>::iterator itr=uzytkownicy.begin(); itr!=uzytkownicy.end(); ++itr) {
        if(itr->nazwa==nazwa) {
            cout << "Istnieje juz uzytkownik o takiej nazwie" << endl;
            Sleep(1500);
            return;
        }
    }
    system("cls");
    cout << "Podaj haslo" << endl;
    cin >> haslo;

    tmp.nazwa=nazwa;
    tmp.haslo=haslo;

    uzytkownicy.push_back(Uzytkownik(tmp));

    plik.open("Uzytkownicy.txt",ios::out | ios::app);

    plik << tmp.idUzytkownika << "|";
    plik <<  tmp.nazwa << "|";
    plik << tmp.haslo << "|" <<endl;

    plik.close();

    system("cls");
    cout << "Utworzono nowego uzytkownika" << endl;
    Sleep(2500);


}

void odczytUzytkownikow(vector<Uzytkownik>&uzytkownicy) {
    fstream plik;
    string linia,bufor;
    int dlugoscLinijki,aktualnaPozycjaZnaku;
    int poprzedniaPozycjaZnaku=0;
    int licznik=0;
    uzytkownicy.clear();
    Uzytkownik tmp;

    plik.open("Uzytkownicy.txt",ios::in| ios::app);

    if(plik.good()==false)
        return;
    else {
        while(getline(plik,linia)) {
            dlugoscLinijki=linia.length();
            char znak;

            for(int i=0; i<=dlugoscLinijki; i++) {
                znak=linia[i];
                if(znak=='|') {
                    licznik++;
                    aktualnaPozycjaZnaku=i;
                    bufor = linia.substr(poprzedniaPozycjaZnaku,aktualnaPozycjaZnaku-poprzedniaPozycjaZnaku);
                    switch(licznik) {
                    case 1:
                        tmp.idUzytkownika=atoi(bufor.c_str());
                        break;
                    case 2:
                        tmp.nazwa=bufor;
                        break;
                    case 3:
                        tmp.haslo=bufor;
                        break;
                    }
                    poprzedniaPozycjaZnaku = i+1;
                }


            }

            uzytkownicy.push_back(Uzytkownik(tmp));

            licznik=0;
            poprzedniaPozycjaZnaku=0;
        }

    }

    plik.close();


}

int logowanie(vector<Uzytkownik>&uzytkownicy) {
    string nazwa,haslo;
    int idZalogowanego;
    system("cls");
    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> nazwa;

    for(vector<Uzytkownik>::iterator itr=uzytkownicy.begin(); itr!=uzytkownicy.end(); ++itr) {
        if(itr->nazwa==nazwa) {
            cout << "Podaj haslo: " << endl;
            cin >> haslo;
            if(itr->haslo==haslo) {
                cout << "Zalogowales sie poprawnie" <<endl;
                Sleep(1500);
                return itr->idUzytkownika;
            }


        }


    }
    system("cls");
    cout << "Nie ma takiego uzytkownika" << endl;
    Sleep(2500);
    return 0;

}


int main() {
    vector<Kontakt>adresaci;
    vector<Uzytkownik>uzytkownicy;
    int idZalogowanego=0;

    int iloscKontaktow=adresaci.size();
    char wybor;

    while(1) {

        odczytUzytkownikow(uzytkownicy);
        if(idZalogowanego==0) {

            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejstracja" << endl;
            cout << "3. Zamknij program" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;


            if(wybor == '1') {
                idZalogowanego=logowanie(uzytkownicy);
            } else if(wybor =='2') {
                rejstracja(uzytkownicy);
            } else if(wybor =='3')
                exit(0);

        } else if(idZalogowanego>0) {

            system("cls");
            iloscKontaktow=odczytZPliku(adresaci,idZalogowanego);
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "9. Wyloguj sie" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if(wybor == '1') {
                iloscKontaktow=dodajKontakt(adresaci,iloscKontaktow,idZalogowanego);

            } else if(wybor == '2') {
                if(iloscKontaktow==0) {
                    cout << "Brak kontaktow w ksiazce adresowej" << endl;
                    Sleep(1500);
                } else  wyszukajPoImieniu(adresaci);
            } else if(wybor == '3') {
                if(iloscKontaktow==0) {
                    cout << "Brak kontaktow w ksiazce adresowej" << endl;
                    Sleep(1500);
                } else wyszukajPoNazwisku(adresaci);
            } else if(wybor == '4') {
                if(iloscKontaktow==0) {
                    cout << "Brak kontaktow w ksiazce adresowej" << endl;
                    Sleep(1500);
                } else wyswietlWszystkieKontakty(adresaci);
            } else if(wybor=='5') {
                if(iloscKontaktow==0) {
                    cout << "Brak kontaktow w ksiazce adresowej" << endl;
                    Sleep(1500);
                } else usunAdresata(adresaci,idZalogowanego);
            } else if(wybor=='6') {
                if(iloscKontaktow==0) {
                    cout << "Brak kontaktow w ksiazce adresowej" << endl;
                    Sleep(1500);
                } else edytujAdresata(adresaci,idZalogowanego);
            } else if(wybor == '9') {
                idZalogowanego=0;
            }

        }
    }

    return 0;
}

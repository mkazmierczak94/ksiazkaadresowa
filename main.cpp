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

void zapisDoPliku(vector<Kontakt>adresaci,int iloscKontaktow) {
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::out | ios::app);

    plik << adresaci[iloscKontaktow].id << "|";
    plik <<  adresaci[iloscKontaktow].imie << "|";
    plik << adresaci[iloscKontaktow].nazwisko << "|";
    plik <<  adresaci[iloscKontaktow].nr_telefonu << "|";
    plik <<  adresaci[iloscKontaktow].adres << "|";
    plik << adresaci[iloscKontaktow].email << "|" << endl;

    plik.close();
}

int dodajKontakt(vector<Kontakt>&adresaci, int iloscKontaktow) {
    system("cls");
    Kontakt ostatnieId;
    int id;
    string imie,nazwisko,nr_telefonu,adres,email;
    if(adresaci.size()>=1)
        ostatnieId=adresaci.back();
    else
        ostatnieId.id=0;
    id=ostatnieId.id + 1;

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

    zapisDoPliku(adresaci,iloscKontaktow);

    cout << "Dodano kontakt" << endl;
    Sleep(1000);
    return adresaci.size();


}

void wyszukajPoImieniu(vector<Kontakt>adresaci) {
    system("cls");
    string imie;
    cout << "Podaj imie po ktorym chcesz wyszukiwac: ";
    cin >> imie;

    for(vector<Kontakt>::iterator itr=adresaci.begin(); itr!=adresaci.end(); ++itr) {
        if((*itr).imie==imie) {
            cout << "Znaleziono kontakt: " << endl;
            cout << (*itr).imie << " " << (*itr).nazwisko << " " <<(*itr).nr_telefonu;
            cout << " " << (*itr).adres << " " << (*itr).email << endl;
            cout << "Nacisnij dowolny klawisz aby kontynuowac" << endl;
            getch();
            return;

        }

    }
    cout << "Nie ma osoby o takim imieniu";
    Sleep(1000);
    return;

}

void wyszukajPoNazwisku(vector<Kontakt>adresaci) {
    system("cls");
    string nazwisko;
    cout << "Podaj nazwisko po ktorym chcesz wyszukiwac: ";
    cin >> nazwisko;

    for(vector<Kontakt>::iterator itr=adresaci.begin(); itr!=adresaci.end(); ++itr) {
        if((*itr).nazwisko==nazwisko) {
            cout << "Znaleziono kontakt: " << endl;
            cout << (*itr).imie << " " << (*itr).nazwisko << " " <<(*itr).nr_telefonu;
            cout << " " << (*itr).adres << " " << (*itr).email << endl;
            cout << "Nacisnij dowolny klawisz aby kontynuowac" << endl;
            getch();
            return;

        }

    }
    cout << "Nie ma osoby o takim nazwisku";
    Sleep(1000);
    return;

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

int odczytZPliku(vector<Kontakt>&adresaci) {
    fstream plik;
    string linia,bufor;
    int dlugoscLinijki,aktualnaPozycjaZnaku;
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
                        tmp.imie=bufor;
                        break;
                    case 3:
                        tmp.nazwisko=bufor;
                        break;
                    case 4:
                        tmp.nr_telefonu=bufor;
                        break;
                    case 5:
                        tmp.adres=bufor;
                        break;
                    case 6:
                        tmp.email=bufor;
                        break;
                    }
                    poprzedniaPozycjaZnaku = i+1;
                }


            }
            adresaci.push_back(Kontakt(tmp));

            licznik=0;
            poprzedniaPozycjaZnaku=0;
        }

    }

    plik.close();

    return adresaci.size();
}

string utworzLinie(vector<Kontakt>::iterator itr) {
    string linia,idString;
    int id =(*itr).id;
    idString = to_string(id);
    linia = idString + "|" + (*itr).imie + "|" + (*itr).nazwisko + "|" + (*itr).nr_telefonu +"|" + (*itr).adres +"|"+ (*itr).email +"|";
    return linia;

}

void usunAdresata(vector<Kontakt>&adresaci) {
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
                usuwanaLinia=utworzLinie(itr);
                plik.open("ksiazka_adresowa.txt");
                tymczasowyPlik.open("tymczasowyPlik.txt");
                while(getline(plik,linia)) {
                    if(linia!=usuwanaLinia)
                        tymczasowyPlik << linia << endl;
                }

                tymczasowyPlik.close();
                plik.close();
                remove("ksiazka_adresowa.txt");
                rename("tymczasowyPlik.txt","ksiazka_adresowa.txt");
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

void edycjaInformacji(vector<Kontakt>::iterator itr,string zmienianiaLinia,int wybor) {
    ifstream plik;
    ofstream tymczasowyPlik;
    string linia,nowaLinia,zmienianaInformacja;
    switch(wybor) {
    case 1:
        cout << "Podaj nowe imie: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("tymczasowyPlik.txt");
        (*itr).imie = zmienianaInformacja;
        nowaLinia = utworzLinie(itr);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("tymczasowyPlik.txt","ksiazka_adresowa.txt");

        return;
    case 2:
        cout << "Podaj nowe nazwisko: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("tymczasowyPlik.txt");
        (*itr).nazwisko = zmienianaInformacja;
        nowaLinia = utworzLinie(itr);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("tymczasowyPlik.txt","ksiazka_adresowa.txt");
        return;
    case 3:
        cout << "Podaj nowy numer telefonu: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("tymczasowyPlik.txt");
        (*itr).nr_telefonu = zmienianaInformacja;
        nowaLinia = utworzLinie(itr);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("tymczasowyPlik.txt","ksiazka_adresowa.txt");

        return;
    case 4:
        cout << "Podaj nowy email: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("tymczasowyPlik.txt");
        (*itr).email = zmienianaInformacja;
        nowaLinia = utworzLinie(itr);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("tymczasowyPlik.txt","ksiazka_adresowa.txt");
        return;
    case 5:
        cout << "Podaj nowe adres: ";
        cin >> zmienianaInformacja;
        plik.open("ksiazka_adresowa.txt");
        tymczasowyPlik.open("tymczasowyPlik.txt");
        (*itr).adres= zmienianaInformacja;
        nowaLinia = utworzLinie(itr);
        while(getline(plik,linia)) {
            if(linia!=zmienianiaLinia)
                tymczasowyPlik << linia << endl;
            else
                tymczasowyPlik << nowaLinia << endl;
        }

        tymczasowyPlik.close();
        plik.close();
        remove("ksiazka_adresowa.txt");
        rename("tymczasowyPlik.txt","ksiazka_adresowa.txt");
        return;
    case 6:
        return;
    }

}

void edytujAdresata(vector<Kontakt>&adresaci) {
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
            zmienianiaLinia=utworzLinie(itr);
            edycjaInformacji(itr,zmienianiaLinia,wyborInformacji);
            return;
        }

    }
    cout << "Nie ma osoby o takim ID" << endl;
    Sleep(1500);
    return;


}

int main() {
    vector<Kontakt>adresaci;
    int iloscKontaktow=adresaci.size();
    char wybor;

    while(1) {

        system("cls");
        iloscKontaktow=odczytZPliku(adresaci);
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        cin >> wybor;

        if(wybor == '1') {
            iloscKontaktow=dodajKontakt(adresaci,iloscKontaktow);

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
            } else usunAdresata(adresaci);
        } else if(wybor=='6') {
            if(iloscKontaktow==0) {
                cout << "Brak kontaktow w ksiazce adresowej" << endl;
                Sleep(1500);
            } else edytujAdresata(adresaci);
        } else if(wybor == '9') {
            exit(0);
        }


    }

    return 0;
}

#define W_LEWO 0
#define W_PRAWO 1
#include <iostream>
using namespace std;


struct Wezel {
    int wartosc = NULL;
    int xorAdrSasiadow = NULL;
    bool zKolejki = false;
};


struct Lista {
    Wezel* poczatek = NULL;
    Wezel* koniec = NULL;
    Wezel* BACK = NULL;
    Wezel* poprzednikBACK = NULL;
    Wezel* nastepnikBACK = NULL;
    int rozmiar = 0;
};


Wezel* wyznaczAdresSasiada(Wezel* innySasiad, Wezel* aktWezel) {
    int adres = (int)innySasiad xor aktWezel->xorAdrSasiadow;
    return (Wezel*)adres;
}


// ADD_BEG N 
void dodajNaPoczatek(Lista* lista, int n, bool zKolejki) {
    Wezel* nowyElem = new Wezel;
    nowyElem->wartosc = n;
    if (zKolejki)
        nowyElem->zKolejki = true;

    if (lista->poczatek == NULL) {
        lista->poczatek = lista->koniec = nowyElem;
        lista->poczatek->xorAdrSasiadow = lista->koniec->xorAdrSasiadow = NULL;

    }
    else {
        if (lista->poczatek == lista->koniec) { // lista ma tylko 1 wezel
            lista->koniec->xorAdrSasiadow = NULL xor (int)nowyElem;
            lista->poczatek = nowyElem;
            lista->poczatek->xorAdrSasiadow = (int)lista->koniec xor NULL;

        }
        else {
            lista->poczatek->xorAdrSasiadow = lista->poczatek->xorAdrSasiadow xor (int)nowyElem;
            nowyElem->xorAdrSasiadow = NULL xor (int)lista->poczatek;
            lista->poczatek = nowyElem;

        }

    }
    lista->rozmiar++;
}


// ADD_END N
void dodajNaKoniec(Lista* lista, int n, bool zKolejki) {
    Wezel* nowyElem = new Wezel;
    nowyElem->wartosc = n;
    if (zKolejki)
        nowyElem->zKolejki = true;

    if (lista->koniec == NULL) {
        lista->poczatek = lista->koniec = nowyElem;
        lista->poczatek->xorAdrSasiadow = lista->koniec->xorAdrSasiadow = NULL;

    }
    else {
        if (lista->koniec == lista->poczatek) { //lista ma 1 wezel
            lista->poczatek->xorAdrSasiadow = NULL xor (int)nowyElem;
            lista->koniec = nowyElem;
            lista->koniec->xorAdrSasiadow = (int)lista->poczatek xor NULL;

        }
        else {
            lista->koniec->xorAdrSasiadow = lista->koniec->xorAdrSasiadow xor (int)nowyElem;
            nowyElem->xorAdrSasiadow = NULL xor (int)lista->koniec;
            lista->koniec = nowyElem;

        }

    }
    lista->rozmiar++;
}


// ADD_ACT N
void dodajPoprzednikAktualnego(Lista* lista, int n, bool zKolejki) {
    Wezel* nowyElem = new Wezel;
    nowyElem->wartosc = n;
    nowyElem->xorAdrSasiadow = (int)lista->BACK xor (int)lista->poprzednikBACK;
    if (zKolejki)
        nowyElem->zKolejki = true;

    // zmieniamy xorAdrSasiadow w aktWezel i jego poprzedniku,
    // bo bedziemy miedzy nimi wstawiac nowyElem
    if (lista->poprzednikBACK == NULL) { //poczatek listy
        lista->BACK->xorAdrSasiadow = (int)lista->nastepnikBACK xor (int)nowyElem;
        lista->poczatek = nowyElem;

    }
    else {
        Wezel* poprzednikPoprzednika = wyznaczAdresSasiada(lista->BACK, lista->poprzednikBACK);
        lista->poprzednikBACK->xorAdrSasiadow = (int)poprzednikPoprzednika xor (int)nowyElem;
        lista->BACK->xorAdrSasiadow = (int)lista->nastepnikBACK xor (int)nowyElem;

        lista->poprzednikBACK = nowyElem;

    }
    lista->rozmiar++;
}


void usunWezlyZDanaLiczba(Lista* lista, int n); // identifier


// DEL_BEG
void usunPierwszyElement(Lista* lista, Lista* kolejka) {
    Wezel* doUsuniecia = lista->poczatek;

    if (lista->poczatek == NULL)
        return;
    else if (lista->poczatek == lista->koniec) { // mamy tylko 1 element
        if (doUsuniecia->zKolejki && kolejka != NULL) {
            usunWezlyZDanaLiczba(kolejka, doUsuniecia->wartosc);

        }
        lista->poczatek = lista->koniec = NULL;
        delete doUsuniecia;

    }
    else {
        Wezel* nowyPoczatek = wyznaczAdresSasiada(NULL, lista->poczatek);

        // musimy zaktualizowac xorAdrSasiadow w nowym poczatku 
        // (lewy sasiad staje sie NULL)
        Wezel* nastepnikNowegoPoczatku = wyznaczAdresSasiada(lista->poczatek, nowyPoczatek);
        nowyPoczatek->xorAdrSasiadow = NULL xor (int)nastepnikNowegoPoczatku;

        lista->poczatek = nowyPoczatek;

        if (doUsuniecia->zKolejki && kolejka != NULL) {
            usunWezlyZDanaLiczba(kolejka, doUsuniecia->wartosc);

        }
        delete doUsuniecia;

    }
    lista->rozmiar--;
}


// DEL_END
void usunOstatniElement(Lista* lista, Lista* kolejka) {
    Wezel* doUsuniecia = lista->koniec;

    if (lista->koniec == NULL)
        return;
    else if (lista->poczatek == lista->koniec) { // mamy tylko 1 element
        if (doUsuniecia->zKolejki && kolejka != NULL) {
            usunWezlyZDanaLiczba(kolejka, doUsuniecia->wartosc);

        }
        lista->poczatek = lista->koniec = NULL;
        delete doUsuniecia;

    }
    else {
        Wezel* nowyKoniec = wyznaczAdresSasiada(NULL, lista->koniec);

        // musimy zaktualizowac xorAdrSasiadow w nowym koncu 
        // (prawy sasiad staje sie NULL)
        Wezel* poprzednikNowegoKonca = wyznaczAdresSasiada(lista->koniec, nowyKoniec);
        nowyKoniec->xorAdrSasiadow = NULL xor (int)poprzednikNowegoKonca;

        lista->koniec = nowyKoniec;

        if (doUsuniecia->zKolejki && kolejka != NULL) {
            usunWezlyZDanaLiczba(kolejka, doUsuniecia->wartosc);

        }
        delete doUsuniecia;

    }
    lista->rozmiar--;
}


void usunWezel(Lista* lista, Wezel* poprzednik, Wezel* usuwanyWezel) {
    if (usuwanyWezel == lista->poczatek)
        usunPierwszyElement(lista, NULL);
    else if (usuwanyWezel == lista->koniec)
        usunOstatniElement(lista, NULL);
    else {
        //musimy zaktualizowac xorAdrSasiadow w sasiednich wezlach
        Wezel* nastepnik = wyznaczAdresSasiada(poprzednik, usuwanyWezel);
        Wezel* nastepnikNastepnika = wyznaczAdresSasiada(usuwanyWezel, nastepnik);
        nastepnik->xorAdrSasiadow = (int)nastepnikNastepnika xor (int)poprzednik;

        Wezel* poprzednikPoprzednika = wyznaczAdresSasiada(usuwanyWezel, poprzednik);
        poprzednik->xorAdrSasiadow = (int)poprzednikPoprzednika xor (int)nastepnik;

        delete usuwanyWezel;
        lista->rozmiar--;

    }
}


// DEL_VAL N
void usunWezlyZDanaLiczba(Lista* lista, int n) {

    if (lista->poczatek == NULL)
        return;
    else {
        Wezel* doSprawdzenia;
        doSprawdzenia = lista->poczatek;
        Wezel* poprzedni = NULL;
        if (lista->poczatek == lista->koniec) {
            if (doSprawdzenia->wartosc == n)
                usunWezel(lista, poprzedni, doSprawdzenia);
            return;

        }
        else {
            Wezel* nastepny = wyznaczAdresSasiada(poprzedni, doSprawdzenia);
            while (doSprawdzenia != lista->koniec) {
                if (doSprawdzenia->wartosc == n) {
                    usunWezel(lista, poprzedni, doSprawdzenia);
                    doSprawdzenia = nastepny;
                    nastepny = wyznaczAdresSasiada(poprzedni, doSprawdzenia);
                    // poprzedni zostaje poprzednim

                }
                else {
                    poprzedni = doSprawdzenia;
                    doSprawdzenia = nastepny;
                    nastepny = wyznaczAdresSasiada(poprzedni, doSprawdzenia);

                }

            }
            if (lista->koniec->wartosc == n)
                usunOstatniElement(lista, NULL);
            return;

        }

    }
}


void drukujOdPoczatku(Lista* lista) {

    if (lista->poczatek == NULL)
        cout << "NULL" << endl;
    else if (lista->poczatek == lista->koniec)
        cout << lista->poczatek->wartosc << endl;
    else {
        Wezel* poprzedni = NULL;
        Wezel* drukowany = lista->poczatek;
        Wezel* nastepny = wyznaczAdresSasiada(poprzedni, drukowany);
        while (drukowany != lista->koniec) {
            cout << drukowany->wartosc << " ";
            poprzedni = drukowany;
            drukowany = nastepny;
            nastepny = wyznaczAdresSasiada(poprzedni, drukowany);

        }
        cout << lista->koniec->wartosc << endl;

    }
}


void drukujOdKonca(Lista* lista) {

    if (lista->koniec == NULL)
        cout << "NULL" << endl;
    else if (lista->poczatek == lista->koniec)
        cout << lista->koniec->wartosc << endl;
    else {
        Wezel* poprzedni = NULL;
        Wezel* drukowany = lista->koniec;
        Wezel* nastepny = wyznaczAdresSasiada(poprzedni, drukowany);
        while (drukowany != lista->poczatek) {
            cout << drukowany->wartosc << " ";
            poprzedni = drukowany;
            drukowany = nastepny;
            nastepny = wyznaczAdresSasiada(poprzedni, drukowany);

        }
        cout << lista->poczatek->wartosc << endl;

    }
}


void drukujRozmiar(Lista* lista) {
    cout << lista->rozmiar << endl;
}


// PUSH N
void dodajNaKoniecKolejki(Lista* lista, Lista* kolejka, int n) {
    Wezel* BACK = kolejka->koniec;
    dodajNaKoniec(kolejka, n, true);

    if (lista->poczatek == NULL)
        dodajNaPoczatek(lista, n, true);
    else if (lista->poczatek == lista->koniec) {    // lista zawiera tylko 1 element
        if (lista->poczatek->zKolejki == false) {   // element nie nalezy do kolejki
            lista->poczatek->wartosc = n;
            lista->poczatek->zKolejki = true;

        }
        else {                                      // tworzymy nowy wezel
            dodajNaPoczatek(lista, n, true);

        }

    }
    else {
        // iterujemy po liscie dopoki nie spotkamy wezel z kolejki
        // wtedy "po lewej" od niego w niezajetym przez kolejke wezle zmieniamy liczbe (wartosc)
        // albo wstawiamy nowy element jesli niezajetych elementow nie ma
        Wezel* aktualny, * nastepny;
        int kierunek;

        if (lista->poczatek->zKolejki == false) {
            aktualny = lista->poczatek;
            kierunek = W_PRAWO;

        }
        else { // jesli poczatek listy juz jest w kolejce
            aktualny = lista->koniec;
            kierunek = W_LEWO;

        }


        if (aktualny->zKolejki == false && aktualny == lista->koniec) {
            aktualny->wartosc = n;
            aktualny->zKolejki = true;
            return;

        }
        else {
            nastepny = wyznaczAdresSasiada(NULL, aktualny);
            if (kierunek == W_PRAWO) {
                while (nastepny != lista->koniec && nastepny->zKolejki != true) {
                    Wezel* temp = aktualny;
                    aktualny = nastepny;
                    nastepny = wyznaczAdresSasiada(temp, nastepny);

                }

                if (nastepny->zKolejki && aktualny->zKolejki == false) {
                    aktualny->wartosc = n;
                    aktualny->zKolejki = true;
                    return;

                }

            }
            else if (kierunek == W_LEWO) {
                while (nastepny->zKolejki != false && nastepny != lista->poczatek) {
                    Wezel* temp = aktualny;
                    aktualny = nastepny;
                    nastepny = wyznaczAdresSasiada(temp, nastepny);

                }

                if (aktualny->zKolejki && nastepny->zKolejki == false) {
                    nastepny->wartosc = n;
                    nastepny->zKolejki = true;
                    return;

                }

            }

            if (lista->koniec->zKolejki == false) { // jezeli nic z listy nie nalezy do kolejki
                lista->koniec->wartosc = n;
                lista->koniec->zKolejki = true;

            }
            else {  // jesli nie znaleziono elementow nie nalezacych do kolejki:
                // szukamy BACK na liscie
                aktualny = lista->poczatek;
                Wezel* poprzedni = NULL;
                nastepny = wyznaczAdresSasiada(poprzedni, aktualny);
                while (aktualny->wartosc != BACK->wartosc) {
                    poprzedni = aktualny;
                    Wezel* temp = aktualny;
                    aktualny = nastepny;
                    nastepny = wyznaczAdresSasiada(temp, nastepny);

                }
                lista->BACK = aktualny;
                lista->nastepnikBACK = nastepny;
                lista->poprzednikBACK = poprzedni;
                dodajPoprzednikAktualnego(lista, n, true);

            }

        }

    }
}


// POP
void wyciagnijZKolejki(Lista* kolejka, Lista* lista) {

    if (kolejka->poczatek == NULL) {
        cout << "NULL" << endl;
        return;

    }
    else {
        int pop = kolejka->poczatek->wartosc;
        cout << pop << endl;
        usunPierwszyElement(kolejka, NULL);

        // musimy rowniez "odznaczyc" ten element w liscie
        Wezel* doSprawdzenia = lista->poczatek;
        Wezel* nastepny = wyznaczAdresSasiada(NULL, doSprawdzenia);
        while (doSprawdzenia->wartosc != pop) {
            Wezel* sprawdzony = doSprawdzenia;
            doSprawdzenia = nastepny;
            nastepny = wyznaczAdresSasiada(sprawdzony, doSprawdzenia);

        }
        doSprawdzenia->zKolejki = false;

    }
}


// GARBAGE_SOFT
void wyzerujElementyNieZKolejki(Lista* lista) {

    if (lista->poczatek == NULL)
        return;
    else if (lista->poczatek == lista->koniec) {
        if (lista->koniec->zKolejki == false)
            lista->koniec->wartosc = 0;

    }
    else {
        Wezel* doSprawdzenia = lista->poczatek;
        Wezel* nastepny = wyznaczAdresSasiada(NULL, doSprawdzenia);
        Wezel* sprawdzony = NULL;
        while (sprawdzony != lista->koniec) {
            if (doSprawdzenia->zKolejki == false)
                doSprawdzenia->wartosc = 0;

            sprawdzony = doSprawdzenia;
            doSprawdzenia = nastepny;
            if (nastepny != lista->koniec)
                nastepny = wyznaczAdresSasiada(sprawdzony, doSprawdzenia);

        }

    }
}


// GARBAGE_HARD
void usunElementyNieZKolejki(Lista* lista) {
    if (lista->poczatek == NULL)
        return;
    else if (lista->poczatek == lista->koniec) {
        if (lista->koniec->zKolejki == false)
            usunOstatniElement(lista, NULL);

    }
    else {
        Wezel* doSprawdzenia = lista->poczatek;
        Wezel* nastepny = wyznaczAdresSasiada(NULL, doSprawdzenia);
        Wezel* sprawdzony = NULL;

        while (doSprawdzenia != lista->koniec) {

            if (doSprawdzenia->zKolejki == false) {
                usunWezel(lista, sprawdzony, doSprawdzenia);
                doSprawdzenia = nastepny;
                nastepny = wyznaczAdresSasiada(sprawdzony, doSprawdzenia);

            }
            else {
                sprawdzony = doSprawdzenia;
                doSprawdzenia = nastepny;
                if (nastepny != lista->koniec)
                    nastepny = wyznaczAdresSasiada(sprawdzony, doSprawdzenia);

            }

        }
        if (lista->koniec->zKolejki == false)
            usunOstatniElement(lista, NULL);

    }
}


bool porownajString(char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' || s2[i] != '\0') {
        if (s1[i] == s2[i]) {
            i++;

        }
        else
            return false;

    }
    return true;
}


void wyznaczKomende(char* komenda, Lista* lista, Lista* kolejka) {
    int n;

    if (porownajString(komenda, "ADD_BEG")) {
        cin >> n;
        dodajNaPoczatek(lista, n, false);

    }
    else if (porownajString(komenda, "ADD_END")) {
        cin >> n;
        dodajNaKoniec(lista, n, false);

    }
    else if (porownajString(komenda, "DEL_BEG")) {
        usunPierwszyElement(lista, kolejka);

    }
    else if (porownajString(komenda, "DEL_END")) {
        usunOstatniElement(lista, kolejka);

    }
    else if (porownajString(komenda, "PRINT_FORWARD")) {
        drukujOdPoczatku(lista);

    }
    else if (porownajString(komenda, "PRINT_BACKWARD")) {
        drukujOdKonca(lista);

    }
    else if (porownajString(komenda, "SIZE")) {
        drukujRozmiar(lista);

    }
    else if (porownajString(komenda, "PUSH")) {
        cin >> n;
        dodajNaKoniecKolejki(lista, kolejka, n);

    }
    else if (porownajString(komenda, "POP")) {
        wyciagnijZKolejki(kolejka, lista);

    }
    else if (porownajString(komenda, "PRINT_QUEUE")) {
        drukujOdPoczatku(kolejka);

    }
    else if (porownajString(komenda, "COUNT")) {
        drukujRozmiar(kolejka);

    }
    else if (porownajString(komenda, "GARBAGE_SOFT")) {
        wyzerujElementyNieZKolejki(lista);

    }
    else if (porownajString(komenda, "GARBAGE_HARD")) {
        usunElementyNieZKolejki(lista);

    }
}


void wyczyscListe(Lista* lista) {
    while (lista->poczatek != lista->koniec)
        usunPierwszyElement(lista, NULL);
    usunPierwszyElement(lista, NULL);
}


int main()
{
    char komenda[15];
    Lista lista;
    Lista kolejka;

    while (cin >> komenda) {
        wyznaczKomende(komenda, &lista, &kolejka);

    }

    if (lista.poczatek != NULL)
        wyczyscListe(&lista);
    if (kolejka.poczatek != NULL)
        wyczyscListe(&kolejka);

    return 0;
}
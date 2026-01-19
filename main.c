#include "bohater.h"
#include "rejestr.h"
#include "pliki.h"
#include <stdio.h>
#include <stdlib.h>

void pokazMenu() { //wyswielta menu za pomoca printf
    printf("\n=== GILDIA POSZUKIWACZY PRZYGOD ===\n");
    printf("1. Dodaj bohatera\n");
    printf("2. Wyswietl bohaterow\n");
    printf("3. Wyszukaj bohaterow\n");
    printf("4. Modyfikuj bohatera\n");
    printf("5. Wczytaj z pliku\n");
    printf("6. Zapisz do pliku\n");
    printf("0. Wyjscie\n");
    printf("Wybor: ");
}

int main() {
    Rejestr r;
    dodajRejestr(&r);
    int wybor;
    do {
        pokazMenu();
        if (scanf("%d", &wybor) != 1) {
            printf("Blad. Wpisz liczbe.\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');
        switch(wybor) {
            case 1: { //dodawanie bohatera
                Bohater b;
                nowyBohatera(&b);
                wklejBohatera(&r, b);
                break;
            }
            case 2:
                wyswietlBohaterow(&r);//wyswietla wszystkich bohaterow z rejestru
                break;
            case 3: { //uruchamia funkcje do filtrow, a po przefiltrowaniu wyswietla rejestr wynik, a na koniec go zwalnia
                Filtry f;
                ustawFiltry(&f);
                Rejestr wynik;
                dodajRejestr(&wynik);
                filtruj(&r, &f, &wynik);
                printf("\n--- WYNIKI WYSZUKIWANIA ---\n");
                wyswietlBohaterow(&wynik);
                break;
            }
            case 4:
                zmienBohatera(&r); //modyfikacja bohatera z podanym numerem
                break;
            case 5:{
                char filename[100];
                nazwaPliku(filename);
                if (wczytajZPliku(&r, filename) == 1) printf("Blad otwarcia pliku");
                break;
            }
            case 6:{
                char filename[100];
                nazwaPliku(filename);
                if (zapiszDoPliku(&r, filename) == 1) printf("Blad otwarcia pliku");
                break;
                }
            case 0:{
                printf("Zapisaæ do pliku? 1 - TAK\n");
                int wybor;
                scanf ("%d", &wybor);
                if (wybor == 1){
                     char filename[100];
                    nazwaPliku(filename);
                    if (zapiszDoPliku(&r, filename) == 1) printf("Blad otwarcia pliku");
                }
                printf("Koniec programu.\n");
                break;
            }
            default:
                printf("Niepoprawny wybor.\n");
        }
    } while(wybor != 0);
    return 0;
}

#include "bohater.h"
#include "rejestr.h"
#include "pliki.h"
#include <stdio.h>
#include <stdlib.h>

void pokazMenu() {
    system("cls");
    printf("      ________________________________________________________________\n");
    printf("    //                                                                \\\\\n");
    printf("   ||             --== G I L D I A  P O S Z U K I W A C Z Y ==--       ||\n");
    printf("   ||                     --== P R Z Y G O D ==--                      ||\n");
    printf("    \\\\________________________________________________________________//\n");
    printf("     +--------------------------+          +--------------------------+\n");
    printf("     |  1. Dodaj bohatera       |          |  2. Wyswietl bohaterow   |\n");
    printf("     +--------------------------+          +--------------------------+\n");
    printf("     +--------------------------+          +--------------------------+\n");
    printf("     |  3. Wyszukaj bohaterow   |          |  4. Modyfikuj bohatera   |\n");
    printf("     +--------------------------+          +--------------------------+\n");
    printf("     +--------------------------+          +--------------------------+\n");
    printf("     |  5. Wczytaj z pliku      |          |  6. Zapisz do pliku      |\n");
    printf("     +--------------------------+          +--------------------------+\n");
    printf("     +--------------------------+          +--------------------------+\n");
    printf("     |  7. Usun bohaterow       |          |  8. Sortuj               |\n");
    printf("     +--------------------------+          +--------------------------+\n");
    printf("                        +--------------------------+\n");
    printf("                        |  0. Wyjscie              |\n");
    printf("                        +--------------------------+\n");
    printf("\n");
    printf("+---------------------------------------------------------------------+\n");
printf("\n");
    printf("                        +--------------------------+\n");
    printf("                        |      DECYZJA GILDII      |\n");
    printf("                        +---------         --------+\n");
    printf("                                  \\       /\n");
    printf("                                   \\     /\n");
    printf("                                    \\   /\n");
    printf("                                     \\ /\n");
    printf("                                      ");
}

int main() {
    Rejestr r;
    dodajRejestr(&r);
    int wybor;
    do {
        pokazMenu();
        if (scanf("%d", &wybor) != 1) {
            printf("==Blad. Wpisz liczbe==\n");
             printf("\n==Nacisnij Enter, aby wrocic do menu==");
            getchar();
            getchar();
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');
        switch(wybor) {
            case 1: {
                system("cls");
                Bohater b;
                nowyBohatera(&b);
                wklejBohatera(&r, b);
                printf("\n==Nacisnij Enter, aby wrocic do menu==");
                getchar();
                getchar();
                break;
            }
            case 2:
                system("cls");
                wyswietlBohaterow(&r);
                printf("\n==Nacisnij Enter, aby wrocic do menu==");
                getchar();
                getchar();
                break;
            case 3: {
                system("cls");
                Filtry f;
                ustawFiltry(&f);
                Rejestr wynik;
                dodajRejestr(&wynik);
                filtruj(&r, &f, &wynik);
                printf("\n--== WYNIKI WYSZUKIWANIA ==--\n");
                wyswietlBohaterow(&wynik);
                usunRejestr(&wynik);
                printf("\n==Nacisnij Enter, aby wrocic do menu==");
                getchar();
                getchar();
                break;
            }
            case 4:
                system("cls");
                zmienBohatera(&r); //modyfikacja bohatera z podanym numerem
                printf("\n==Nacisnij Enter, aby wrocic do menu==");
                getchar();
                getchar();
                break;
            case 5:{
                system("cls");
                char filename[100];
                nazwaPliku(filename);
                if (wczytajZPliku(&r, filename) == 1) printf("Blad otwarcia pliku");
                printf("\nNacisnij Enter, aby wrocic do menu...");
                getchar();
                getchar();
                break;
            }
            case 6:{
                char filename[100];
                nazwaPliku(filename);
                if (zapiszDoPliku(&r, filename) == 1) printf("==Blad otwarcia pliku==");
                printf("\nNacisnij Enter, aby wrocic do menu...");
                getchar();
                getchar();
                break;
                }
            case 7:
                system("cls");
                printf("==Podaj cechy bohaterów do usuniecia==\n")
                Filtry f;
                ustawFiltry(&f);
                usunBohaterow(&r, &f);
                printf("\n==Nacisnij Enter, aby wrocic do menu==");
                getchar();
                getchar();
                break;
            case 8:
                system("cls");
                sortuj(&r);
                printf("\n==Nacisnij Enter, aby wrocic do menu==");
                getchar();
                getchar();
                break;
            case 0:{
                system("cls");
            char d;
            do {
                printf("==Czy chcesz zapisac [T/N]==\n>>");
                scanf("%c", &d);
                if (d != 't' && d != 'T' && d != 'n' && d != 'N') {
                printf("==BLAD! Wybierz [T]ak lub [N]ie.\n==");
                while(getchar() != '\n');
            }
            } while (d != 't' && d != 'T' && d != 'n' && d != 'N');
                if (d == 't' || d == 'T'){
                     char filename[100];
                    nazwaPliku(filename);
                    if (zapiszDoPliku(&r, filename) == 1) printf("==Blad otwarcia pliku==");
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

#include "pliki.h"
#include <stdio.h>
#include <stdlib.h>

void nazwaPliku(char *filename) {
    while (1) {
        printf("==Podaj nazwe pliku>>\n");
        if (scanf(" %99[^\n]", filename) != 1){
            printf("==Podaj prawidlowa nazwe==\n");
        }
        int len = strlen(filename);
        if (strcmp(filename + len - 4, ".txt") == 0) break;
        else{
            printf("==Niepoprawne rozszerzenie(obslugiwane - .txt)==\n");
        }
    }
}

int zapiszDoPliku(Rejestr *r, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) return 1;

    Element *obecny = r->glowa;
    while (obecny != NULL) {
        Bohater b = obecny->dane;
        fprintf(f, "%s\n%s\n%d %d %d %d\n",
                b.imie, b.rasa, b.klasa, b.poziom, b.reputacja, b.status);
        obecny = obecny->nastepny;
    }
    printf("==Zapisano poprawnie==");
    fclose(f);
    return 0;
}

int wczytajZPliku(Rejestr *r, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) return 1;

    Bohater b;
    while (fscanf(f, " %99[^\n] %49[^\n] %d %d %d %d",
                  b.imie, b.rasa, (int*)&b.klasa, &b.poziom, &b.reputacja, (int*)&b.status) == 6) {
        wklejBohatera(r, b);
    }
    printf("==Wczytano poprawnie==\n");
    fclose(f);
    return 0;
}

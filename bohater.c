#include "bohater.h"
#include "rejestr.h"
#include <stdio.h>

void nowyBohatera(Bohater *b) { //modyfikuje imie w strukturze b i odpala funkcje modyfikacji atrybutów
    printf("Podaj imie bohatera: ");
    scanf(" %99[^\n]", b->imie);
    atrybutyBohatera(b);
}

void atrybutyBohatera(Bohater *b) { //modyfikuje atrybuty bohatera w strukturze b
    printf("Podaj rase bohatera: ");
    scanf(" %49[^\n]", b->rasa);
    int temp;
    printf("Podaj klase bohatera (0-wojownik, 1-mag, 2-kaplan, 3-lotrzyk, 4-lowca, 5-druid): ");
    while(scanf("%d", &temp) != 1 || temp < 0 || temp > 5) {
        printf("Blad. Podaj liczbe calkowita 0-5: ");
        while(getchar() != '\n');
    }
    b->klasa = (enumKlasa)temp;
    printf("Podaj poziom bohatera (>=1): ");
    while(scanf("%d", &b->poziom) != 1 || b->poziom < 1) {
        printf("Blad. Podaj liczbe calkowita >= 1: ");
        while(getchar() != '\n');
    }
    printf("Podaj reputacje bohatera (0-100): ");
    while(scanf("%d", &b->reputacja) != 1 || b->reputacja < 0 || b->reputacja > 100) {
        printf("Blad. Podaj liczbe calkowita 0-100: ");
        while(getchar() != '\n');
    }
    printf("Podaj status bohatera (0-aktywny, 1-na_misji, 2-ranny, 3-zaginiony, 4-zawieszony): ");
    while(scanf("%d", &temp) != 1 || temp < 0 || temp > 4) {
        printf("Blad. Podaj liczbe calkowita 0-4: ");
        while(getchar() != '\n');
    }
    b->status = (enumStatus)temp;
}

void zmienBohatera(Rejestr *r) {
    if (r->glowa == NULL) {
        printf("Brak bohaterow do modyfikacji.\n");
        return;
    }
    printf("Podaj numer bohatera do modyfikacji:\n");
    Element* obecny = r->glowa;
    int i = 1;
    while(obecny != NULL) {
        printf("%d. %s\n", i, obecny->dane.imie);
        obecny = obecny->nastepny;
        i++;
    }
    int numer;
    while(scanf("%d", &numer) != 1 || numer < 1 || numer > r->rozmiar) {
        printf("Blad. Podaj poprawny numer bohatera: ");
        while(getchar() != '\n');
    }
    obecny = r->glowa;
    for(int k = 1; k < numer; k++) {
        obecny = obecny->nastepny;
    }
    atrybutyBohatera(&obecny->dane);
}

char* statusNaTekst(enumStatus status) { //pobiera status z enum i zwraca tekstowa wersje statusu
    switch(status) {
        case AKTYWNY: return "aktywny";
        case NA_MISJI: return "na_misji";
        case RANNY: return "ranny";
        case ZAGINIONY: return "zaginiony";
        case ZAWIESZONY: return "zawieszony";
        default: return "nieznany";
    }
}

char* klasaNaTekst(enumKlasa klasa) {//pobiera klase z enum i zwraca tekstowa wersje klasy
    switch(klasa) {
        case WOJOWNIK: return "wojownik";
        case MAG: return "mag";
        case KAPLAN: return "kaplan";
        case LOTRZYK: return "lotrzyk";
        case LOWCA: return "lowca";
        case DRUID: return "druid";
        default: return "nieznany";
    }
}

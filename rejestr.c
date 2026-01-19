#include "rejestr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dodajRejestr(Rejestr* r) { //tworzy nowy rejestr bohaterow (uzywane do glownego rejestru i zwracania wynikow wyszukiwania)
    r->glowa = NULL;
    r->rozmiar = 0;
}


void wklejBohatera(Rejestr* r, Bohater b) { //bierze strukture b i wkleja ja do rejestru r
    Element *nowy = malloc(sizeof(Element));
    if (!nowy){
        printf("Blad alokacji pamieci");
        return;
    }
    nowy->dane = b;
    nowy->nastepny = NULL;

    if(r->glowa==NULL){
    r->glowa = nowy;
    }
    else
    {
    Element* obecny = r->glowa;
    while (obecny->nastepny != NULL){
        obecny=obecny->nastepny;
    }
    obecny->nastepny=nowy;
    }
    r->rozmiar++;
}

void ustawFiltry(Filtry* f) { //pobiera od uzytkownika filtry i zapisuje je w strukturze Filtry f
    printf("==Podaj imie bohatera lub prefiks (lub '-' aby pominac)>> ");
    scanf(" %99[^\n]", f->imie);
    printf("==Podaj rase bohatera lub prefiks (lub '-' aby pominac)>> ");
    scanf(" %49[^\n]", f->rasa);
    printf("==Podaj klase bohatera (-1 aby pominac) WOJOWNIK - 0, MAG - 1, KAPLAN - 2, LOTRZYK - 3, LOWCA - 4, DRUID - 5>> ");
    while(scanf("%d", &f->klasa) != 1 || f->klasa < -1 || f->klasa > 5) {
        printf("Blad. Podaj liczbe -1 do 5: ");
        while(getchar() != '\n');
    }
    printf("==Podaj minimalny poziom (-1 aby pominac)>> ");
    while(scanf("%d", &f->minpoziom) != 1 || f->minpoziom < -1) {
        printf("Blad. Podaj liczbe >= -1: ");
        while(getchar() != '\n');
    }
    printf("==Podaj maksymalny poziom (-1 aby pominac)>> ");
    while(scanf("%d", &f->maxpoziom) != 1 || (f->maxpoziom != -1 && f->maxpoziom < f->minpoziom)) {
        printf("Blad. Podaj liczbe >= minpoziom lub -1: ");
        while(getchar() != '\n');
    }
    printf("==Podaj minimalna reputacje (-1 aby pominac)>> ");
    while(scanf("%d", &f->minreputacja) != 1 || f->minreputacja < -1) {
        printf("Blad. Podaj liczbe >= -1: ");
        while(getchar() != '\n');
    }
    printf("==Podaj maksymalna reputacje (-1 aby pominac)>> ");
    while(scanf("%d", &f->maxreputacja) != 1 || (f->maxreputacja != -1 && f->maxreputacja < f->minreputacja)) {
        printf("Blad. Podaj liczbe >= minreputacja lub -1: ");
        while(getchar() != '\n');
    }
    printf("==Podaj status bohatera (-1 aby pominac), AKTYWNY - 0, NA MISJI - 1, RANNY - 2, ZAGINIONY -3 , ZAWIESZONY - 4>> ");
    while(scanf("%d", &f->status) != 1 || f->status < -1 || f->status > 4) {
        printf("Blad. Podaj liczbe -1 do 4: ");
        while(getchar() != '\n');
    }
}

void filtruj(Rejestr* r, Filtry* f, Rejestr* wynik) {
    Element* obecny = r->glowa;

    while (obecny != NULL) {
        Bohater* b = &obecny->dane;
        int pasuje = 1;
        if(strcmp(f->imie, "-") != 0 && strncmp(b->imie, f->imie, strlen(f->imie)) != 0) pasuje = 0;
        if(strcmp(f->rasa, "-") != 0 && strncmp(b->rasa, f->rasa, strlen(f->rasa)) != 0) pasuje = 0;
        if(f->klasa != -1 && b->klasa != (enumKlasa)f->klasa) pasuje = 0;
        if(f->minpoziom != -1 && b->poziom < f->minpoziom) pasuje = 0;
        if(f->maxpoziom != -1 && b->poziom > f->maxpoziom) pasuje = 0;
        if(f->minreputacja != -1 && b->reputacja < f->minreputacja) pasuje = 0;
        if(f->maxreputacja != -1 && b->reputacja > f->maxreputacja) pasuje = 0;
        if(f->status != -1 && b->status != (enumStatus)f->status) pasuje = 0;

        if(pasuje==1) {
            wklejBohatera(wynik, *b);
        }
        obecny = obecny->nastepny;
    }
}

void wyswietlBohaterow(Rejestr* r) {
    if (r->glowa == NULL) {
        printf("Brak bohaterow do wyswietlenia.\n");
        return;
    }
    system("cls");
    Element* obecny = r->glowa;
    printf("%-3s|%-100s|%-50s|", "lp", "Imie", "Rasa");
    printf("%-10s|%-4s|%-4s|%-10s\n", "Klasa", "Poz", "Rep", "Status");
    int i = 1;
    while (obecny != NULL) {
        Bohater b = obecny->dane;
        printf("%-3d|", i);
        printf("%-100s|", b.imie);
        printf("%-50s|", b.rasa);
        printf("%-10s|", klasaNaTekst(b.klasa));
        printf("%-4d|", b.poziom);
        printf("%-4d|", b.reputacja);
        printf("%-10s\n", statusNaTekst(b.status));
        printf("---+");
        for (int i = 0; i < 100; i++) {
            printf("-");
        }
        printf("+");
        for (int i = 0; i < 50; i++) {
            printf("-");
        }
        printf("+----------+----+----+----------+\n");
        obecny = obecny->nastepny;
        i++;
    }
}
void usunRejestr(Rejestr *r){
    Element* obecny = r->glowa;
    while (obecny != NULL){
        Element *temp = obecny;
        obecny = obecny->nastepny;
        free(temp);
    }
    r->glowa=NULL;
    r->rozmiar=0;
}
void usunBohaterow(Rejestr* r, Filtry* f) {
    Rejestr nowy;
    dodajRejestr(&nowy);
    Element* obecny = r->glowa;

    while (obecny != NULL) {
        Bohater* b = &obecny->dane;
        int pasuje = 1;
        if(strcmp(f->imie, "-") != 0 && strncmp(b->imie, f->imie, strlen(f->imie)) != 0) pasuje = 0;
        if(strcmp(f->rasa, "-") != 0 && strncmp(b->rasa, f->rasa, strlen(f->rasa)) != 0) pasuje = 0;
        if(f->klasa != -1 && b->klasa != (enumKlasa)f->klasa) pasuje = 0;
        if(f->minpoziom != -1 && b->poziom < f->minpoziom) pasuje = 0;
        if(f->maxpoziom != -1 && b->poziom > f->maxpoziom) pasuje = 0;
        if(f->minreputacja != -1 && b->reputacja < f->minreputacja) pasuje = 0;
        if(f->maxreputacja != -1 && b->reputacja > f->maxreputacja) pasuje = 0;
        if(f->status != -1 && b->status != (enumStatus)f->status) pasuje = 0;
        if(b->status == NA_MISJI) pasuje = 0;

        if(pasuje==0) {
            wklejBohatera(&nowy, *b);
        }
        obecny = obecny->nastepny;
    }
    usunRejestr(r);
    r->glowa=nowy.glowa;
    r->rozmiar=nowy.rozmiar;
    printf("==Usuwanie zakonczone==\n");
}

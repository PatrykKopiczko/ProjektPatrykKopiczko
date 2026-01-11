#include "rejestr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dodajRejestr(Rejestr* r) { //tworzy nowy rejestr bohaterow (uzywane do glownego rejestru i zwracania wynikow wyszukiwania)
    r->pojemnosc = 10;
    r->rozmiar = 0;
    r->bohaterowie = malloc(r->pojemnosc * sizeof(Bohater));
    if(!r->bohaterowie) {
        printf("Blad alokacji pamieci!\n");
        exit(1);
    }
}

void wklejBohatera(Rejestr* r, Bohater b) { //bierze strukture b i wkleja ja do rejestru r
    if(r->rozmiar >= r->pojemnosc) {
        int new_capacity = r->pojemnosc * 2;
        if (new_capacity == 0) new_capacity = 10;
        Bohater* temp = realloc(r->bohaterowie, new_capacity * sizeof(Bohater));
        if(!temp) {
            printf("Blad realokacji pamieci!\n");
            return;
        }
        r->bohaterowie = temp;
        r->pojemnosc = new_capacity;
    }
    r->bohaterowie[r->rozmiar] = b;
    r->rozmiar++;
}

void ustawFiltry(Filtry* f) { //pobiera od uzytkownika filtry i zapisuje je w strukturze Filtry f
    printf("Podaj imie bohatera lub prefiks (lub '-' aby pominac): ");
    scanf(" %99[^\n]", f->imie);
    printf("Podaj rase bohatera lub prefiks (lub '-' aby pominac): ");
    scanf(" %49[^\n]", f->rasa);
    printf("Podaj klase bohatera (-1 aby pominac, 0-5): ");
    while(scanf("%d", &f->klasa) != 1 || f->klasa < -1 || f->klasa > 5) {
        printf("Blad. Podaj liczbe -1 do 5: ");
        while(getchar() != '\n');
    }
    printf("Podaj minimalny poziom (-1 aby pominac): ");
    while(scanf("%d", &f->minpoziom) != 1 || f->minpoziom < -1) {
        printf("Blad. Podaj liczbe >= -1: ");
        while(getchar() != '\n');
    }
    printf("Podaj maksymalny poziom (-1 aby pominac): ");
    while(scanf("%d", &f->maxpoziom) != 1 || (f->maxpoziom != -1 && f->maxpoziom < f->minpoziom)) {
        printf("Blad. Podaj liczbe >= minpoziom lub -1: ");
        while(getchar() != '\n');
    }
    printf("Podaj minimalna reputacje (-1 aby pominac): ");
    while(scanf("%d", &f->minreputacja) != 1 || f->minreputacja < -1) {
        printf("Blad. Podaj liczbe >= -1: ");
        while(getchar() != '\n');
    }
    printf("Podaj maksymalna reputacje (-1 aby pominac): ");
    while(scanf("%d", &f->maxreputacja) != 1 || (f->maxreputacja != -1 && f->maxreputacja < f->minreputacja)) {
        printf("Blad. Podaj liczbe >= minreputacja lub -1: ");
        while(getchar() != '\n');
    }
    printf("Podaj status bohatera (-1 aby pominac, 0-4): ");
    while(scanf("%d", &f->status) != 1 || f->status < -1 || f->status > 4) {
        printf("Blad. Podaj liczbe -1 do 4: ");
        while(getchar() != '\n');
    }
}

void filtruj(Rejestr* r, Filtry* f, Rejestr* wynik) { //bierze rejestr r, porownuje kazdego bohatera z filtrami, i jesli pasuje to wkleja bohatera rejestru wynik
    for(int i = 0; i < r->rozmiar; i++) {
        int pasuje = 1;
        if(strcmp(f->imie, "-") != 0 && strncmp(r->bohaterowie[i].imie, f->imie, strlen(f->imie)) != 0)
            pasuje = 0;
        if(strcmp(f->rasa, "-") != 0 && strncmp(r->bohaterowie[i].rasa, f->rasa, strlen(f->rasa)) != 0)
            pasuje = 0;
        if(f->klasa != -1 && r->bohaterowie[i].klasa != (enumKlasa)f->klasa)
            pasuje = 0;
        if(f->minpoziom != -1 && r->bohaterowie[i].poziom < f->minpoziom)
            pasuje = 0;
        if(f->maxpoziom != -1 && r->bohaterowie[i].poziom > f->maxpoziom)
            pasuje = 0;
        if(f->minreputacja != -1 && r->bohaterowie[i].reputacja < f->minreputacja)
            pasuje = 0;
        if(f->maxreputacja != -1 && r->bohaterowie[i].reputacja > f->maxreputacja)
            pasuje = 0;
        if(f->status != -1 && r->bohaterowie[i].status != (enumStatus)f->status)
            pasuje = 0;
        if(pasuje) {
            wklejBohatera(wynik, r->bohaterowie[i]);
        }
    }
}

void wyswietlBohaterow(Rejestr* r) { //wyswietla wszystkich bohaterow z podanego rejestru
    if (r->rozmiar == 0) {
        printf("Brak bohaterow do wyswietlenia.\n");
        return;
    }
    for(int i = 0; i < r->rozmiar; i++) {
        Bohater b = r->bohaterowie[i];
        printf("Bohater %d:\n", i+1);
        printf("Imie: %s\n", b.imie);
        printf("Rasa: %s\n", b.rasa);
        printf("Klasa: %s\n", klasaNaTekst(b.klasa));
        printf("Poziom: %d\n", b.poziom);
        printf("Reputacja: %d\n", b.reputacja);
        printf("Status: %s\n", statusNaTekst(b.status));
        printf("-----------------------\n");
    }
}

#ifndef REJESTR_H
#define REJESTR_H

#include "bohater.h"
typedef struct Element{
    Bohater dane;
    struct Element *nastepny;
}Element;
typedef struct Rejestr{
    Element *glowa;
    int rozmiar;
}Rejestr;
typedef struct {
    char imie[IMIE_DLUGOSC];
    char rasa[TEKST_DLUGOSC];
    int klasa;
    int minpoziom;
    int maxpoziom;
    int minreputacja;
    int maxreputacja;
    int status;
} Filtry;
void dodajRejestr(Rejestr* r);
void wklejBohatera(Rejestr* r, Bohater b);
void ustawFiltry(Filtry* f);
void filtruj(Rejestr* r, Filtry* f, Rejestr* wynik);
void wyswietlBohaterow(Rejestr* r);
#endif

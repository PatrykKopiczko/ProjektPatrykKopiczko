#ifndef BOHATER_H
#define BOHATER_H

#define IMIE_DLUGOSC 100
#define TEKST_DLUGOSC 50

struct Rejestr;
typedef struct Rejestr Rejestr;
typedef enum {
    AKTYWNY,
    NA_MISJI,
    RANNY,
    ZAGINIONY,
    ZAWIESZONY
} enumStatus;

typedef enum {
    WOJOWNIK,
    MAG,
    KAPLAN,
    LOTRZYK,
    LOWCA,
    DRUID
} enumKlasa;

typedef struct {
    char imie[IMIE_DLUGOSC];
    char rasa[TEKST_DLUGOSC];
    enumKlasa klasa;
    int poziom;
    int reputacja;
    enumStatus status;
} Bohater;
void nowyBohatera(Bohater *b);
void atrybutyBohatera(Bohater *b);
void zmienBohatera(Rejestr *r);
char* statusNaTekst(enumStatus status);
char* klasaNaTekst(enumKlasa klasa);

#endif

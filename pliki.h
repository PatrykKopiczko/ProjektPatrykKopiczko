#ifndef PLIKI_H
#define PLIKI_H

#include "rejestr.h"

int zapiszDoPliku(Rejestr *r, const char *filename);
int wczytajZPliku(Rejestr *r, const char *filename);
void nazwaPliku(char *filename);

#endif

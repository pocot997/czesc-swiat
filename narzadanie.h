#ifndef NARZADANIE_H
#define NARZADANIE_H

int pesel_na_rzadanie(Pesel **glowa);

int plec_na_rzadanie(Pesel *glowa);

void kobieta(Pesel *glowa);

void mezczyzna(Pesel *glowa);

void seria_na_rzadanie(Pesel *glowa);

void stulecie_na_rzadanie(Pesel *glowa, char *data);

int data_na_rzadanie(Pesel *glowa);

#endif // NARZADANIE_H

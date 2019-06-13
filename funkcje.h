#ifndef FUNKCJE_H
#define FUNKCJE_H

typedef struct P
{
    int numer[11];
    struct P* next;
} Pesel;

typedef struct G
{
    Pesel** glowa_u;
    Pesel** glowa_g;
    Pesel** glowa_n;
    Pesel** glowa_p;
} Glowy;

int rozmiar_listy(Pesel* glowa);

int informacje();

void plec(Pesel* glowa);

void usun(Pesel** glowa);

void zakoncz(Glowy abc, char* nazwa);

int rok_przestepny(Pesel *glowa);

void data_urodzenia(Pesel *glowa);

void menu(Glowy abc);

int wybor_opcji(Glowy abc, int wybor);

void zapisz(Glowy abc, char *nazwa);

void zapisz_liste(Pesel *glowa, FILE *fp, int jaka_lista);

void jaka_lista(FILE *fp, int jaka_lista);

void wypisz(Pesel *glowa);

Glowy nowe_glowy();

void dodano_pesel();

char* plik_wyjsciowy(int argc, char ** argv);

char* plik_wejsciowy(int argc, char ** argv);

int wczytaj(char* nazwa_in, Pesel** glowa, char* tab);

int wczytaj_z_pliku(Pesel **glowa, char *nazwa_in);

#endif // FUNKCJE_H

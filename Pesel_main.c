#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funkcje.h"

int main(int argc, char** argv)
{
    srand(time(0));
    char* nazwa_in=plik_wejsciowy(argc, argv);
    char* nazwa_out=plik_wyjsciowy(argc, argv);
    Glowy abc = nowe_glowy();
    menu(abc);
    wczytaj_z_pliku(abc.glowa_p, nazwa_in);
    zakoncz(abc, nazwa_out);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "funkcje.h"
#include "wpisz.h"

int dodaj(Pesel** glowa)
{
    Pesel* nowy = (Pesel*)malloc(sizeof(Pesel));
    if(pobierz_numer(nowy))
    {
        if(sprawdz(nowy))
        {
            nowy->next = *glowa;
            *glowa = nowy;
            dodano_pesel();
            return 1;
        }
    }
    printf("Podany numer pesel nie jest poprawny");
    getchar();
    free(nowy);
    return 0;
}

int pobierz_numer(Pesel *glowa)
{
    if(!glowa)
        return 0;
    printf("Prosze podac nowy Pesel: ");
    char nrPesel [12];
    scanf("%11s", nrPesel);
    for(int i=0; i<11; i++)
    {
        if(!isdigit(nrPesel[i]))
        {
            printf("Niepoprawny numer pesel\n");
            return 0;
        }
        glowa->numer[i] = nrPesel[i]-48;
    }
    return 1;
}

int sprawdz(Pesel* glowa)
{
    int pom=29, kontrolna=0;
    for(int i=0; i<10; i++)
    {
        if(pom%10==5)
            pom-=2;
        kontrolna += glowa->numer[i] * pom%10;
        pom-=2;
    }
    if(kontrolna%10==glowa->numer[10])
        return 1;

    return 0;
}

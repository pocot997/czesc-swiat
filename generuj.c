#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "funkcje.h"
#include "generuj.h"

void generuj_stulecie(Pesel *glowa)
{
    int stulecie = (rand()%5);
    int pom = 8;
    for(int i=0; i<5; i++)
    {
        if(stulecie==i)
        {
            glowa->numer[2]=(pom%10);
        }
        pom+=2;
    }
}

void generuj_rok(Pesel *glowa)
{
    int rok = (rand()%100);
    glowa->numer[0]=rok/10;
    glowa->numer[1]=rok%10;
}

void generuj_miesiac(Pesel *glowa)
{
    int miesiac = 1+ (rand()%12);
    if(miesiac>=10)
        glowa->numer[2]+=1;

    glowa->numer[3]= miesiac%10;
}

void generuj_dzien(Pesel *glowa)
{
    if((glowa->numer[2]%2==0)&&(glowa->numer[3]==2))
    {
        luty(glowa);
    }
    else if((glowa->numer[3]==4)||(glowa->numer[3]==6)||(glowa->numer[3]==9)||((glowa->numer[2]%2==1)&&(glowa->numer[3]==1)))
    {
        dni_30(glowa);
    }
    else
    {
        dni_31(glowa);
    }
}

void luty(Pesel *glowa)
{
    int dzien = 1 + rand()%rok_przestepny(glowa);
    glowa->numer[4]=(dzien/10);
    glowa->numer[5]=(dzien%10);
}

void dni_30(Pesel *glowa)
{
    int dzien = 1 + (rand()%30);
    glowa->numer[4]=dzien/10;
    glowa->numer[5]=dzien%10;
}

void dni_31(Pesel *glowa)
{
    int dzien = 1 + (rand()%31);
    glowa->numer[4]=dzien/10;
    glowa->numer[5]=dzien%10;
}

void generuj_serie(Pesel *glowa)
{
    for(int i=6; i<10; i++)
        glowa->numer[i] = rand()%10;
    int pom=29, kontrolna=0;
    for(int i=0; i<10; i++)
    {
        if(pom%10==5)
            pom-=2;
        kontrolna += glowa->numer[i] * pom%10;
        pom-=2;
    }
    glowa->numer[10]=kontrolna%10;
}

int generuj_pesel(Pesel **glowa)
{
    void (*ptr)(Pesel*) = &generuj_serie;
    Pesel* nowy = (Pesel*)malloc(sizeof(Pesel));
    if(!nowy)
        return 0;
    generuj_stulecie(nowy);
    generuj_rok(nowy);
    generuj_miesiac(nowy);
    generuj_dzien(nowy);
    (*ptr)(nowy);
    nowy->next = *glowa;
    *glowa = nowy;
    dodano_pesel();
    return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "funkcje.h"
#include "narzadanie.h"

int pesel_na_rzadanie(Pesel **glowa)
{
    Pesel* nowy = (Pesel*)malloc(sizeof(Pesel));
    if(!nowy)
        return 0;
    data_na_rzadanie(nowy);
    plec_na_rzadanie(nowy);
    seria_na_rzadanie(nowy);
    nowy->next = *glowa;
    *glowa = nowy;
    dodano_pesel();
    return 1;
}

int data_na_rzadanie(Pesel *glowa)
{
    printf("Prosze podac date urodzenia w formacie RRRRMMDD: ");
    char data [8];
    scanf("%8s", data);
    for(int i=0; i<8; i++)
    {
        if(!isdigit(data[i]))
        {
            printf("Niepoprawna data urodzenia\n");
            return 0;
        }
        data[i]-=48;
    }
    for(int i=2; i<8; i++)
    {
        glowa->numer[i-2]=data[i];
    }
    stulecie_na_rzadanie(glowa, data);
    return 1;
}

void stulecie_na_rzadanie(Pesel *glowa, char *data)
{
    int stulecie = (*data)*10 + *(data+1), pom = 18, licznik=8;
    while(stulecie!=pom)
    {
        pom++;
        licznik+=2;
    }
    glowa->numer[2]+=licznik%10;
}

int plec_na_rzadanie(Pesel *glowa)
{
    printf("Prosze podac plec: ");
    char plec;
    getchar();
    scanf("%c", &plec);
    if((plec=='k')||(plec=='K'))
        kobieta(glowa);
    else if((plec=='m')||(plec=='M'))
        mezczyzna(glowa);
    else
    {
        printf("Bledne dane\n");
        return 0;
    }
    return 1;
}

void seria_na_rzadanie(Pesel *glowa)
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

void kobieta(Pesel *glowa)
{
    int a = rand()%10;
    while(a%2!=0)
    {
        a=rand()%10;
    }
    glowa->numer[9] = a;
}

void mezczyzna(Pesel *glowa)
{
    int a = rand()%10;
    while(a%2!=1)
    {
        a=rand()%10;
    }
    glowa->numer[9] = a;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "funkcje.h"
#include "wpisz.h"
#include "generuj.h"
#include "narzadanie.h"

void dodano_pesel()
{
    system("cls");
    printf("Pesel dodano do bazy danych\nPress ENTER to continue:");
    getchar();
    getchar();
}

int rozmiar_listy(Pesel* glowa)
{
    int d = 0;
    Pesel* wsk = glowa;
    while(wsk != NULL)
    {
        d++;
        wsk = wsk->next;
    }
    return d;
}

int informacje()
{
    Pesel* nowy = (Pesel*)malloc(sizeof(Pesel));
    if(!nowy)
        return 0;
    pobierz_numer(nowy);
    data_urodzenia(nowy);
    plec(nowy);
    free(nowy);
    printf("Press ENTER to continue:");
    getchar();
    getchar();
    return 1;
}

void data_urodzenia(Pesel *glowa)
{
    int r_p = 18, pom = 8;
    while(glowa->numer[2]!=pom%10)
    {
        pom+=2;
        r_p++;
    }
    int rok=r_p*100 + glowa->numer[0]*10 + glowa->numer[1];
    printf("Data urodzenia: %d%d.%d%d.%d\n", glowa->numer[4], glowa->numer[5], (glowa->numer[2]-pom%10), glowa->numer[3], rok);
}

void plec(Pesel* glowa)
{
    char plec;
    if(glowa->numer[9]%2==0)
        plec='K';
    else
        plec='M';
    printf("Plec: %c\n", plec);
}

void usun(Pesel** glowa)
{
    while(*glowa)
    {
        Pesel* wsk = (*glowa)->next;
        free(*glowa);
        *glowa = wsk;
    }
}

void zakoncz(Glowy abc, char *nazwa)
{
    zapisz(abc, nazwa);
    usun(abc.glowa_u);
    usun(abc.glowa_g);
    usun(abc.glowa_n);
    free(abc.glowa_u);
    free(abc.glowa_g);
    free(abc.glowa_n);
}

int rok_przestepny(Pesel *glowa)
{
    int r_p = 18, pom = 8;
    while(glowa->numer[2]!=pom%10)
    {
        pom+=2;
        r_p++;
    }
    int rok=r_p*100 + glowa->numer[0]*10 + glowa->numer[1];
    if(((rok%4==0)&&(rok%100!=0))||(rok%400==0))
        return 29;
    else
        return 28;
}

void wypisz(Pesel *glowa)
{
    Pesel* wsk = glowa;
    while(wsk != NULL)
    {
        for(int i =0; i<11; i++)
        {
            printf("%d", wsk->numer[i]);
        }
        printf("\n");
        wsk = wsk->next;
    }
}

Glowy nowe_glowy()
{
    Glowy nowy;
    nowy.glowa_u = (Pesel**)malloc(sizeof(Pesel*));
    nowy.glowa_g = (Pesel**)malloc(sizeof(Pesel*));
    nowy.glowa_n = (Pesel**)malloc(sizeof(Pesel*));
    nowy.glowa_p = (Pesel**)malloc(sizeof(Pesel*));
    *(nowy.glowa_u)=NULL;
    *(nowy.glowa_g)=NULL;
    *(nowy.glowa_n)=NULL;
    *(nowy.glowa_p)=NULL;
    return nowy;
}

void menu(Glowy abc)
{
    int wybor;
    while(1)
    {
        system("cls");
        printf("Nacisnij odpowieni klawisz aby przejsc dalej:\n[1] wprowadz pesel \n[2] wygeneruj losowy pesel \n[3] utworz pesel z podanych danych\n[4] wypisz informacje na podstawie peselu\n[5] zakoncz program\n");
        scanf("%d", &wybor);
        if (wybor_opcji(abc, wybor)==1)
            break;
    }
}

int wybor_opcji(Glowy abc, int wybor)
{
    if((wybor==1) && dodaj(abc.glowa_u))
        return 0;
    else if((wybor==2) && generuj_pesel(abc.glowa_g))
        return 0;
    else if((wybor==3) && pesel_na_rzadanie(abc.glowa_n))
        return 0;
    else if((wybor==4) && informacje())
        return 0;
    else if(wybor==5)
        return 1;
    else
    {
        printf("Blad");
        getchar();
        return 0;
    }
}

void zapisz(Glowy abc, char *nazwa)
{
    FILE *fp;
    fp = fopen(nazwa, "w");
    if(fp==NULL)
        printf("Blad otwarcia pliku");
    else
    {
        zapisz_liste(*(abc.glowa_u), fp, 1);
        zapisz_liste(*(abc.glowa_g), fp, 2);
        zapisz_liste(*(abc.glowa_n), fp, 3);
        zapisz_liste(*(abc.glowa_p), fp, 4);
    }
    fclose(fp);
}

void zapisz_liste(Pesel *glowa, FILE *fp, int jaka_l)
{
    Pesel* wsk = glowa;
    if(glowa == NULL){}
    else
    {
        jaka_lista(fp, jaka_l);
        while( wsk != NULL)
        {
            for(int i =0; i<11; i++)
            {
                fprintf(fp, "%d", wsk->numer[i]);
            }
            fprintf(fp, "\n");
            wsk=wsk->next;
        }
    }
}

void jaka_lista(FILE *fp, int jaka_lista)
{
    if(jaka_lista==1)
        fprintf(fp, "Pesele dodane przez urzytkownika:\n");
    else if(jaka_lista==2)
        fprintf(fp, "Pesele wygenerowane losowo:\n");
    else if(jaka_lista==3)
        fprintf(fp, "Pesele wygenerowane z podanych danych:\n");
    else if(jaka_lista==4)
        fprintf(fp, "Pesele z pliku wejsciowego:\n");
}

char* plik_wyjsciowy(int argc, char ** argv)
{
    char* nazwa_out = "out.txt";
	if (argc == 0)
		return nazwa_out;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "/i") == 0)
		{
			nazwa_out = malloc(strlen(argv[i + 1]) * sizeof(char));
			nazwa_out = argv[i + 1];
		}
	}
	return nazwa_out;
}

char* plik_wejsciowy(int argc, char ** argv)
{
    char* nazwa_in = "in.txt";
	if (argc == 0)
		return nazwa_in;

    for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "/o") == 0)
		{
			nazwa_in = malloc(strlen(argv[i + 1]) * sizeof(char));
			nazwa_in = argv[i + 1];
		}
	}
	return nazwa_in;
}

int wczytaj(char* nazwa_in, Pesel** glowa, char* tab)
{
    Pesel* nowy = (Pesel*)malloc(sizeof(Pesel));
    if(nowy)
    {
        for(int i=0; i<11; i++)
            nowy->numer[i]=*(tab+i)-48;
        nowy->next = *glowa;
        *glowa = nowy;
        return 1;
    }
    free(nowy);
    return 0;
}

int wczytaj_z_pliku(Pesel **glowa, char *nazwa_in)
{
    FILE *fp;
    fp = fopen(nazwa_in, "r");
    if (fp == NULL)
    {
        printf("Brak pliku wejsciowego");
        return 0;
    }
    else
    {
        int c = getc(fp);
        char pom;
        char tab[11];
        while (c != EOF)
        {
            for(int i=0; i<11; i++)
                fscanf(fp, "%c", &tab[i]);

            fscanf(fp, "%c", &pom);
            c = getc(fp);
            wczytaj(nazwa_in, glowa, tab);
        }
    }
    fclose(fp);
    return 1;
}


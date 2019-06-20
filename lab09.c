#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* plik_wyjsciowy(int argc, char ** argv, FILE* plik)
{
    fprintf(plik, "Rozpoczeto zczytywanie argumntow wiersza polecen\n");
    char* nazwa_out = "out.txt";
	if (argc == 0)
		{
        fprintf(plik, "Uzyto domyslnej nazwy pliku wyjsciowego");
        return nazwa_out;
    }
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "/i") == 0)
		{
			nazwa_out = malloc(strlen(argv[i + 1]) * sizeof(char));
			nazwa_out = argv[i + 1];
		}
	}
	fprintf(plik, "Sczytano nazwe pliku wyjsciowego z wiersza polecen\n");
	return nazwa_out;
}

char* plik_wejsciowy(int argc, char ** argv, FILE* plik)
{
    char* nazwa_in = "in.txt";
	if (argc == 0)
	{
        fprintf(plik, "Uzyto domyslnej nazwy pliku wejsciowego");
        return nazwa_in;
    }
    for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "/o") == 0)
		{
			nazwa_in = malloc(strlen(argv[i + 1]) * sizeof(char));
			nazwa_in = argv[i + 1];
		}
	}
	fprintf(plik, "Sczytano nazwe pliku wejsciowego z wiersza polecen\n");
	return nazwa_in;
}

char* plik_json(int argc, char ** argv, FILE* plik)
{
    char* nazwa_json = "json.json";
	if (argc == 0)
    {
        fprintf(plik, "Uzyto domyslnej nazwy pliku JSON");
        return nazwa_json;
    }


    for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "/o") == 0)
		{
			nazwa_json = malloc(strlen(argv[i + 1]) * sizeof(char));
			nazwa_json = argv[i + 1];
		}
	}
	fprintf(plik, "Sczytano nazwe pliku JSON z wiersza polecen\n");
	return nazwa_json;
}

void konwertuj(int liczba, FILE* fp_out, FILE* fp_json, int numer)
{
    int licznik = 1;
    float pom=liczba;
    while((pom/16)>=1)
    {
        licznik++;
        pom=pom/16;
    }
    char* liczba_pk = malloc((licznik+1) * sizeof(char));
    for(int i=licznik-1; i>-1; i--)
    {
         if(liczba%16>9)
         {
            switch(liczba%16)
            {
               case 10:
                  *(liczba_pk+i) = 'A'; break;
               case 11:
                  *(liczba_pk+i) = 'B'; break;
               case 12:
                  *(liczba_pk+i) = 'C'; break;
               case 13:
                  *(liczba_pk+i) = 'D'; break;
               case 14:
                  *(liczba_pk+i) = 'E'; break;
               case 15:
                  *(liczba_pk+i) = 'F'; break;
            }
         }
        else
            *(liczba_pk+i) = liczba%16+48;
        liczba=liczba/16;
    }
    *(liczba_pk+licznik)='\0';
    fprintf(fp_out,"%s\n", liczba_pk);
    fprintf(fp_json,"{ \"liczba nr%d\" : \"%s\" },\n", numer, liczba_pk);
}

int wczytaj_liczby(char* nazwa_in, int* tab, int* licznik, FILE* plik)
{
    FILE* fp = fopen (nazwa_in, "r");
    int pom=0;
    if (fp == NULL)
    {
        return 0;
    }
    fprintf(plik, "Rozpoczeto zczytywanie liczb z pliku wejsciowego\n");
    while (!feof (fp))
    {
        fscanf (fp, "%d", &pom);
        *(tab+(*licznik))=pom;
        (*licznik)++;
    }
    fclose (fp);
    fprintf(plik, "Zakonczono zczytywanie liczb z pliku wejsciowego\n");
    return 1;
}

void zapisz_do_pliku(char* nazwa_out, int* tab, int licznik, FILE* plik, char* nazwa_json)
{
    FILE *fp_out = fopen(nazwa_out, "w");
    fprintf(plik, "Otwarto plik wyjsciowy\n");
    FILE* fp_json = fopen(nazwa_json, "w");
    fprintf(plik, "Otwarto plik JSON\n");
    fprintf(plik, "Rozpoczeto konwertowanie liczb na system szesnastkowy\n");
    fprintf(plik, "Rozpoczeto zapis do plikow\n");
    fprintf(fp_json, "{\n\"Liczby po konwersji\" : [\n");
    int numer=1;
    for(int i =0; i<licznik;i++)
    {
        konwertuj(*(tab+i), fp_out, fp_json, numer);
        numer++;
    }

    fprintf(fp_json, "] \n}");
    fprintf(plik, "Zakonczono konwertowanie liczb na system szesnastkowy\n");
    fprintf(plik, "Zakonczono zapis do pliku\n");
    fclose(fp_out);
    fclose(fp_json);
    fprintf(plik, "Zamknieto plik wyjsciowy\n");
    fprintf(plik, "Zamknieto plik JSON\n");
}

int main(int argc, char** argv)
{
    FILE* plik = fopen("log.txt", "w");
    if (argc == 0)
    {
        fprintf(plik, "Brak argumentow wiersza polecen\n");
        return 0;
    }
    char* nazwa_in = plik_wejsciowy(argc, argv, plik);
    char* nazwa_out = plik_wyjsciowy(argc, argv, plik);
    char* nazwa_json = plik_json(argc, argv, plik);
    int tab[64];
    int licznik=0;
    if (!wczytaj_liczby(nazwa_in, tab, &licznik, plik))
    {
        fprintf(plik, "Brak pliku wejsciowego\n");
        return 0;
    }
    zapisz_do_pliku(nazwa_out, tab, licznik, plik, nazwa_json);
    fprintf(plik, "Program wykonal sie poprawnie\n");
    fclose(plik);
    system("pause");
    return 0;

}

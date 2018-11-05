#include <iostream>

using namespace std;

int main()
{
int dlugosc=1, dlugosc2=0, wartosc=0, wartosc2=0, pozycja=0, pozycja2=0, k;

int tab[10]={1,2,2,2,2,4,4,5,6,6};

for(int i=0; i<10; i++){

k=i;
        while(tab[k]==tab[k+1]){
            k++;
            dlugosc++;
            wartosc=tab[i];
            pozycja=i+1;

        }

        if(dlugosc>dlugosc2){
            dlugosc2=dlugosc;
            wartosc2=wartosc;
            pozycja2=pozycja;
        }


            dlugosc=1;
            wartosc=0;
            pozycja=0;





}
cout<<"Ciag sklada sie z "<< dlugosc2 << " elementow o wartosci "<< wartosc2 << ", a pierwszy wyraz tego ciagu lezy na " << pozycja2 <<" pozycji" << endl;
    return( 0 );
}


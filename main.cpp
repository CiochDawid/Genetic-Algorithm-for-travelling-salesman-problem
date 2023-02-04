#include <iostream>
#include <math.h>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>




using namespace std;


int n = 30;
int i,j,k,p,p1,p2,z,x,los1,los2;
int M[30][30]; //Macierz sąsiedztwa


int P[300][32]; //Tablica do tworzenia populacji, P[i][30] bedzie przechowywac dlugosci cykli


int liczba_osobnikow = 4; //tyle bedzie wynosic populacja, ruchome
int liczba_krzyzowan = liczba_osobnikow/2; //liczna najlepszych osobnikow, bioracych udzial w reprodukcji
int losowe_krzyzowanie = 2; //wskazuje na liczbe wykonanych krzyzowan w kolejnych pokoleniach


int lokalne_min = 10000;
int optymalna_trasa;
int X[30];


int licznik = 0;
int wpisz;
int sprawdz;
int wstaw;


void sortowanie_szybkie(int l, int p)
{
        i = l;
        j = p;
        x = P[rand()%(liczba_osobnikow+licznik-1)][n];
        while( i <= j)
        {
                while(P[i][n] < x) i++;
                while(P[j][n] > x) j--;
                if(i <= j)
                {
                        for(k = 0; k <= n; k++)
                        {
                                z = P[i][k];
                                P[i][k] = P[j][k];
                                P[j][k] = z;
                        }
                        i++;
                        j--;
                }
        }
        if(j > l) sortowanie_szybkie(l,j);
        if(i < p) sortowanie_szybkie(i,p);
}


void wypisywanie_dwuwymiarowa(int y1, int y2)
{
        for(i = 0; i < y1; i++)
        {
                for(j = 0; j < y2; j++)
                {
                        cout<<P[i][j]<<" ";
                }
                cout<<endl;
        }
}


void szukanie_minimalnej_trasy()
{


        for(j = 0; j < liczba_osobnikow + licznik; j++)
        {
                if(P[j][n] < lokalne_min)
                {
                        for(k = 0; k < n; k++)
                        {
                                X[k] = P[j][k];
                        }
                lokalne_min = P[j][n];
                }
        }
        optymalna_trasa = lokalne_min;
}


void dlugosc_cyklu(int c)
{
        for(k = 0; k < n; k++)
        {
                P[c][n] = M[ P[c][k] ][ P[c][ (k+1)%n ]] + P[c][n];
        }
}


void tworzenie_populacji()
{


        for(i = 0; i < liczba_osobnikow; i++)
                for(j = 0; j < n; j++)
                        P[i][j] = j;



        for(i = 0; i < liczba_osobnikow; i++)
                for(j = n; j > 1; j--)
                {
                        p = 1 + (rand()%j)%(j-1);
                        z = P[i][p];
                        P[i][p] = P[i][j-1];
                        P[i][j-1] = z;
                }

        for(i = 0; i < liczba_osobnikow; i++) P[i][n] = 0;

        cout<<"Wygenerowane cykle"<<endl;


        wypisywanie_dwuwymiarowa(liczba_osobnikow,n+1);

        for(i = 0; i < liczba_osobnikow; i++)
        {
                dlugosc_cyklu(i);
        }

        szukanie_minimalnej_trasy();
        cout<<endl;
        cout<<"Wygenerowane cykle z ich dlugoscia"<<endl;
        wypisywanie_dwuwymiarowa(liczba_osobnikow,n+1);
        sortowanie_szybkie(0,liczba_osobnikow - 1);
        cout<<endl;
        cout<<"Wygenerowane cykle z ich dlugoscia - posortowane"<<endl;
        wypisywanie_dwuwymiarowa(liczba_osobnikow,n+1);
}


void krzyzowanie_dwoch_osobnikow(int a, int b)
{
        int c1 = rand()%(n-6)+3;
        int c2 = rand()%(n-6)+3;
        cout<<endl<<c1<<" "<<c2<<endl;


        for(i = 0; i <= c1; i++)
        {
                P[liczba_osobnikow][i] = P[a][i];
        }


        wpisz = 0;
        wstaw = 0;


        for(i = 1; i < n; i++)
        {
                sprawdz = 0;
                wpisz++;
                for(j = 1; j <= c1; j++)
                {
                        if(P[a][j] != P[b][i])
                        {
                                sprawdz++;
                                if(sprawdz == c1)
                                {
                                        wstaw++;
P[liczba_osobnikow][c1 + wstaw] = P[b][wpisz];
                                }
                        }
                        else break;
                }
        }


        dlugosc_cyklu(liczba_osobnikow);

        for(i = 1; i <= n + 1 - c2; i++)
        {
                P[liczba_osobnikow + 1][i] = P[b][n + 1 - i];
        }
        P[liczba_osobnikow + 1][0] = 0;


        wpisz = 0;
        wstaw = 0;


for(i = 1; i < n; i++)
        {
                sprawdz = 0;
                for(j = c2; j <= n - 1; j++)
                {
                        if(P[a][i] != P[b][j])
                        {
                                sprawdz++;
                                if(sprawdz == (n + 1 - c2))
                                {
                                        wstaw++;
P[liczba_osobnikow + 1][n - c2 + wstaw] = P[a][i];
                                }
                        }
                        else break;
                }
        }




        dlugosc_cyklu(liczba_osobnikow + 1);
}


void zamienianie_wierszy(int c, int d)
{
        for(int m = 0; m < n  + 1; m++)
        {
                z = P[c][m];
                P[c][m] = P[d][m];
                P[d][m] = z;
        }
}


void usun_powtorzenia()
{
        for(i = 0; i < liczba_osobnikow + licznik; i++)
        {
                for(j = i+1; j < liczba_osobnikow + licznik; j++)
                {
                        if(P[i][n] == P[j][n])
{
        for(k = j; k < liczba_osobnikow + licznik - 1; k++)
        {
                zamienianie_wierszy(k,k+1);
        }
        licznik--;
                        }
                }
        }
}


void mutacja_pierwsza()
{
        los1 = rand()%(n - 1) + 1; // losowanie numeru kolumny
        los2 = rand()%(n - 1) + 1;
        while(los1 == los2)
        {
                los2 = rand()%(n - 1) + 1;
        }


int p3 = rand()%(liczba_krzyzowan); //losowanie wiersza


        for(i = 0 ; i < n; i++)
        {
                P[liczba_osobnikow + 2][i] = P[p3][i];
        }
        P[liczba_osobnikow + 2][los1] = P[p3][los2];
P[liczba_osobnikow + 2][los2] = P[p3][los1];


        dlugosc_cyklu(liczba_osobnikow + 2);
}


void mutacja_druga()
{
int los3; //miejsce wstawienia fragmentu los2-los1;


        los2 = rand()%(n/2 - 4)+3;
los1 = rand()%(los2 - 2) + 1;
los3 = rand()%(n/2 - 2) + 16; //los1 < los2


int p4 = rand()%(liczba_krzyzowan); //losowanie wiersza




for(i = 0; i < los1; i++)
{
P[liczba_osobnikow + 3][i] = P[p4][i];
}


wpisz = los1 - 1;


for(i = los2 + 1; i < los3; i++)
{
        wpisz++;
        P[liczba_osobnikow + 3][wpisz] = P[p4][i];
}


for(i = los1; i <= los2; i++)
{
        wpisz++;
        P[liczba_osobnikow + 3][wpisz] = P[p4][i];
}


for(i = los3; i < n; i++)
{
        wpisz++;
        P[liczba_osobnikow + 3][wpisz] = P[p4][i];
}


        dlugosc_cyklu(liczba_osobnikow + 3);
}


main()
{
        srand(time(0));

        ifstream plik("miasta.txt");
                   for(i = 0; i < n; i++)
               {
                for(j = 0; j < n; j++)
{
                                plik >> M[i][j];
}
        }



        tworzenie_populacji();


        for(int f = 0; f < losowe_krzyzowanie; f++)
        {
                p1 = rand()%(liczba_krzyzowan);
                p2 = rand()%(liczba_krzyzowan);


                while(p1 == p2)
                {
                        p2 = rand()%(liczba_krzyzowan);
                }


                cout<<endl<<p1<<" "<<p2<<endl;
                cout<<endl<<"Osobniki po "<<f<<" krzyzowaniu"<<endl;


                krzyzowanie_dwoch_osobnikow(p1,p2);


                mutacja_pierwsza();

                mutacja_druga();

                licznik = 3;

                sortowanie_szybkie(0,liczba_osobnikow + licznik - 1);


                wypisywanie_dwuwymiarowa(liczba_osobnikow + 3, n + 1);


                usun_powtorzenia();


szukanie_minimalnej_trasy();
        }


        cout<<endl;
        for(i = 0; i < n; i++)
                cout<<X[i]<<" ";
        cout<<endl;
        return optymalna_trasa;
}
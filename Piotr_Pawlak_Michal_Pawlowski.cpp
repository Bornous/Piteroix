#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

const double epsilon=1e-10;

void Zestaw1(double **tab);//zestaw danych
void Zestaw2(double **tab);//zestaw danych
void Pokaz(double **tab,int n);//pokazuje macierz
int WybierzZestaw();//wybieramy zestaw danych
int WybierzMetode();//wybieramy metode
int ZwracanieN(int dane);//zwraca nam wielkosc macierzy
void Wybor(int metoda,int dane, int n);//skladmy wszytkie wybory poprzednie w jedno
void GaussPodstawowy(double **wspolczynnik,int n);
void GaussKolumny(double **wspolczynnik,int n);
void GaussPelny(double **wspolczynnik,int n);//oblicza gausa plenego
void MaxElementKolumna(double ** wspolczynnik,int &wiersz,int krok, int n);
void MaxElement(double ** wspolczynnik,int &wiersz,int &kolumna,int krok,int n);//wyszukje maksymalny element
void ZamianaWierszy(double **wspolczynnik,int krok,int wiersz,int n);//zamienia wiersze
void ZamianaKolumn(double **wspolczynnik,int krok,int kolumna,int *kolumnyzam,int n);//zamienia kolumny
bool Poprawnosc(double **wspolczynnik,int n);//sprawdzamy poprawnosc
bool Kroczek(double **wspolczynnik,int krok,int n);
void Zerowanie(double **wspolczynnik,int n);
void Niewiadome(double **wspolczynnik,int n,int *kolumnyzam);

int main()
{
    int dane,metoda,n;
    dane=WybierzZestaw();
    metoda=WybierzMetode();
    n=ZwracanieN(dane);
    Wybor(metoda,dane,n);

    return 0;
}

void Zestaw1(double **tab)
{
    tab[0][0]=0; tab[0][1]=1; tab[0][2]=2; tab[0][3]=3; tab[0][4]=8;
    tab[1][0]=1; tab[1][1]=0; tab[1][2]=1; tab[1][3]=2; tab[1][4]=4;
    tab[2][0]=1; tab[2][1]=2; tab[2][2]=3; tab[2][3]=4; tab[2][4]=10;
    tab[3][0]=0; tab[3][1]=1; tab[3][2]=3; tab[3][3]=2; tab[3][4]=7;
}

void Zestaw2(double **tab)
{
    tab[0][0]=2; tab[0][1]=3; tab[0][2]=-4; tab[0][3]=9;
    tab[1][0]=1; tab[1][1]=2; tab[1][2]=-2; tab[1][3]=7;
    tab[2][0]=4; tab[2][1]=-2; tab[2][2]=5; tab[2][3]=-5;
}

void Pokaz(double **tab,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            cout<<tab[i][j]<<",";
        }
        cout<<endl;
    }
}

void Wybor(int metoda,int dane, int n)
{
    double **wspolczynnik=new double *[n];
    for(int i=0;i<n;i++)
    {
        wspolczynnik[i]=new double[n+1];
    }
    if(dane==1)
        Zestaw1(wspolczynnik);
    else if(dane==2)
        Zestaw2(wspolczynnik);
    else if(dane==3)
    {

    }
    else
    {
        cout<<"Zle wybrales zestaw!!!"<<endl;
        exit(0);
    }

    if(metoda==1)
    {
        Pokaz(wspolczynnik,n);
    }
    else if(metoda==2)
    {

    }
    else if(metoda==3)
    {
        GaussPelny(wspolczynnik,n);
    }
    else
    {
        cout<<"zle wybrales metode!!"<<endl;
    }
}

int ZwracanieN(int dane)
{
    int n=0;
    if(dane==1)
        return n=4;
    else if(dane==2)
        return n=3;
    else if(dane==3)
    {
        return n;
    }
    else
    {
        cout<<"Zle wybrales zestaw!!!"<<endl;
        exit(0);
    }
}

int WybierzZestaw()
{
    int wybor;

    cout<<"Wybierz zestaw danych:"<<endl;
    cout<<"1. Zestaw 1"<<endl;
    cout<<"2. Zestaw 2"<<endl;
    cout<<"3. Wpisz wlasne dane"<<endl;
    cin>>wybor;

    return wybor;
}

int WybierzMetode()
{
    int opcja,n;

    cout<<"Wybierz metode:"<<endl;
    cout<<"1. Gauss podstawowy"<<endl;
    cout<<"2. Gauss z wyszukaniem elementu maksymalnego w kolumnie"<<endl;
    cout<<"3. Gauss z wyszukaniem elementu maksymalnego w macierzy"<<endl;
    cin>>opcja;

    return opcja;
}

void MaxElementKolumna(double ** wspolczynnik,int &wiersz,int krok, int n)
{
    wiersz=krok;
    double maks;
    maks=wspolczynnik[krok][krok];

    for(int i=krok;i<n; i++)
    {
        if(fabs(wspolczynnik[i][krok]) > maks)
        {
            maks = fabs(wspolczynnik[i][krok]);
            wiersz=i;
        }
    }
}


void MaxElement(double ** wspolczynnik,int &wiersz,int &kolumna,int krok,int n)
{
    wiersz=krok;
    kolumna=krok;

    double maks;
    maks=wspolczynnik[krok][krok];

    for(int i=krok;i<n;i++)
    {
        for(int j=krok;j<n;j++)
        {
            if(fabs(wspolczynnik[i][j])>maks)
            {
                maks=fabs(wspolczynnik[i][j]);
                wiersz=i;
                kolumna=j;
            }
        }
    }
}

void ZamianaWierszy(double **wspolczynnik,int krok,int wiersz,int n)
{
    if(wiersz==krok)
    return;
    for(int i=0;i<n+1;i++)
        swap(wspolczynnik[krok][i],wspolczynnik[wiersz][i]);
}

void ZamianaKolumn(double **wspolczynnik,int krok,int kolumna,int *kolumnyzam,int n)
{
    if(kolumna==krok)
    return;

    swap(kolumnyzam[krok],kolumnyzam[kolumna]);

    for(int j=0;j<n;j++)
        swap(wspolczynnik[j][krok],wspolczynnik[j][kolumna]);
}

bool Poprawnosc(double **wspolczynnik,int n)
{
    bool popr=false;

    for(int i=0;i<n;i++)
    {
        popr=false;

        if(fabs(wspolczynnik[i][n])<=epsilon)
        {
            popr=true;
            continue;
        }

        for(int j=0;j<n;j++)
        {
            if(fabs(wspolczynnik[i][j])>epsilon)
            {
                popr=true;
                break;
            }
        }

        if(!popr)
        {
            cout<<"Uklad sprzeczny!!!"<<endl;
            break;
        }
    }

    return popr;
}

bool Kroczek(double **wspolczynnik,int krok,int n)
{
    double wspmacierzy;

    if(fabs(wspolczynnik[krok][krok])>epsilon)
    {
        for(int i=krok+1;i<n;i++)
        {
            wspmacierzy=wspolczynnik[i][krok]/wspolczynnik[krok][krok];
            for(int j=krok;j<n+1;j++)
            {
                wspolczynnik[i][j]-=wspmacierzy*wspolczynnik[krok][j];
            }
        }
    }
    else
    {
        if(GaussPodstawowy)
            cout<<"Dzielimy przez 0!!!"<<endl;
        else
            cout<<"Uklad nieoznaczony!!!"<<endl;
        return false;
    }

    Zerowanie(wspolczynnik,n);
    return Poprawnosc(wspolczynnik,n);
}

void Zerowanie(double **wspolczynnik,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            if(fabs(wspolczynnik[i][j])<=epsilon)
                {
                    wspolczynnik[i][j]=0;
                }
        }
    }
}

void Niewiadome(double **wspolczynnik,int n,int *kolumnyzam = NULL)
{
    double suma;
    double *X=new double[n];

    if(kolumnyzam==NULL)
    {
        kolumnyzam=new int[n];
        for(int i=0;i<n;i++)
            kolumnyzam[i] = i;
    }

    X[kolumnyzam[n-1]]=wspolczynnik[n-1][n]/wspolczynnik[n-1][n-1];

    for(int i=n-2;i>=0;i--)
    {
        suma=0;
        for(int j=i+1;j<n;j++)
        {
            suma+=X[kolumnyzam[j]]*wspolczynnik[i][j];
        }

        X[kolumnyzam[i]]=(wspolczynnik[i][n]-suma)/wspolczynnik[i][i];
        if(fabs(X[kolumnyzam[i]])<=epsilon)
        {
            X[kolumnyzam[i]]=0;
        }
    }
    cout<<"Wyniki:"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<X[i]<<",";
    }
}

void GaussPodstawowy(double **wspolczynnik,int n)
{
    for(int i=0;i<n;i++)
        if(Kroczek(wspolczynnik,i,true)==false)
            return;

    Niewiadome(wspolczynnik,n);
}

void GaussKolumny(double **wspolczynnik,int n)
{
    if(Poprawnosc(wspolczynnik,n)==false)
        return;

    int wiersze;

    int *kolumnyzam=new int[n];
    for(int i=0;i<n;i++)
        kolumnyzam[i]=i;

    for(int i=0;i<n;i++)
    {
        MaxElementKolumna(wspolczynnik,wiersze,i,n);
        ZamianaWierszy(wspolczynnik,i,wiersze,n);
        if(Kroczek(wspolczynnik,i,n)==false)
            return;
    }
    Niewiadome(wspolczynnik,n,kolumnyzam);
}

void GaussPelny(double **wspolczynnik,int n)
{
    if(Poprawnosc(wspolczynnik,n)==false)
        return;

    int *kolumnyzam= new int[n];
    for(int i = 0; i < n; i++)
    kolumnyzam[i] = i;

    int krok,wiersz,kolumna;
    for(krok=0;krok<n;krok++)
    {
        MaxElement(wspolczynnik,wiersz,kolumna,krok,n);
        ZamianaWierszy(wspolczynnik,krok,wiersz,n);
        ZamianaKolumn(wspolczynnik,krok,kolumna,kolumnyzam,n);
        if(Kroczek(wspolczynnik,krok,n)==false);
        return;
    }
    Niewiadome(wspolczynnik,n,kolumnyzam);
}


#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;


// Numero massimo di sottointervalli in [a,b]
const long int Nmax = 10000;



double F( double x )
{
    double ff;
    if(abs(x) < acos(-1))
        ff = x;
    else if(x == acos(-1))
        ff = 0;
    else if(x > acos(-1) && x <= 2*acos(-1))
        ff = (x-2*acos(-1));

    
    return( ff );

}



/*
    Funzione int_trap
    calcola l'integrale di una funzione nota su N+1 punti
    con la regola dei trapezi.
    Nota che il vettore contenente i valori da integrare ha dimensione: f[N+1]!

*/
double int_trap( double f[], double h, long int N )
{
    double sum;

    sum = 0.5 * ( f[0] + f[N] );
    for( long int i = 1; i < N; i++ )
        sum += f[i];
    
    return( h * sum );
}

double coefficientian( double a, double h, double N, int n )
{
    
    double xj;
    double f[Nmax+1];

    // Definisce la funzione sui punti nodali
    for ( long int j = 0; j <= N; j++ )
    {
        xj   = a + j * h;
        f[j] = F(xj)*cos(n*xj);
    }


    // Calcolo dell'integrale definito
    double an;
    an = int_trap( f, h, N )/acos(-1);
    return an;

}

double coefficientibn( double a, double h, double N, int n)
{
    double xj;
    double g[Nmax+1];

    // Definisce la funzione sui punti nodali
    for ( long int j = 0; j <= N; j++ )
    {
        xj   = a + j * h;
        g[j] = F(xj)*sin(n*xj);
    }


    // Calcolo dell'integrale definito
    double bn;
    bn = int_trap( g, h, N )/acos(-1);
    return bn;

}

double E( int n, double an, double bn )
{
    if(n == 0)
        return(an*an/2.0);
    else if(n != 0)
        return(an*an + bn*bn);

    return 0;
}

// Main program
int main()
{
    cout << "Calcolo i coefficienti di Fourier a_n e b_n e lo spettro della funzione F(x) = (   x  [0 <= x < Pi] ;    0   [x = Pi] ;    x-2Pi   [Pi < x <= 2Pi ]   )." << endl;
    cout << "Verificherò successivamente l'identità di Parceval." << endl;
    cout << "Per n = 0,1,2,....,64:" << endl << endl;

    double a = 0, b = 2*acos(-1);
    
    long int N = 128;

    double h = ( b - a ) / N;
    
    double an,bn;
    for(int n = 0; n < 65; n++)
    {   
        an = coefficientian(a,h,N,n);
        bn = coefficientibn(a,h,N,n);
        cout << "Coefficiente a_" << n << " : " << an << "     Coefficiente b_" << n << " : " << bn << endl;

        cout << "Spettro E(" << n << ") = " << E(n,an,bn) << endl;

    }

    cout << endl << endl;
    cout << "Verifica id. Parceval: " << endl;
    
    double primomembro, secondomembro;
    
    double xj;
    double f[Nmax+1];
    for ( long int j = 0; j <= N; j++ )
    {
        xj   = a + j * h;
        f[j] = F(xj)*F(xj);
    }
    
    primomembro = int_trap(f,h,N)/acos(-1);

    double sum = 0;
    for(int i = 0; i < 65; i++)
    {
        an = coefficientian(a,h,N,i);
        bn = coefficientibn(a,h,N,i);
        sum = sum + E(i,an,bn);

    }
    secondomembro = sum;

    cout << primomembro << "  =  " << secondomembro << endl;

    return 0;

}


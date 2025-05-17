#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

const long int Nmax = 10000;

int Fatt(int n)
{
    if( n <= 1 )
	    return 1;

	else
		return( n * Fatt( n-1 ) );
}

double Gamma(int k)
{
    double gg = pow(acos(-1), 0.5) * Fatt(k-2) / pow(2, ((k-1)/2.));
    return gg;

}   

double ChiQuadro(double xj, int k)
{
    double ff;
    ff = pow(xj, ((k/2.)-1))*exp(-xj/2.) / ( pow(2, k/2.) * Gamma(k) );

    return ff;
}    

double int_simp( double f[], double h, long int N )
{
  double sump = 0.0, sumd = 0.0;

  for( long int j = 2; j <= N - 2; j = j + 2 )
    sump += f[j];
  for( long int j = 1; j <= N - 1; j = j + 2 )
    sumd += f[j];
  
  return( ( h / 3.0 ) * ( f[0] + f[N] + 2.0 * sump + 4.0 * sumd ) );

}

double Atteso( int a, int b, double h, long int N, int k)
{
    
    double f[Nmax+1];
    double xj;
    
    for( long int j = 0; j <= N; j++ )
    {
        xj   = a + j * h;
        f[j] = xj*ChiQuadro( xj, k );
    }

    double aa = int_simp(f,h,N);
    return aa;

}

int main()
{
    cout << "Calcolo, per un insieme di 3,5,7,9,11 variabili aleatorie indipendenti aventi distribuzione normale standard, il valore atteso, la varianza, la skewness e la flatness utilizzando il metodo di Cavalieri-Simpson." << endl;
    int k;
    cout << "Inserisci numero di variabili aleatorie k (dispari) :";
    cin >> k;

    double a = 0, b = 5000;
    long int N = 6000;
    double h = ( b - a ) / N;

    double att =  Atteso(a,b,h,N,k);
    cout << "Il valore atteso è: " << att << endl;
    cout << "(Teorico): " << k << endl << endl;

    return 0;

}
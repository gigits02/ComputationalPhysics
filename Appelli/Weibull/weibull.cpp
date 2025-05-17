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

double F(double x, double k, double l)
{
    double ff = k*pow(x, (k-1))*exp( -1*pow((x/l),k)) / pow(l,k);
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

double momento(double a, double b, double h, long int N, double k, double l, int n)
{
    
    double f[Nmax+1];
    double xj;
    
    for( long int j = 0; j <= N; j++ )
    {
        xj   = a + j * h;
        f[j] = pow(xj,n)*F( xj, k, l);
    }

    double m = int_simp(f,h,N);
    return m;

}

double teorico(double k, double l, int n)
{
    double mu = pow(l,n)*Fatt(n/k);
    return mu;
}

int main()
{
    cout << "Calcolo, per 5 valori interi distinti di k e altrettanti lambda, i momenti di ordine 1,2,3,4 della distribuzione di Weibull, utilizzando il metodo di Cavalieri-Simpson." << endl;
    double k,l;
    cout << "Inserisci rispettivamente k e l reali positivi: ";
    cin >> k >> l;
    cout << endl;
    
    double a = 0, b = 5000;
    cout << "f(5000) vale: " << F(b, k, l) << endl;

    long int N = 6000;
    double h = ( b - a ) / N;

    for(int n = 1; n <= 4; n++)
    {
        cout << "Momento di ordine " << n << ": " << momento(a,b,h,N,k,l,n) << endl;
        
        int rapporto = n/k;
        if(n/k == rapporto)
        {
            double teo = teorico(k,l,n);
            cout << "Il rapporto n/k e' intero, posso calcolare la previsione teorica: " << teo << endl;
        }
    }

    return 0;

}
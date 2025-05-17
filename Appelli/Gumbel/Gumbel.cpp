
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

// Numero massimo di sottointervalli in [a,b]
const long int Nmax = 10000;


double F( double x )
{
    double ff = exp(- x - exp(-x));
    return( ff );
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




int main()
{
    double k = 0.5772;

    double mu,beta;
    cout << "Inserisci parametri mu e beta: ";
    cin >> mu >> beta;


    double a, b;
    cout << "Estremi a, b dell'intervallo: ";
    cin >> a >> b;

    
    long double z;
    z = (a-mu)/beta;
    long double prova1 = F(z)/beta;
    cout << "La funzione in a vale: " << prova1 << endl;
    z = (b-mu)/beta;
    long double prova2 = F(z)/beta;
    cout << "La funzione in b vale: " << prova2 << endl;

    long int N;
    cout << "Numero di intervalli su cui calcolare l\'integrale: ";
    cin >> N;
  
    if ( ( N % 2 ) != 0 )
    {
        cout << "Errore! In numero di intervalli DEVE essere PARI!" << endl;
        exit( 0 );
    }


    double xj;
    double f[Nmax+1];
    double h = ( b - a ) / N;

    for( long int j = 0; j <= N; j++ )
    {
        xj   = a + j * h;
        z = (xj-mu)/beta;
        f[j] = xj * F( z )/beta;
    }


    // Calcolo dell'integrale definito

    double E = int_simp( f, h, N );
    
    cout.precision(15);
    cout << "Risultato valore atteso: E = " << E << endl;
    cout << "Risultato teorico: " << mu + beta*k << endl;

    double xi;
    double g[Nmax+1];

    for( long int i = 0; i <= N; i++ )
    {
        xi = a + i*h;
        z = (xi-mu)/beta;

        g[i] = (xi - E)*(xi - E)*F(z)/beta;
    }

    double Var = int_simp( g, h, N);

    cout << "Risultato della varianza attesa: Var = " << Var << endl; 
    cout << "Risultato teorico: " << acos(-1)*acos(-1)*beta*beta/6 << endl;
    return 0;

}

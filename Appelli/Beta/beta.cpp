#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;


// Numero massimo di sottointervalli in [a,b]
const long int Nmax = 10000;

double int_simp( double f[], double h, long int N )
{
  double sump = 0.0, sumd = 0.0;

  for( long int j = 2; j <= N - 2; j = j + 2 )
    sump += f[j];
  for( long int j = 1; j <= N - 1; j = j + 2 )
    sumd += f[j];
  
  return( ( h / 3.0 ) * ( f[0] + f[N] + 2.0 * sump + 4.0 * sumd ) );

}

double funzione( double x, double p, double q)
{
    double B;
    double a,b;

    long int N = 6000;

    // Definisce la funzione sui punti nodali
    double tj;
    double f[Nmax+1];
    a = 0, b = x;
    double h = ( b - a ) / N;

    for ( long int j = 0; j <= N; j++ )
    {
        tj   = a + j * h;
        f[j] = (pow(tj, (p-1)))*(pow((1-tj), (q-1)));
    
    }

    B = int_simp( f, h, N );
    
    
    return B;
}

int main()
{
    cout << "Calcolo il valore della funzione Beta incompleta per 20 valori equispaziati di x nell'intervallo [0,1] e valori di p e q inseriti da tastiera. " << endl;
    
    double x,p,q;
    
    cout << "Inserisci valori di p e q (devono essere POSITIVI!): ";
    cin >> p >> q;
    
    for( int i = 1; i <= 20; i++ )
    {
        cout << "Valore di x: " << endl;
        cin >> x;

        double b = funzione(x,p,q);
        cout << "Il valore numerico dell'integrale è: " << b << endl;
    }

    return 0;

}

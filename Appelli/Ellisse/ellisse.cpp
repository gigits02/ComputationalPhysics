#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;


// Numero massimo di sottointervalli in [a,b]
const long int Nmax = 10000;

int main()
{

    double a = 0, b = acos(-1)/2;
    
    

    long int N = 6000;

    double l[10];
    double e[10];

    cout << "Calcolerò la lunghezza dell'ellisse tramite l'integrale ellittico completo di seconda specie per 10 diversi valori di eccintricità " << endl;
    

    for(int u = 1; u <= 10; u++)
    {
        cout << "Inserire valore dell'eccentricità dell'ellisse: " << endl;
        cin >> e[u];
    }

    cout << endl;
    cout << "eccentricità        integrale      " << endl;

    for(int n = 1; n <= 10; n++)
    {
        double xj;
        double f[Nmax+1];
        double h = ( b - a ) / N;

        for( long int j = 0; j <= N; j++ )
        {
            xj   = a + j * h;
            f[j] = pow((1-e[n]*e[n]*sin(xj)*sin(xj)), 1.0/2.0);
        }

        
        double sump = 0.0, sumd = 0.0;

        for( long int j = 2; j <= N - 2; j = j + 2 )
            sump += f[j];
        for( long int j = 1; j <= N - 1; j = j + 2 )
            sumd += f[j];
    

        double I = ( ( h / 3.0 ) * ( f[0] + f[N] + 2.0 * sump + 4.0 * sumd ) );
        l[n] = 4*I;

        cout << e[n] << "               "  << l[n] << endl;         
    }

  return 0;

}

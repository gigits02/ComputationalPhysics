#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

double f( double x, int n )
{
    double y = pow(x, n) - n;
    return( y );
}

double fp( double x, int n )
{
    double y = n*pow(x, (n-1));
    return( y );
}


// Main program
int main()
{
    cout << "Soluzione dell'equazione: x^n - n = 0 col metodo di Newton, per n = 2,3,...,1000" << endl;

    double a = 0, b = 2, x0, eps = pow(10, -13), xk, xkp1, largh, xz;
    int cont, num_max_iter;

    // Parametri iniziali
    cout << "Stima iniziale dello zero x0: ";
    cin >> x0;
    cout << "Numero massimo di iterazioni: ";
    cin >> num_max_iter;   

    for( int n = 2; n < 1001; n++)
    {
        // Check sull'intervallo iniziale
        
        cout << "N = " << n << ": " << endl;
        if ( f( a, n ) * f( b, n ) > 0.0 )
        {
            cout << "Errore! L\'intervallo [" << a << "," << b << "] non contiene uno zero!" << endl;
            exit( 0 );
        }

        // Inizializzazione

        cont = 0;
        xk = x0;
 
        cout.precision(15);

        // Ciclo per la ricerca col metodo di Newton
        do
        {
            cont++;
            xkp1 = xk - f( xk, n ) / fp( xk, n );
            //    xk+1 = xk - f(xk)/ f'(xk)
        
            largh = abs( xkp1 - xk );
            xk = xkp1;
        

        }while( ( largh > eps ) && ( cont < num_max_iter ) );

        if ( cont < num_max_iter )
        {
            xz = xk;
            cout << "Zero della funzione in: " << xz << " +- " << 0.5 * largh << endl;
            cout << "Differenza con quella teorica: " << abs(xz - pow(n, 1.0/n)) << endl;
        }
        else
        { 
            cout << "La successione di valori NON e' arrivata a convergenza entro ";
            cout << num_max_iter << " iterazioni!" << endl;
            cout << "Prova ad aumentare il numero massimo di iterazioni o a scegliere un x0 differente!" << endl;
        }
        x0 = xz;
        largh = 0;
    }  
    return 0;

} 
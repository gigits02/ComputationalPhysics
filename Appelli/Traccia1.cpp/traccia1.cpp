#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

double f( double x )
{
    const long int Nmax = 10000;
    long int N = 6000;

    double tj;
    double f[Nmax+1];
    double a2 = 0;
    double h = ( x - a2 ) / N;

    double risultato;

    if(x == 0)
    {
        risultato = -3.0/2.0;
        return risultato;
    }


    for( long int j = 0; j <= N; j++ )
    {
        tj   = a2 + j * h;
        f[j] = sin(tj)/tj;
    }

    double sump = 0.0, sumd = 0.0;

    for( long int j = 2; j <= N - 2; j = j + 2 )
        sump += f[j];
    for( long int j = 1; j <= N - 1; j = j + 2 )
        sumd += f[j];
  
    double I = ( ( h / 3.0 ) * ( 1 + f[N] + 2.0 * sump + 4.0 * sumd ) );
    risultato = I-3./2.;

    return(risultato);
  

}
    
double fp( double x )
{
    double y = sin(x)/x;

    return( y );
}



int main()
{
    cout << "Ricerca degli zeri della funzione:" << endl;
    cout << "F(x) = integrale da 0 a x di sin(t)/t dt - 3/2" << endl;
    double a, b, x0, eps, xk, xkp1, largh, xz;
    int cont, num_max_iter;

       

    a = 6, b = 10, x0 = 8, eps = 0.1,num_max_iter = 10;

    // Check sull'intervallo iniziale

    cout << "f(a) vale : " << f(a) << endl;
    cout << "f(b) vale : " << f(b) << endl;

    if ( f( a ) * f( b ) > 0.0 )
    {
        cout << "Errore! L\'intervallo [" << a << "," << b << "] non contiene uno zero!" << endl;
        exit( 0 );
    }

    // Inizializzazione

    cont = 0;
    xk = x0;
    cout << "Iter." << "\t" << "x_k" << "\t" << "|x_k+1 - x_k|" << endl;
    cout.precision(15);

    // Ciclo per la ricerca col metodo di Newton

    do
    {
        cont++;
        xkp1 = xk - f( xk ) / fp( xk );
        //    xk+1 = xk - f(xk)/ f'(xk)
        
        largh = abs( xkp1 - xk );
        xk = xkp1;
        cout << cont << "\t" << xk << "\t" << largh << endl;

    }while( ( largh > eps ) && ( cont < num_max_iter ) );

    if ( cont < num_max_iter )
    {
        xz = xk;
        cout << "Zero della funzione in: " << xz << " +- " << 0.5 * largh << endl;
        cout << "Valore della funzione nello zero: " << f( xz ) << endl;
        cout << "Numero di iterazioni necessarie per il calcolo dello zero con la tolleranza voluta: " << cont << endl;
    }
    else
    { 
        cout << "La successione di valori NON e' arrivata a convergenza entro ";
        cout << num_max_iter << " iterazioni!" << endl;
        cout << "Prova ad aumentare il numero massimo di iterazioni o a scegliere un x0 differente!" << endl;
    }


    return 0;

} 
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;


// Numero massimo di sottointervalli in [a,b]
const long int Nmax = 10000;

double int_trap( double f[], double h, long int N )
{
    double sum;

    sum = 0.5 * ( f[0] + f[N] );
    for( long int i = 1; i < N; i++ )
        sum += f[i];
    
    return( h * sum );
}

double funzione( double x)
{
    double erf;
    double a,b;

    long int N = 6000;

    // Definisce la funzione sui punti nodali
    double zj;
    double f[Nmax+1];
    a = 0, b = x;
    double h = ( b - a ) / N;

    for ( long int j = 0; j <= N; j++ )
    {
        zj   = a + j * h;
        f[j] = exp(-zj*zj);
    
    }

    erf = 2.0/(pow((acos(-1)), 0.5)) * int_trap( f, h, N );
    double ff = erf - 0.5;
    
    return ff;
}

int main()
{
    cout << "Calcolo il valore della funzione erf(x)-0.5 per 20 valori equispaziati di x nell'intervallo [0,1]. " << endl;
    
    
    
    double f;
    double s = 0;
    cout << endl;
    cout << "xj          erf-0.5" << endl;

   
 
    cout << "Cerco lo zero della funzione col metodo di bisezione..." << endl;

    double a = 0, b = 1, ak, bk, xk, fa, fb, fx, largh, eps = 0.01;
    int cont;

    ak = a; 
    bk = b;
    cont = 0;
    largh = abs( bk - ak );
    cout << "Iter." << "\t" << "a_k" << "\t" << "b_k" << "\t" << "x_k" << "\t" << "|b_k-a_k|" << endl;
    cout.precision(15); 

    do
    {
        xk = 0.5 * ( ak + bk );
        cout << cont << "\t" << ak << "\t" << bk << "\t" << xk << "\t" << largh << endl;
        fa = funzione( ak );
        fb = funzione( bk );
        fx = funzione( xk );
        if ( fx == 0.0 )
	    {
	        cout << "Zero della funzione in: " << xk << "+- 0.0" << endl;
	        cout << "Numero di iterazioni: " << cont << endl;
	        exit( 0 );
	    }
        else
	    {
	        if ( fa * fx < 0.0 ) 
                bk = xk;
	        
            if ( fx * fb  < 0.0 ) 
                ak = xk;
	        
            largh = abs( bk - ak );
	        cont++;
	    }

    }while ( largh > eps );

    xk = 0.5 * ( ak + bk );
    cout << cont << "\t" << ak << "\t" << bk << "\t" << xk << "\t" << largh << endl;
    cout << "Zero della funzione in: " << xk << " +- " << 0.5 * largh << endl;
    cout << "Valore della funzione nello zero: " << funzione( xk ) << endl;   

    return 0;

}

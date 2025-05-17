#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

// Variabili globali del programma

const int N = 1001;       //(Numero di punti griglia, inclusi i bordi)

// Y(a) e Y(b) noti:
const int dim = N - 2;


double f( double x )
{
  return( x/(pow(x,2)-1));
}


double g( double x, int n )
{
  return( pow(n,2)/(1-pow(x,2)) );
}


double h( double x )
{
  return( 0.0 );
}


/*

  LU_fact( A ): effettua la fattorizzazione LU di una matrice tridiagonale
  secondo l'algoritmo di Thomas

*/

void LU_fact( double A[3][dim] )
{
  for ( int i = 1; i <= dim - 1; i++ )
    {
      A[0][i] = A[0][i] / A[1][i-1];
      A[1][i] = A[1][i] - A[0][i] * A[2][i-1];
    }
}


/*

  LU_solve( A, f, x ): esegue l'inversione del sistema a*x=b
  secondo l'algoritmo di Thomas.

*/

void LU_solve( double A[3][dim], double f[dim], double x[dim] )
{
  double y[dim];

  y[0] = f[0];
  for ( int i = 1; i <= dim - 1; i++ )
    y[i] = f[i] - A[0][i] * y[i-1];

  x[dim-1] = y[dim-1] / A[1][dim-1];
  for ( int i = dim - 2; i >= 0; i-- ) 
    x[i] = ( y[i] - A[2][i] * x[i+1] ) / A[1][i];
}



int main()
{
    
    cout << "Inserisci il valore di n: (0,1,2,3 o 4)" << endl;
    int n;
    cin >> n;
    
    int j_init = 1, j_end = N - 2;
    
    double Ya  = pow(-1,n);
    double Yb  = 1;
    
    double Ypa = 0.0;   // Nota come Ypa e Ypb debbono comunque essere definiti
    double Ypb = 0.0;   // per evitare errori di compilazione!


  // Intervallo di definizione di x

  double x[N], a, b;
  a = -1.0;     // Inserire l'estremo sinistro dell'intervallo di definizione
  b = 1.0 ;    // Inserire l'estremo destro dell'intervallo di definizione
  double dx = ( b - a )/( N - 1 );     // Nota: il numero di intervalli e' N-1!
  double dx2 = dx * dx;
  double ddx = 2.0 * dx;


  for( int j = 0; j < N; j++ ) 
    x[j] = a + j * dx;


  // Definizione della matrice D delle derivate e secondo membro

  double D[3][dim];
  double sm[dim];

  // Quello che appare nella prima e nell'ultima riga della matrice,
  // nonche' a secondo membro, dipende dalle condizioni al bordo

        D[0][0] = 0.0;
        D[1][0] = - 2.0 / dx2 + g( x[j_init], n ); //mu
        D[2][0] = 1.0 / dx2 + f( x[j_init] ) / ddx; //csi
        sm[0]  = h( x[j_init] ) - Ya * ( 1.0 / dx2 - f( x[j_init] ) / ddx ); 
        D[0][dim-1] = 1.0 / dx2 - f( x[j_end] ) / ddx; //lambda
        D[1][dim-1] = - 2.0 / dx2 + g( x[j_end], n ); //mu
        D[2][dim-1] = 0.0;
        
        sm[dim-1]   = h( x[j_end] ) - Yb * ( 1.0 / dx2 + f( x[j_end] ) / ddx );
        
        
        
    for ( int j = 1; j < dim - 1; j++ )
    {
        D[0][j] = 1.0 / dx2 - f( x[j_init+j] ) / ddx;  // lambda_j
        D[1][j] = - 2.0 / dx2 + g( x[j_init+j], n );      // mu_j
        D[2][j] = 1.0 / dx2 + f( x[j_init+j] ) / ddx;  // xi_j
        sm[j]   = h( x[j_init+j] );
    }


    // Fattorizzazione LU della matrice D

    LU_fact( D );


    // Inverte il sistema fattorizzato LU

    double Y[dim];
    LU_solve( D, sm, Y );


    // Stampa del risultato

    // Legge in input il nome del file

    char fname[250];
    cout << "Nome del file dei risultati: ";
    cin >> fname;

    // Apre il file e imposta la massima precisione

    ofstream fout;
    fout.open( fname );
    fout.precision( 15 );

    
    // Se Y(a) e' noto, lo scrive nel file
    fout << "# x      Y       Yex     err" << endl;
    double Yex;
    Yex = cos(n*(acos(x[0])));
    fout << x[0] << "\t\t" << Ya <<  "\t\t" << Yex << "\t\t" << abs(Ya-Yex) << endl;

    // Scrive su file i valori calcolati
    for( int j = 0; j < dim; j++ )
    {
        Yex = cos(n*(acos(x[j_init+j])));
        fout << x[j_init+j] << "\t\t" << Y[j] << "\t\t" << Yex << "\t\t" << abs(Ya-Yex) << endl;

    }
    // Se Y(b) e' noto, lo scrive nel file
    Yex = cos(n*(acos(x[N-1])));
    fout << x[N-1] << "\t\t" << Yb << "\t\t" << Yex << "\t\t" << abs(Ya-Yex) << endl;

    
    
    fout.close();

    return( 0 );


}

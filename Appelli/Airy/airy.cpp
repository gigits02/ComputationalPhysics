#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

const long int Nmax = 10000;

void Simplettico(double dt, long int Nend1, long int Nend2, long int Nprint, double y0, double vy0)
{
    
    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    double  t_n, y_n, y_np1, vy_n, vy_np1;


    t_n  = -10;
    y_n  = y0;
    vy_n  = vy0;


    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t     y     vy     " << endl;
    fout << t_n << "   " << y_n << "    " << vy_n << endl;


    double t_np1 = 0;
    for( long n = 1; n >= Nend1; n-- )
    {


        t_n = t_n + dt;
        t_np1 =  t_n + dt;      
	    
        y_np1 = y_n + dt * vy_n;
	      vy_np1 = vy_n + dt * t_np1*y_np1;	
	

        y_n = y_np1;
        vy_n = vy_np1;

    

        // Stampa ogni Tprint intervalli di stampa

        if( (n % Nprint)  == 0 )
	      {
            fout << t_n << "  " << y_n << "   " << vy_n << endl;
	      }

    }

    t_n = 0.0;
    t_np1 = 0.0;
    y_n  = y0;
    vy_n  = vy0;
    for( long i = 1; i <= Nend2; i++ )
    {


        t_n = t_n + dt;
        t_np1 =  t_n + dt;      
	    
        y_np1 = y_n + dt * vy_n;
	      vy_np1 = vy_n + dt * t_np1*y_np1;	
	

        y_n = y_np1;
        vy_n = vy_np1;

    

        // Stampa ogni Tprint intervalli di stampa

        if( (i % Nprint)  == 0 )
	    {
            fout << t_n << "  " << y_n << "   " << vy_n << endl;
	    }

    }

    fout.close();
  
}


// Funzione da integrare

double F( double t, double z)
{
  double ff = pow(t,(z-1))*exp(-t);
  return( ff );
}


double int_simp( double f[], double h, long int N, double z0 )
{
  double sump = 0.0, sumd = 0.0;

  for( long int j = 2; j <= N - 2; j = j + 2 )
    sump += f[j];
  
  for( long int j = 1; j <= N - 1; j = j + 2 )
    sumd += f[j];
  
  return( ( h / 3.0 ) * ( f[0]/z0 + f[N] + 2.0 * sump + 4.0 * sumd ) );

}

int main()
{
    
    double dt = 0.001;
    double Tend1 = -10;
    double Tend2 = 5;
    double Tprint = 0.005;


    long Nend1 = long( (Tend1) / dt );
    long Nend2 = long( (Tend2) / dt );
    long Nprint = long( Tprint / dt );

    

    double a = 0, b = 40;
    

    long int N;
    cout << "Numero di intervalli su cui calcolare l\'integrale: ";
    cin >> N;
  
    if ( ( N % 2 ) != 0 )
    {
        cout << "Errore! In numero di intervalli DEVE essere PARI!" << endl;
        exit( 0 );
    }

    // Definisce la funzione sui punti nodali

    double tj;
    double f1[Nmax+1], f2[Nmax+1];
    double h = ( b - a ) / N;

    double z1= 2./3.;
    double z2 = 1./3.;
    for( long int j = 0; j <= N; j++ )
    {
        tj   = a + j * h;
        
        if(j == 0)
        { 
          f1[j] = F( tj, (z1+1) );
          f2[j] = F( tj, (z2+1) );
      
        }
        else
        {
          f1[j] = F( tj, z1 );
          f2[j] = F( tj, z2 );
        }

    }   

    // Calcolo dell'integrale definito

    double I1 = int_simp( f1, h, N, z1 );
    double I2 = int_simp( f2, h, N, z2 );

    cout << "I1 vale " << I1 << endl;
    cout << "I2 vale " << I2 << endl;

    double y0, vy0;
    
    y0 = 1/(pow(3, 2/3)*I1);
    vy0 = -1/(pow(3, 1/3)*I2);

    Simplettico(dt,Nend1,Nend2,Nprint,y0,vy0);

    return 0;
    
} 
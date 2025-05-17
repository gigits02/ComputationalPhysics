#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void Simplettico(double dt, long int Nend, long int Nprint, double x0, double y0, double vx0, double vy0)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    double  t_n, x_n, x_np1, y_n, y_np1, vx_n, vx_np1, vy_n, vy_np1;


    t_n  = 0.0;
    x_n = x0, y_n = y0;
    vx_n = vx0, vy_n = vy0;


    double r_n = sqrt(x_n*x_n + y_n*y_n);
    double vr_n = sqrt(vx_n*vx_n + vy_n*vy_n); 
    double r_np1;

    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t    x     y     r     vr     " << endl;
    fout << t_n << "  " << x_n << "   " << y_n << "   "  << r_n << "     " << vr_n << endl;


    for( long n = 1; n <= Nend; n++ )
    {
        t_n = n * dt;       
	    
        x_np1 = x_n + dt * vx_n;
        y_np1 = y_n + dt * vy_n;

        r_np1 = sqrt(x_np1*x_np1 + y_np1*y_np1);

        vx_np1 = vx_n + dt * (-1/pow(r_np1,3))*x_np1;		
        vy_np1 = vy_n + dt * (-1/pow(r_np1,3))*y_np1;
        
        x_n = x_np1;
        y_n = y_np1;
        vx_n = vx_np1;
        vy_n = vy_np1;

        r_n = sqrt(x_n*x_n + y_n*y_n);
        vr_n = sqrt(vx_n*vx_n + vy_n*vy_n);  
        
        // Stampa ogni Tprint intervalli di stampa
        if( (n % Nprint)  == 0 )
	    {
            fout << t_n << "  " << x_n << "   " << y_n << "   "  << r_n << "     " << vr_n << endl;
	    }

    }

  fout.close();
  
}


// Funzione da integrare

double F( double x, double vth0, double w2)
{
  double ff = 1/sqrt(vth0*vth0-2*w2*(1-cos(x)));
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
  
    double dt = 0.001;
    double Tend = 50;
    double Tprint = 0.005;


    long Nend = long( Tend / dt );
    long Nprint = long( Tprint / dt );

    double x0 = 1, y0 = 0, vx0 = 0, vy0;
    cout << "Inserire velocità iniziare vy compresa nell'intervallo [0.5 , 1.4]: ";
    cin >> vy0;

    Simplettico(dt,Nend,Nprint,x0,y0,vx0,vy0);

    return 0;
    
} 
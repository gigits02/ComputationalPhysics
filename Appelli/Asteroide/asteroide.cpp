#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double x0, double vx0, double y0, double vy0)
{

  cout << "Nome del file di output: ";
  char nfile[256];
  cin >> nfile;

  // Condizioni iniziali

  double t_n, x_n, x_np1, x_star, vx_n, vx_np1, vx_star;
  double den, y_n, y_np1, y_star, vy_n, vy_np1, vy_star;

  t_n  = 0.0;
  x_n  = x0;
  vx_n  = vx0;
  y_n  = y0;
  vy_n  = vy0;


  ofstream fout;
  fout.open( nfile );
  fout.precision( 15 );
  fout << "#   t     x     vx    y     vy" << endl;
  fout << t_n << "   " << x_n << "    " << vx_n << "   " << y_n <<  "   " << vy_n << endl;

  double kk = 19.8944;
  
  for(int n = 1; n <= Nend; n++)
  {
    
    t_n = n * dt;

    //(R-K)

    den = pow( x_n * x_n + y_n * y_n, 1.5 );
    x_star = x_n + 0.5 * dt * vx_n;
    y_star = y_n + 0.5 * dt * vy_n;
    vx_star = vx_n - dt * kk * x_n / den;
    vy_star = vy_n - dt * kk * y_n / den;
    den = pow( x_star * x_star + y_star * y_star, 1.5 );
    x_np1 = x_n + dt * vx_star;
    y_np1 = y_n + dt * vy_star;
    vx_np1 = vx_n - dt * kk * x_star / den;
    vy_np1 = vy_n - dt * kk * y_star / den;

    x_n = x_np1;
    y_n = y_np1;
    vx_n = vx_np1;
    vy_n = vy_np1;

    // Stampa ogni Tprint intervalli di stampa

  if(( n%Nprint ) == 0 )
	{
        fout << t_n << "   " << x_n << "    " << vx_n << "   " << y_n <<  "   " << vy_n << endl;
	}
  
  }

  fout.close();



}

double trovaVelmin(double dt, long int Nend, long int Nprint, double x0, double vx0, double y0, double vy0)
{
  
  double t_n, x_n, x_np1, x_star, vx_n, vx_np1, vx_star;
  double den, y_n, y_np1, y_star, vy_n, vy_np1, vy_star;

  double kk = 19.8944;

  t_n  = 0.0;
  x_n  = x0;
  
  y_n  = y0;
  vy_n  = vy0;

  double vxmax=0.0, vxmin=0.0;
  vx0 = -3.0;
  vx_n = vx0;

  double vi = vx_n; 

  for(int i = 1; i <= Nend; i++)
  {
    
    
    
    t_n = i * dt;

    //(R-K)

    den = pow( x_n * x_n + y_n * y_n, 1.5 );
    x_star = x_n + 0.5 * dt * vx_n;
    y_star = y_n + 0.5 * dt * vy_n;
    vx_star = vx_n - dt * kk * x_n / den;
    vy_star = vy_n - dt * kk * y_n / den;
    den = pow( x_star * x_star + y_star * y_star, 1.5 );
    x_np1 = x_n + dt * vx_star;
    y_np1 = y_n + dt * vy_star;
    vx_np1 = vx_n - dt * kk * x_star / den;
    vy_np1 = vy_n - dt * kk * y_star / den;

    x_n = x_np1;
    y_n = y_np1;
    vx_n = vx_np1;
    vy_n = vy_np1;
    
    double eps = pow(10, -2);


    if((abs(y_n) <= 0+eps) &&  x_n < -1.1)
    {
  
      vxmax = vi;
      vi = (vxmax + vxmin)/2;
      vx_n  = vi;
      i = 1;
      x_n  = x0;
      y_n  = y0;
      vy_n  = vy0;
      
    }
    else if((abs(y_n) <= 0+eps) &&  x_n > -0.9)
    {
         
      vxmin = vi;
      vi  = (vxmax+vxmin)/2;
      vx_n = vi;
      i = 1;
      x_n  = x0;
      y_n  = y0;
      vy_n  = vy0;
    
    }
    else if((abs(y_n) <= 0+eps) &&  x_n <= -1.0) 
      i = Nend+1;


  
  }
    

  return vi;

}

int main()
{

  double dt = 0.001; 
  double Tend = 30; 
  double Tprint = 0.005;

  long int Nend = long( Tend / dt );
  long int Nprint = long( Tprint / dt );
  
  cout << "Inserire parametro di impatto d (l'altezza y0 iniziale): ";
  double x0=50.0, vx0=-15.0, y0, vy0=0.0;
  cin >> y0;
  

  RungeKutta(dt, Nend, Nprint, x0, vx0, y0, vy0);

  double kk = 19.8944;
  double vteo = sqrt(2*kk/(y0*y0-1));
  cout << "Velocità minima teorica di non impatto: " << vteo << endl;

  cout << "Velocità minima trovata vx0 = " << trovaVelmin(dt, Nend, Nprint, x0, vx0, y0, vy0) << endl;

  cout << "Creazione file per le soluzioni numeriche con velocità iniziale minima di non impatto:" << endl;
  vx0 = trovaVelmin(dt, Nend, Nprint, x0, vx0, y0, vy0);
  RungeKutta(dt, Nend, Nprint, x0, vx0, y0, vy0);


  return 0;

}


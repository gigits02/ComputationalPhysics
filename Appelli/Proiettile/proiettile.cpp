#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double v0, double th)
{
  cout << "Nome del file di output: ";
  char nfile[256];
  cin >> nfile;


  const int g = 9.81;
  double t_n;
  double x_n, vx_n, x_np1, vx_np1, x_star, vx_star;
  double y_n, vy_n, y_np1, vy_np1, y_star, vy_star;

  // Condizioni iniziali
  t_n = 0;
  x_n = 0;
  y_n = 0;
  vx_n = v0*cos(th);
  vy_n = v0*sin(th);


  ofstream fout;
  fout.open( nfile );
  fout.precision( 15 );
  fout << "#   t      x      y     vx      vy      " << endl;
  fout << t_n << "   " << x_n << "    " << y_n << "   " << vx_n << "     " << vy_n << endl;

  double ymax = y_n, tmax = t_n;
  bool entra = false;
  for(long int n = 1; n <= Nend; n++)
  {
    t_n = n * dt;
    
    //(R-K)
    x_star = x_n + 0.5* dt * vx_n;
    vx_star = vx_n + 0;
    y_star = y_n + 0.5 * dt * vy_n;
    vy_star = vy_n - 0.5 * dt * g;

    x_np1 = x_n + dt * vx_star;
    vx_np1 = vx_n + 0;
    y_np1 = y_n + dt * vy_star;
    vy_np1 = vy_n - dt * g;

    x_n = x_np1;
    y_n = y_np1;
    vx_n = vx_np1;
    vy_n = vy_np1;  

        
    if(( n%Nprint ) == 0 )
	  {
      fout << t_n << "   " << x_n << "    " << y_n << "   " << vx_n << "      " << vy_n << endl;
	  }

    if( y_n > ymax )
    {  
      ymax = y_n;    
      tmax = t_n;
    }
    if( t_n > 0.05 && abs(y_n) < 0.0001 && entra == false)
    {
      entra = true;
      cout << "La gittata vale approssimativamente: " << x_n << endl;
      cout << "Quella teorica: " << v0*v0*sin(2*th)/g << endl;
      cout << "Err:" << abs(v0*v0*sin(2*th)/g - x_n) << endl;
    }
  }
    
  cout << "La massima altezza di " << ymax << "m viene raggiunta dopo " << tmax << " secondi. " << endl;
  cout << "Il tempo teorico è: " << v0*sin(th)/g << endl;
  cout << "Err: " << abs(tmax -  v0*sin(th)/g) << endl;
  
           
  fout.close();


}

int main()
{
  cout << "Inserire condizioni iniziali v0 e theta: ";
  double v0, th;
  cin >> v0 >> th;

  double dt = 0.0001; 
  double Tend = 5; 
  double Tprint = 0.005;

  long int Nend = long( Tend / dt );
  long int Nprint = long( Tprint / dt );


  RungeKutta(dt, Nend, Nprint, v0, th);

  
  return 0;

}


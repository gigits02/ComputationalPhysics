#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double th0, double z0, double vz0)
{

  cout << "Nome del file di output: ";
  char nfile[256];
  cin >> nfile;

  // Condizioni iniziali
  double vth = 10;
  double alpha = acos(-1)/4; 
  const int g = 9.81;
  double t_n, th_n, z_n, th_np1, z_np1, th_star, z_star, vz_n, vz_np1, vz_star;

  
  t_n = 0.0;
  th_n = th0;
  z_n = z0;
  vz_n = vz0;

 
  double r_n = z_n*tan(alpha);

  double x_n = z_n*tan(alpha)*cos(th_n);
  double y_n = z_n*tan(alpha)*sin(th_n);
  ofstream fout;
  fout.open( nfile );
  fout.precision( 15 );
  fout << "#   t     r     th    z   x   y     " << endl;
  fout << t_n << "   " << r_n << "    " << th_n << "   " << z_n <<  "   " << x_n << "    " << y_n << "   " <<  endl;

  
  for(long int n = 1; n <= Nend; n++)
  {
    
    t_n = n * dt;

    //(R-K)
    r_n = z_n*tan(alpha);

    th_star = th_n + 0.5* dt * z0*vth/(z_n*z_n*tan(alpha));
    z_star = z_n + 0.5 * dt * vz_n;
    vz_star = vz_n + 0.5*dt*(pow(cos(alpha),2)*((z0*z0*vth*vth/pow(z_n,3))-g));
    
    th_np1 = th_n + dt * z0*vth/(z_star*z_star*tan(alpha));
    z_np1 = z_n + dt * vz_star;
    vz_np1 = vz_n + dt * (pow(cos(alpha),2))*((z0*z0*vth*vth/pow(z_star,3))-g);
    

    th_n = th_np1;
    z_n = z_np1;
    vz_n = vz_np1;

    x_n = z_n*tan(alpha)*cos(th_n);
    y_n = z_n*tan(alpha)*sin(th_n);


    // Stampa ogni Tprint intervalli di stampa

  if(( n%Nprint ) == 0 )
	{
        fout << t_n << "   " << r_n << "    " << th_n << "   " << z_n <<  "   " << x_n << "   " << y_n <<  endl;
	}
  
  }
  double z2 = ( vth*vth + sqrt( pow(vth,4) + 8*vth*vth*z0*g ) ) / (4*g);
  cout << "Verificare (grafico) che la posizione della massima altezza sia compresa tra " << z0 << " e " << z2 << endl;
  fout.close();



}

int main()
{

  double dt = 0.0001; 
  double Tend = 50; 
  double Tprint = 0.005;

  long int Nend = long( Tend / dt );
  long int Nprint = long( Tprint / dt );
  
  cout << "Inserire costanti th0, z0, vz0: ";
  double th0, z0, vz0;
  cin >> th0 >> z0 >> vz0;
    
  RungeKutta(dt, Nend, Nprint, th0, z0, vz0);

  

  
  return 0;

}


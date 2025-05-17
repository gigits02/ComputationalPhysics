#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double x0, double vx0, double a)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    
    double t_n;
    double x_n, vx_n, x_np1, vx_np1, x_star, vx_star;

    // Condizioni iniziali
    t_n = 0;
    x_n = x0;
    vx_n = vx0;

    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t      x        vx      " << endl;
    fout << t_n << "   " << x_n << "    " << vx_n << endl;

    bool entra1 = false;
    bool entra2 = false;
    bool seconda = false;
    for(long int n = 1; n <= Nend; n++)
    {
        t_n = n * dt;
        
        //(R-K)
        x_star = x_n + 0.5* dt * vx_n;
        vx_star = vx_n + 0.5 * dt * ( a*(1-(x_n*x_n))*vx_n - x_n );
    
    
        x_np1 = x_n + dt * vx_star;
        vx_np1 = vx_n + 0.5 * dt * ( a*(1-(x_star*x_star))*vx_star - x_star );

        x_n = x_np1;
        vx_n = vx_np1;
        
        if(( n%Nprint ) == 0 )
	    {
            fout << t_n << "   " << x_n << "    " << vx_n << "      " << endl;    

	    }
        
       
        
    }
         
    fout.close();

}

int main()
{
        
    double dt = 0.001; 
    double Tend = 80; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );

    double x0 = 0, vx0 = 1;
    double a;
    cout << "Inserire parametro a (0.1, 0.5, 1.0, 5.0, 10.0): " << endl;
    cin >> a;
    
    RungeKutta(dt, Nend, Nprint, x0, vx0, a);

  
  return 0;

}


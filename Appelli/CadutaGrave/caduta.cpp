#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double y0, double vy0)
{

      cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    // Condizioni iniziali 
    const int g = 9.81;
    const int k = 1;
    double t_n, y_n, vy_n, y_np1, vy_np1, y_star, vy_star;

  
    t_n = 0.0;
    y_n = y0;
    vy_n = vy0;

    double yteo = g*(t_n-(1-exp(-k*t_n))/k)/k;

    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t     y     vy     err          " << endl;
    fout << t_n << "   " << y_n << "    " << vy_n << "   " << abs(y_n - yteo) << "  " << endl;

  
    for(long int n = 1; n <= Nend; n++)
    {
    
        t_n = n * dt;

        //(R-K)
        

        y_star = y_n + 0.5* dt * vy_n;
        vy_star = vy_n + 0.5 * dt * (-k*vy_n + g);

        y_np1 = y_n + dt * vy_star;
        vy_np1 = vy_n + dt * (-k*vy_star + g);

        y_n = y_np1;
        vy_n = vy_np1;
        
        yteo = g*(t_n-(1-exp(-k*t_n))/k)/k;
        
        // Stampa ogni Tprint intervalli di stampa
        if(( n%Nprint ) == 0 )
	    {
            fout << t_n << "   " << y_n << "    " << vy_n << "   " << abs(y_n - yteo) << "    " << endl;
	    }
  
    }

    fout.close();



}

int main()
{

    double dt = 0.0001; 
    double Tend = 6; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
  
    cout << "Inserire costanti y0, vz0: ";
    double y0, vy0;
    cin >> y0 >> vy0;


    RungeKutta(dt, Nend, Nprint, y0, vy0);
  
    return 0;

}


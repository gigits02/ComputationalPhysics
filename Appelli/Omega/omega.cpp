#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double y0, double vy0, int w)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    // Condizioni iniziali
    double t_n, t_star, y_n, vy_n, y_np1, vy_np1, y_star, vy_star;

    
    t_n = 0.0;
    y_n = y0;
    vy_n = vy0;
        
    double yteo = sin(w*t_n*t_n + t_n);

    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t     y     vy    err    " << endl;
    fout << t_n << "   " << y_n << "    " << vy_n << "   " << abs(y_n-yteo) << endl;

    
    for(long int n = 1; n <= Nend; n++)
    {
        
        t_n = n * dt;
        t_star = t_n + 0.5 * dt;
        yteo = sin(w*t_n*t_n + t_n);

        //(R-K)
        y_star = y_n + 0.5* dt * vy_n;
        vy_star = vy_n + 0.5 * dt * 2*w*vy_n/(2.0*w*t_n + 1.0) - (2*w*t_n +1)*y_n;
        
        y_np1 = y_n + dt * vy_star;
        vy_np1 = vy_n + dt * 2*w* vy_star/(2.0*w*t_star + 1.0) - (2*w*t_star +1)*y_star;

        y_n = y_np1;
        vy_n = vy_np1;

        // Stampa ogni Tprint intervalli di stampa
        if(( n%Nprint ) == 0 )
        {
            fout << t_n << "   " << y_n << "    " << vy_n << "   " << abs(y_n-yteo) << endl;
        }
    
    }

    fout.close();

}

int main()
{

    double dt = 0.0001; 
    double Tend = 50; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
  
    double y0 = 0.0, vy0 = 1.0;
  

    for(int w = 1; w < 6; w++)
        RungeKutta(dt, Nend, Nprint, y0, vy0, w);


  
    return 0;

}


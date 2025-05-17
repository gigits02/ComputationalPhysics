#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double y0, double vy0, int i)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    // Condizioni iniziali

    double t_n, t_star, y_n, vy_n, y_np1, vy_np1, y_star, vy_star;
  
    t_n = 0.0;
    y_n = y0;
    vy_n = vy0;
    
    double teo;

    if( i == 0)
        teo = exp(-t_n*t_n/2.0);

    if( i == 1)
        teo = t_n * exp(-t_n*t_n/2.0);

    if( i == 2)
        teo = (2*t_n*t_n - 1) * exp(-t_n*t_n/2.0);

    if( i == 3 )
        teo = (2*t_n*t_n*t_n - 3*t_n) * exp(-t_n*t_n/2.0);


    double err = abs(y_n - teo);

    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t     y   err" << endl;
    fout << t_n << "   " << y_n << "   " << err << endl;

    
    for(long int n = 1; n <= Nend; n++)
    {
        
        t_n = n * dt;
        t_star = t_n + 0.5 * dt;
        //(R-K)
        
        y_star = y_n + 0.5* dt * vy_n;
        vy_star = vy_n + 0.5 * dt * (-y_n)*(2*i + 1 - t_n*t_n);
        
        
        y_np1 = y_n + dt * vy_star;
        vy_np1 = vy_n + dt * (-y_star)*(2*i + 1 - t_star*t_star);
        
        

        y_n = y_np1;
        vy_n = vy_np1;

        err = abs(y_n - teo);

        // Stampa ogni Tprint intervalli di stampa
        if(( n%Nprint ) == 0 )
        {
            fout << t_n << "   " << y_n << "    " << err <<  endl;
        }

        

    }

    fout.close();

}

int main()
{

    double dt = 0.0001; 
    double Tend = 3; 
    double Tprint = 0.001;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
  
    for(int i = 0; i < 4; i++)
    {
        double y0, vy0;
        cout << "N = "<< i << endl;
        cout << "Inserire condizioni iniziali per y e vy: ";
        cin >> y0 >> vy0;
    
    
        RungeKutta(dt, Nend, Nprint, y0, vy0, i);


    }

  
    return 0;

}


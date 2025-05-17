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

    double t_n, t_star, y_n, y_np1, y_star, vy_n, vy_np1, vy_star;
    t_n  = 0.0;
    y_n  = y0;
    vy_n = vy0;
/*
    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t      y        vy     " << endl;
    fout << t_n << "      " << y_n << "     " << vy_n << "      " << endl;
*/

    double eps = 0.001;    
    for(int n = 1; n <= Nend; n++)
    {
        t_n = n * dt;  
        t_star = t_n + 0.5 * dt;
        
        //(R-K)
        y_star = y_n + 0.5 * dt * vy_n;
        vy_star = vy_n + 0.5 * dt * -(vy_n/t_n + y_n);

        y_np1 = y_n + dt * vy_star;
        vy_np1 = vy_n + dt * -(vy_star/t_star + y_star);


        // Stampa ogni Tprint intervalli di stampa

        /*
        if(n%Nprint==0)
        {            
            fout << t_n << "       " << y_n << "       " << vy_n << "      " << endl;
        }        
        */

        if(abs(y_n) < 0.001 )
        {
            cout << "Zero della funzione in :  " << t_n << endl;
        }

        y_n = y_np1;
        vy_n = vy_np1;
    }

//    fout.close();
    
}


int main()
{


    double dt = 0.001; 
    double Tend = 100; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
  
    double y0 = 1.0;
    double vy0 = 0.0;

    RungeKutta(dt, Nend, Nprint, y0, vy0);

    return 0;

}


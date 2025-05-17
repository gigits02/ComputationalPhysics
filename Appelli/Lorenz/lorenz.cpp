#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double x0, double y0, double z0)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    
    double sigma = 10;
    double ro = 28;
    double beta = 8.0/3.0;
    
    double t_n, x_n, y_n, x_np1, y_np1, x_star, y_star, z_n, z_np1, z_star;

    // Condizioni iniziali
    t_n = 0.0;
    x_n = x0;
    y_n = y0;
    z_n = z0;

    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t     x   y   z     " << endl;
    fout << t_n << "   " << x_n <<  "   " << y_n << "    " << z_n << "   " <<  endl;

  
    for(long int n = 1; n <= Nend; n++)
    {
    
        t_n = n * dt;

        //(R-K)
        

        x_star = x_n + 0.5* dt * sigma * (y_n - x_n);
        y_star = y_n + 0.5 * dt * (ro*x_n - x_n*z_n - y_n);
        z_star = z_n + 0.5*dt* (x_n*y_n - beta*z_n);
        
        x_np1 = x_n + dt * sigma * (y_star - x_star);
        y_np1 = y_n + dt * (ro*x_star - x_star*z_star - y_star);
        z_np1 = z_n + dt * (x_star*y_star - beta*z_star);
        

        x_n = x_np1;
        y_n = y_np1;
        z_n = z_np1;



        // Stampa ogni Tprint intervalli di stampa

        if(( n%Nprint ) == 0 )
        {
            fout << t_n << "   " << x_n << "    " << y_n << "   " << z_n << endl;
        }
    
    }

    fout.close();



}

int main()
{

    double dt = 0.00001; 
    double Tend = 20; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
  
    double x0 = 1, y0 = 11, z0 = 20;

    cout << "Primo file soluzioni con condizioni iniziali x0 = 1, y0 = 11 e z0 = 20..." << endl;
    RungeKutta(dt, Nend, Nprint, x0, y0, z0);
    x0 = 0.999;
    cout << "Secondo file soluzioni con condizioni iniziali x0 = 0.999, y0 = 11 e z0 = 20..." << endl;
    RungeKutta(dt, Nend, Nprint, x0, y0, z0);
    cout << "Le due soluzioni a lungo andare si discostano molto anche se le condizioni iniziali sono molto vicine tra loro. Questo perché il sistema è caotico." << endl;
  
    return 0;

}


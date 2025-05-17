#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double x0, double vx0, double y0, double vy0, double v0, double th0)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    const int g = 9.81;
    double t_n, x_n, y_n, x_np1, y_np1, x_star, y_star, vx_n, vy_n, vx_np1, vy_np1, vx_star, vy_star;
    double gamma = 0.3;
    double angolo = acos(-1)/4;
    
    // Condizioni iniziali
    t_n = 0.0;
    x_n = x0;
    y_n = y0;
    vx_n = vx0;
    vy_n = vy0;
    
    double xteo = v0*cos(angolo)*(1-exp(-gamma*t_n))/gamma;
    double yteo = v0*sin(angolo)*(1-exp(-gamma*t_n))/gamma  -  g*(t_n - ((1 - exp(-gamma*t_n))/gamma))/gamma;
    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t     x    xteo    y     yteo      vx     vy     xerr      yerr" << endl;
    fout << t_n << "   " << x_n << "    " << "      " << xteo << "     " << y_n << "   " << yteo << "       " << vx_n <<  "   " << vy_n << "    " <<  abs(x_n-xteo) << "        " << abs(y_n-yteo) << endl;

    double xmax;  
    bool entra = false;  
    for(long int n = 1; n <= Nend; n++)
    {
        
        t_n = n * dt;

        //(R-K)
        x_star = x_n + 0.5* dt * vx_n;
        vx_star = vx_n + 0.5 * dt * -gamma*vx_n;
        y_star = y_n + 0.5 * dt * vy_n;
        vy_star = vy_n + 0.5 * dt * (-gamma*vy_n -g);

        x_np1 = x_n + dt * vx_star;
        vx_np1 = vx_n + dt * -gamma*vx_star;
        y_np1 = y_n + dt * vy_star;
        vy_np1 = vy_n + dt * (-gamma*vy_star -g);

        x_n = x_np1;
        vx_n = vx_np1;
        y_n = y_np1;
        vy_n = vy_np1;

        xteo = v0*cos(angolo)*(1-exp(-gamma*t_n))/gamma;
        yteo = v0*sin(angolo)*(1-exp(-gamma*t_n))/gamma  -  g*(t_n - ((1 - exp(-gamma*t_n))/gamma))/gamma;
        
        if( t_n > 0.05 && y_n < 0.0001 && entra == false)
        {
            entra = true;
            cout << "Per th= " << th0 << "   la gittata vale circa= " << x_n << endl;
        }

        // Stampa ogni Tprint intervalli di stampa
        if(( n%Nprint ) == 0 )
        {
        
            fout << t_n << "   " << x_n << "    " << "      " << xteo << "     " << y_n << "   " << yteo << "       " << vx_n <<  "   " << vy_n << "    " <<  abs(x_n-xteo) << "        " << abs(y_n-yteo) << endl;
        
        }
    
    }

    fout.close();



}

int main()
{

    double dt = 0.0001; 
    double Tend = 20; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
  
    
    double v0 = 100,th0;
    double x0,y0;

    for(int i = 1; i < 11; i++)
    {
        th0 = th0 + 0.15;
        double vx0 = v0*cos(th0), vy0 = v0*sin(th0);
        RungeKutta(dt, Nend, Nprint, x0, vx0, y0, vy0, v0, th0);
    }
    return 0;
}


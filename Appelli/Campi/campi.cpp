#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double x0, double y0, double z0, double vx0, double vy0, double vz0)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;


    // Condizioni iniziali
    double vth = 9.91;
    double alpha = acos(-1)/4; 
    const int g = 9.81;
    double t_n, x_n, y_n, z_n, x_np1, y_np1, z_np1, x_star, y_star, z_star, vx_n, vx_np1, vx_star, vy_n, vy_np1, vy_star, vz_n, vz_np1, vz_star;

    
    t_n = 0.0;
    x_n = x0;
    y_n = y0;
    z_n = z0;
    vx_n = vx0;
    vy_n = vy0;
    vz_n = vz0;

    double E0 = 2, B0 = 3;

    double vr_n = sqrt(vx_n*vx_n + vy_n*vy_n + vz_n*vz_n);
    double vr_star = sqrt(x_star*vx_star + vy_star*vy_star + vz_star*vz_star);
    
    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t   x   y   z     " << endl;
    fout << t_n << "   " << x_n << "    " << y_n << "   " << z_n << endl;

    for(long int n = 1; n <= Nend; n++)
    {
    
        t_n = n * dt;

        //(R-K)

        x_star = x_n + 0.5* dt * vx_n;
        y_star = y_n + 0.5 * dt * vy_n;
        z_star = z_n + 0.5 * dt * vz_n;
        vx_star = vx_n + 0.5 * dt *  -vr_n*B0;
        vy_star = vy_n + 0.5 * dt * vr_n*B0;
        vz_star = vz_n + 0.5 * dt * E0;

        x_np1 = x_n + dt * vx_star;
        y_np1 = y_n + dt * vy_star;
        z_np1 = z_n + dt * vz_star;
        vx_np1 = vx_n + dt *  -vr_star*B0;
        vy_np1 = vy_n + dt * vr_star*B0;
        vz_np1 = vz_n + dt * E0;
        

        x_n = x_np1;
        y_n = y_np1;
        z_n = z_np1;
        vx_n = vx_np1;
        vy_n = vy_np1;
        vz_n = vz_np1;

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

    double dt = 0.0001; 
    double Tend = 50; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
  
    double x0 = 1, y0 = 2, z0 = 3;
    double vx0 = 1, vy0 = 1, vz0 = 2;
    RungeKutta(dt, Nend, Nprint, x0, y0, z0, vx0, vy0, vz0);


    return 0;

}


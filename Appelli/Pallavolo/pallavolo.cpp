#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double x0, double y0, double vx0, double vy0)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    const int g = 9.81;
    double t_n, x_n, y_n, x_np1, y_np1, x_star, y_star, vx_n, vx_np1, vx_star, vy_n, vy_np1, vy_star;

    //Condizioni iniziali
    t_n = 0.0;
    x_n = x0;
    y_n = y0;
    vx_n = vx0;
    vy_n = vy0;

    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t     x     y     vx      vy    " << endl;
    fout << t_n << "   " << x_n << "    " << y_n << "   " << vx_n <<  "   " << vy_n << "    " << "   " <<  endl;

    
    for(long int n = 1; n <= Nend; n++)
    {
        
        t_n = n * dt;

        //(R-K)
        x_star = x_n + 0.5* dt * vx_n;
        y_star = y_n + 0.5 * dt * vy_n;
        vx_star = vx_n + 0.5*dt*0.0;
        vy_star = vy_n + 0.5*dt*-g;
        
        x_np1 = x_n + dt * vx_star;
        y_np1 = y_n + dt * vy_star;
        vx_np1 = vx_n + dt * 0;
        vy_np1 = vy_n + dt * -g;

        x_n = x_np1;
        y_n = y_np1;
        vx_n = vx_np1;
        vy_n = vy_np1;

        if(( n%Nprint ) == 0 )
        {
              fout << t_n << "   " << x_n << "    " << y_n << "   " << vx_n <<  "   " << vy_n << "    " << "   " <<  endl;
        }
    
    }
   
   fout.close();

}

void trovaVelmin(double dt, long int Nend, long int Nprint, double x0, double y0, double th, double vmax, double vmin)
{
    
    double h = 2.4, l = 18;
    const int g = 9.81;
    double t_n, x_n, y_n, x_np1, y_np1, x_star, y_star, vx_n, vx_np1, vx_star, vy_n, vy_np1, vy_star;

    //Condizioni iniziali
    t_n = 0.0;
    x_n = x0;
    y_n = y0;
    
    double vi = (vmax+vmin)/2.0;
    vx_n = vi*cos(th);
    vy_n = vi*sin(th);

    double xmax = x_n;
    double ymax = y_n;
    double eps = pow(10, -3);
    for(long int n = 1; n <= Nend; n++)
    {
        
        //(R-K)
        x_star = x_n + 0.5* dt * vx_n;
        y_star = y_n + 0.5 * dt * vy_n;
        vx_star = vx_n + 0.5*dt*0.0;
        vy_star = vy_n + 0.5*dt*-g;
        
        x_np1 = x_n + dt * vx_star;
        y_np1 = y_n + dt * vy_star;
        vx_np1 = vx_n + dt * 0;
        vy_np1 = vy_n + dt * -g;

        x_n = x_np1;
        y_n = y_np1;
        vx_n = vx_np1;
        vy_n = vy_np1;

        if(x_n < 14.0)    
            if(y_n > ymax)
                ymax = y_n;

    }
    
    if(ymax < h-eps)
    {
        vmin = vi;
        trovaVelmin(dt,Nend,Nprint,x0,y0,th,vmax,vmin);
    }
    if(ymax > h+eps)
    {
        vmax = vi;
        trovaVelmin(dt,Nend,Nprint,x0,y0,th,vmax,vmin);
    } 
    else
        cout << "La velocità MINIMA affinche' la palla superi la rete è': " << vi << endl;
}

void trovaVelmax(double dt, long int Nend, long int Nprint, double x0, double y0, double th, double vmax, double vmin)
{
    
    double h = 2.4, l = 18;
    const int g = 9.81;
    double t_n, x_n, y_n, x_np1, y_np1, x_star, y_star, vx_n, vx_np1, vx_star, vy_n, vy_np1, vy_star;

    //Condizioni iniziali
    t_n = 0.0;
    x_n = x0;
    y_n = y0;
    
    double vi = (vmax+vmin)/2.0;
    vx_n = vi*cos(th);
    vy_n = vi*sin(th);

    double xmax = x_n;
    double ymax = y_n;
    double eps = pow(10, -3);
    for(long int n = 1; n <= Nend; n++)
    {
        
        //(R-K)
        x_star = x_n + 0.5* dt * vx_n;
        y_star = y_n + 0.5 * dt * vy_n;
        vx_star = vx_n + 0.5*dt*0.0;
        vy_star = vy_n + 0.5*dt*-g;
        
        x_np1 = x_n + dt * vx_star;
        y_np1 = y_n + dt * vy_star;
        vx_np1 = vx_n + dt * 0;
        vy_np1 = vy_n + dt * -g;

        x_n = x_np1;
        y_n = y_np1;
        vx_n = vx_np1;
        vy_n = vy_np1;

        if(y_n > 0.0)
            if(x_n > xmax)
                xmax = x_n;
        
    }

    
    if(xmax < l-eps)
    {
        vmin = vi;
        trovaVelmax(dt,Nend,Nprint,x0,y0,th,vmax,vmin);
    }
    if(xmax > l+eps)
    {
        vmax = vi;
        trovaVelmax(dt,Nend,Nprint,x0,y0,th,vmax,vmin);
    } 
    else
        cout << "La velocità MASSIMA affinche' la palla cada in campo è': " << vi << endl;
}

int main()
{

    double dt = 0.0001; 
    double Tend = 2; 
    double Tprint = 0.0005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
    
    double x0 = 0, y0 = 2.2, th = 0.2618, v0;
    cout << "Inserisci valore velocità iniziale: " << endl;
    cin >> v0;
    double vx0 = v0*cos(th), vy0 = v0*sin(th);

    double vmax = 20.0, vmin = 5.0;

    RungeKutta(dt, Nend, Nprint, x0, y0, vx0, vy0);
    trovaVelmin(dt, Nend, Nprint, x0, y0, th, vmax, vmin);
    trovaVelmax(dt, Nend, Nprint, x0, y0, th, vmax, vmin);

    return 0;

}


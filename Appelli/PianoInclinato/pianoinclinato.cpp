#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

const int g = 9.81;

void Backward(double dt, long int Nend, long int Nprint, double x0, double vx0, double th)
{
    double t_n, x_n, vx_n, x_np1, vx_np1;

  

    char nomeFile[256];
    cout << "Inserisci il nome del file di output:" << endl;
    cin >> nomeFile;

    //Inizializzazione
    t_n = 0;
    x_n = x0;
    vx_n = vx0;


    double m = 5, mu = 0.5, l = 20.0, k = 2.0;

    const double w = sqrt(k/m);

    double alpha = (g*(sin(th)-mu*cos(th)))/(w*w);

    double xteo = (vx0*sin(w*t_n) - alpha*w*cos(w*t_n))/w  +  alpha; 
    ofstream fout;
    fout.open(nomeFile);
    fout << "#      t_n         x_n         xteo        err    "       << endl;
    fout << "       " << t_n << "         " << x_n << "         " << xteo <<  "           " << abs(x_n-xteo) << endl;  
        
    for(long int i = 1; i <= Nend; i++)
    {
        t_n = i*dt;
        
        x_np1 = x_n + dt* vx_n;
        vx_np1 = vx_n + dt* ( -w*w*x_np1 + g*(sin(th)-mu*cos(th)) );
        
        x_n = x_np1;
        vx_n = vx_np1;
      
        xteo = (vx0*sin(w*t_n) - alpha*w*cos(w*t_n))/w  +  alpha; 
        if(i%Nprint==0)
        {       
            fout << "       " << t_n << "       " << x_n << "       " << xteo <<  "        " << abs(x_n-xteo) << endl;  
        }

    }
    fout.close();

}

void trovaVelmin(double dt, long int Nend, long int Nprint, double x0, double vx0, double th, double vmax, double vmin)
{
    double t_n, x_n, vx_n, x_np1, vx_np1;

    double m = 5, mu = 0.5, l = 20.0, k = 2.0;
    const double w = sqrt(k/m);

    //Inizializzazione
    t_n = 0;
    x_n = x0;  

    double vi = (vmax + vmin)/2.0;
    vx_n = vi;

    double xmax = x_n;
    double eps = pow(10,-2);
    for(long int i = 1; i <= Nend; i++)
    {
        t_n = i*dt;
        
        x_np1 = x_n + dt* vx_n;
        vx_np1 = vx_n + dt* ( -w*w*x_np1 + g*(sin(th)-mu*cos(th)) );
        
        x_n = x_np1;
        vx_n = vx_np1;
        
        if(x_n > xmax)
            xmax = x_n;
        
    }

    if(xmax > (l+eps))
    {
        vmax = vi;
        cout << "Troppo forte!! " << endl;
        trovaVelmin(dt,Nend,Nprint,x0,vx0,th,vmax,vmin);
    } 
    else if(xmax < (l-eps))
    {
        vmin = vi;
        cout << "Troppo piano..." << endl;
        trovaVelmin(dt,Nend,Nprint,x0,vx0,th,vmax,vmin);
    }
    else
        cout << "La velocità minima affinche' il corpo arrivi alla base del piano e': " << vi << endl;

}

int main()
{
    double v0,th;
    cout << "Inserisci valore rispettivamente di v0 (direzione x) e angolo teta del piano (suggerito th = 0.5): ";
    cin >> v0 >> th;
    double x0=0,vx0=v0;

    double dt = 0.0001;
    double Tend = 60;
    double Tprint = 0.005;

    long Nend = long(Tend/dt);
    long Nprint = long(Tprint/dt);


    Backward(dt,Nend,Nprint,x0,vx0,th);

    //Cerco la velocità minima affinché il corpo percorra x = l lunghezza del piano.
    double vmax = 13.0, vmin = 10.0;
    trovaVelmin(dt,Nend,Nprint,x0,vx0,th,vmax,vmin);
  

    return 0;

}

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double th0, double vth0, double m, double l, double d)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;


    const int g = 9.81;
  
  
    double t_n, th_n, vth_n, th_np1, vth_np1, th_star, vth_star;


    double th2_n, vth2_n, th2_np1, vth2_np1, th2_star, vth2_star;

    // Condizioni iniziali
    t_n = 0.0;
    th_n = th0;
    vth_n = vth0;
    
    double T = m*g*sin(th_n) + m*l*pow(vth_n,2);

    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t      th      vth     T       " << endl;
    fout << t_n << "   " << th_n << "    " << vth_n << "   " << T << endl;

    double eps = pow(10, -5);
    bool entra = false;
    for(long int n = 1; n <= Nend; n++)
    {
        t_n = n * dt;
        if(th_n < (3.14159/2.0 - eps) )
        {
            //(R-K)
            th_star = th_n + 0.5* dt * vth_n;
            vth_star = vth_n + 0.5 * dt * (g/l)*cos(th_n);
    
            th_np1 = th_n + dt * vth_star;
            vth_np1 = vth_n + dt * (g/l)*cos(th_star);
    
            th_n = th_np1;
            vth_n = vth_np1;
            
            T = m*g*sin(th_n) + m*l*pow(vth_n,2);


            if(( n%Nprint ) == 0 )
	        {
                fout << t_n << "   " << th_n << "    " << vth_n << "   " << T << endl;
	        }

        }
        else if(th_n > (3.14159/2.0 + eps) )
        {
            if(entra == false)
            {
                double th20 = 0, vth20 = vth_n*l/(l-d);
                th2_n = th20;
                vth2_n = vth20;
            }

            entra = true;
            //(R-K)
            th2_star = th2_n + 0.5* dt * vth2_n;
            vth2_star = vth2_n + 0.5 * dt * -(g/(l-d))*sin(th2_n);
    
            th2_np1 = th2_n + dt * vth2_star;
            vth2_np1 = vth2_n + dt * -(g/(l-d))*sin(th2_star);
    
            th2_n = th2_np1;
            vth2_n = vth2_np1;
            
            T = m*g*cos(th2_n) + m*(l-d)*pow(vth2_n,2);

            th_n = th_n + th2_n;
            if(( n%Nprint ) == 0 )
	        {
                fout << t_n << "   " << th_n << "    " << vth2_n << "   " << T << endl;
	        }


        }
        else
        {
            double vteo = sqrt(2*g*l);
            cout << "La velocità in B vale: " << l*vth_n << endl;
            cout << "Teorica: " << vteo << endl;
            cout << "Errore: " << abs(vteo-l*vth_n) << endl; 

        }
    
    }

    fout.close();



}

int main()
{

    double dt = 0.001; 
    double Tend = 100; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
  
    cout << "Inserire costanti m, l, d: ";
    double m,l,d;
    cin >> m >> l >> d;
    double th0 = 0, vth0 = 0;
    
    
    RungeKutta(dt, Nend, Nprint, th0, vth0, m, l, d);

  

  
  return 0;

}


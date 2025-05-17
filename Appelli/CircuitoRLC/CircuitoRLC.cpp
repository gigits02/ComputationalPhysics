#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double RungeKutta(double dt, long int Nend, long int Nprint, double V0, double I0, double vI0, double R, double L, double C, double w)
{

    //cout << "Nome del file di output: ";
    char nfile[256];
    //cin >> nfile;

    double t_n, t_star, I_n, vI_n, I_np1, vI_np1, I_star, vI_star;

    // Condizioni iniziali
    t_n = 0.0;
    I_n = I0;
    vI_n = vI0;
    double V_n = V0*sin(w*t_n);
    
    ofstream fout;
    //fout.open( nfile );
    //fout.precision( 15 );
//    fout << "#   t     I     V    " << endl;
//    fout << t_n << "   " << I_n << "    " << V_n << endl;

    double Imax = abs(I_n);
    for(long int n = 1; n <= Nend; n++)
    {
    
        t_n = n * dt;
        t_star = t_n + 0.5 * dt;
        //(R-K)
        I_star = I_n + 0.5* dt * vI_n;
        vI_star = vI_n + 0.5 * dt * (1/L)*V0*w*cos(w*t_n) - (R/L)*vI_n - (1/(L*C))*I_n;
    
        I_np1 = I_n + dt * vI_star;
        vI_np1 = vI_n + dt *(1/L)*V0*w*cos(w*t_star) - (R/L)*vI_star - (1/(L*C))*I_star;
        
    
        I_n = I_np1;
        vI_n = vI_np1;

        V_n = V0*sin(w*t_n);

        // Stampa ogni Tprint intervalli di stampa
        /*if(( n%Nprint ) == 0 )
        {
            fout << t_n << "   " << I_n << "    " << V_n <<  endl;
        }
        */
        if( t_n > 50 && abs(I_n) > Imax)
            Imax = abs(I_n);


    }

    fout.close();
    return Imax;

}

void checkRegime(double R, double L, double C)
{

    double parametro = (R/2)*sqrt(C/L);

    if(parametro < 1.0)
        cout << "Il regime è sotto-smorzato." << endl;
    else if(parametro > 1.0)
        cout << "Il regime è sovra-smorzato." << endl;
    else if(parametro = 1.0)
        cout << "Il regime è criticamente smorzato." << endl;

}

int main()
{

    double dt = 0.001; 
    double Tend = 100; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
    
    cout << "Inserire costanti R, L C: ";
    double R, L, C;
    cin >> R >> L >> C;

    double V0 = 1;
    double I[7];

   
    cout << "Inserisci pulsazione w: ";
    double w;
    cin >> w;

    double I0 = 0, vI0 = (V0*w)/R;
    //checkRegime(R,L,C);  
    cout << "Imax è: " << RungeKutta(dt, Nend, Nprint, V0, I0, vI0, R, L, C, w) << endl;
  
  return 0;

}


#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double RungeKutta(double dt, long int Nend, long int Nprint, double q0, double w)
{
//    cout << "Nome del file di output: ";
//    char nfile[256];
//    cin >> nfile;

    // Condizioni iniziali

    double t_n, t_star, q_n, q_np1, q_star;

    t_n  = 0.0;
    q_n  = q0;

//    ofstream fout;
//    fout.open( nfile );
//    fout.precision( 15 );
//    fout << "#   t     q     " << endl;
//    fout << t_n << "   " << q_n <<  endl;

    double V_n = sin(w*t_n);
    double VMax = V_n;
    double qMax = q_n;
    for(int n = 1; n <= Nend; n++)
    {
        t_n = n * dt;  
        t_star = t_n + 0.5 * dt;
        
        //(R-K)
        q_star = q_n + 0.5 * dt * (sin(w*t_n)-q_n);
        q_np1 = q_n + dt * (sin(w*t_star)-q_star);
        V_n = sin(w*t_n);


        // Stampa ogni Tprint intervalli di stampa

        
//       if(n%Nprint==0)
//        {            
//            fout << "       " << t_n << "       " << q_n << "       " << endl;
//        }        
  
        q_n = q_np1;

        if(q_n > qMax)
            qMax = q_n;

        if(V_n > VMax)
            VMax = V_n;

    }

    

//    fout.close();
    return qMax/VMax;
}


int main()
{


    double dt = 0.001; 
    double Tend = 100; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
  
    double q0 = 0;

    
//    RungeKutta(dt, Nend, Nprint, q0);


/*    double V[10];
    for(int i = 0; i < 10; i++)
    {
        V[i] = RungeKutta(dt, Nend, Nprint, q0);
        cout << "V[" << i << "]:  " << V[i] << endl;
    }
*/
    double w;
    cout << "Inserire w compresa tra 0.1 e 3: " << endl;
    cin >> w;

    cout << "Rapporto H = maxVu/maxV: " << RungeKutta(dt,Nend,Nprint,q0,w) << endl;
    cout << "Teorico: " << 1/sqrt(1+pow(w,2)) << endl;
    cout << "Errore: " << abs(1/sqrt(1+pow(w,2)) - RungeKutta(dt,Nend,Nprint,q0,w) ) << endl;
    return 0;

}


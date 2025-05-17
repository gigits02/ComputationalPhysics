#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

/*double bisezione(double omega1, double omega2, double vth, double th_n, long int &i, long int &N)
{
    double err = pow(10,-1);
    if(th_n < -acos(-1)-err)
    {
            omega1 = (omega2+vth)/2;
            i = 1;
            cout << "alto" << endl;
            cout << "bisezione i: " << i << endl;
    }
    else if(th_n > -acos(-1)+err)
    {
            omega2 = (omega1+vth)/2;
            i = 1;
            cout << "basso" << endl;
            cout << "bisezione i: " << i << endl;
    }
    else if(abs(th_n) == -acos(-1)-err)
    {
            double vth_n = (omega1+omega2)/2;
            i = N;
            return vth_n;
            cout << "TROVATO!" << endl;
    }

    double vth_n = (omega1+omega2)/2;

    return vth_n;
}
*/
int main()
{
    double th, vth, th_n, vth_n, th_np1, vth_np1;
    double m, g, L;
    double t_n = 0.0;

    g = 9.81;

    cout << "massa e lunghezza: " << endl;
    cin >> m;
    cin >> L;

    double omega1;
    double omega2;
    /*cout << "inserire omega1 e omega2: " << endl;
    cin >> omega1;
    cin >> omega2;
    vth = (omega1+omega2)/2;*/
    cout << "Inserisci il valore della velocità angolare:" << endl;
    cin >> vth;
    double Rx,Ry;

    th = acos(-1)/2;

    th_n = th;
    vth_n = vth;

    Rx = (m*L/2)*((-3*g/L*2)*sin(th_n)*cos(th_n)-pow(vth_n,2)*sin(th_n));
    Ry = (m*L/2)*((-3*g/L*2)*sin(th_n)*sin(th_n)+pow(vth_n,2)*cos(th_n))+m*g;

    double dt,Tprint,Tend;
    cout << "inserire dt, Tend, Tprint: " << endl;
    cin >> dt;
    cin >> Tend;
    cin >> Tprint;

    long N = long (Tend/dt);
    long Nprint = long (Tprint/dt);

    char nomeFile[256];
    cout << "Inserisci il nome del file di output: " << endl;
    cin >> nomeFile;

    ofstream file;
    file.open(nomeFile);
    file << "#      t_n         th_n        vth_n       Rx          Ry          " << endl;
    file << "       " << t_n << "       " << th_n << "      " << vth_n << "         " << Rx << "        " << Ry << "        " << endl;

    long int i = 1;
    while(i < N)
    {
        t_n = i*dt;
        th_np1 = th_n + dt*vth_n;
        vth_np1 = vth_n - dt*(3*g/2*L)*sin(th_np1);

        Rx = (m*L/2)*((-3*g/L*2)*sin(th_np1)*cos(th_np1)-pow(vth_np1,2)*sin(th_np1));
        Ry = (m*L/2)*((-3*g/L*2)*sin(th_np1)*sin(th_np1)+pow(vth_np1,2)*cos(th_np1))+m*g;

        if(i%Nprint==0)
        {
            file << "       " << t_n << "       " << th_n << "      " << vth_n << "         " << Rx << "        " << Ry << "        " << endl;
        }

        th_n = th_np1;
        vth_n = vth_np1;

        //Confronto con i valori teorici di Rx e Ry sul punto di equilibrio instabile:
        /*if(th_n <= pow(10,-2) && th_n >= -pow(10,-2))
        {
            cout << "Errore |Rx - Rx_n| = " << abs(Rx) << endl;
            cout << "Errore |Ry - Ry_n| = " << abs((5*m*g/2)-Ry) << endl;
        }
        */
        i++;   
       //Cerco il punto -pigreco con il metodo di bisezione:
       //vth_n = bisezione(omega1,omega2,vth,th_n,i,N);
      
    }

    file.close();
    return 0;
}
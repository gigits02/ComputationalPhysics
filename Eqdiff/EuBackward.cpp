#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main()
{
    cout << "Risolvo equazione: dy/dt = -k*v" << endl;
    cout << "con lo schema ad un passo EULERO BACKWARD" << endl;

    double v_n, v_np1, t_n, k, v0, v_ex, err;
    cout << "Inserisci valore della costante k:" << endl;
    cin >> k;
    cout << "Inserisci valore della velocità iniziale v0:" << endl;
    cin >> v0;


    double dt, Tend, Tprint;
    cout << "Inserire dt, Tend, Tprint:" << endl;
    cin >> dt;
    cin >> Tend;
    cin >> Tprint;

    long N = long(Tend/dt);
    long Nprint = long(Tprint/dt);

    char nomeFile[256];
    cout << "Inserisci il nome del file di output:" << endl;
    cin >> nomeFile;

    t_n = 0;
    v_n = v0;
    v_ex = v0;
    err = abs(v_ex-v0);
    ofstream fout;
    fout.open(nomeFile);
    fout << "#      t_n         v_n         v_ex        err         " << endl;
    fout << "       " << t_n << "       " << v_n << "       " << v_ex << "      " << err << endl;  


    for(long int i = 1; i <= N; i++)
    {
        //Considero eul backward ma con un passo in avanti per ottenere lo schema numerico: y_np1 = y_n + h*F(y_np1;t_np1) - h*eps(h)
        //isolo in questo caso v_np1 e trovo:
        t_n = i*dt;
        v_np1 = v_n/(1.0+k*dt ); 
        v_n = v_np1;

        if(i%Nprint==0)
        {
            v_ex = v0*exp(-k*t_n);
            err = abs(v_ex - v_n);            
            fout << "       " << t_n << "       " << v_n << "       " << v_ex << "      " << err << "       " << endl;
        }

    }
    fout.close();
    return 0;

}

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void Backward(double dt, long int Nend, long int Nprint, double x10, double vx10, double y10, double vy10, double x20, double vx20, double y20, double vy20)
{
    double t_n, x1_n, x2_n, y1_n, y2_n, vx1_n, vx2_n, vy1_n, vy2_n;
    double x1_np1, x2_np1, y1_np1, y2_np1, vx1_np1, vx2_np1, vy1_np1, vy2_np1; 
    
    const int g = 9.81;

    char nomeFile[256];
    cout << "Inserisci il nome del file di output:" << endl;
    cin >> nomeFile;

    //Inizializzazione
    t_n = 0;
    x1_n = x10;
    y1_n = y10;
    x2_n = x20;
    y2_n = y20;
    vx1_n = vx10;
    vy1_n = vy10;
    vx2_n = -vx20;
    vy2_n = vy20;

    ofstream fout;
    fout.open(nomeFile);
    fout << "#      t_n         x1_n         x2_n        y1_n       y2_n        vx1_n       vx2_n        vy1_n       vy2_n       " << endl;
    fout << "       " << t_n << "       " << x1_n << "       " << x2_n << "      " << y1_n << "        " << y2_n << "        " << vx1_n << "         " << vx2_n << "        " << vy1_n << "          " << vy2_n << "        " << endl;  

    for(long int i = 1; i <= Nend; i++)
    {
        t_n = i*dt;
        
        x1_np1 = x1_n + dt* vx1_np1;
        x2_np1 = x2_n + dt* vx2_np1;
        y1_np1 = y1_n + dt* vy1_np1;
        y2_np1 = y2_n + dt* vy2_np1;
        vx1_np1 = vx1_n + dt* 0;
        vx2_np1 = vx2_n + dt* 0;
        vy1_np1 = vy1_n + dt* -g;
        vy2_np1 = vy2_n + dt* -g;

        x1_n = x1_np1;
        x2_n = x2_np1;
        y1_n = y1_np1;
        y2_n = y2_np1;
        vx1_n = vx1_np1;
        vx2_n = vx2_np1;
        vy1_n = vy1_np1;
        vy2_n = vy2_np1;
        
        if(i%Nprint==0)
        {       
            fout << "       " << t_n << "       " << x1_n << "       " << x2_n << "      " << y1_n << "        " << y2_n << "        " << vx1_n << "         " << vx2_n << "        " << vy1_n << "          " << vy2_n << "        " << endl;  
        }

    }
    fout.close();

}

int main()
{
    double h = 30.0;
    double x10=0,x20=0,y10=h,y20=h,vx10,vy10=0,vx20,vy20=0;
    cout << "Inserisci rispettivamente la velocità del primo corpo e quella del secondo (lungo asse x):";
    cin >> vx10 >> vx20;

    double dt = 0.0001;
    double Tend = 60;
    double Tprint = 0.005;

    long Nend = long(Tend/dt);
    long Nprint = long(Tprint/dt);

    Backward(dt,Nend,Nprint,x10,vx10,y10,vy10,x20,vx20,y20,vy20);

    return 0;

}

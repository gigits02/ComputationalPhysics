#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

const long int Nmax = 10000;

void StampaRungeKutta(double dt, long int Nend, long int Nprint, double ph0, double vph0, double kn)
{

    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    double t_n, ph_n, vph_n, ph_np1, vph_np1, ph_star, vph_star;

    
    t_n = 0.0;
    ph_n = ph0;
    vph_n = vph0;

    double phteo = sqrt(2)*sin(kn*t_n);

    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   x     ph    phteo     err " << endl;
    fout << t_n << "   " << ph_n << "     "  << phteo << "      " << abs(ph_n-phteo) << endl;

    
    for(long int n = 1; n <= Nend; n++)
    {
        
        t_n = n * dt;

        //(R-K)
        ph_star = ph_n + 0.5 * dt * vph_n;
        vph_star = vph_n + 0.5*dt* -kn*kn*ph_n;
        
        ph_np1 = ph_n + dt * vph_star;
        vph_np1 = vph_n + dt *  -kn*kn*ph_star;
        
        ph_n = ph_np1;
        vph_n = vph_np1;

        phteo = sqrt(2)*sin(kn*t_n);

        // Stampa ogni Tprint intervalli di stampa
        if(( n%Nprint ) == 0 )
        {
            fout << t_n << "   " << ph_n << "     "  << phteo << "      " << abs(ph_n-phteo) << endl;
        }
    
    }

    fout.close();

}

double RungeKutta(double h, long int N, long int Nprint, double ph0, double vph0, double kn, double xj)
{
    // Condizioni iniziali
    double t_n, ph_n, vph_n, ph_np1, vph_np1, ph_star, vph_star;

    ph_n = ph0;
    vph_n = vph0;
    double y;

    for( long int j = 0; j <= N; j++ )
    {
            
        t_n = 0 + j * h;

        //(R-K)
        ph_star = ph_n + 0.5 * h * vph_n;
        vph_star = vph_n + 0.5*h* -kn*kn*ph_n;
    
        ph_np1 = ph_n + h * vph_star;
        vph_np1 = vph_n + h * -kn*kn*ph_star;
    

        ph_n = ph_np1;
        vph_n = vph_np1;

        if(t_n == xj)
        {
            y = ph_n;
            break;
        }
    }
    return y;
}


double int_simp( double f[], double h, long int N )
{
  double sump = 0.0, sumd = 0.0;

  for( long int j = 2; j <= N - 2; j = j + 2 )
    sump += f[j];
  for( long int j = 1; j <= N - 1; j = j + 2 )
    sumd += f[j];
  
  return( ( h / 3.0 ) * ( f[0] + f[N] + 2.0 * sump + 4.0 * sumd ) );

}

double funzione( double a, double h, long int N, long int Nprint, double ph0, double xk, double kn)
{
        double f[Nmax+1];
        double xj;
        
        for( long int j = 0; j <= N; j++ )
        {
            xj   = a + j * h;    
            double y = RungeKutta(h,N,Nprint,ph0,xk,kn,xj);        
            f[j] = pow(abs(y), 2);
        }

        double Norma = int_simp(f,h,N);

        return(Norma-1);

}

double derivata(double a, double h, long int N, long int Nprint, double ph0, double xk, double kn)
{
    double ff = (funzione(a,h,N,Nprint,ph0,xk+0.001,kn) - funzione(a,h,N,Nprint,ph0,(xk),kn))/0.001;
    return ff;
}

int main()
{

    double dt = 0.0001; 
    double Tend = 10; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
    
    double d = 1.0;

    double a = 0, b = d;
    long int N = 10000;
    double h = ( b - a ) / N;


    for(int n  = 1; n < 4; n++)
    {
        
        cout << "N = " << n << endl;

        double kn = n*acos(-1)/d;
        double vph0teo = sqrt(2/d)*kn;
        
        double ph0 = 0, vph0 = vph0teo + 0.01;    
        
        
        StampaRungeKutta(dt,Nend,Nprint,ph0,vph0,kn);
        
        
        cout << "Eseguirò il metodo di Newton sul parametro di ingresso di derivata prima per far sì che la norma sia uguale ad 1..." << endl;

        double eps, xk, xkp1, largh, xz;
        int cont, num_max_iter;

     
        cout << "Numero massimo di iterazioni: ";
        cin >> num_max_iter;   
        
        eps = 0.001;


        cont = 0;
        xk = vph0;
        cout.precision(15);

        // Ciclo per la ricerca col metodo di Newton
        do
        {
            cont++;
            xkp1 = xk - funzione(a,h,N,Nprint,ph0,xk,kn) / derivata(a,h,N,Nprint,ph0,xk,kn );
            //    xk+1 = xk - f(xk)/ f'(xk)
        
            largh = abs( xkp1 - xk );
            xk = xkp1;
            cout << "largh : " << largh << endl;

        }while( ( largh > eps ) );

        if ( cont < num_max_iter )
        {
            xz = xk;
            cout << "La norma ha valore 1 per una f' di ingresso pari a : " << xz << " +- " << 0.5 * largh << endl;
            cout << "Valore della norma nello zero: " << funzione(a,h,N,Nprint,ph0,xz,kn) << endl;
            cout << "Numero di iterazioni necessarie per il calcolo dello zero con la tolleranza voluta: " << cont << endl;
        }
        else
        { 
            cout << "La successione di valori NON e' arrivata a convergenza entro ";
            cout << num_max_iter << " iterazioni!" << endl;
            cout << "Prova ad aumentare il numero massimo di iterazioni o a scegliere un x0 differente!" << endl;
        } 
        
        cout << "Valore della funzione nel parametro iniziale = " << funzione(a,h,N,Nprint,ph0,vph0teo,kn) << endl;
    }
        
    return 0;

}


#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void RungeKutta(double dt, long int Nend, long int Nprint, double x0, double y0, double a, double b, bool due)
{
    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    // Condizioni iniziali
    double t_n, x_n, y_n, x_np1, y_np1, x_star, y_star;

    
    t_n = 0.0;
    x_n = x0;
    y_n = y0;
    
    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t      x       y     " << endl;
    fout << t_n << "   " << x_n << "    " << y_n << "   " <<  endl;

    
    for(long int n = 1; n <= Nend; n++)
    {
        
        t_n = n * dt;

        //(R-K)
        x_star = x_n + 0.5* dt * ( a+ x_n*x_n*y_n - b*x_n - x_n );
        y_star = y_n + 0.5 * dt * ( b*x_n - x_n*x_n*y_n );

        x_np1 = x_n + dt * ( a+ x_star*x_star*y_star - b*x_star - x_star );
        y_np1 = y_n + dt * ( b*x_star - x_star*x_star*y_star );
        

        x_n = x_np1;
        y_n = y_np1;


        // Stampa ogni Tprint intervalli di stampa
        if(( n%Nprint ) == 0 )
        {
            fout << t_n << "   " << x_n << "    " << y_n << "   " << endl;
        }
    
    }
    if(due == true)
    {
        cout << "Le soluzioni tendono ad essere x = " << x_n << "       y_n = " << y_n << endl;
        cout << "Quelle previste sono:   x = " << a << "       y = " <<  b/a << endl;
    }
    
    fout.close();

}

bool equazione(double a, double b)
{

    if( b < (1+pow(a,2)) )
        return true;
    else
        return false;
}

int main()
{

    double dt = 0.0001; 
    double Tend = 100; 
    double Tprint = 0.005;

    long int Nend = long( Tend / dt );
    long int Nprint = long( Tprint / dt );
    
        
    double a,b;
    double x0,y0;
    
    cout << "Inserisci valori di a e b: " << endl;
    cin >> a >> b;

    bool due = equazione(a,b);
    if(due == true)
        cout << "L'equazione 2 è soddisfatta" << endl;
    else if(due == false)
        cout << "L'equazione 2 NON è soddisfatta!!" << endl;
            
     for(int n = 1; n < 4; n++)
    {   
        cout << n << "° COPPIA DI VALORI INIZIALI " << endl;
        cout << "Inserisci valori di x0 e y0: " << endl;
        cin >> x0 >> y0;

        RungeKutta(dt, Nend, Nprint, x0, y0,a,b,due);  
    }

  return 0;

}


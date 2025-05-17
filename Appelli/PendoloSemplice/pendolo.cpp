#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void Simplettico(double dt, long int Nend, long int Nprint, double th0, double vth0, double w, double w2)
{
    
    cout << "Nome del file di output: ";
    char nfile[256];
    cin >> nfile;

    double  t_n, th_n, th_np1, vth_n, vth_np1;
    

    t_n  = 0.0;
    th_n  = th0;
    vth_n  = vth0;


    ofstream fout;
    fout.open( nfile );
    fout.precision( 15 );
    fout << "#   t     th     vth     " << endl;
    fout << t_n << "   " << th_n << "    " << vth_n << endl;


    for( long n = 1; n <= Nend; n++ )
    {
        t_n = n * dt;       
	      th_np1 = th_n + dt * vth_n;
	      vth_np1 = vth_n - w2 * dt * sin(th_np1);	
	

        th_n = th_np1;
        vth_n = vth_np1;

    

        // Stampa ogni Tprint intervalli di stampa

        if( (n % Nprint)  == 0 )
	    {
            fout << t_n << "  " << th_n << "   " << vth_n << endl;
	    }

    }

  fout.close();
  
}


// Funzione da integrare

double F( double x, double vth0, double w2)
{
  double ff = 1/sqrt(vth0*vth0-2*w2*(1-cos(x)));
  return( ff );
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

int main()
{
  
  double dt = 0.001;
  double Tend = 50;
  double Tprint = 0.005;


  long Nend = long( Tend / dt );
  long Nprint = long( Tprint / dt );

  double th0 = 0.0;
  cout << "Inserire costanti w, vth0: ";
  double w,vth0;
  cin >> w >> vth0;
  double w2 = w * w;

//Simplettico(dt,Nend,Nprint,th0,vth0,w,w2);

 
  const long int Nmax = 10000;

  

  long int N;
  cout << "Numero di intervalli su cui calcolare l\'integrale: ";
  cin >> N;
  
  if ( ( N % 2 ) != 0 )
  {
    cout << "Errore! In numero di intervalli DEVE essere PARI!" << endl;
    exit( 0 );
  }

  if ( Nmax < N )
  {
    cout << "Errore! Il valore di Nmax e' piu' piccolo del valore di N scelto!" << endl;
    cout << "Nmax = " << Nmax << endl;
    cout << "N = " << N << endl;
    exit( 0 );
  }

  // Definisce la funzione sui punti nodali

  double th;
  cout << "Inserisci l'estremo superiore (theta) dell'integrale per ricavare il tempo: " << endl;
  cin >> th;

  double Inum[10];

  for(int i = 0; i < 10; i++)
  {  
    double xj;
    double f[Nmax+1];
    double h = ( th - 0 ) / N;



    for( long int j = 0; j <= N; j++ )
    {
      xj   = j * h;
      f[j] = F( xj, vth0, w2 );
    }


    // Calcolo dell'integrale definito


    Inum[i] = int_simp( f, h, N );


    // Stampa del risultato

    cout.precision(15);
    cout << "Risultato integrazione numerica: I_num = " << Inum[i] << endl;

    th = th+0.0001; 
  }
  
  return 0;
    
} 
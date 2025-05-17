#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void Simplettico(double dt, long int Nend, long int Nprint, double ph0, double vph0)
{

  cout << "Nome del file di output: ";
  char nfile[256];
  cin >> nfile;

  double  t_n, ph_n, vph_n, ph_np1, vph_np1;


  t_n  = 0.0;
  ph_n = ph0;
  vph_n = vph0;

  ofstream fout;
  fout.open( nfile );
  fout.precision( 15 );
  fout << "#   r    ph     vph    " << endl;
  fout << t_n << "  " << ph_n << "   " << vph_n << endl;

  double t_np1;
  for( long n = 1; n <= Nend; n++ )
  {
    t_n = n * dt;       
	  t_np1 = t_n + dt;

    ph_np1 = ph_n + dt * vph_n;
    vph_np1 = vph_n + dt * pow(ph_np1, 3./2.)/sqrt(t_np1);		
                
    ph_n = ph_np1;
    vph_n = vph_np1;
      
    // Stampa ogni Tprint intervalli di stampa
    if( (n % Nprint)  == 0 )
    {
      fout << t_n << "  " << ph_n << "     " << vph_n << endl;
	  }

  }

  fout.close();
  
}


int main()
{

  double dt = 0.0001;
  double Tend = 4.5;
  double Tprint = 0.005;


  long Nend = long( Tend / dt );
  long Nprint = long( Tprint / dt );

  double ph0 = 1, vph0 = 1.588;

  Simplettico(dt,Nend,Nprint,ph0,vph0);

  return 0;
    
} 
#include <iostream>
#include <cmath>
#include <fstream>


using namespace std;


void leggiFile( double* a, int dim );
double media( double* a, int dim );
double devst( double* a, int dim);
void istogramma( double* a, int dim, double* xc, double* yc, int dimc);
double trovaMin( double* a, int dim );
double trovaMax( double* a, int dim );
void printout( double* xc, double* yc, int dimc );

//------------------------------


int main()
{
    
    int size;							
	cout << "Quanti valori inserisci? ";			
	cin >> size;

    int sizec;
    cout << "In quante classi vuoi dividerli? ";
    cin >> sizec;

	double* v = new double[size];				
	double* xc = new double[sizec];
    double* yc = new double[sizec];

    for(int i = 0; i < sizec; i++ )
    {   
        xc[i] = 0.0;
        yc[i] = 0.0;
    }
 
    leggiFile( v, size );

    cout << "Media dei valori: " << media(v, size) << endl;
    cout << "Deviazione standard: " << devst(v, size) << endl;
    
    

    istogramma( v, size, xc, yc, sizec);

    printout( xc, yc, sizec);
	
    delete[]v;
    delete[]xc;
    delete[]yc;

	return 0;   

}

//Lettura del file "dati.dat"
void leggiFile( double* a, int dim)
{

    ifstream readfile;

    readfile.open( "dati.dat");

    for(int i = 0; i < dim; i++)
        readfile >> a[i];

    readfile.close();

}

//Scrittura del file
void printout( double* xc, double* yc, int dimc )
{

    cout << "Nome del file di output: ";
    char writefile[200];
    cin >> writefile;
   
    ofstream fout;
    fout.open( writefile );

    for(int i = 0; i < dimc; i++ )
        fout << xc[i] << "       " << yc[i] << endl;

    fout.close(); 


}



double media( double* a, int dim )
{
    double average;
    double sum = 0.0;

    for(int i = 0; i < dim; i++)
        sum += a[i];
    //  (sum = sum + a[i]);

    average = sum/dim;

    return average;

}


double devst( double* a, int dim)
{
    double stdev;
    double sum = 0.0;
    double average = media(a,dim);

    for(int i = 0; i < dim; i++)
        sum += pow( (a[i]- average), 2 );


    stdev = sqrt(sum/dim);

    return stdev;
    

}


void istogramma( double* a, int dim, double* xc, double* yc, int dimc)
{

    double step = (trovaMax(a,dim)-trovaMin(a,dim))/dimc;
    double maxc;
    double minc = trovaMin(a,dim);

    int k = 0;
    int n = 0;

    for(int i = 0; i < dimc; i++)
    {
        n = i;
        maxc = minc + step;
    
        for(int j = 0; j < dim; j++)
        {
            if(a[j] >= minc && a[j] <= maxc )
            { 
                yc[k]= yc[k]+1.0;   
            }
        }    
        
        xc[n] = n+1;
        
        cout << "Classe nr. " << xc[n] << ":  (Min: " << minc << " Max: " << maxc << " )" << endl << "occorrenze: " << yc[k] << endl;
        k++;
        minc = maxc;
     
    }








}

double trovaMin( double* a, int dim )
{
    double min = a[0];
    
    for(int i = 1; i < dim; i++)
        if( a[i] < min )
            min = a[i];

    return min;
}

double trovaMax( double* a, int dim )
{
    double max = a[0];

    for(int i = 1; i < dim; i++)
        if( a[i] > max )
            max = a[i];

    return max;
}





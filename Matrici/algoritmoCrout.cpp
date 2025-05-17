#include <iostream>
#include <cmath>

using namespace std;

#define dim 3

void stampa_matrice(double A[dim][dim])
{
    cout.precision(15);
    for(int i = 0; i < dim; i++)
    {   
        for(int j = 0; j < dim; j++)
            cout << A[i][j] << "   ";

        cout << endl;
    }

    cout << endl;

}

void stampa_vettore(double a[dim])
{
    cout.precision(15);
    for(int i = 0; i < dim; i++)
        cout << a[i] << "   ";

    cout << endl;

}

void compilamatrice( double A[dim][dim] )
{
    for( int i = 0; i < dim; i++ )
		for( int j = 0; j < dim; j++ )
		{
			cout << "Inserisci elemento in posizione M[" << i << "][" << j << "]" << endl;
			cin >> A[i][j];
		}

}

void lu_fact(double A[dim][dim])
{
    double sum;

    for(int j = 1; j < dim; j++)
        A[0][j] = A[0][j]/A[0][0];

    
    for(int i = 1; i < dim; i++ )
    {
        for(int j = 1; j <= i; j++)
        {
            sum = 0,0;
            for(int k = 0; k <= j-1; k++)
                sum = sum + A[i][k]*A[k][j];
            
            
            A[i][j] = A[i][j] - sum;
                    
        }

        for(int j = i+1; j < dim; j++)
        {   
           
           
            sum = 0.0;
            for(int k = 0; k <= i-1; k++)
                sum = sum + A[i][k]*A[k][j];
                
                
            A[i][j] = ( A[i][j] - sum )/A[i][i];

        }     

        

    }


}

void lu_solve( double A[dim][dim], double b[dim], double x[dim])
{

    double sum;
    double y[dim];


    //Forward substitution: Ly = b
    y[0] = b[0]/A[0][0];

    for(int i = 1; i < dim; i++)
    {
        sum = 0.0;
        for(int j = 0; j <=i-1; j++)
            sum = sum + A[i][j] * y[j];
        
        
        y[i] = (b[i] - sum) / A[i][i];
        

    }


    //Backward substitution: Ux = y
    x[dim-1] = y[dim-1];

    for(int i = dim-2; i >= 0; i--)
    {
        sum = 0.0;
        for(int j = i+1; j < dim; j++)
            sum = sum + A[i][j] * x[j];
            
            
        x[i] = y[i] - sum;
        
        

    }
    

}

void prodmatricexvettore(double A[dim][dim],double x[dim], double bb[dim])
{

    double sum;
    
    for(int i = 0; i < dim; i++)
    {
        sum = 0.0;
        for(int j = 0; j < dim; j++)
            sum = sum + A[i][j]*x[j];

    
        bb[i] = sum;
    
    }       


}

int main()
{
    cout << "calcolo della soluzione di un sistema tramite fattorizzazione LU" << endl;
    int i, j;

    double A[dim][dim];
    compilamatrice(A);

    
    //poichè la matrice mat viene modificata dalla fattorizzazione, la copiamo in una matrice temporanea che verrà utilizzata per verifica;
    double temp[dim][dim];
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
            temp[i][j] = A[i][j];



    //stampa sullo schermo la matrice iniziale
    cout << "Matrice iniziale:" << endl;
    stampa_matrice(A);

    //esegue la fattorizzazione LU della matrice
    lu_fact(A);

    cout << "Matrice fattorizzata LU:" << endl;
    stampa_matrice(A);


    //costruisce i secondi membri del sistema e alloca la memoria per il vettore soluzione
    double b[dim] = {0.0, 1.0, 2.0};
    double x[dim];

    //stampo vettore secondo membro per verifica
    cout << "Vettore secondo membro:" << endl;
    stampa_vettore(b);

    //Risolvo il sistema lineare con la risoluzione FS e BS: 
    lu_solve (A,b,x);

    cout << "Vettore soluzione del sistema lineare:" << endl;
    stampa_vettore(x);


    //VERIFICA DELLA SOLUZIONE:

    cout << "Verifica del risultato:" << endl;
    cout << "Prodotto matrice per vettore soluzione:" << endl;
    double bb[dim];
    prodmatricexvettore(temp,x,bb);
    stampa_vettore(bb);


    return 0;

}




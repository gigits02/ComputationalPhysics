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
        {
            if(A[i][j]*A[i][j] <= pow(10, -10))
                A[i][j] = 0;
            
            cout << A[i][j] << "   ";
        }    

        cout << endl;
    }

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
        for(int j = i+1; j <= dim; j++)
            sum = sum + A[i][j] * x[j];
            
            
        x[i] = y[i] - sum;
        

    }
    

}

void prodmatricexmatrice(double A[dim][dim], double B[dim][dim], double C[dim][dim])
{

    double sum;
    
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
        {
            sum = 0.0;
            for(int k = 0; k < dim; k++)
                sum = sum + A[i][k]*B[k][j];

            C[i][j] = sum;
        }
            
  
}

int main()
{
    cout << "calcolo della matrice inversa" << endl;

    double A[dim][dim];
    compilamatrice(A);                

    
    double temp[dim][dim];
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
            temp[i][j] = A[i][j];


    double inv[dim][dim];

    //esegue la fattorizzazione LU della matrice
    lu_fact(A);

    cout << "Matrice fattorizzata LU:" << endl;
    stampa_matrice(A);


    //costruisce i secondi membri del sistema e alloca la memoria per il vettore soluzione
    double x[dim];
    double b[dim];

    for(int j = 0; j < dim; j++)
    {
        for(int i = 0; i < dim; i++)
        {
            b[i] = 0.0;
            if(j==i)
                b[i] = 1.0;

        }
        //Risolve il j-esimo sistema Ax = b
        lu_solve(A,b,x);

        //Copia nella j-esima colonna della inversa
        for(int i = 0; i < dim; i++)
            inv[i][j] = x[i];

    }

    cout << "Matrice inversa:" << endl;
    stampa_matrice(inv);

    //VERIFICA DELLA SOLUZIONE:
    double I[dim][dim];
    cout << "Verifica del risultato:" << endl;
    cout << "Prodotto matrice per matrice:" << endl;
    double bb[dim];
    prodmatricexmatrice(temp,inv,I);
    stampa_matrice(I);


    return 0;

}














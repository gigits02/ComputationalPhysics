#include <iostream>
#include <cmath>

#define dim 3
using namespace std;

void compilamatrice( double A[dim][dim] )
{
    for( int i = 0; i < dim; i++ )
		for( int j = 0; j < dim; j++ )
		{
			cout << "Inserisci elemento in posizione M[" << i << "][" << j << "]" << endl;
			cin >> A[i][j];
		}

}

void stampa_matrice(double A[3][dim])
{
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            if(A[i][j] <= 0.00005)
                cout << 0 << " ";
            else 
                cout << A[i][j] << " ";
        
        }
        cout << endl;
    }

}

void stampa_vettore(double a[dim])
{
    for(int i = 0; i < dim; i++)
        cout << a[i] << " "; 

    cout << endl;
}


void lu_fact(double A[3][dim], double L[dim][dim], double U[dim][dim] )
{
    //(Doolittle)
    U[0][0] = A[0][0];

    for(int i = 1; i < dim; i++)
    {
        L[i][i-1] = A[i][i-1]/U[i-1][i-1];
        U[i][i] = A[i][i] - L[i][i-1]*A[i-1][i];
        U[i-1][i] = A[i-1][i]; 
    }

}

void lu_solve( double A[dim][dim], double L[dim][dim], double U[dim][dim], double f[dim], double x[dim] )
{
    double y[dim];

    y[0] = f[0];
    for(int i = 1; i < dim; i++)
        y[i] = f[i] - L[i][i-1]*y[i-1];
    
    x[dim-1] = y[dim-1]/U[dim-1][dim-1];
    for(int i = dim-2; i >= 0; i--)
        x[i] = (y[i]-A[i][i+1]*x[i+1])/U[i][i];
}

void prodmatricexvettore( double A[dim][dim], double x[dim], double f[dim])
{

    for(int i = 0; i < dim; i++)
    {
        double sum=0;
        for(int j = 0; j < dim; j++)
        {
            sum += A[i][j]*x[j];
        }
        f[i] = sum;
    }

}
   
void ProdottoMatriciale(double L[dim][dim], double U[dim][dim])
{
    double somma=0.0;
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
        {
            for(int k=0;k<dim;k++)
            {
               somma+= L[i][k]*U[k][j];
            }
            if(somma <= 0.00005)
                cout << 0 << " ";
            else 
                cout<<somma<<" ";
            
            
            somma=0;
        }
        cout<<endl;
    }   
}

int main()
{
    double A[dim][dim];
    compilamatrice(A);
    cout << "Matrice A:" << endl;
    stampa_matrice(A);
    double L[dim][dim];
    double U[dim][dim];
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++ )
        {
            if(j == i)
            {
                L[i][j] = 1;
                U[i][j] = 0;
            }
            else
            {
                L[i][j] = 0;
                U[i][j] = 0;
            }
            
        }
    
    lu_fact(A,L,U);
    cout << "Matrice A:" << endl;
    stampa_matrice(A);
    cout << "Matrice L:" << endl;
    stampa_matrice(L);
    cout << "Matrice U:" << endl;
    stampa_matrice(U);
    cout << "Matrice prodotto:" << endl;
    ProdottoMatriciale(L,U);
    double f[3] = {1.0,2.0,3.0};
    double x[3];
    lu_solve(A,L,U,f,x);
    cout << "Vettore soluzione sistema:" << endl;
    stampa_vettore(x);
    cout << "Verifica soluzione:" << endl;
    prodmatricexvettore(A,x,f);
    stampa_vettore(f);

    return 0;

}
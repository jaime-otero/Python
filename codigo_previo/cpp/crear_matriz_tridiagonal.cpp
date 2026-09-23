#include <iostream>
#include <fstream>  // para salida/entrada por fichero
#include <string>
#include <cmath>
#include <iomanip>  // para std::setprecision
using namespace std;

#include <cmatrix>
using namespace techsoft;

int main(){

  // Definimos una matriz

    int n = 1000; // tamaño de la matriz tridiagonal

    int nrows=n, ncols=n+1;
    matrix<double> A(nrows,ncols);

    // Rellenamos la matriz tridiagonal
    for (int i = 0; i < nrows; ++i) {
        A(i,i) = 3; // diagonal principal
        if (i > 0) {
            A(i,i-1) = 1.2; // subdiagonal
        }
        if (i < nrows -1) {
            A(i,i+1) = -2.5; // superdiagonal
        }
        A(i,ncols-1) = -50; // inicializamos el último elemento de cada fila a 0

    }

    A(0,ncols-1) = 2.2; // último elemento de la primera fila
    A(n-1,ncols-1)= 3.6; // último elemento de la última fila



   string nombre = "matriz.txt";
  
  ofstream ff(nombre);
    
  if (ff.is_open()){
    // ff << scientific << setprecision();
    ff << A;
    // Cerramos el fichero
    ff.close();
    
  } else cout << "No se ha podido abrir el fichero" << endl;
  


  return 0;
}


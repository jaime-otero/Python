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
    int nrows=3, ncols=4;
    matrix<double> A(nrows,ncols);
    A.null();

    double lambda1, lambda2, lambda3;
    lambda1 = 6563;
    lambda2 = 6439;
    lambda3 = 5890;

    A(0,0) = 1; A(0,1) = pow(lambda1,-2); A(0,2) = pow(lambda1,-4); A(0,3) = 1.50883;
    A(1,0) = 1; A(1,1) = pow(lambda2,-2); A(1,2) = pow(lambda2,-4); A(1,3) = 1.50917;  
    A(2,0) = 1; A(2,1) = pow(lambda3,-2); A(2,2) = pow(lambda3,-4); A(2,3) = 1.51124;

   string nombre = "matriz.txt";
  
  ofstream ff(nombre);
    
  if (ff.is_open()){
    ff << scientific << setprecision(8);
    ff << A;
    // Cerramos el fichero
    ff.close();
    
  } else cout << "No se ha podido abrir el fichero" << endl;
  


  return 0;
}


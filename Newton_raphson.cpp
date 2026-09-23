#include <iostream>
#include <fstream>
#include <string>
#include <cmath>    
#include <iomanip>
#include <sstream>

using namespace std;

// Inclusión de la librería de matrices 'cmatrix'
#include <cmatrix> 
using namespace techsoft;

const double pi = 3.14159265358979323846;


// Norma máxima de una matriz
double norma_maxima (const matrix<double>& A) {
    int nrows = A.rowno();
    int ncols = A.colno();
    double max_val = 0.0;
    double sum = 0.0;
    for (int i = 0; i < nrows; i++) {
        sum = 0.0;
        for (int j = 0; j < ncols; j++) {
            sum += abs(A(i, j));    
        }
        if (sum > max_val) {
                max_val = sum;
        }
    }
    return max_val;
}
    

// Define el vector de funciones F(x,y,z)
matrix <double> F(const matrix <double> xx) {

    // Extraer variables del vector columna (x, y, z)
    double x = xx(0,0);
    double y = xx(1,0); 
    double z = xx(2,0);

    matrix <double> funciones(3,1); // Vector columna F(x)
    
    // Ecuaciones:
    funciones(0,0) =  6*x - 2*cos(y*z) -1.5;
    funciones(1,0) =  y + sqrt(x*x + sin(z) + 3.3);
    funciones(2,0) = 40*z + 3*exp(-x*y) + pi - 3;

    return funciones;
}

matrix <double> J(const matrix <double> vars) {

    
    double x = vars(0,0);
    double y = vars(1,0); 
    double z = vars(2,0);

    matrix <double> jacobiano(3,3);

    // Fila 0 (derivadas de f0)
    jacobiano(0,0) = 6; 
    jacobiano(0,1) = 2*z*sin(y*z); 
    jacobiano(0,2) = 2*y*sin(y*z); 

    // Fila 1 (derivadas de f1)
    jacobiano(1,0) = x/sqrt(x*x + sin(z) + 3.3); 
    jacobiano(1,1) = 1; 
    jacobiano(1,2) = cos(z)/(2*sqrt(x*x + sin(z) +3.3)); 

    // Fila 2 (derivadas de f2)
    jacobiano(2,0) = -3*y*exp(-x*y); 
    jacobiano(2,1) = -3*x*exp(-x*y); 
    jacobiano(2,2) = 40; 

    return jacobiano;
}

// metodo de Newton-Raphson
matrix <double> NewtonRaphson(matrix <double>& xx, double tol, int max_iter, matrix <double> (*F)( matrix <double>), matrix <double> (*J)(matrix <double>)) {

        matrix <double> F_act = F(xx);
        matrix <double> J_act = J(xx);
        
    do
    for (int iter = 0; iter < max_iter; ++iter) {
        


        double det = J_act.det();

        // Comprobación de que la matriz del Jacobiano no es singular
        if (abs(det) < 1e-12) { 
            cout << "\nEl jacobiano es singular o casi singular. No se puede continuar." << endl;
            return xx;
        }
        
        matrix <double> delta = -1/det * J_act.adj() * F_act;
        
        // Aplicar la corrección: x^(k+1) = x^k + delta
        xx = xx + delta;
        
        // Condición de parada: ||delta|| < tolerancia
        if (norma_maxima(delta)< tol) {
            cout << "\n\nLa solucion converge en " << iter + 1 << " iteraciones." << endl;

            cout << "\n La solucion es: " << endl;
            cout << "x = " << xx(0,0)  << endl;
            cout << "y = " << xx(1,0)  << endl;
            cout << "z = " << xx(2,0)  << endl;

            // Comprobacion de la solucion (F(x) = 0)
            matrix <double> F_sol = F(xx);

                cout << scientific << setprecision(2); // Usamos 8 decimales para la precisión de 10^-8


            cout << "\n --- Comprobacion de la Solucion (Residual) ---" << endl;
            cout << "Tolerancia (eps): " << tol << endl;
            
            // Imprimir el valor residual de cada funcion
            for (int i = 0; i < F_sol.rowno(); ++i) {
                char func_name = char('f' + i);
                double residual = F_sol(i,0);

                cout << func_name << "(x,y,z) = " << residual;

                if (abs(residual) > tol) {
                    cout << " --> NO CUMPLE |residual| > tol" << endl;
                } 
                else {
                    cout << " --> CUMPLE: |residual| < tol" << endl;
                }
            }
           
            return xx;
        } else if (iter == max_iter - 1) {
            cout << "\n No se alcanzo la convergencia en el maximo numero de iteraciones." << endl;
        }
        F_act = F(xx);
        J_act = J(xx);      
    }
    while (xx(0,0)<5 &&  xx (1,0) < 4 );
    
    return xx;
}

// Programa principal
int main(){

    cout << fixed << setprecision(8); // Usamos 8 decimales para la precisión de 10^-8
    
    // Definición de constantes
    double tol = 1e-8; // Tolerancia de convergencia
    int max_iter = 100; // Máximo número de iteraciones

    // Valores iniciales (x0, y0, z0) = (1, 1, 1) 
    double x_init = 1, y_init = 1, z_init = 1; 
    matrix <double> xx(3,1); 

    xx(0,0) = x_init; // valor inicial x
    xx(1,0) = y_init; // valor inicial y  
    xx(2,0) = z_init; // valor inicial z

    matrix <double> funciones = F(xx);

    // Comprobación inicial
    if (norma_maxima(funciones) < tol) {
        cout << "La solucion inicial ya satisface el sistema de ecuaciones." << endl;
        cout << "x = " << xx(0,0)  << endl;
        cout << "y = " << xx(1,0)  << endl;
        cout << "z = " << xx(2,0)  << endl;
        return 0;
    }
    
    cout << "Metodo de Newton-Raphson para sistemas de ecuaciones no lineales: \n" << endl;
    cout << "Sistema a resolver (F(x) = 0):"<< endl;
    cout << "f: 6*x - 2*cos(y*z) - 1.5 = 0"<< endl;
    cout << "g: y + sqrt(x*x + sin(z) + 3.3) = 0" << endl;
    cout << "h: 40*z + 3*exp(-x*y) + pi - 3 = 0" << endl;
    cout << "------------------------------------------" << endl;

    cout << "\nBuscando solucion ";


    matrix <double> solucion = NewtonRaphson(xx, tol, max_iter, F, J);


    return 0;
}
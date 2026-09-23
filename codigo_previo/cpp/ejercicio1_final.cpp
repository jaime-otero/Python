#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>  // para setprecision
#include <sstream>
#include <fstream>
using namespace std;

// constantes

double V = 1e-3;
double rho = 6.022e28;
double kb = 1.381e-23;
double theta = 428;

// ==========================================================
// 1. DEFINICIÓN DE FUNCIONES
// ==========================================================
double f(double x) { 
    return x*x*x*x*exp(x)/(exp(x)-1)/(exp(x)-1);
}


// --- Simpson 1/3 ---
double simpson13(double a, double b, int n,double (*func)(double)) {
    if (n % 2 == 1) n++; // n debe ser par
    double h = (b - a) / n;
    double suma = func(a) + func(b);
    for (int i = 1; i < n; i += 2) { 
        suma += 4.0 * func(a + i * h);
    }
    for (int i = 2; i < n; i += 2) { 
        suma += 2.0 * func(a + i * h);
    }
    return suma * h / 3.0;
}

// ==========================================================
// MAIN
// ==========================================================
int main() {

    cout << fixed << setprecision(8);
    double h = 1.0; //paso de temperatura
    double T = 5.0;
    double Tmax = 1000;
    double a = 0.000000000000001; // limite inferior, no pongo 0 porque sino f(0) = 0/0 y da error
    double b = theta/T;

    double C = 9*V*rho*kb*pow(T/theta, 3);

    double int13,int38,res13,res38;


    
    // Fichero de salida
string nombrei = "ejercicio1.txt";
ofstream fi(nombrei);

    cout << "Comenzando la integracion" << endl;

if (fi.is_open()) {
        fi << fixed << setprecision(5);
        // Usamos 'fi' para escribir el encabezado
        fi << "Temperatura\t\t  Simpson 1/3  \t\t  Simpson 3/8  \n";
        fi << "----------------------------------------------------------------------------------\n";
        do{

        b = theta/T;
        C = 9*V*rho*kb*pow(T/theta, 3);

        int13 = simpson13(a, b, 100, f);

        res13 = C*int13;

        fi << T << "\t\t\t\t" << res13 << endl;
        
        T += h;

        }while (T < Tmax + h/2); // para evitar que el residual del ordenador cause un mayor numero de iteraciones 
        fi.close();
    } else {
        cout << "No se ha podido abrir el fichero: " << nombrei << endl;
    }

    cout << "Datos guardados en " << nombrei << endl;

    return 0;
}
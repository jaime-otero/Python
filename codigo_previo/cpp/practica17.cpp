#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

#include <cmatrix> 
using namespace techsoft;
using namespace std;

// Constantes del sistema
const double w = 7.29e-5;      // Velocidad angular (s^-1) 
const double g = 9.8;          // Gravedad (m/s^2) 
const double l = 25.0;         // Longitud (m) 
const double k_sq = g / l;     // Constante k^2 = g/l
const double psi = M_PI / 4.0; // Latitud (radianes)

// Cálculo de la norma máxima de una matriz/vector
double norma_maxima(const matrix<double> &A) {
    double max_val = 0.0;
    for (size_t i = 0; i < A.rowno(); ++i) {
        for (size_t j = 0; j < A.colno(); ++j) {
            double val = fabs(A(i,j));
            if (val > max_val) {
                max_val = val;
            }
        }
    }
    return max_val;
}

// Sistema de Ecuaciones Diferenciales Ordinarias
matrix<double> Z(const matrix<double> &X, double t) {
    matrix<double> dY(4,1);
    
    // x' = vx
    dY(0,0) = X(1,0); 
    // vx' = 2*w*sin(psi)*vy - k^2*x
    dY(1,0) = (2.0 * w * sin(psi) * X(3,0)) - (k_sq * X(0,0)); 
    // y' = vy
    dY(2,0) = X(3,0); 
    // vy' = -2*w*sin(psi)*vx - k^2*y
    dY(3,0) = (-2.0 * w * sin(psi) * X(1,0)) - (k_sq * X(2,0)); 

    return dY;
}

// Método de Runge-Kutta de 4º orden
matrix<double> runge_kutta_4(const matrix<double> &X, double t, double dt, double t_max, const string &nombre, bool guardar) {

    matrix<double> k1(4,1), k2(4,1), k3(4,1), k4(4,1);
    matrix<double> X_new = X;
    ofstream fout;

    if (guardar) {
        fout.open(nombre);
        if (!fout.is_open()) {
            cerr << "Error al abrir el fichero: " << nombre << endl;
            return X_new;
        }
        fout << fixed << setprecision(6);
    }

    do {
        if (guardar) {
            fout << t << "\t" << X_new(0,0) << "\t" << X_new(2,0) << endl;
        }

        k1 = Z(X_new, t);
        k2 = Z(X_new + 0.5 * dt * k1, t + 0.5 * dt);
        k3 = Z(X_new + 0.5 * dt * k2, t + 0.5 * dt);
        k4 = Z(X_new + dt * k3, t + dt);

        X_new = X_new + (dt / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
        t += dt;

    } while(t <= t_max);

    if (guardar) {
        fout.close();
    }

    return X_new;
}

int main() {
    // Definición de condiciones iniciales
    matrix<double> X_init(4,1);
    X_init(0,0) = 0.25; // x(0)
    X_init(1,0) = 0.0;  // vx(0)
    X_init(2,0) = 0.0;  // y(0)
    X_init(3,0) = 0.0;  // vy(0)

    // Parámetros de simulación
    double t = 0.0;
    double t_max = 10.0; 
    double tol = 1e-2;    
    double dt = 0.1;      // Paso inicial

    string nombre = "pendulo_foucault.txt";    
    
    matrix <double> X_act(4,1);
    matrix <double> X_sig(4,1);
    double diff;

    cout << "Iniciando calculo adaptativo..." << endl;

    // Ejecución inicial de referencia
    X_act = runge_kutta_4(X_init, t, dt, t_max, nombre, false);

    // Bucle iterativo para determinar el paso de tiempo adecuado
    do {
        dt = dt / 2.0;
        
        X_sig = runge_kutta_4(X_init, t, dt, t_max, nombre, false);
        diff = norma_maxima(X_act - X_sig);

        cout << "dt: " << dt << " s, Diferencia: " << diff << endl;
        
        X_act = X_sig;
    
    } while (diff > tol);

    cout << "Paso de tiempo seleccionado: " << dt << " s" << endl;
    
    // Ejecución final con escritura de datos
    runge_kutta_4(X_init, t, dt, t_max, nombre, true);

    cout << "Resultados guardados en " << nombre << endl;

    return 0;
}
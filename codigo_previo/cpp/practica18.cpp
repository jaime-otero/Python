#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

// Inclusión de la librería de matrices solicitada
#include <cmatrix> 
using namespace techsoft;
using namespace std;

// Constantes del problema
const double R1 = 15.0;
const double R2 = 30.0;
const double U1 = 110.0;
const double U2 = 0.0;
bool guardar = true;
string nombre = "resultados_p18.txt";

// Solución Exacta para comparar
double solucion_exacta(double r) {
    return (U1 * R1 / r) * ((R2 - r) / (R2 - R1));
}

// Sistema de Ecuaciones Diferenciales Ordinarias
// Vector de estado Y: [u, u']^T
// Y(0,0) = u (potencial)
// Y(1,0) = u' (derivada)
matrix<double> F(double r, const matrix<double> &Y) {
    matrix<double> dY(2,1);
    
    // du/dr = u'
    dY(0,0) = Y(1,0); 
    
    // d(u')/dr = -(2/r) * u'
    dY(1,0) = -(2.0 / r) * Y(1,0); 

    return dY;
}

// Método de Runge-Kutta de 4º orden
matrix<double> runge_kutta_4(matrix<double> Y, double r, double dr, double r_max, bool guardar, string nombre) {

    matrix<double> k1(2,1), k2(2,1), k3(2,1), k4(2,1);
    ofstream fout;

    if (guardar) {
        fout.open(nombre.c_str());
        if (!fout.is_open()) {
            cerr << "Error al abrir el fichero: " << nombre << endl;
            return Y;
        }
        fout << "r\t\t\tCalculada\tExacta\t\tDerivada" << endl;
        fout << fixed << setprecision(6);
    }

    while (r < r_max) {
        // Ajuste para llegar exactamente a r_max si el paso se pasa
        if (r + dr > r_max) dr = r_max - r;

        if (guardar) {
            fout << r << "\t" << Y(0,0) << "\t" << solucion_exacta(r) << "\t" << Y(1,0) << endl;
        }

        k1 = F(r, Y);
        k2 = F(r + 0.5 * dr, Y + 0.5 * dr * k1);
        k3 = F(r + 0.5 * dr, Y + 0.5 * dr * k2);
        k4 = F(r + dr, Y + dr * k3);

        Y = Y + (dr / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
        r += dr;
    }

    if (guardar) {
        // Guardar el último punto
        fout << r << "\t" << Y(0,0) << "\t" << solucion_exacta(r) << "\t" << Y(1,0) << endl;
        fout.close();
    }

    return Y;
}

int main() {
    double dr = 0.05;         // Paso de integración
    double tol = 1e-7;        // Tolerancia

    cout << "--- Metodo del Disparo con ---" << endl;

    // --- Disparo 1 ---

    matrix<double> Y_init_a(2,1);
    Y_init_a(0,0) = U1; // Condición inicial u(R1)
    matrix<double> Y_final_a(2,1);
    matrix<double> Y_init_b(2,1);
    Y_init_b(0,0) = U1; // Condición inicial u(R1)
    matrix<double> Y_final_b(2,1);
    double error_a, error_b;
    double tan_a, tan_b;

    tan_a = (U2 - U1) / (R2 - R1); // Primera adivinanza para u'(R1)


    Y_init_a(1,0) = tan_a; // Adivinanza u'(R1)


    Y_final_a = runge_kutta_4(Y_init_a, R1, dr, R2, false, "");
    error_a = Y_final_a(0,0) - U2; 
    
    cout << "Disparo 1 (slope=" << tan_a << "): Error en frontera=" << error_a << endl;

    if (abs(error_a) < tol) {
        // Solución encontrada en el primer intento
        cout << "Solucion encontrada. Derivada inicial: " << tan_a << endl;
        cout << "Guardando resultados en 'potencial_esferas.txt'..." << endl;
        
        Y_final_a(1,0) = tan_a;
        
        Y_final_a = runge_kutta_4(Y_final_a, R1, dr, R2, true, nombre);
        
        return 0;

    }
    else if (error_a < 0) {
        // --- Disparo 2 ---
        double tan_b = tan_a*2.0;

        Y_init_b(1,0) = tan_b;

        Y_final_b = runge_kutta_4(Y_init_b, R1, dr, R2, false, "");
        error_b = Y_final_b(0,0) - U2;

        cout << "Disparo 2 (slope=" << tan_b << "): Error en frontera=" << error_b << endl;
    }
    else{
        // --- Disparo 2 ---
        double tan_b = tan_a*0.5;

        Y_init_b(1,0) = tan_b;

        Y_final_b = runge_kutta_4(Y_init_b, R1, dr, R2, false, "");
        error_b = Y_final_b(0,0) - U2;
    
        cout << "Disparo 2 (slope=" << tan_b << "): Error en frontera=" << error_b << endl;
    }

    // --- Preparación para la iteración ---
    matrix<double> Y_init_new(2,1);
    Y_init_new(0,0) = U1;
    matrix<double> Y_final_new(2,1);
    double error_new;
    double tan_new;

    int iteracion = 0;


    // --- Iteraciones (Método de la Secante) ---
    
    cout << "\nIniciando iteraciones..." << endl;


    do{

        iteracion++;
        cout << "\nIteracion " << iteracion << ":" << endl;
        // Cálculo de la nueva pendiente usando el método de la secante
        tan_new = tan_a - error_a * (tan_b - tan_a) / (error_b - error_a);

        Y_init_new(1,0) = tan_new;

        Y_final_new = runge_kutta_4(Y_init_new, R1, dr, R2, false, nombre);
        error_new = Y_final_new(0,0) - U2;

        cout << "Nuevo Disparo (slope=" << tan_new << "): Error en frontera=" << error_new << endl;

        // Actualización de valores para la siguiente iteración
        tan_a = tan_b;
        error_a = error_b;
        tan_b = tan_new;
        error_b = error_new;

    }while (abs(error_new) > tol);
    double tan_fin = tan_new;


    // --- Ejecución Final ---
    cout << "\nSolucion encontrada. Derivada inicial: " << tan_fin << endl;
    cout << "Guardando resultados en 'potencial_esferas.txt'..." << endl;
    
    matrix<double> Y_final(2,1);
    Y_final(0,0) = U1;
    Y_final(1,0) = tan_fin;
    
    Y_final = runge_kutta_4(Y_final, R1, dr, R2, true, "potencial_esferas.txt");
    
    return 0;
}
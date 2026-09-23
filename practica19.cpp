#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cmatrix> 

using namespace techsoft;
using namespace std;

// --- CONSTANTES Y CONFIGURACIÓN DEL PROBLEMA ---
const double L = 10.0;        // Largo (m)
const double T_A = 210.0;     // Condición de frontera u(a)
const double T_B = 140.0;     // Condición de frontera u(b)

// ==========================================
// DEFINICIÓN DE LA EDO GENÉRICA
// ==========================================
// Ecuación de la forma: u'' = p(x)u' + q(x)u + r(x)

double func_p(double x) { return 0.0; }
double func_q(double x) { return 0.14; }
double func_r(double x) { return 0.0; }


// --- SISTEMA DE EDOs (PARA MÉTODO DE DISPARO) ---
matrix<double> F(double x, const matrix<double> &Y) {
    matrix<double> dY(2,1);
    dY(0,0) = Y(1,0); 
    dY(1,0) = func_p(x)*Y(1,0) + func_q(x)*Y(0,0) + func_r(x); 
    return dY;
}

// --- RUNGE-KUTTA 4 ---
matrix<double> runge_kutta_4(matrix<double> Y, double x, double dx, double x_max, bool guardar, const string& nombre) {
    matrix<double> k1(2,1), k2(2,1), k3(2,1), k4(2,1);
    ofstream fout;

    if (guardar) {
        fout.open(nombre.c_str());
        fout << "x\t\t\tu\t\tdu/dx" << endl;
        fout << fixed << setprecision(6);
    }

    while (x < x_max - 1e-9) { 
        if (x + dx > x_max) dx = x_max - x;
        if (guardar) fout << x << "\t" << Y(0,0) << "\t" << Y(1,0) << endl;

        k1 = F(x, Y);
        k2 = F(x + 0.5 * dx, Y + 0.5 * dx * k1);
        k3 = F(x + 0.5 * dx, Y + 0.5 * dx * k2);
        k4 = F(x + dx, Y + dx * k3);

        Y = Y + (dx / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
        x += dx;
    }
    if (guardar) { fout << x << "\t" << Y(0,0) << "\t" << Y(1,0) << endl; fout.close(); }
    return Y;
}


// --- RESOLUCIÓN DEl SISTEMA  POR LU TRIDIAGONAL ---
matrix<double> resolver_lu_tridiagonal(int n, const matrix<double>& Dinf, const matrix<double>& D, const matrix<double>& DS, const matrix<double>& b) {
    
    matrix<double> x(n, 1); // Vector solución
    matrix<double> vec_delta_f(n, 1, 0.0);
    matrix<double> vec_delta(n, 1, 0.0);
    matrix<double> z(n, 1, 0.0); // Vector intermedio

    // 1. CÁLCULO DE LOS VECTORES delta y delta_f (Descomposición)
    if (abs(D(0, 0)) < 1e-15) { cerr << "Error: Pivote cero." << endl; return x; }

    vec_delta(0, 0) = D(0, 0); 

    for (int i = 1; i < n; ++i) {
        if (abs(vec_delta(i - 1, 0)) < 1e-15) { cerr << "Error: Pivote cero." << endl; return x; }

        vec_delta_f(i, 0) = Dinf(i, 0) / vec_delta(i - 1, 0);
        vec_delta(i, 0) = D(i, 0) - vec_delta_f(i, 0) * DS(i - 1, 0);
    }

    // 2. SOLUCIÓN Lz = b (Sustitución hacia adelante)
    z(0, 0) = b(0, 0);
    for (int i = 1; i < n; ++i) {
        z(i, 0) = b(i, 0) - vec_delta_f(i, 0) * z(i - 1, 0);
    }

    // 3. SOLUCIÓN Ux = z (Sustitución hacia atrás)
    if (abs(vec_delta(n - 1, 0)) < 1e-15) { cerr << "Error: Pivote cero." << endl; return x; }
    
    x(n - 1, 0) = z(n - 1, 0) / vec_delta(n - 1, 0);

    for (int i = n - 2; i >= 0; --i) {
        if (abs(vec_delta(i, 0)) < 1e-15) { cerr << "Error: Pivote cero." << endl; return x; }
        
        x(i, 0) = (z(i, 0) - DS(i, 0) * x(i + 1, 0)) / vec_delta(i, 0);
    }

    return x;
}

// ==========================================
// MAIN
// ==========================================
int main() {
    // IMPORTANTE: Pon aqui tu ruta COMPLETA de OneDrive para evitar usar mklink
    // Ejemplo: "C:\\Users\\jaime\\OneDrive\\Documents\\UNIVERSIDAD\\COMPU\\COMPU2\\resultados_disparo.txt"
    string nombre_disparo = "resultados_disparo.txt";
    string nombre_dif = "resultados_dif_finitas.txt";

    // ------------------------------------------
    // PARTE 1: MÉTODO DEL DISPARO (SHOOTING)
    // ------------------------------------------
    double dx = 0.05;
    double tol = 1e-6;

    cout << fixed << setprecision(6);
    cout << "--- 1. Metodo del Disparo ---" << endl;

    matrix<double> Y_init(2,1); Y_init(0,0) = T_A; 
    matrix<double> Y_final(2,1);
    
    double error_a, error_b, error_new;
    double tan_a, tan_b, tan_new; 

    // Disparo 1 (Lineal)
    tan_a = (T_B - T_A) / L; 
    Y_init(1,0) = tan_a; 
    Y_final = runge_kutta_4(Y_init, 0.0, dx, L, false, "");
    error_a = Y_final(0,0) - T_B;
    
    if (abs(error_a) < tol) {
        runge_kutta_4(Y_init, 0.0, dx, L, true, nombre_disparo);
    } else {
        // Disparo 2
        tan_b = (error_a < 0) ? tan_a * 2.0 : tan_a * 0.5;
        Y_init(1,0) = tan_b;
        Y_final = runge_kutta_4(Y_init, 0.0, dx, L, false, "");
        error_b = Y_final(0,0) - T_B;

        // Secante
        int iter = 0;
        do {
            iter++;
            tan_new = tan_b - error_b * (tan_b - tan_a) / (error_b - error_a);
            
            Y_init(1,0) = tan_new;
            Y_final = runge_kutta_4(Y_init, 0.0, dx, L, false, "");
            error_new = Y_final(0,0) - T_B;

            tan_a = tan_b; error_a = error_b;
            tan_b = tan_new; error_b = error_new;
        } while (abs(error_new) > tol && iter < 100);
        
        // Guardar resultado final Disparo
        Y_init(1,0) = tan_new;
        runge_kutta_4(Y_init, 0.0, dx, L, true, nombre_disparo);
        cout << "Disparo completado. Derivada inicial: " << tan_new << endl;
    }

    // ------------------------------------------
    // PARTE 2: DIFERENCIAS FINITAS (LU TRIDIAGONAL)
    // ------------------------------------------
    cout << "\n--- 2. Metodo de Diferencias Finitas (Optimizado LU) ---" << endl;
    
    double h = 1.0; 
    cout << "Paso h = " << h << " m" << endl;

    int n = (int)(L / h) - 1; // Nodos internos

    // Definimos vectores para la matriz tridiagonal
    matrix<double> D(n, 1);    // Diagonal principal
    matrix<double> Dinf(n, 1); // Diagonal inferior
    matrix<double> DS(n, 1);   // Diagonal superior
    matrix<double> b(n, 1);    // Vector lado derecho

    // Inicializamos a 0 por
    D.null(); Dinf.null(); DS.null(); b.null();

    double pi, qi, ri, xi;
    double coef_izq, coef_cen, coef_der, rhh_val;

    for (int i = 0; i < n; i++) {
        xi = (i + 1) * h; 
        
        pi = func_p(xi); qi = func_q(xi); ri = func_r(xi);

        // Coeficientes teóricos
        coef_izq = -((h / 2.0) * pi + 1.0); // Coef u_{i-1} (Diagonal Inferior)
        coef_cen = (2.0 + (h * h) * qi);   // Coef u_{i}   (Diagonal Principal)
        coef_der = ((h / 2.0) * pi - 1.0);  // Coef u_{i+1} (Diagonal Superior)
        rhh_val  = -(h * h) * ri;

        // Rellenar vectores diagonales
        D(i, 0) = coef_cen;
        
        if (i > 0)      { Dinf(i, 0) = coef_izq;} // Ojo: Dinf(0) se queda en 0
        if (i < n - 1)  { DS(i, 0)   = coef_der;} // Ojo: DS(n-1) se queda en 0

        // Manejo del vector b
        b(i, 0) = rhh_val;

        if (i == 0) {
            // Frontera izquierda T_A pasa al vector b
            b(i, 0) = b(i, 0) - (coef_izq * T_A);
        }
        if (i == n - 1) {
            // Frontera derecha T_B pasa al vector b
            b(i, 0) = b(i, 0) - (coef_der * T_B);
        }
    }

    // Resolución del sistema usando LU TRIDIAGONAL
    matrix<double> T_interior = resolver_lu_tridiagonal(n, Dinf, D, DS, b);

    // Guardar
    ofstream fout(nombre_dif.c_str());
    if (!fout.is_open()) { cerr << "Error fichero dif finitas." << endl; return 1; }
    
    fout << "x\t\t\tTemperatura" << endl;
    fout << fixed << setprecision(6);
    
    fout << 0.0 << "\t" << T_A << endl; 
    for (int i = 0; i < n; i++) {
        double x_pos = (i + 1) * h;
        fout << x_pos << "\t" << T_interior(i, 0) << endl;
    }
    fout << L << "\t" << T_B << endl;
    fout.close();

    cout << "Resultados guardados en '" << nombre_dif << "'." << endl;

    return 0;
}
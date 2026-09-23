#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

// Constantes fisicas
const double h_const = 6.626e-34;
const double k_const = 1.381e-23;
const double c_const = 2.998e8;
const double pi = 3.14159265358979323846;

// Funcion f(x) = x^3 / (e^x - 1)
double f(double x) {
    if (abs(x) < 1e-15) {
        return 0.0;
    }
    return (x * x * x) / (exp(x) - 1.0);
}

// --- Metodo de Simpson 1/3 (ADAPTATIVO) ---

// CORRECCION: Esta es una funcion auxiliar que calcula Simpson
// para un numero FIJO 'n' de intervalos.
double calcularSimpson(double a, double b, int n, double (*func)(double)) {
    if (n % 2 == 1) n++; // n debe ser par
    
    double h = (b - a) / n;
    double suma = func(a) + func(b);

    for (int i = 1; i < n; i += 2) { // Impares
        suma += 4.0 * func(a + i * h);
    }
    for (int i = 2; i < n; i += 2) { // Pares
        suma += 2.0 * func(a + i * h);
    }
    return suma * h / 3.0;
}

// CORRECCION: Esta es la funcion principal que llama a la otra
// hasta alcanzar la tolerancia. Tu version anterior tenia un bucle infinito.
double metodoSimpsonAdaptativo(double a, double b, double tol, double (*func)(double)) {
    int n = 4; // n inicial (debe ser par)
    
    // Las variables DEBEN declararse fuera del bucle
    double resAnt = 0.0;
    double resAct = calcularSimpson(a, b, n, func); // Primera estimacion

    do {
        resAnt = resAct; // Guardamos el resultado anterior
        n *= 2;          // DUPLICAMOS el numero de intervalos
        resAct = calcularSimpson(a, b, n, func); // Calculamos el nuevo resultado

    } while (abs(resAct - resAnt) > tol); // Comparamos el nuevo con el anterior

    return resAct;
}


// --- Cuadratura Gaussiana (5 Puntos) ---

// CORRECCION: Parametros 'a' y 'b' en el orden correcto
double metodoGauss(const double a, const double b, double (*func)(double),const int n) {

double suma = 0.0;

if (n == 5){
    const double posiciones[] = {
        -0.90618,
        -0.538469,
        0.0,
        0.538469,
        0.90618
    };
    const double pesos[] = {
        0.236927,
        0.478629,
        0.568889,
        0.478629,
        0.236927
    };

    for (int i = 0; i < 5; ++i) {
        // CORRECCION: Formula de transformacion de intervalo
        double xi = ((b - a) / 2.0) * posiciones[i] + (a + b) / 2.0;
        suma += pesos[i] * func(xi);
    }
}
else if (n == 4){
    const double posiciones[] = {
        -0.861136,
        -0.339981,
        0.339981,
        0.861136
    };
    const double pesos[] = {
        0.347855,
        0.652145,
        0.652145,
        0.347855
    };
    for (int i = 0; i < 4; ++i) {
        double xi = ((b - a) / 2.0) * posiciones[i] + (a + b) / 2.0;
        suma += pesos[i] * func(xi);
    }
}
else if (n == 3){
    const double posiciones[] = {
        -0.774597,
        0.0,
        0.774597
    };
    const double pesos[] = {
        0.555556,
        0.888889,
        0.555556
    };
    for (int i = 0; i < 3; ++i) {
        double xi = ((b - a) / 2.0) * posiciones[i] + (a + b) / 2.0;
        suma += pesos[i] * func(xi);
    }

}
else if (n == 2){
    const double posiciones[] = {
        -0.577350,
        0.577350
    };
    const double pesos[] = {
        1.0,
        1.0
    };
    double suma = 0.0;
    for (int i = 0; i < 2; ++i) {
        double xi = ((b - a) / 2.0) * posiciones[i] + (a + b) / 2.0;
        suma += pesos[i] * func(xi);
    }
}
else if (n == 1){
    const double posiciones[] = {
        0.0
    };
    const double pesos[] = {
        2.0
    };
    for (int i = 0; i < 1; ++i) {
        double xi = ((b - a) / 2.0) * posiciones[i] + (a + b) / 2.0;
        suma += pesos[i] * func(xi);
    }
}
else {
    cerr << "Error: n debe ser 1, 2, 3, 4 o 5." << endl;
    return 0.0;
}
    return (b - a) / 2.0 * suma;
}

int main() {
    
    const double T = 6000.0;
    const double tolerancia = 0.0001;

    const double x0 = 1e-12;
    const double xc = 1200.0 / T;  

    cout << fixed << setprecision(10); // Usar mas precision para ver
    cout << "Calculando la integral de f(x) = x^3 / (e^x - 1)" << endl;
    cout << "Limites: x0 = " << x0 << ", xc = " << xc << endl;
    cout << "------------------------------------------------" << endl;

    // 1. Metodo de Simpson
    // CORRECCION: Llamamos a la nueva funcion adaptativa
    double integralSimpson = metodoSimpsonAdaptativo(x0, xc, tolerancia, f);
    cout << "Resultado (Integral) con Simpson: " << integralSimpson << endl;
    // 2. Metodo de Gauss
    const int n = 5; // Numero de puntos para Gauss
    double integralGauss = metodoGauss(x0, xc, f, n); // La llamada esta bien
    cout << "Resultado (Integral) con Gauss n= "<<n << ": " << integralGauss << endl;
    cout << "------------------------------------------------" << endl;

    // C. Calcular el resultado final W
    // CORRECCION: Usar los nombres de las constantes (k_const, etc.)
    double k4 = pow(k_const, 4);
    double T4 = pow(T, 4);
    double c2 = pow(c_const, 2);
    double h3 = pow(h_const, 3);

    double C = (2.0 * pi * k4 * T4) / (c2 * h3);
    
    cout << scientific << setprecision(7); 
    cout << "Constante de radiacion C = " << C << endl;
    
    double W_Simpson = C * integralSimpson;
    double W_Gauss = C * integralGauss;

    cout << "Intensidad W (Simpson) = " << W_Simpson << " W/m^2" << endl;
    cout << "Intensidad W (Gauss)   = " << W_Gauss << " W/m^2" << endl;

    return 0;
}
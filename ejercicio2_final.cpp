#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <string>
#include <cmatrix> // techsoft

using namespace std;
using namespace techsoft;

// ==========================================================
// 1. DEFINICIÓN DE CONSTANTES
// ==========================================================

const double pi = acos(-1.0);
const double g = 9.81;
double th1, th2;
double w1, w2;

double t1, t2, den;

// ==========================================================
// 2. DEFINICIÓN DEL SISTEMA (pendulo doble)
// ==========================================================
// Y = [th1, w1, th2, w2]
// ==========================================================

matrix<double> F(double t, const matrix<double>& Y, double l1, double l2, double m) {

    th1 = Y(0,0);
    w1 = Y(1,0);
    th2 = Y(2,0);
    w2 = Y(3,0);

    den = m + sin(th1-th2)*sin(th1-th2);
    t1 = g/l1*sin(th2) - w1*w1*sin(th1-th2);
    t2 = (m+1)*g/l2*sin(th1) + w2*w2*sin(th1-th2);

    matrix<double> dY(4, 1);
    dY.null(); //
    dY(0,0) = w1;
    dY(1,0) = (cos(th1-th2) * t1 - l2/l1 * t2) / den; 

    dY(2,0) = w2;
    dY(3,0) = (cos(th1-th2) * t2 - (m+1)*l1/l2 * t1) / den; 

    return dY;
}

// ==========================================================
// 3. MÉTODOS DE INTEGRACIÓN (PASO INDIVIDUAL)
// ==========================================================

matrix<double> un_paso(double t, const matrix<double>& Y, double h,double l1,double l2,double m) {
    matrix<double> k1, k2, k3, k4;

    k1 = h * F(t, Y, l1, l2, m);
    k2 = h * F(t + 0.5 * h, Y + 0.5 * k1, l1, l2, m);
    k3 = h * F(t + 0.5 * h, Y + 0.5 * k2, l1, l2, m);
    k4 = h * F(t + h, Y + k3, l1, l2, m);
            
    return Y + (1.0 / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
}


// ==========================================================
// 4. FUNCIÓN MAESTRA: RESOLVER CON TOLERANCIA
// ==========================================================


void resolverEDO(const matrix<double>& Y_init, double t0, double tf, string nombre_fich, double h,double l1,double l2,double m) {
    
    // B. Integración final y guardado en fichero
    ofstream fout(nombre_fich.c_str());
    fout << fixed << setprecision(6);
    matrix<double> Y = Y_init;
    double t = t0;
    do{
        fout << t << "\t" << Y(0,0) << "\t" << Y(1,0) << "\t" << Y(2,0) << "\t" << Y(3,0) << endl;
        Y = un_paso(t, Y, h, l1, l2, m);
        t += h; 
    }while (t < tf + h/2.0);
    fout.close();
    cout << "Resultados guardados en " << nombre_fich << endl;
}

// ==========================================================
// 5. MAIN
// ==========================================================
int main() {
    matrix<double> Y_init(4, 1);
    Y_init.null();
    double l1,l2,m1,m2, m;

    double t_ini = 0.0;
    double t_end = 10.0;
    double h = 0.01;
// ==========================================================
// a)
// ==========================================================

    // condiciones iniciales:
    Y_init(0,0) = pi/3.0;
    Y_init(1,0) = 0.0;
    Y_init(2,0) = -pi/6.0;
    Y_init(3,0) = 0.0;

    l1 = 1.0;
    l2 = 2.0;
    m1 = 1.0;
    m2 = 1.0;
    m = m1/m2;

    string nombre_a = "ejercicio2_a.txt";

    // Llamada: resolver_con_tolerancia(Y_init, t_ini, t_fin, tol, metodo, fichero)
    resolverEDO(Y_init, t_ini, t_end, nombre_a, h, l1, l2, m);

    Y_init.null();

// ==========================================================
// b)
// ==========================================================

    // condiciones iniciales:
    Y_init(0,0) = pi/4.0;
    Y_init(1,0) = 0.0;
    Y_init(2,0) = pi/6.0;
    Y_init(3,0) = 0.0;

    l1 = 1.0;
    l2 = 1.0;
    m1 = 2.0;
    m2 = 0.5;
    m = m1/m2;

    string nombre_b = "ejercicio2_b.txt";

    // Llamada: resolver_con_tolerancia(Y_init, t_ini, t_fin, tol, metodo, fichero)
    resolverEDO(Y_init, t_ini, t_end, nombre_b, h, l1, l2, m);
    
    Y_init.null();

// ==========================================================
// c)
// ==========================================================

    // condiciones iniciales:
    Y_init(0,0) = -pi/3.0;
    Y_init(1,0) = 0.0;
    Y_init(2,0) = pi/4.0;
    Y_init(3,0) = 0.0;

    l1 = 1.0;
    l2 = 2.0;
    m1 = 1.0;
    m2 = 1.0;
    m = m1/m2;

    string nombre_c = "ejercicio2_c.txt";

    // Llamada: resolver_con_tolerancia(Y_init, t_ini, t_fin, tol, metodo, fichero)
    resolverEDO(Y_init, t_ini, t_end, nombre_c, h, l1, l2, m);
    
    return 0;
}
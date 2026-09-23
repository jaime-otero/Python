#include <iostream>
#include <cmath>

using namespace std;

double f (const double x) {
    return x*x - 5.;
}

double df (const double x) {
    return 2*x;
}

int newton(const double tol, double &x, const int max_iter) {

    double fx = f(x);
    double dfx = df(x);
    int n = 0;
    while (abs(fx)>=tol && n < max_iter) {

        if (dfx == 0) {
            cerr << "Error: division por cero en la derivada." << endl;
            break;
        }

        x = x - fx/dfx;
        fx = f(x);
        dfx = df(x);


        n++;
    }
    return n;   
}

int biseccion(const double tol, double &x, double a, double b, const int max_iter) {
    if (f(a) * f(b) > 0) {
        cerr << "Error: f(a) y f(b) deben tener signos opuestos." << endl;
        return 0;
    }
    int n = 0;
    double fa = f(a);
    double fb = f(b);
    double xm, fxm;
    while ((b - a) / 2.0 > tol && n < max_iter) {
        xm = (a + b) / 2.0;
        fxm = f(xm);
        if (fxm == 0.0) {
            x = xm;
            return n + 1;
        }
        if (fa * fxm < 0) {
            b = xm;
            fb = fxm;
        } else {
            a = xm;
            fa = fxm;
        }
        n++;
    }
    x = (a + b) / 2.0;
    return n;
}

int secante(const double tol, double &x0, double &x1, const int max_iter) {
    double f0 = f(x0);
    double f1 = f(x1);
    int n = 0;
    double x2;
    while (abs(f1) >= tol && n < max_iter) {
        if (abs(f1 - f0) < 1e-12) {
            cerr << "Error: denominador demasiado pequeño en la secante." << endl;
            break;
        }
        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f(x1);
        n++;
    }
    return n;
}



int main() {
    cout << endl;
    cout << "Metodo de Newton:" << endl;
    
    double x = 2;
    double tol = 1e-6;
    const int max_iter = 1000;

    int n = newton(tol, x, max_iter);

    if (n == max_iter) {
        cerr << "Se ha alcanzado el maximo de iteraciones, la tolerancia alcanzada es " << abs(f(x)) << endl;
    }
    else if (n == 0) {
        cout << "La aproximacion inicial ya cumple la tolerancia o se divide por 0" << endl;
    }
    else {
        cout << "Se ha alcanzado la tolerancia en " << n << " iteraciones" << endl;

    }
    cout << "La raiz aproximada es " << x << endl;

    cout << "\nMetodo de biseccion:" << endl;

    double a = 1, b = 3;
    double x_bis = 0;
    int n_bis = biseccion(tol, x_bis, a, b, max_iter); 
    
    if (n_bis == 0) {
        cerr << "No se pudo aplicar biseccion." << endl;
    } else if (n_bis == max_iter) {
        cerr << "Biseccion: se alcanzo el máximo de iteraciones." << endl;
    } else {
        cout << "Tolerancia alcanzada en " << n_bis << " iteraciones." << endl;
    }
    cout << "Raiz aproximada por biseccion: " << x_bis << endl;

    cout<< "\nMetodo de la secante:" << endl;
    double x0 = 1, x1 = 3;
    int n_sec = secante(tol, x0, x1, max_iter);
    if (n_sec == max_iter) {
        cerr << "Se alcanzo el maximo de iteraciones." << endl;
    } else if (n_sec == 0) {
        cout << "La aproximacion inicial ya cumple la tolerancia o hay division por cero." << endl;
    } else {
        cout << "Tolerancia alcanzada en " << n_sec << " iteraciones." << endl;
    }
    cout << "Raiz aproximada por secante: " << x1 << endl;
    cout << endl;
    return 0;
}
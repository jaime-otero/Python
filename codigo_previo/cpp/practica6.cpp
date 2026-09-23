#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Implementa la función g(x) = (1/x^2 + 1/x) * exp(-x)
double f(const double x) {
    if (x == 0) return 1e18; // Evitar división por cero
    return (1.0/(x*x) + 1.0/x) * exp(-x);
}

// Derivada de g(x) respecto a x
double df(const double x) {
    if (x == 0) {return 1e18;} // Evitar división por cero
    return -(2.0/(x*x*x) + 2.0/(x*x) + 1.0/x) * exp(-x);
}

// Implementa el metodo de Newton para encontrar la raiz de f(x) = 0.01*f(1)
int newton(const double tol, double &x, const int max_iter, const double f0) {

    double fx = f(x);
    double dfx = df(x);
    int n = 0;
    while (abs(fx-f0) >= tol && n < max_iter) {

        if (dfx == 0) {
            cerr << "Error: division por cero en la derivada." << endl;
            break;
        }

        x = x - (fx-f0)/dfx;
        fx = f(x);
        dfx = df(x);


        n++;
    }
    return n;   
}

// Implementa el metodo de bisección para encontrar la raiz de f(x) = 0.01*f(1)
int biseccion(const double tol, double &x, double a, double b, const int max_iter, const double f0) {
    
    // Verifica que f(a) y f(b) tengan signos opuestos
    if ((f(a) - f0) * (f(b)-f0) > 0) {
        cerr << "Error: f(a) y f(b) deben tener signos opuestos." << endl;
        return 0;
    }

    // Definimos las variables necesarias
    int n = 0;
    double fa = f(a);
    double fb = f(b);
    double xm, fxm; // puntos medios

    // Iteramos hasta alcanzar la tolerancia o el máximo de iteraciones
    while (abs (b - a) / 2.0 > tol && n < max_iter) {
        xm = (a + b) / 2.0; 
        fxm = f(xm);

        // Verificamos si hemos encontrado la raiz
        if (fxm - f0 == 0.0) {
            x = xm;
            return n + 1;
        }
        // Actualizamos los límites del intervalo
        if ((fa-f0) * (fxm-f0) < 0) {
            b = xm;
            fb = fxm;
        } else {
            a = xm;
            fa = fxm;
        }
        n++;
    }
    // Calculamos la aproximación final
    x = (a + b) / 2.0;
    return n;
}

// Implementa el metodo de la secante para encontrar la raiz de f(x) = 0.01*f(1)
int secante(const double tol, double &x0, double &x1, const int max_iter, const double f0) {
    int n = 0;
    while (n < max_iter) {
        double f_x0 = f(x0);
        double f_x1 = f(x1);

        // Condición de parada
        if (abs(f_x1 - f0) < tol) {
            return n;
        }

        // Evitamos división por cero
        double denominador = f_x1 - f_x0;
        if (abs(denominador) < 1e-15) { 
            cerr << "Error: denominador demasiado pequeno en la secante." << endl;
            break;
        }
        
        // Calculamos el siguiente punto de la secuencia
        double x2 = x1 - (f_x1 - f0) * (x1 - x0) / denominador;
        
        // Actualizamos los puntos para la siguiente iteración
        x0 = x1;
        x1 = x2;
        
        n++;
    }
    return n;
}



int main() {
    
    double tol = 1e-5;
    const int max_iter = 1000;

    const double r0 = 1.2e-15;  // Radio caracteristico en m
    double f0 = f(1.0)*0.01;

    // primero el metodo de Newton

    cout << endl;
    cout << "Metodo de Newton:" << endl;
    
    double x = 3.5;


    int n = newton(tol, x, max_iter, f0);

    if (n == max_iter) {
        cerr << "Se ha alcanzado el maximo de iteraciones, la tolerancia alcanzada es " << abs(f(x)) << endl;
    }
    else if (n == 0) {
        cout << "La aproximacion inicial ya cumple la tolerancia o se divide por 0" << endl;
    }
    else {
        cout << "Se ha alcanzado la tolerancia en " << n << " iteraciones" << endl;

    }
    cout << "La raiz aproximada es " << x*r0 << endl;

    // ahora el metodo de biseccion

    cout << "\nMetodo de biseccion:" << endl;

    double a = 3, b = 4;
    double x_bis = 0;
    int n_bis = biseccion(tol, x_bis, a, b, max_iter, f0); 
    
    if (n_bis == 0) {
        cerr << "No se pudo aplicar biseccion." << endl;
    } else if (n_bis == max_iter) {
        cerr << "Biseccion: se alcanzo el máximo de iteraciones." << endl;
    } else {
        cout << "Tolerancia alcanzada en " << n_bis << " iteraciones." << endl;
    }
    cout << "Raiz aproximada por biseccion: " << x_bis*r0 << endl;

    // ahora el metodo de la secante

    cout<< "\nMetodo de la secante:" << endl;
    double x0 = 3, x1 = 4;
    int n_sec = secante(tol, x0, x1, max_iter, f0);
    if (n_sec == max_iter) {
        cerr << "Se alcanzo el maximo de iteraciones." << endl;
    } else if (n_sec == 0) {
        cout << "La aproximacion inicial ya cumple la tolerancia o hay division por cero." << endl;
    } else {
        cout << "Tolerancia alcanzada en " << n_sec << " iteraciones." << endl;
    }
    cout << "Raiz aproximada por secante: " << x1*r0 << endl;
    cout << endl;



    // ahora vamos a implementar los tres metodos pero vamos a ir cambiando la tolerancia desde 
    // 1e-3 hasta 1e-12 y vamos a ver cuantas iteraciones tarda en cada caso
    
    tol = 1e-3; // reiniciamos la tolerancia

    // Abrimos el fichero para escribir los resultados
    string nombre = "practica6.txt";
    ofstream ff(nombre);

    string nombrei = "practica6_iteraciones.txt";
    ofstream fi(nombrei);

    vector<double> vnewton, vbiseccion, vsecante; // vectores para almacenar los resultados
    vector<int> inewton, ibiseccion, isecante; // vector para almacenar las iteraciones
    
    while (tol >= 1e-12) {
        // Reiniciamos las variables
        double x = 3.5;
        double x_bis = 0;
        double a = 3, b = 4;
        double x0 = 3, x1 = 4; 
        int n =0 ; n_bis=  0; n_sec = 0;

        // Ejecutamos los métodos y almacenamos los resultados
        n = newton(tol, x, max_iter, f0);
        vnewton.push_back(x*r0);
        inewton.push_back(n);
        n_bis = biseccion(tol, x_bis, a, b, max_iter, f0);
        vbiseccion.push_back(x_bis*r0);
        ibiseccion.push_back(n_bis);
        n_sec = secante(tol, x0, x1, max_iter, f0);
        vsecante.push_back(x1*r0);
        isecante.push_back(n_sec);
        
        tol *= 0.1;
    }

  // Escribimos los resultados en los ficheros

    if (ff.is_open()) {
        ff << "tolerancia\t\tnewton (m)\t\tbiseccion (m)\t\tsecante (m)\n";
        ff << "----------------------------------------------------------------------------------\n";
        // El bucle se ejecuta 10 veces, así que el límite es vnewton.size() o 10
        for (int i = 0; i < vnewton.size(); ++i) { 
            ff << scientific << 1e-3*pow(0.1,i) << "\t" << vnewton[i] << "\t" << vbiseccion[i] << "\t" << vsecante[i] << endl;
        }
        ff.close();
    } else {
        cout << "No se ha podido abrir el fichero: " << nombre << endl;
    }

    if (fi.is_open()) {
        // Usamos 'fi' para escribir el encabezado
        fi << "tolerancia\t\tnewton (it)\t\tbiseccion (it)\t\tsecante (it)\n";
        fi << "----------------------------------------------------------------------------------\n";
        // El límite del bucle es el tamaño del vector (10)
        for (int i = 0; i < inewton.size(); ++i) { 
            // Usamos 'fi' para escribir los datos de iteraciones
            fi << scientific << 1e-3*pow(0.1,i) << "\t" << fixed << inewton[i] << "\t\t\t\t" << ibiseccion[i] << "\t\t\t\t\t" << isecante[i] << endl;
        }
        fi.close(); // Cerramos el archivo correcto
    } else {
        cout << "No se ha podido abrir el fichero: " << nombrei << endl;
    }

    return 0;
}




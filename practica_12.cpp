#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>  // para setprecision
#include <sstream>
#include <fstream>
using namespace std;

const double pi = 3.14159265358979323846;

// Función a integrar
double f(double x, double k) {
    return 1/sqrt(1-k*k*sin(x)*sin(x));
}

double metodoSimpson13(double a, double b, double n,int nint,  double (*f)(double, double), double k) {

    if (nint % 2 == 1) n += 1; // n debe ser par
    double h = (b - a) / n;
    double suma = f(a, k) + f(b, k);

    for (int i = 1; i < n; i += 2) {
        suma += 4 * f(a + i * h, k);
    }
    for (int i = 2; i < n-1; i += 2) {
        suma += 2 * f(a + i * h, k);
    }
    return suma * h / 3.0;
}

double metodoSimpson38(double a, double b, double n,int nint, double (*f)(double, double), double k) {
    // aseguramos que n sea multiplo de 3
    if (nint % 3 == 1) n += 2;
    else if (nint % 3 == 2) n += 1;

    double h = (b - a) / n;
    double suma = f(a, k) + f(b, k);

    for (int i = 1; i < n; i++) {
        if (i % 3 == 0) {
            suma += 2 * f(a + i * h, k);
        } else {
            suma += 3 * f(a + i * h, k);
        }
    }
    return suma * 3. * h / 8.0;
}
// Método del trapecio
double metodoTrapecio(double a, double b, double n, double (*f)(double, double), double k) {
    double af = f(a, k); 
    double fb = f(b, k);

    double h = (b - a) / n;
    double suma = (af + fb) / 2.0;
    for (int i = 1; i < n; ++i) {
        suma += f(a + i * h, k);
    }
    return suma * h;
}

int main() {
    double a = 0.0; // límite inferior
    double b = pi/2.; // límite superior
    double n = 100; // número de trapecios
    int nint = 100; // número de intervalos para Simpson

    // Fichero de salida
    string nombrei = "practica12.txt";
    ofstream fi(nombrei);

if (fi.is_open()) {
        fi << fixed << setprecision(20);
        // Usamos 'fi' para escribir el encabezado
        fi << "theta_max\t\t    Trapecio  \t\t  Simpson 1/3  \t\t  Simpson 3/8  \n";
        fi << "----------------------------------------------------------------------------------\n";
        for (double theta_max = 0; theta_max <= pi*2/3; theta_max += pi/36) {
            double k = sin (theta_max /2.); // ejemplo de valor para k

            double resultado_trapecio = metodoTrapecio(a, b, n, f, k);
            double resultado_simpson13 = metodoSimpson13(a, b, n,nint, f, k);
            double resultado_simpson38 = metodoSimpson38(a, b, n,nint, f, k);

            double t_tprimT = 2/pi*resultado_trapecio;
            double t_tprim13 = 2/pi*resultado_simpson13;
            double t_tprim38 = 2/pi*resultado_simpson38;

            //pasamos theta_ max a grados para mostrar por pantalla
            double theta_max_g = theta_max * 180 / pi;


        fi << theta_max_g << "\t\t\t\t\t" <<  t_tprimT<< "\t\t\t\t" << t_tprim13<< "\t\t\t\t" << t_tprim38 << endl;    
        }   
        fi.close();
    } else {
        cout << "No se ha podido abrir el fichero: " << nombrei << endl;
    }

    return 0;
}
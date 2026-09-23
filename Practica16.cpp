#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cmatrix>

using namespace std;
using namespace techsoft;

// Parámetros
const double m1 = 1.2;
const double m2 = 2.8;
const double k1 = 1.9;
const double k2 = 2.1;

// Condiciones iniciales
const double y1_0 = 3.0;
const double y2_0 = 4.0;
const double v1_0 = 0.0;
const double v2_0 = 0.0;

// dy/dx = f(x, y)
matrix<double> derivada(double t, const matrix<double>& Equil) {
	
    matrix<double> dEquil(4,1);
    	double y1 = Equil(0,0);
    	double y2 = Equil(1,0);
    	double v1 = Equil(2,0);
    	double v2 = Equil(3,0);
    	
    // Primera derivada
    dEquil(0,0) = v1;
    // Segunda derivada
    dEquil(1,0) = v2;
    // Tercera derivada
    dEquil(2,0) = -(k1/m1)*y1 - (k2/m1)*(y1-y2);
    // Cuarta derivada
    dEquil(3,0) = (k2/m2)*(y1-y2);
    
    return dEquil;
}

// Método de Euler
matrix<double> euler(double h, double t_final, string nombrearchivo) {
	// Estado inicial
	matrix<double> Equil(4,1);
    Equil(0,0) = y1_0; // Corresponde a y1
    Equil(1,0) = y2_0; // Corresponde a y2
    Equil(2,0) = v1_0; // Corresponde a v1
    Equil(3,0) = v2_0; // Corresponde a v2
    
    ofstream archivo(nombrearchivo.c_str());
    if (archivo.is_open()){
    	//archivo << "t, y1, y2, v1, v2" << endl;
    	
    	for(double t = 0.0; t <= t_final + 1e-9; t += h) { 
    	// Escribimos los resultados
        	archivo << t << "  " << Equil(0, 0) << "  " << Equil(1, 0) << "  " << Equil(2, 0) << "  " << Equil(3, 0) << endl;
            
        // Calculmaos las derivadas
            matrix<double> dEquil = derivada(t, Equil);
            
        // Actualizamos el resultado de Euler
            for (int i = 0; i < 4; i++) {
                Equil(i, 0) = Equil(i, 0) + h * dEquil(i, 0);
            }
        }
    archivo.close();
   }
   else cout << "No se ha podido generar el fichero." << endl;
   return Equil;
}

// Runge-Kutta de Segundo Orden
matrix<double> runge_kutta_2(double h, double t_final, string nombrearchivo) {
    
    double t = 0.0;
	// Estado inicial
	matrix<double> Equil(4,1);
    Equil(0,0) = y1_0; // Corresponde a y1
    Equil(1,0) = y2_0; // Corresponde a y2
    Equil(2,0) = v1_0; // Corresponde a v1
    Equil(3,0) = v2_0; // Corresponde a v2
    
    matrix<double> k1(4, 1), k2(4, 1);
    ofstream archivo(nombrearchivo.c_str());
    if (archivo.is_open()){
    	//archivo << "t,y1,y2,v1,v2" << endl;
    	while (t <= t_final+h - 1e-9) {
    		
        	k1 = derivada(t, Equil);
        	k2 = derivada(t + h/2.0, Equil + h/2.0 * k1);
        	Equil = Equil + h * k2;
        	archivo << t << "  " << Equil(0, 0) << "  " << Equil(1, 0) << "  " << Equil(2, 0) << "  " << Equil(3, 0) << endl;
        	t = t + h;
    	}
    archivo.close();
	}
	else cout << "No se ha podido generar el fichero." << endl;
    return Equil;
}

// Runge-Kutta de Cuarto Orden
matrix<double> runge_kutta_4(double h, double t_final, string nombrearchivo) {
	double t = 0.0;
    // Estado inicial
	matrix<double> Equil(4,1);
    Equil(0,0) = y1_0; // Corresponde a y1
    Equil(1,0) = y2_0; // Corresponde a y2
    Equil(2,0) = v1_0; // Corresponde a v1
    Equil(3,0) = v2_0; // Corresponde a v2
    
    matrix<double> k1(4, 1), k2(4, 1), k3(4, 1), k4(4, 1);
    ofstream archivo(nombrearchivo.c_str());
    if (archivo.is_open()){
    	//archivo << "t,y1,y2,v1,v2" << endl;
    	while (t < t_final+h - 1e-9) {
    	// Escribimos los resultados
            archivo << t << "  " << Equil(0, 0) << "  " << Equil(1, 0) << "  " << Equil(2, 0) << "  " << Equil(3, 0) << endl;
    	// Calculamos cada k
        	k1 = derivada(t, Equil);
        	k2 = derivada(t + h/2.0, Equil + h/2.0 * k1);
        	k3 = derivada(t + h/2.0, Equil + h/2.0 * k2);
        	k4 = derivada(t + h, Equil + h * k3);
        	Equil = Equil + (h / 6.0) * (k1 + 2.0*k2 + 2.0*k3 + k4);
        	
        	
        	t = t + h;
        	
    	}
    archivo.close();
	}
	else cout << "No se ha podido generar el fichero." << endl;
    return Equil;
}

// Función principal
int main() {
    // Parámetros
    matrix<double> y_euler(3,1);
    matrix<double> y_rk2(3,1);
    matrix<double> y_rk4(3,1);
    
    const double t_final = 100;
    const int lenh = 1;
    double pasos [1] = {0.1};
    double h;
    for(int i=0; i<lenh; i++){
    	h = pasos[i];
    	cout << "Para h = " << h << endl;
    	if(i == 0){
    		//cout << "\n Resultados para el metodo de Euler" << endl;
    		y_euler = euler(h,t_final,"resultadoseuler_0.1.txt");
    		//cout << "\n Resultados para el metodo de rk2" << endl;
    		y_rk2 = runge_kutta_2(h,t_final,"resultadosrk2_0.1.txt");
    		//cout << "\n Resultados para el metodo de rk4" << endl;
    		y_rk4 = runge_kutta_4(h,t_final,"resultadosrk4_0.1.txt");
		}
		/*if(i == 1){
			cout << "\Resultados para el metodo de Euler" << endl;
    		y_euler(i,0) = euler(h,t_final,"resultadoseuler_0.5.txt");
    		cout << "\Resultados para el metodo de rk2" << endl;
    		y_rk2(i,0) = runge_kutta_2(h,t_final,"resultadosrk2_0.5.txt");
    		cout << "\Resultados para el metodo de rk4" << endl;
    		y_rk4(i,0) = runge_kutta_4(h,t_final,"resultadosrk4_0.5.txt");
		}
		if(i == 2){
			y_euler(i,0) = euler(x0,y0,h,x_final,"resultadoseuler_0.02.txt");
    		y_rk2(i,0) = runge_kutta_2(x0,y0,h,x_final,"resultadosrk2_0.02.txt");
    		y_rk4(i,0) = runge_kutta_4(x0,y0,h,x_final,"resultadosrk4_0.02.txt");
		}
		cout << "La solucion exacta para y cuando x=1 es y=" << solucion_exacta <<endl;*/
	}

}
	

#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cmatrix>

using namespace std;
using namespace techsoft;

// dy/dx = f(x, y) = -tan(x)sec(x) - sen(x)
double derivada(double x, double y) {
    double cos_x = cos(x);
    if (cos_x == 0.0) return NAN; // Evitar división por cero
    return - (sin(x) / (cos_x * cos_x)) - sin(x);
}

// Solución Exacta y = cos(x) - 1/cos(x)
double solucion_exacta(double x) {
    double cos_x = cos(x);
    if (cos_x == 0.0) return NAN;
    return cos_x - (1.0 / cos_x);
}

// Método de Euler
double euler(double x0, double y0, double h, double x_final, string nombrearchivo) {
    double x = x0;
    double y = y0;
    
    ofstream archivo(nombrearchivo.c_str());
    if (archivo.is_open()){
    	archivo << x0 << "  " << y0 << endl;
    	while (x <= x_final-1e-9) { 
        	y = y + h * derivada(x, y);
        	x = x + h;
        	archivo << x << "  " << y << endl;
    	}
    archivo.close();
   }
   else cout << "No se ha podido generar el fichero." << endl;
   return y;
}

// Runge-Kutta de Segundo Orden
double runge_kutta_2(double x0, double y0, double h, double x_final, string nombrearchivo) {
    double x = x0;
    double y = y0;
    double k1, k2;

    ofstream archivo(nombrearchivo.c_str());
    if (archivo.is_open()){
    	//archivo << x0 << "  " << y0 << endl;
    	while (x <= x_final+h - 1e-9) {
    		
    		
        	k1 = derivada(x, y);
        	k2 = derivada(x + h/2.0, y + h/2.0 * k1);
        	
        	y = y + h * k2;
        	archivo << x << "  " << y << endl;
        	x = x + h;
    	}
    archivo.close();
	}
	else cout << "No se ha podido generar el fichero." << endl;
    return y;
}

// Runge-Kutta de Cuarto Orden
double runge_kutta_4(double x0, double y0, double h, double x_final, string nombrearchivo) {
    double x = x0;
    double y = y0;
    double k1, k2, k3, k4;
    
    ofstream archivo(nombrearchivo.c_str());
    if (archivo.is_open()){
    	//archivo << x0 << "  " << y0 << endl;
    	while (x < x_final+h - 1e-9) {
    	//cout << x << endl;
    		
        	k1 = derivada(x, y);
        	k2 = derivada(x + h/2.0, y + h/2.0 * k1);
        	k3 = derivada(x + h/2.0, y + h/2.0 * k2);
        	k4 = derivada(x + h, y + h * k3);
        	y = y + (h / 6.0) * (k1 + 2*k2 + 2*k3 + k4);
        	
        	archivo << x << "  " << y << endl;
        	x = x + h;
        	cout << x << " xf "<< x_final << " h= "<< (x<x_final) <<endl;
    	}
    archivo.close();
	}
	else cout << "No se ha podido generar el fichero." << endl;
    return y;
}

// Función principal
int main() {
    // Parámetros
    matrix<double> y_euler(3,1);
    matrix<double> y_rk2(3,1);
    matrix<double> y_rk4(3,1);
    
    const double x0 = 0.0;
    const double y0 = 0.0;
    const double x_final = 1.0;
    
    const int lenh = 3;
    double pasos [lenh] = {0.5, 0.1, 0.02};
    
    for(int i=0; i<lenh; i++){
    	double h = pasos[i];
    	cout << "Para h =" << pasos << endl;
    	if(i == 0){
    		y_euler(i,0) = euler(x0,y0,h,x_final,"resultadoseuler_0.5.txt");
    		y_rk2(i,0) = runge_kutta_2(x0,y0,h,x_final,"resultadosrk2_0.5.txt");
    		y_rk4(i,0) = runge_kutta_4(x0,y0,h,x_final,"resultadosrk4_0.5.txt");
		}
		if(i == 1){
			y_euler(i,0) = euler(x0,y0,h,x_final,"resultadoseuler_0.1.txt");
    		y_rk2(i,0) = runge_kutta_2(x0,y0,h,x_final,"resultadosrk2_0.1.txt");
    		y_rk4(i,0) = runge_kutta_4(x0,y0,h,x_final,"resultadosrk4_0.1.txt");
		}
		if(i == 2){
			y_euler(i,0) = euler(x0,y0,h,x_final,"resultadoseuler_0.02.txt");
    		y_rk2(i,0) = runge_kutta_2(x0,y0,h,x_final,"resultadosrk2_0.02.txt");
    		y_rk4(i,0) = runge_kutta_4(x0,y0,h,x_final,"resultadosrk4_0.02.txt");
		}
		cout << "La solucion exacta para y cuando x=1 es y=" << solucion_exacta <<endl;
	}
}
	

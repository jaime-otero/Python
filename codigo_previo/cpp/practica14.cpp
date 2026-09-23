#include <iostream>
#include <fstream>  // Para gestionar ficheros (ifstream)   
#include <string>
#include <cmath>    // Para exp() y abs()
#include <iomanip>  // Para setprecision() y fixed
#include <sstream>  // Para istringstream (leer líneas)
#include <vector>   // Para usar vectores dinámicos
using namespace std;

double pos_analitica(double t) {
    return 1.3 - 0.6 * t + 7.0 * exp(-t / 10.0);
}

double vel_analitica(double t) {
    return -0.6 - 0.7 * exp(-t / 10.0);
}

double acel_analitica(double t) {
    return 0.07 * exp(-t / 10.0);
}

double* derivar(double* funcion, int nlen, double h) {
    
    // Creamos el vector para guardar la derivada
    double* derivada = new double[nlen];

    // 1. Punto inicial (Fórmula de diferencia hacia adelante de 3 puntos)
    derivada[0] = (-3.0 * funcion[0] + 4.0 * funcion[1] - funcion[2]) / (2.0 * h);
    // 2. Puntos centrales (Fórmula de diferencia central de 3 puntos)
    for (int i = 1; i < nlen - 1; i++) {
        derivada[i] = (funcion[i + 1] - funcion[i - 1]) / (2.0 * h);
    }

    // 3. Punto final (Fórmula de diferencia hacia atrás de 3 puntos)
    derivada[nlen - 1] = (3.0 * funcion[nlen - 1] - 4.0 * funcion[nlen - 2] + funcion[nlen - 3]) / (2.0 * h);

    return derivada;
}



int main(){
    string infile = "posiciones.txt";
    ifstream ffin;

    // leemos el fichero para obtener nlen

    int nlen = 0;
    double h = 0.0;

    string linea;
    double t_actual = 0.0, t_prev = 0.0, pos = 0.0;

    ffin.open(infile);
    if (!ffin.is_open()) {
        cout << "Error: No se pudo abrir el fichero " << infile << endl;
        return 1;
    }
    while (getline(ffin, linea)) {
        if (linea.empty() || linea[0] == '#') continue; 

        istringstream iss(linea);
        nlen++; 
    }
    ffin.close();

    

    cout << "--- Lectura ---" << endl;
    cout << "Fichero: " << infile << endl;
    cout << "Numero de puntos (nlen): " << nlen << endl;

    if (nlen < 3) {
        cout << "Error: Se necesitan al menos 3 puntos de datos." << endl;
        return 1;
    }

    // Declarar vectores y leer datos
    double* t = new double[nlen];
    double* x_num = new double[nlen];
    ffin.open(infile);
    if (!ffin.is_open()) {
        cout << "Error: No se pudo re-abrir el fichero " << infile << endl;
        return 1;
    }
    string encabezado;
    getline(ffin, encabezado); // Lee y descarta la primera línea
    for (int i = 0; i < nlen; i++) {
        ffin >> t[i] >> x_num[i];
    }
    ffin.close();

    // Calculamos el paso de tiempo h 
    h = t[1]- t[0];
    cout << "Paso de tiempo (h): " << h  <<endl;

    // Calcular derivadas numéricas
    double* v_num = derivar(x_num, nlen, h); // Velocidad numérica
    double* a_num = derivar(v_num, nlen, h); // Aceleración numérica

    // Calcular valores analíticos y errores
    vector<double> x_analit(nlen), v_analit(nlen), a_analit(nlen);
    vector<double> err_x(nlen), err_v(nlen), err_a(nlen);
    
    for (int i = 0; i < nlen; i++) {
        x_analit[i] = pos_analitica(t[i]);
        v_analit[i] = vel_analitica(t[i]);
        a_analit[i] = acel_analitica(t[i]);

        err_x[i] = abs(x_num[i] - x_analit[i]);
        err_v[i] = abs(v_num[i] - v_analit[i]);
        err_a[i] = abs(a_num[i] - a_analit[i]);
    }

    // Imprimir resultados en un fichero para graficar
    ofstream ffout("resultados.txt");
    ffout << fixed << setprecision(6);  
    ffout << "#  t        x_num      x_analit   err_x     v_num      v_analit   err_v     a_num      a_analit   err_a" << endl;
    for (int i = 0; i < nlen; i++) {
        ffout << setw(8) << t[i]
              << setw(12) << x_num[i]
              << setw(12) << x_analit[i]
              << setw(10) << err_x[i]
              << setw(12) << v_num[i]
              << setw(12) << v_analit[i]
              << setw(10) << err_v[i]
              << setw(12) << a_num[i]
              << setw(12) << a_analit[i]
              << setw(10) << err_a[i] << endl;
    }
    ffout.close();

    // vemos el maximo error de cada uno
    double max_err_x = 0.0, max_err_v = 0.0, max_err_a = 0.0;
    for (int i = 0; i < nlen; i++) {
        if (err_x[i] > max_err_x) max_err_x = err_x[i];
        if (err_v[i] > max_err_v) max_err_v = err_v[i];
        if (err_a[i] > max_err_a) max_err_a = err_a[i];
    }
    cout << "\n--- Errores Maximos --" << endl;
    cout << "Error maimo en posicion:" << max_err_x << endl;
    cout << "Error maimo en velocidad: " << max_err_v << endl;
    cout << "Error maimo en aceleracio: " << max_err_a << endl;
    cout << "Resultados escritos en 'resultados.txt'" << endl;
    // Liberar memoria
    delete[] t;
    delete[] x_num;
    delete[] v_num;
    delete[] a_num;
    return 0;



}
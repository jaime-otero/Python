#include <iostream>
#include <cmatrix>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace techsoft;

// Genera el nombre del archivo de salida según filas, columnas y tipo
string fnom(const int nrows, const int ncols, const string& tipo) {
	return tipo + to_string(nrows) + "x" + to_string(ncols) +  ".txt";
}

void contar(int& nrows, int& ncols) {

    ifstream fin("matriz.txt");
    if (!fin) {
        cout << "No se pudo abrir el archivo 'matriz.txt'.\n";
        exit(1);
    }
    vector<double> lines;
    string line;

	while (getline(fin, line)) {
		nrows++;
		if (nrows == 1) {
			// Contar columnas en la primera línea
			istringstream iss(line);
			double col;
			while (iss >> col) {
				ncols++;
			}
		}
	}
	fin.close();   
}

void metodo_lu(const matrix<double>& A, matrix<double>& L, matrix<double>& U) {
    int n = A.rowno();
    L = matrix<double>(n, n);
    U = matrix<double>(n, n);
    double sum=0;

    for (int i = 0; i < n; ++i) {
        // U
        for (int j = i; j < n; ++j) {
            sum = 0;    
            if (i>j){
                U(i,j)=0;
            }
            
            else {

                for (int k = 0;k < i; ++k) {
                    sum += L(i, k) * U(k, j);
                }
                U(i, j) = A(i, j) - sum;
        }
        }
        // L
        
        for (int j = i; j < n; ++j) {
            
            sum = 0;
            
            if (i==j){
                L(i,i)=1;
            }
            else if (i>j){
                L(j,i)=0;
            }
            else {
                for (int k = 0; k < i; ++k) {
                     sum += L(j, k) * U(k, i);
                }
                L(j, i) = A(j, i) - sum;
                L(j, i) /= U(i, i);
            }
        }
    
}}

int main() {

    cout << "\nComprobaciones medias: " << endl;


    cout << scientific << setprecision(3);
 ifstream ff("matriz.txt");
	if (!ff.is_open()) {
		cout << "No se pudo abrir el archivo 'matriz.txt'.\n";
		return 1;
	}

    int nrows = 0, ncols = 0;
    contar(nrows, ncols);

    if (ncols < 2) {
        cout << "La matriz debe tener al menos dos columnas (una para A y otra para b)." << endl;
        return 1;
    }
    else if (nrows < 1) {
        cout << "La matriz debe tener al menos una fila." << endl;
        return 1;
    }
    else if (nrows != ncols - 1) {
        cout << "La matriz A debe ser cuadrada (numero de filas = numero de columnas - 1)." << endl;
        return 1;
    }
    else{ cout << "El sistema se ha leido correctamente." << endl;
    }

	// Leer la matriz usando cmatrix
	matrix<double> m(nrows, ncols);
	ff >> m;
	ff.close();

    matrix<double> A(nrows, ncols-1);
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols-1; ++j) {
            A(i, j) = m(i, j);
        }
    }

    

    // Definimos el vector b
    matrix<double> b (nrows, 1);
    for (int i = 0; i < nrows; ++i) {
        b(i, 0) = m(i, ncols-1);
    }
    



    // Realizamos la descomposición LU

    matrix<double> L, U;
    metodo_lu(A, L, U);

    double tol = 1e-10;

// comprobamos que A = LU

    if ((A - L * U).norm1() < tol) {
        cout << "La descomposicion LU es correcta: A = LU" << endl;
    } else {
        cout << "La descomposicion LU es incorrecta." << endl;
    }

    cout << endl;

    // Resolvemos Ly = b
    matrix<double> z(nrows, 1);
    
    for (int i = 0; i < nrows; ++i) {
        z(i, 0) = b(i, 0);
        for (int j = 0; j < i; ++j) {
            z(i, 0) -= L(i, j) * z(j, 0);
        }
        z(i, 0) /= L(i, i);
    }

    // Resolvemos Ux = z
    matrix<double> x(nrows, 1);
    for (int i = nrows - 1; i >= 0; --i) {
        x(i, 0) = z(i, 0);
        for (int j = i + 1; j < nrows; ++j) {
            x(i, 0) -= U(i, j) * x(j, 0);
        }
        x(i, 0) /= U(i, i);
    }

    // Mostramos la solución

    char res = 'A';
    cout << "La solucion del sistema Ax = b es:" << endl;
    for (int i = 0; i < nrows; ++i) {
        cout << res << " = " << x(i, 0) << endl;
        res++;
    }
    cout << endl;

    // Verificamos la solución
    if ((A * x - b).norm1() < tol) {
        cout << "La solucion es correcta: Ax = b" << endl;
    } else {
        cout << "La solucion es incorrecta." << endl;
    }

    cout << endl;

    return 0;
}

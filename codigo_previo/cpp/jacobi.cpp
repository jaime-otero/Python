#include <iostream>
#include <fstream>  // para salida/entrada por fichero
#include <string>
#include <cmath>
#include <iomanip>  // para setprecision
#include <sstream>
#include <vector>
using namespace std;

#include <cmatrix>
using namespace techsoft;

double norma_maxima (const matrix<double>& A) {
    int nrows = A.rowno();
    int ncols = A.colno();
    double max_val = 0.0;
    double sum = 0.0;
    for (int i = 0; i < nrows; ++i) {
        sum = 0.0;
        for (int j = 0; j < ncols; ++j) {
            sum += abs(A(i, j));    
        }
        if (sum > max_val) {
                max_val = sum;
        }
    }
    return max_val;
}

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
int diag_dom(const matrix<double>& A) {

    int nrows = A.rowno();
    int ncols = A.colno();

    for (int i = 0; i < nrows; ++i) {
        double sum = 0.;
        for (int j = 0; j < ncols-1; ++j) {
            if (i != j) {
                sum += abs(A(i, j));
            }
        }
        if (fabs(A(i, i)) < sum) {
            return 1;
        }
       
    }
    return 0;
}
matrix<double> xnew(const matrix<double>& A, const matrix<double>& b,matrix<double>& x,double const max_iter,double const tol, const int nrows, const int ncols) {
    
    matrix<double> x_new (nrows,1);
    
    for (int k = 0; k < max_iter; ++k) {
        // Calculamos la nueva aproximacion
        for (int i = 0; i < nrows; ++i) {
            double sum = 0.;
            for (int j = 0; j < ncols-1; ++j) {
                if (i != j) {
                    sum += A(i, j) * x(j, 0);
                }
            }
            x_new(i, 0) = (b(i, 0) - sum) / A(i, i);
        }

        // Comprobamos la convergencia
        if (norma_maxima(A*x_new-b) < tol) {
            cout << "+ La solucion ha convergido en " << k << " iteraciones.\n";
            break;
        }
        x = x_new;

    }
    return x_new;
}

int main(){{

  // cout << scientific << setprecision(3);
    
  
  ifstream ff("matriz.txt");
	if (!ff.is_open()) {
		cout << "No se pudo abrir el archivo 'matriz.txt'.\n";
		return 1;
	}

    int nrows = 0, ncols = 0;
    contar(nrows, ncols);

    cout << "\n Comprobaciones intermedias:\n " << endl;

    if (ncols < 2) {
        cout << "La matriz debe tener al menos dos columnas (una para A y otra para b).\n " << endl;
        return 1;
    }
    else if (nrows < 1) {
        cout << "La matriz debe tener al menos una fila.\n " << endl;
        return 1;
    }
    else if (nrows != ncols - 1) {
        cout << "La matriz A debe ser cuadrada (numero de filas = numero de columnas - 1).\n " << endl;
        return 1;
    }
    else{ cout << "+ El sistema se ha leido correctamente.\n " << endl;
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

    // comprobamos que abs(Aii) >= sum(|Aij|) para i!=j

    int result = diag_dom(A);
    if (result == 1) {
        cout << "La matriz NO cumple la condicion de diagonal dominante.\n";
        return 1;
    } else {
        cout << "+ La matriz cumple la condicion de diagonal dominante.\n";
    }

    // ahora resolvemos el sistema Ax = b por el metodo de Jacobi

    matrix<double> x(nrows, 1); // solucion inicializada a cero

    // Iteramos hasta que la solucion converja
    const double tol = 1e-10;
    int max_iter = 1000;
    matrix<double> x_new = xnew(A, b, x, max_iter, tol, nrows, ncols);

    cout << "\n La solucion del sistema Ax = b es:\n" << endl;
    cout << x << endl;

    // Verificamos la solucion

    cout << "Comprobacion de la solucion:\n" << endl;

    if (norma_maxima(A*x_new-b) < tol) {
        cout << "+ La solucion es correcta: Ax = b\n" << endl;
    } else {
        cout << "- La solucion es incorrecta.\n" << endl;
    }    


    return 0;
}}
    

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

// Genera los nombre de cada variable de la solucion
string fnom(const int i, const string& tipo = "x") {
	return tipo + to_string(i);
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
        for (int j = 0; j < ncols; ++j) {
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

void descomposicion_lu(const matrix<double>& A, matrix<double>& L, matrix<double>& U) {
    int n = A.rowno();
    L = matrix<double>(n, n);
    U = matrix<double>(n, n);
    double sum=0;

    for (int i = 0; i < n; ++i) {
        // U
        for (int j = i; j < n; ++j) {
            sum = 0;    

                for (int k = 0;k < i; ++k) {
                    sum += L(i, k) * U(k, j);
                }
                U(i, j) = A(i, j) - sum;
        }
        // L
        
        for (int j = i; j < n; ++j) {
            
            sum = 0;
            
            if (i == j) {
                L(i, i) = 1;
            }
            else {
                for (int k = 0; k < i; ++k) {
                     sum += L(j, k) * U(k, i);
                }
                L(j, i) = A(j, i) - sum;
                L(j, i) /= U(i, i);
            }
        }

}
}
void metodo_lu(const matrix<double>& A, matrix<double>& L, matrix<double>& U, const matrix<double>& b, double tol, matrix<double>& x) {// Realizamos la descomposición LU

   int nrows = A.rowno();
   int ncols = A.colno();

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
    for (int i = nrows - 1; i >= 0; --i) {
        x(i, 0) = z(i, 0);
        for (int j = i + 1; j < nrows; ++j) {
            x(i, 0) -= U(i, j) * x(j, 0);
        }
        x(i, 0) /= U(i, i);
    }

    // Mostramos la solución

    cout << "La solucion del sistema Ax = b es:" << endl;
    for (int i = 0; i < nrows; ++i) {
        cout << fnom(i) << " = " << x(i, 0) << endl;
    }
    cout << endl;


     

    // Verificamos la solución
    if ((A * x - b).norm1() < tol) {
        cout << "La solucion es correcta: Ax = b" << endl;
    } else {
        cout << "La solucion es incorrecta." << endl;
    }

    cout << endl;
}

void Metodo_jacobi(const matrix<double>& A, const matrix<double>& b,matrix<double>& xj,int const max_iter,double const tol) {  
    int nrows = A.rowno();
    int ncols = A.colno();
    
    matrix<double> xj_new (nrows,1);

    
    for (int k = 0; k < max_iter; ++k) {
        // Calculamos la nueva aproximacion
        for (int i = 0; i < nrows; ++i) {
            double sum = 0.;
            for (int j = 0; j < ncols; ++j) {
                if (i != j) {
                    sum += A(i, j) * xj(j, 0);
                }
            }
            xj_new(i, 0) = (b(i, 0) - sum) / A(i, i);
        }

        // Comprobamos la convergencia
        if (norma_maxima(A*xj_new-b) < tol) {
            cout << "\nLa solucion ha convergido en " << k+1 << " iteraciones.\n";
            break;
        }
        xj = xj_new;
    }
    
    xj = xj_new;
    cout << "La solucion del sistema Ax = b es:\n" << endl;
    for (int i = 0; i < nrows; ++i) {
        cout << fnom(i) << " = " << xj(i, 0) << endl;
    }
    // Verificamos la solucion

    cout << "Comprobacion de la solucion:\n" << endl;

    if (norma_maxima(A*xj-b) < tol) {
        cout << "La solucion es correcta: Ax = b\n" << endl;
    } else {
        cout << "La solucion es incorrecta.\n" << endl;
    }
}

void Gauss_Seidel(const matrix<double>& A, const matrix<double>& b,matrix<double>& xg,int const max_iter,double const tol) {  

    int nrows = A.rowno();
    int ncols = A.colno();


    
    for (int k = 0; k < max_iter; ++k) {
        // Calculamos la nueva aproximacion

        for (int i = 0; i < nrows; ++i) {
            double sum = 0.;
            for (int j = 0; j < ncols; ++j) {
                if (i != j) {
                    sum += A(i, j) * xg(j, 0);
                }
            }
            xg(i, 0) = (b(i, 0) - sum) / A(i, i);
        }

        // Comprobamos la convergencia
        if (norma_maxima(A*xg-b) < tol) {
            cout << "\nLa solucion ha convergido en " << k+1 << " iteraciones.\n";
            break;
        }
    }
    cout << "La solucion del sistema Ax = b es:\n" << endl;
    for (int i = 0; i < nrows; ++i) {
        cout << fnom(i) << " = " << xg(i, 0) << endl;
    }
    // Verificamos la solucion

    cout << "Comprobacion de la solucion:\n" << endl;

    if (norma_maxima(A*xg-b) < tol) {
        cout << "La solucion es correcta: Ax = b\n" << endl;
    } else {
        cout << "La solucion es incorrecta.\n" << endl;
    }
}

int main() {

  cout << fixed << setprecision(6);
    
  
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
    else{ cout << "+ El sistema se ha leido correctamente." << endl;
    }

	// Leer la matriz completa (A y b)
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


    // inicializamos todas las matrices de resultados

        matrix<double> xLU(nrows, 1);
        matrix<double> xj(nrows, 1); 
        matrix<double> xg(nrows, 1); 
        int max_iter = 1000;
        double tol = 1e-5;

    matrix<double> L, U;
    descomposicion_lu(A, L, U);

// comprobamos que A = LU

    if (norma_maxima(A - L * U) < tol) {
        cout << "+ La descomposicion LU es correcta: A = LU" << endl;
    } else {
        cout << "+ La descomposicion LU es incorrecta." << endl;
    }

    cout << endl;

 


    // Resolvemos el sistema Ax = b usando la descomposicion LU
    cout << "\nResolviendo el sistema Ax = b usando la descomposicion LU:\n" << endl;
    metodo_lu(A, L, U, b, tol, xLU);

    // ahora resolvemos el sistema Ax = b por el metodo de Jacobi
    cout << "Resolviendo el sistema Ax = b usando el metodo de Jacobi:" << endl;
    Metodo_jacobi(A, b, xj, max_iter, tol);

    // ahora resolvemos el sistema Ax = b por el metodo de Gauss-Seidel
    cout << "Resolviendo el sistema Ax = b usando el metodo de Gauss-Seidel:" << endl;
    Gauss_Seidel(A, b, xg, max_iter, tol);


    

    return 0;

}

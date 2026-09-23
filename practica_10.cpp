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

#include <chrono>
using namespace chrono;
time_point<high_resolution_clock> start_lu, end_lu;
microseconds duration_lu;

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
void metodo_lu(const matrix<double>& A, const matrix<double>& b, double tol, matrix<double>& x) {// Realizamos la descomposición LU

    matrix<double> L, U;
    descomposicion_lu(A, L, U);

// comprobamos que A = LU

    if (norma_maxima(A - L * U) < tol) {
        cout << "+ La descomposicion LU es correcta: A = LU" << endl;
    } else {
        cout << "+ La descomposicion LU es incorrecta." << endl;
    }

    cout << endl;
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

     

    // Verificamos la solución
    if ((A * x - b).norm1() < tol) {
        cout << "La solucion es correcta: Ax = b" << endl;
    } else {
        cout << "La solucion es incorrecta." << endl;
    }

    cout << endl;
}


void metodo_lu_tridiagonal(
    const matrix<double>& Dinf, 
    const matrix<double>& D, 
    const matrix<double>& DS, 
    const matrix<double>& b, 
    matrix<double>& x,
    double tol,
    const matrix<double>& A) 
{
    int n = D.rowno();

    matrix<double> vec_delta_f(n, 1, 0.0);
    matrix<double> vec_delta(n, 1, 0.0);

    // z es el vector intermedio de la solución Lz = b
    matrix<double> z(n, 1, 0.0);
    // --- 2. CÁLCULO DE LOS VECTORES δ y δ^(f)

    // Caso i = 0
    if (abs(D(0, 0)) < 1e-15) { 
        cout << "Error: Pivote cero en la descomposición." << endl; return; 
    }

    vec_delta(0, 0) = D(0, 0); 

    for (int i = 1; i < n; ++i) {
        if (abs(vec_delta(i - 1, 0)) < 1e-15) { 
            cout << "Error: Pivote cero en la descomposición." << endl; return; 
        }

        vec_delta_f(i, 0) = Dinf(i, 0) / vec_delta(i - 1, 0);
        
        vec_delta(i, 0) = D(i, 0) - vec_delta_f(i, 0) * DS(i - 1, 0);
    }

    // --- 3. SOLUCIÓN Lz = b
    
    z(0, 0) = b(0, 0); // Fórmula: z_0 = b_0

    // Casos i = 1 hasta n-1
    for (int i = 1; i < n; ++i) {
        z(i, 0) = b(i, 0) - vec_delta_f(i, 0) * z(i - 1, 0);
    }

    
    if (abs(vec_delta(n - 1, 0)) < 1e-15) { 
        cout << "Error: Pivote cero en la sustitución." << endl; return; 
    }
    x(n - 1, 0) = z(n - 1, 0) / vec_delta(n - 1, 0);

    for (int i = n - 2; i >= 0; --i) {
        if (abs(vec_delta(i, 0)) < 1e-15) { 
            cout << "Error: Pivote cero en la sustitución." << endl; return; 
        }
        x(i, 0) = (z(i, 0) - DS(i, 0) * x(i + 1, 0)) / vec_delta(i, 0);
    }


    
    if ((A * x - b).norm1() < tol) {
        cout << "La solucion es correcta: Ax = b" << endl;
    } else {
        cout << "La solucion es incorrecta." << endl;
    }
    cout << endl;
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

   // Comprobamos que la matriz A es cuadrada
    if (A.rowno() == A.colno()) {
        cout << "+ La matriz de coeficientes es cuadrada." << endl;
    } else {
        cout << "+ La matriz de coeficientes no es cuadrada." << endl;
        return 1;
    }

    double tol = 1e-5;

    bool es_tridiagonal = true;
    // Comprobamos que la matriz A es tridiagonal
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols - 1; ++j) {
                if (i == j + 1 || i == j - 1  || i == j ) {
                    // Elemento en una de las 3 diagonales
                    continue;
                } else if (A(i, j) > tol) {
                    es_tridiagonal = false;
                    break;
                }
        }
      
    }

    if (es_tridiagonal) {
        cout << "+ La matriz de coeficientes es tridiagonal." << endl;
    } else {
        cout << "+ La matriz de coeficientes no es tridiagonal." << endl;
    }


    // inicializamos todas las matrices de resultados

    matrix<double> xLU(nrows, 1);
    matrix<double> xtri(nrows, 1);

    
    
    
    matrix<double> D(nrows,1);
    matrix<double> Dinf(nrows,1); Dinf(0,0)=0; 
    matrix<double> DS(nrows,1); DS(nrows-1,0)=0;


    for (int h = 0; h<nrows; h++){

        D(h,0)=A(h,h);
        
        if (h>0){
            Dinf(h,0)=A(h,h-1);
        }
        if (h<nrows-1){
            DS(h,0)=A(h,h+1);
        }
    }

    // Resolvemos el sistema Ax = b usando la descomposicion LU
    cout << "\nResolviendo el sistema Ax = b usando la descomposicion LU:\n" << endl;

    start_lu = high_resolution_clock::now();
    metodo_lu(A, b, tol, xLU);
    end_lu = high_resolution_clock::now();
    duration_lu = duration_cast<microseconds>(end_lu - start_lu);

    cout << "Tiempo de ejecucion del metodo LU: " << duration_lu.count() << " microsegundos." << endl;

    if (es_tridiagonal) {
        cout << "\nResolviendo el sistema Ax = b usando la descomposicion LU optimizada para matrices tridiagonales:\n" << endl;
        start_lu = high_resolution_clock::now();
        metodo_lu_tridiagonal(Dinf, D, DS, b, xtri, tol, A);
        end_lu = high_resolution_clock::now();
        duration_lu = duration_cast<microseconds>(end_lu - start_lu);

        cout << "Tiempo de ejecucion del metodo LU optimizado para matrices tridiagonales: " << duration_lu.count() << " microsegundos." << endl;

        cout << "\nComparando las soluciones obtenidas por ambos metodos:\n" << endl;
        if (norma_maxima(xLU - xtri) < tol) {
            cout << "Las soluciones obtenidas por ambos metodos son iguales." << endl;
        } else {
            cout << "Las soluciones obtenidas por ambos metodos son diferentes." << endl;
        }


    }
    

    return 0;

}

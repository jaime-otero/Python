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
vector<int> diag_dom(const matrix<double>& A) {

    int nrows = A.rowno();
    int ncols = A.colno();

    vector<int> comp(nrows, 1); // Inicializamos con true

    for (int i = 0; i < nrows; ++i) {
        double sum = 0.;
        for (int j = 0; j < ncols-1; ++j) {
            if (i != j) {
                sum += abs(A(i, j));
            }
        }
        if (fabs(A(i, i)) < sum) {
            comp[i] = 0; // No cumple
        }

        if (comp[i] == 1) {
            cout << "+ La fila " << i+1 << " cumple la condicion de diagonal dominante.\n";
        }
        else {
            cout << "- La fila " << i+1 << " NO cumple la condicion de diagonal dominante.\n";
        }
    }

    return comp; 
}

int main(){

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

    vector <int> comp = diag_dom(A);

    if (comp[0] && comp[1] && comp[2] && comp[3]) {
        cout << "\n+ La matriz A cumple la condicion de diagonal dominante.\n " << endl;
    } else {
        cout << "\n- La matriz A NO cumple la condicion de diagonal dominante.\n " << endl;
    }





    return 0;
}
    

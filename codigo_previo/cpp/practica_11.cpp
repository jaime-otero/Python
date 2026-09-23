#include <iostream>
#include <fstream>  // para salida/entrada por fichero
#include <string>
#include <cmath>
#include <iomanip>  // para setprecision
#include <sstream>
using namespace std;

#include <cmatrix>
using namespace techsoft;

const double pi = 3.141592;

// Norma máxima de una matriz
double norma_maxima (const matrix<double>& A) {
    int nrows = A.rowno();
    int ncols = A.colno();
    double max_val = 0.0;
    double sum = 0.0;
    for (int i = 0; i < nrows; i++) {
        sum = 0.0;
        for (int j = 0; j < ncols; j++) {
            sum += abs(A(i, j));    
        }
        if (sum > max_val) {
                max_val = sum;
        }
    }
    return max_val;
}
 
void max_valor(double& max_val, int& pos_i, int& pos_j, const matrix<double> A){
    
    int nrows = A.rowno();
    int ncols = A.colno();

    for (int i = 0; i<nrows;i++ ){
        for (int j = i+1; j<ncols; j++){
            if (abs(A(i,j)) > max_val){
                max_val = abs(A(i,j));
                pos_i = i;
                pos_j = j;
            }
        }
    }
}

matrix <double> tensor_de_inercia(const matrix<double> &x, const matrix<double> &y, const matrix<double> &z, const matrix<double> &m){
    
    int n = x.rowno();

    double Ixx = 0.0;
    double Iyy = 0.0;
    double Izz = 0.0;
    double Ixy = 0.0;
    double Ixz = 0.0;
    double Iyz = 0.0;
    
    for (int i=0; i<n; i++){
        Ixx += m(i,0)*(pow(y(i,0),2)+pow(z(i,0),2));
        Iyy += m(i,0)*(pow(x(i,0),2)+pow(z(i,0),2));
        Izz += m(i,0)*(pow(x(i,0),2)+pow(y(i,0),2));
        Ixy += -m(i,0)*x(i,0)*y(i,0);
        Ixz += -m(i,0)*x(i,0)*z(i,0);
        Iyz += -m(i,0)*y(i,0)*z(i,0);
    }

    matrix <double> A(3,3); // matriz de inercia 
        A(0,0)=Ixx;
        A(0,1)=Ixy;
        A(0,2)=Ixz;
        A(1,0)=Ixy;
        A(1,1)=Iyy;
        A(1,2)=Iyz;
        A(2,0)=Ixz;
        A(2,1)=Iyz;
        A(2,2)=Izz;

    return A;
}
void jacobi(matrix<double> &A,matrix<double> &U, matrix<double> &D, double tol, int &contador_rot,const matrix<double> &I, void (*max_valor)(double&, int&, int&, const matrix<double>)){


    matrix<double> A0 = A; // guardamos la matriz original antes de la rotacion
    matrix<double> D0 = D; // guardamos la matriz de autovalores antes de la rotacion
    matrix<double> U0 = U; // guardamos la matriz de autovectores antes de la rotacion
    int nrows = A0.rowno();
    int ncols = A0.colno();

    
    
    double max_val = 0.0;
    int pos_i;
    int pos_j;

    max_valor(max_val, pos_i, pos_j,A );

    double theta = 0.0;
    if (A(pos_i, pos_i) == A(pos_j,pos_j) ){
        theta = pi/4;
    }
    else{
        theta = .5*atan(2*A(pos_i,pos_j)/(A(pos_i,pos_i)-A(pos_j,pos_j)));
    }

    for (int k = 0; k<nrows;k++){
        if (k != pos_i && k != pos_j ){
            A(k,pos_i) = A0(pos_i,k)*cos(theta) + A0(pos_j,k)*sin(theta);
            A(pos_i, k) = A(k,pos_i);
            A(k,pos_j) = -A0(pos_i,k)*sin(theta) + A0(pos_j,k)*cos(theta);
            A(pos_j, k) = A(k,pos_j);
        }
        U(k,pos_i) = U0(k,pos_i)*cos(theta) + U(k,pos_j)*sin(theta);
        U(k,pos_j) = -U0(k,pos_i)*sin(theta) + U0(k,pos_j)*cos(theta);
    }

    
    double A_ii = A0(pos_i,pos_i);
    double A_jj = A0(pos_j,pos_j);
    double A_ij = A0(pos_i,pos_j);
    A(pos_i,pos_i) = A_ii*cos(theta)*cos(theta) + A_jj*sin(theta)*sin(theta) + 2*A_ij*sin(theta)*cos(theta);
    A(pos_j,pos_j) = A_jj*cos(theta)*cos(theta) + A_ii*sin(theta)*sin(theta) - 2*A_ij*sin(theta)*cos(theta);
    A(pos_i,pos_j) = 0.0;
    A(pos_j,pos_i) = 0.0;

    max_val = 0.0;
    max_valor(max_val, pos_i, pos_j,A );

    if (max_val > tol){
        contador_rot += 1;
        jacobi(A,U,D,tol,contador_rot,I, max_valor);
    }
    else{
        for (int i = 0; i<nrows;i++ ){
            D(i,i) = A(i,i);
        }
        cout << "\nNumero de rotaciones: " << contador_rot << endl;
        cout << "\n Autovalores: " << endl;
        for (int i = 0; i<nrows;i++ ){
            cout << D(i,i) << endl;
        }
        cout << "\n Autovectores: " << endl;
        for (int i = 0; i<nrows;i++ ){
            for (int j = 0; j<ncols;j++ ){
                cout << U(i,j) << " ";
            }
            cout << endl<<endl;
        }

        if (norma_maxima((A-D*I)*U) < tol){
            cout << "Solucion correcta: (A-lambda*I)U ~ 0" << endl;
        }
        else{
            cout << "Solucion incorrecta: |(A-lambda*I)U| > 0" << endl;
        }
        return;
    }
}

int main(){

    cout << fixed << setprecision(3);


    
    // definimos las matrices de posiciones y masas de las particulas

    int n = 5; //numero de particulas
    
    matrix <double> I(3,3,0.0); // matriz identidad 3x3
        I(0,0)=1.0;
        I(1,1)=1.0;
        I(2,2)=1.0;

    matrix <double> x(n,1);
        x(0,0)=0.0;
        x(1,0)=0.635; 
        x(2,0)=-0.635;
        x(3,0)=0.0;
        x(4,0)=0.0;

    matrix <double> y(n,1);
        y(0,0)=0.0;
        y(1,0)=0.635; 
        y(2,0)=0.635;
        y(3,0)=0.0;
        y(4,0)=0.0;

    matrix <double> z(n,1);
        z(0,0)=0.0;
        z(1,0)=0.0; 
        z(2,0)=0.0;
        z(3,0)=-0.6350;
        z(4,0)=-0.8;
        
    matrix <double> m(n,1);
        m(0,0)=12;
        m(1,0)=1; 
        m(2,0)=1;
        m(3,0)=1;
        m(4,0)=28;

    cout << "Posiciones iniciales (Angstroms):" << endl;
    for (int i=0; i<n; i++){
        cout << "Particula " << i+1 << ": (" << x(i,0) << ", " << y(i,0) << ", " << z(i,0) << "), m = "<< m(i,0) << endl;
    }   

    double sum_m=0.0;
    for (int i=0; i<n; i++){
        sum_m += m(i,0);
    }

    double x_cm=0.0;
    double y_cm=0.0;
    double z_cm=0.0;

    // calculamos el CM

    for (int i=0; i<n ; i++){
        x_cm += m(i,0)*x(i,0);
        y_cm += m(i,0)*y(i,0);
        z_cm += m(i,0)*z(i,0);
    }

    x_cm /= sum_m;
    y_cm /= sum_m;  
    z_cm /= sum_m;

    cout << "---------------------------------------------------------" << endl;

    
    cout << fixed << setprecision(6);
    cout << "\n Centro de masa (Angstroms): (" << x_cm << ", " << y_cm << ", " << z_cm << ")" << endl;

    // ahora trasladamos las particulas al CM

    for (int i=0; i<n; i++){
        x(i,0) = x(i,0) - x_cm;
        y(i,0) = y(i,0) - y_cm;
        z(i,0) = z(i,0) - z_cm;
    }

    cout << "\n Posiciones respecto al CM (Angstroms):" << endl;
    for (int i=0; i<n; i++){
        cout << "Particula " << i+1 << ": (" << x(i,0) << ", " << y(i,0) << ", " << z(i,0) << "), m = "<< m(i,0) << endl;
    }

    // ahora calculamos la matriz de inercia respecto al CM

    matrix <double> A = tensor_de_inercia(x,y,z,m);
    cout << "\nMatriz de inercia respecto al CM:" << endl;
    cout << A << endl;
    
    int nrows = A.rowno();
    int ncols = A.colno();

    // inicializamos la matriz de autovectores y el vector de autovalores
    matrix <double> U(nrows,ncols); // autovectores
    U = I; // la inicializamos como la matriz identidad
    matrix <double> D(nrows,ncols,0.0); // autovalores

    double tol = 1e-10;
    int contador_rot = 1;

    cout << "---------------------------------------------------------" << endl;


    cout << "\n Calculando autovalores y autovectores mediante el metodo de Jacobi... " << endl;
    
    jacobi(A,U,D,tol,contador_rot,I, max_valor);

    // Rotamos las coordenadas atomicas de los ejes principales

    // --- Paso 4: Rotar coordenadas al sistema de ejes principales ---

    cout << "---------------------------------------------------------" << endl;

    matrix <double> x_prima(n, 1);
    matrix <double> y_prima(n, 1);
    matrix <double> z_prima(n, 1);

    // Recorremos cada uno de los 'n' átomos
    for (int i = 0; i < n; i++) {
        
        // Obtenemos las coordenadas (ya centradas en el CM) del átomo 'i'
        double old_x = x(i, 0);
        double old_y = y(i, 0);
        double old_z = z(i, 0);

        // Aplicamos la fórmula: (nuevas_coords) = U.transpose() * (viejas_coords)

        // Fila 1 de U.transpose() * (viejas_coords)
        // (es Columna 1 de U)
        double new_x = U(0, 0) * old_x + U(1, 0) * old_y + U(2, 0) * old_z;
        
        // Fila 2 de U.transpose() * (viejas_coords)
        // (es Columna 2 de U)
        double new_y = U(0, 1) * old_x + U(1, 1) * old_y + U(2, 1) * old_z;

        // Fila 3 de U.transpose() * (viejas_coords)
        // (es Columna 3 de U)
        double new_z = U(0, 2) * old_x + U(1, 2) * old_y + U(2, 2) * old_z;

        // Guardamos las nuevas coordenadas calculadas
        x_prima(i, 0) = new_x;
        y_prima(i, 0) = new_y;
        z_prima(i, 0) = new_z;
    }

    // Imprimimos los resultados finales
    cout << "Nuevas posiciones (Angstroms) en el sistema de ejes principales:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Particula " << i + 1 << ": (" 
             << x_prima(i, 0) << ", " 
             << y_prima(i, 0) << ", " 
             << z_prima(i, 0) << ")" << endl << endl;
    }

    matrix<double> A_final = tensor_de_inercia(x_prima, y_prima, z_prima, m);
    cout << "Matriz de inercia en el sistema de ejes principales:" << endl;
    cout << A_final << endl;

    //comrpobamos que todo es correcto si el tensor de inercia en el sistema de ejes principales es diagonal y coincide con los autovalores
    cout << "Comprobamos que el tensor de inercia en el sistema de ejes principales es diagonal y coincide con los autovalores: " << endl;  
    if (norma_maxima(A_final - D) < tol){
        cout << "Comprobacion correcta" << endl;
    }
    else{
        cout << "Comprobacion incorrecta" << endl;
    }

    return 0;
}
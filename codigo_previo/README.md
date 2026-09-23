# Código previo

Prácticas de métodos numéricos en C++ del curso pasado. Aquí sirven para tres cosas:

1. **Diagnóstico:** ver qué hábitos traes de C++ para ajustar el plan (ver
   [`apuntes/02_de_tu_cpp_a_python.md`](../apuntes/02_de_tu_cpp_a_python.md)).
2. **Ejercicios de traducción:** en M6, M8 y M10 reescribirás en Python varias de estas prácticas.
   Ya conoces el problema, así que te centras en el lenguaje, y el resultado en C++ sirve para
   comprobar que tu versión en Python es correcta.
3. **Retos de depuración:** algunas prácticas tienen fallos sutiles (ver abajo). Encontrarlos al
   traducir es un buen ejercicio.

> Las prácticas usan `cmatrix` (`techsoft::matrix`), la librería de matrices de la asignatura. No
> está en el repositorio, así que estos archivos no se compilan aquí. En Python, su papel lo hace
> NumPy. Tampoco están los ficheros de datos que leen (`matriz.txt`, `posiciones.txt`); si los
> tienes, súbelos a `codigo_previo/datos/`.

## Catálogo

| Archivo | Qué hace | Método | Se traduce en |
|---|---|---|---|
| `raices.cpp` | Raíz de x² − 5 | Newton, bisección, secante | **M8** (primera traducción) |
| `practica6.cpp` | Alcance de una fuerza tipo Yukawa (r₀ = 1,2 fm): dónde cae al 1 % | Newton, bisección, secante y barrido de tolerancias | M8 + gráfica en M7 |
| `Newton_raphson.cpp` | Sistema no lineal 3×3 | Newton-Raphson con jacobiano | M8 (`scipy.optimize.root`) |
| `crear_matrix.cpp` | Sistema para ajustar la fórmula de Cauchy n(λ) = A + B/λ² + C/λ⁴ | Construcción de matrices | **M6** |
| `crear_matriz_tridiagonal.cpp` | Sistema tridiagonal 1000×1000 | Construcción de matrices | **M6** |
| `LU.cpp` → `comp_lu.cpp` → `practica7.cpp` | Resolver Ax = b (tres versiones de la misma práctica) | Descomposición LU de Doolittle | M8 |
| `Practica_8.cpp` | Comparar métodos directos e iterativos | LU, Jacobi, Gauss-Seidel | M8 |
| `jacobi.cpp` | Resolver Ax = b | Jacobi iterativo | **M6** (vectorizado) y M8 |
| `reordenar_matriz.cpp` | Comprobar diagonal dominante fila a fila | — | **M6** (cabe en una línea) |
| `practica_10.cpp` | LU general frente a LU tridiagonal, con tiempos | LU, algoritmo de Thomas | **M10** (medir rendimiento) |
| `practica_11.cpp` | Tensor de inercia de una molécula y sus ejes principales | Jacobi para autovalores (recursivo) | M8 (`np.linalg.eigh`) |
| `practica_12.cpp` | Periodo del péndulo con amplitud grande (integral elíptica) | Trapecio, Simpson 1/3 y 3/8 | M8 (comparar con `scipy.special.ellipk`) |
| `practica13.cpp` | Potencia radiada por un cuerpo negro (Planck) | Simpson adaptativo, Gauss-Legendre | M8 |
| `ejercicio1_final.cpp` | Capacidad calorífica de Debye frente a T | Simpson 1/3 | M6 (vectorizar en T) + M8 |
| `practica14.cpp` | Velocidad y aceleración a partir de datos de posición | Diferencias finitas de 3 puntos | **M6** (`np.gradient`) |
| `Practica15.cpp` | EDO de primer orden con solución exacta | Euler, RK2, RK4 | M8 |
| `Practica16.cpp` | Dos masas acopladas con muelles | RK4 para sistemas | M8 + M7 |
| `practica17.cpp` | Péndulo de Foucault con ajuste de paso | RK4, reducción de paso | M8 |
| `practica18.cpp` | Potencial entre esferas concéntricas | Método del disparo + secante | M8 (`scipy.integrate.solve_bvp`) |
| `practica19.cpp` | Temperatura en una barra | Disparo frente a diferencias finitas tridiagonales | M8 |
| `ejercicio2_final.cpp` | Péndulo doble | RK4 | **M11** (candidato a proyecto final) |

## Retos de depuración

Estos programas tienen un fallo sutil: compilan, y a veces hasta dan un resultado que parece
correcto. Solo te doy la pista; encontrarlo es cosa tuya, idealmente al traducirlos.

| Archivo | Pista |
|---|---|
| `practica13.cpp` | Prueba `metodoGauss` con `n = 2`. ¿Cuánto vale la integral? ¿Por qué? |
| `practica18.cpp` | Sigue el valor de `tan_b` desde que se declara hasta que entra en la secante. |
| `jacobi.cpp` | `diag_dom` recibe `A`, no la matriz ampliada. ¿Qué columnas recorre? ¿Y qué vector se imprime al final? |
| `practica_10.cpp` | La comprobación de "es tridiagonal", ¿detecta un −5 fuera de las tres diagonales? |
| `Practica15.cpp` | Hay dos `cout` que no imprimen lo que parece. Y, en RK2/RK4, ¿el `x` que se escribe corresponde al `y` que se escribe? |
| `LU.cpp` | ¿Qué garantiza que `det(A − LU) < tol`? ¿Tiene sentido el determinante de un vector columna? |
| `Newton_raphson.cpp` | ¿Qué ocurre si Newton no converge en `max_iter` iteraciones? Fíjate en el `do ... while`. |

Varios de estos fallos **no pueden darse en Python** o Python los hace muy visibles. Cuando los
encuentres, piensa por qué.

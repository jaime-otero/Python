# De tu C++ a Python

Diagnóstico sacado de tus prácticas de `codigo_previo/cpp/`. Primero lo que ya haces bien, y
después los hábitos que en Python conviene cambiar, cada uno con su equivalente.

## Lo que ya haces bien

- **Compruebas los resultados:** `A = LU`, `Ax = b`, residuos por debajo de la tolerancia y
  comparación con la solución exacta. Es la mentalidad correcta, y en Python se convierte en tests
  (M5) y en `np.allclose`.
- **Piensas en los casos límite:** división por cero, pivotes nulos, número máximo de iteraciones,
  intervalos sin cambio de signo.
- **Separas en funciones** y comentas el código.
- **Mides tiempos** (`practica_10.cpp`) y **adaptas el paso** (`practica17.cpp`). Es un buen punto de partida para M10.

## Hábitos para cambiar

### 1. Copiar y pegar funciones entre prácticas → módulos (M3)

`contar`, `norma_maxima`, `descomposicion_lu` y la lectura de `matriz.txt` están copiados en 6–7
archivos, cada uno con pequeñas diferencias. En Python se escriben una vez en un módulo y se
importan:

```python
# metodos_numericos/lineal.py
def lu(A): ...

# cualquier práctica
from metodos_numericos.lineal import lu
```

La biblioteca `metodos_numericos/` del M8 es justo eso: tus prácticas reunidas, sin duplicados.

### 2. Devolver resultados por referencia → devolver tuplas (M1–M2)

```cpp
int newton(const double tol, double &x, const int max_iter);   // x sale por referencia
```

```python
def newton(f, df, x0, tol=1e-6, max_iter=1000):
    ...
    return x, n            # se devuelven los dos valores

raiz, iteraciones = newton(f, df, 2.0)
```

En Python no hay `&`: los números son inmutables y no se pueden modificar "desde fuera". Se devuelven.

### 3. Bucles con índices y vectores `(i, 0)` → NumPy vectorizado (M6)

Tu `tensor_de_inercia` son 6 acumuladores en un bucle. `norma_maxima` son dos bucles anidados.
Con NumPy:

```python
np.abs(A).sum(axis=1).max()             # tu norma_maxima (norma infinito)
np.linalg.norm(A, np.inf)               # lo mismo, ya hecho
```

Además, en NumPy un vector es un array 1-D (`shape (n,)`) y no una matriz `n×1`. Se acabó
escribir `x(i, 0)`.

### 4. Leer ficheros a mano → `np.loadtxt` (M3/M6)

Tu `contar()` recorre el fichero para saber su tamaño y luego lo vuelves a abrir para leerlo.
En Python:

```python
m = np.loadtxt("matriz.txt")       # lee la matriz entera y deduce el tamaño
A, b = m[:, :-1], m[:, -1]         # separa A y b con slicing
```

### 5. Punteros a función → funciones como objetos (M2)

`double (*f)(double, double)` pasa a ser simplemente `f`. Para fijar un parámetro, como la `k` de
`practica_12.cpp`, se usa una `lambda` o `functools.partial`:

```python
trapecio(lambda x: 1 / np.sqrt(1 - k**2 * np.sin(x)**2), 0, np.pi / 2, n=100)
```

### 6. Variables globales mutables → funciones puras

En `ejercicio2_final.cpp`, `th1`, `w1`, `t1` y `den` son globales que `F` modifica en cada llamada.
Funciona, pero cualquier otra función puede pisarlas. En Python, mejor variables locales y
parámetros explícitos. Tus constantes físicas (`g`, `k1`, `m1`…) sí tiene sentido que sean
constantes de módulo, en MAYÚSCULAS por convención.

### 7. Código repetido con pequeñas variaciones → bucles y f-strings (M1)

```cpp
if (i == 0) { ... "resultadoseuler_0.5.txt" ... }
if (i == 1) { ... "resultadoseuler_0.1.txt" ... }
```

```python
for h in [0.5, 0.1, 0.02]:
    euler(..., h=h, fichero=f"resultados_euler_{h}.txt")
```

### 8. Contadores `double` en bucles → `np.linspace` o contadores enteros (M6)

`for (double t = 0; t <= t_final + 1e-9; t += h)` necesita el `+ 1e-9` porque sumar `h` muchas
veces acumula error de redondeo (ver el capítulo 15 del tutorial). Mejor:

```python
t = np.linspace(0, t_final, n_pasos + 1)   # los extremos son exactos
for i in range(n_pasos): ...
```

### 9. `cout` de error + `return 1`/`exit(1)` → excepciones (M3)

```python
if f(a) * f(b) > 0:
    raise ValueError("f(a) y f(b) deben tener signos opuestos")
```

Quien llame a la función decide qué hacer con el error. No lo decide la función imprimiendo mensajes.

### 10. `new[]` / `delete[]` → nada

En `practica14.cpp` gestionas la memoria a mano. En Python (y en NumPy) no existe: el recolector de
basura libera lo que ya no se usa.

### 11. Recursión profunda (`practica_11.cpp`)

Tu Jacobi para autovalores se llama a sí mismo en cada rotación. En C++ funciona, pero Python
limita la recursión a unas 1000 llamadas (`sys.getrecursionlimit()`). Con una matriz grande
fallaría. En Python, esto se escribe con un bucle `while`.

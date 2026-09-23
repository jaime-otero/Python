# Chuleta: de C++ y MATLAB a Python

## El mismo programa en los tres lenguajes

```python
# Python
datos = [3, 1, 4, 1, 5]          # lista: sin tipo declarado ni tamaño fijo
total = 0
for x in datos:                  # recorre los elementos directamente, sin índice
    if x > 2:                    # sin llaves: la indentación ES el bloque
        total += x
print(total)                     # 12

print(datos[0])                  # 3  -> índices desde 0, como en C++ (no como en MATLAB)
print(datos[1:3])                # [1, 4] -> el final del rango NO se incluye
```

```cpp
// C++
std::vector<int> datos{3, 1, 4, 1, 5};
int total = 0;
for (int x : datos) { if (x > 2) total += x; }
```

```matlab
% MATLAB
datos = [3 1 4 1 5];
total = sum(datos(datos > 2));
```

## Sintaxis básica

| Concepto | C++ | MATLAB | Python |
|---|---|---|---|
| Comentario | `// ...` | `% ...` | `# ...` |
| Bloques | `{ }` | `... end` | `:` + indentación (4 espacios) |
| Fin de sentencia | `;` obligatorio | `;` suprime la salida | nada |
| Declarar variable | `int x = 3;` | `x = 3;` | `x = 3` |
| Distinto | `!=` | `~=` | `!=` |
| Lógicos | `&& \|\| !` | `&& \|\| ~` | `and or not` |
| Potencia | `pow(a, b)` | `a^b` | `a ** b` (`^` es XOR a nivel de bits) |
| División | `7/2 == 3` (enteros) | `7/2 == 3.5` | `7/2 == 3.5`, `7//2 == 3` |
| Resto | `%` | `mod(a, b)` | `%` (con divisor positivo, el resultado es siempre ≥ 0: `-7 % 3 == 2`) |
| Nulo | `nullptr` | `[]` | `None` |
| Verdadero/falso | `true/false` | `true/false` | `True/False` |
| Imprimir | `std::cout << x` | `disp(x)`, `fprintf` | `print(x)`, `print(f"x = {x:.3f}")` |
| Función anónima | `[](int x){ return x*x; }` | `@(x) x.^2` | `lambda x: x**2` |

## Control de flujo

```python
if x > 0:
    ...
elif x == 0:          # "elif", no "else if" ni "elseif"
    ...
else:
    ...

for i in range(5):            # 0, 1, 2, 3, 4   (MATLAB: for i = 0:4)
    ...
for i in range(2, 10, 3):     # 2, 5, 8         (MATLAB: 2:3:9) -> fin EXCLUIDO
    ...
for i, x in enumerate(datos): # índice y valor a la vez: nada de datos[i]
    ...
for a, b in zip(xs, ys):      # recorrer dos listas en paralelo
    ...
while cond:
    ...
```

No hay `do-while` ni `switch` clásico (existe `match`, pero es más potente que un `switch`).

## Colecciones

| Python | Parecido a | Notas |
|---|---|---|
| `list` `[1, 2, 3]` | `std::vector` | Mutable y puede mezclar tipos. **No es una matriz**: `[1, 2] * 2 == [1, 2, 1, 2]` |
| `tuple` `(1, 2)` | `std::tuple` | Inmutable. Se usa para devolver varios valores: `return a, b` |
| `dict` `{"a": 1}` | `std::unordered_map` | Conserva el orden de inserción |
| `set` `{1, 2}` | `std::unordered_set` | Sin duplicados |
| `str` `"hola"` | `std::string` | **Inmutable**. Comillas simples o dobles, da igual |

Para matrices y cálculo numérico se usa **NumPy** (módulo M6), no listas.

## Slicing: `secuencia[inicio:fin:paso]`

```python
a = [10, 20, 30, 40, 50]
a[0]      # 10          primer elemento     (MATLAB: a(1))
a[-1]     # 50          último              (MATLAB: a(end))
a[1:3]    # [20, 30]    fin excluido        (MATLAB: a(2:3))
a[:2]     # [10, 20]    los 2 primeros
a[2:]     # [30, 40, 50] desde el 3º
a[::-1]   # [50, 40, 30, 20, 10] al revés  (MATLAB: a(end:-1:1))
```

Truco: con fin excluido, `a[:k] + a[k:] == a` y `len(a[i:j]) == j - i`.

## Las variables son nombres, no cajas

Es la mayor diferencia con C++. `b = a` **no copia**: hace que `b` sea otro nombre del mismo objeto.

```python
a = [1, 2, 3]
b = a            # mismo objeto (como una referencia de C++)
b.append(4)
print(a)         # [1, 2, 3, 4]   <- ¡a también ha cambiado!

c = a.copy()     # o list(a), o a[:]  -> copia (superficial)
```

En MATLAB, `b = a` se comporta como una copia (*copy-on-write*), así que este fallo no te pasaba.

Trampa clásica con listas de listas:

```python
m = [[0] * 3] * 2      # ¡las 2 filas son EL MISMO objeto!
m[0][0] = 1
print(m)               # [[1, 0, 0], [1, 0, 0]]

m = [[0] * 3 for _ in range(2)]   # correcto: cada fila es un objeto nuevo
```

## Funciones

```python
def estadisticas(datos, redondeo=2):       # parámetro con valor por defecto
    """Docstring: qué hace la función (se ve con help(estadisticas))."""
    media = sum(datos) / len(datos)
    return round(media, redondeo), max(datos)   # devuelve una tupla

m, mx = estadisticas([1, 2, 3])            # desempaquetado (MATLAB: [m, mx] = ...)
estadisticas([1, 2, 3], redondeo=0)        # argumento por nombre
```

## Estilo pythónico ("C++ traducido" frente a Python)

| Evitar | Mejor |
|---|---|
| `for i in range(len(a)): print(a[i])` | `for x in a: print(x)` |
| `for i in range(len(a)): print(i, a[i])` | `for i, x in enumerate(a): print(i, x)` |
| `if len(a) == 0:` | `if not a:` |
| `if x == True:` | `if x:` |
| `if x == None:` | `if x is None:` |
| `r = []` + bucle con `r.append(f(x))` | `r = [f(x) for x in a]` |
| `tmp = a; a = b; b = tmp` | `a, b = b, a` |
| `s = s + str(x)` en bucle | `"".join(partes)` |

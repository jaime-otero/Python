# Plan de aprendizaje de Python

## Perfil de partida

- **Sabe programar:** C++ (tipos, memoria, POO) y MATLAB (cálculo vectorizado, gráficas).
- **Oxidado:** JavaScript y HTML (no son necesarios para este plan).
- **Objetivos:**
  1. Dominar Python como lenguaje general, escrito "a la manera de Python" y no como C++ traducido.
  2. Dominar el Python científico (NumPy, SciPy, matplotlib) como sustituto de MATLAB.
  3. Cubrir por cuenta propia el contenido de **Computación Avanzada**.
     *Pendiente: ajustar los módulos 8–11 cuando tengamos la guía docente.*

## Filosofía

- **Nada de "qué es un bucle".** Nos centramos en lo que Python hace distinto de C++/MATLAB.
- **Aprender escribiendo código.** Cada módulo termina con ejercicios comprobados por tests.
- **Revisión real.** Pasar los tests no basta: el código se revisa buscando estilo pythónico,
  y hay que saber explicar *por qué* funciona.

## Recursos (todos gratuitos)

| Abreviatura | Recurso | Para qué |
|---|---|---|
| **TUT** | [Tutorial oficial de Python (español)](https://docs.python.org/es/3/tutorial/) | Referencia principal del lenguaje |
| **CS50P** | [CS50's Introduction to Programming with Python](https://cs50.harvard.edu/python/) | Problemas extra; vídeos solo de los temas nuevos para ti |
| **NP-ML** | [NumPy for MATLAB users](https://numpy.org/doc/stable/user/numpy-for-matlab-users.html) | Tabla de equivalencias MATLAB → NumPy |
| **SPL** | [Scientific Python Lectures](https://lectures.scientific-python.org/) | NumPy, matplotlib, SciPy, optimización y rendimiento |

Enlaces a cada capítulo, qué usar en cada módulo y PDF para leer sin conexión: ver [`RECURSOS.md`](RECURSOS.md).

## Calendario orientativo (~6–8 h/semana, ~15 semanas)

| # | Módulo | Semanas |
|---|---|---|
| M0 | Entorno de trabajo | 0.5 |
| M1 | Fundamentos y colecciones | 1.5 |
| M2 | Funciones y modelo de objetos | 1 |
| M3 | Errores, módulos y ficheros | 1 |
| M4 | Programación orientada a objetos pythónica | 1 |
| M5 | Herramientas profesionales | 0.5 |
| M6 | NumPy | 2 |
| M7 | Visualización con matplotlib | 0.5 |
| M8 | SciPy y métodos numéricos | 2 |
| M9 | Python avanzado | 1 |
| M10 | Rendimiento | 1 |
| M11 | Proyecto final | 2 |

---

## M0 · Entorno de trabajo

**Objetivo:** tener un entorno profesional desde el primer día.

- Instalar la última versión estable de Python (3.14 en septiembre de 2026) y VS Code con la extensión de Python.
- Clonar este repositorio y crear un entorno virtual (`venv`). Entender por qué no se instala todo a nivel global.
- `pip install -r requirements.txt` y ejecutar los tests del M1 (deben fallar).
- Usar el intérprete interactivo (REPL) como calculadora y banco de pruebas: el equivalente a la
  Command Window de MATLAB.

**Lecturas:** TUT "Usando el intérprete de Python" y "Entornos virtuales y paquetes".

**Entregable:** los tests de M1 se ejecutan (y fallan) en tu máquina.

## M1 · Fundamentos y colecciones

**Objetivo:** escribir código Python básico con fluidez y sin reflejos de C++/MATLAB.

- Tipos básicos: `int` (precisión arbitraria), `float`, `bool`, `None`, `str` (inmutable).
- División `/` frente a `//`, potencia `**`, operadores `and`/`or`/`not`.
- `if`/`elif`/`else`, `for` sobre elementos, `range`, `enumerate`, `zip`, `while`.
- Colecciones: `list`, `tuple`, `dict`, `set`. Cuándo usar cada una.
- Indexado desde 0, índices negativos y *slicing* `a[inicio:fin:paso]` (sin incluir `fin`).
- Comprensiones de listas y diccionarios.
- Formateo con f-strings.

**Trampas desde C++/MATLAB:** índices desde 0, `fin` excluido, `[0]*3` frente a matrices,
`[[0]*c]*f` (filas compartidas), `x = y` no copia.

**Lecturas:** TUT "Una introducción informal a Python", "Más herramientas para control de flujo"
(hasta las sentencias `match`) y "Estructuras de datos". CS50P lecciones 0–2 (solo los problemas).

**Entregable:** `modulos/m01_fundamentos/`, con todos los tests pasando y el código revisado.

## M2 · Funciones y modelo de objetos

**Objetivo:** entender qué es de verdad una variable en Python. Es el tema que más confunde viniendo de C++.

- Todo es un objeto; las variables son *nombres* que apuntan a objetos. `id()` e `is` frente a `==`.
- Objetos mutables e inmutables. Paso de argumentos "por referencia a objeto".
- Copia superficial y profunda (`copy`, `copy.deepcopy`).
- Argumentos por defecto (¡y el bug del argumento mutable por defecto!), argumentos por nombre,
  `*args`, `**kwargs`, parámetros solo posicionales y solo por nombre.
- Ámbito (regla LEGB), `global`/`nonlocal`, *closures*, `lambda`.
- Funciones como objetos de primera clase (pasarlas como argumento: el `@(x)` de MATLAB).
- Anotaciones de tipo (*type hints*) básicas.

**Lecturas:** TUT 4.8 "Definir funciones", 4.9 "Más sobre definición de funciones" y 9.1–9.2 (nombres, objetos y ámbitos). SPL "The Python language",
apartados de funciones.

**Entregable:** ejercicios de M2 más una explicación escrita de por qué falla el argumento mutable por defecto.

## M3 · Errores, módulos y ficheros

- Excepciones: `try`/`except`/`else`/`finally`, lanzar excepciones propias, EAFP frente a LBYL.
- `with` y gestión de recursos (el RAII de Python).
- Ficheros de texto, `pathlib`, CSV y JSON.
- Módulos y paquetes, `import`, `if __name__ == "__main__":`.
- Scripts de línea de comandos con `argparse`.

**Lecturas:** TUT "Módulos", "Entrada y salida" y "Errores y excepciones". CS50P lecciones 3, 4 y 6.

**Entregable:** un pequeño programa de línea de comandos que lea un CSV de datos, calcule estadísticas y
escriba un JSON, con manejo de errores.

## M4 · Programación orientada a objetos pythónica

- Clases, `self`, atributos de instancia y de clase.
- Métodos especiales: `__init__`, `__repr__`, `__str__`, `__eq__`, `__add__`, `__len__`,
  `__getitem__` y `__iter__` (la sobrecarga de operadores de C++, al estilo Python).
- `@property`, `@classmethod`, `@staticmethod`.
- Herencia, `super()` y composición. *Duck typing* frente a jerarquías rígidas.
- No hay `private`: la convención `_nombre`.
- `dataclasses`.

**Lecturas:** TUT "Clases". CS50P lección 8.

**Entregable:** una clase `Vector` (o `Polinomio`) con sus operadores, más sus tests.

## M5 · Herramientas profesionales

- Escribir tus propios tests con `pytest` (fixtures, `parametrize`, `approx`).
- Git: commits pequeños y ramas.
- `ruff` para estilo y *linting*; PEP 8.
- Tipado estático con `mypy`.
- Depurador de VS Code y `breakpoint()`.

**Lecturas:** CS50P lección 5 (Unit Tests). Documentación de pytest ("Get started").

**Entregable:** a partir de aquí, **tú** escribes los tests de tus ejercicios.

## M6 · NumPy (el MATLAB de Python)

- `ndarray`: `shape`, `dtype`, `ndim`. Creación (`zeros`, `ones`, `arange`, `linspace`, `eye`).
- Diferencias clave con MATLAB: 0-indexado, orden por filas, `*` es elemento a elemento y `@` es
  producto matricial, arrays 1-D que no son ni fila ni columna.
- Indexado, *slicing*, máscaras booleanas e indexado avanzado.
- **Vistas frente a copias** (un slice de NumPy no copia, al revés que en MATLAB).
- *Broadcasting* y vectorización: eliminar bucles.
- Reducciones con `axis`. Álgebra lineal con `np.linalg`. Aleatorios con `np.random.default_rng`.

**Lecturas:** NP-ML completo. SPL "NumPy: creating and manipulating numerical data" y después
"Advanced NumPy" (solo la parte de *strides* y vistas).

**Entregable:** reimplementar con NumPy vectorizado varios ejercicios de M1, midiendo la mejora de tiempo.

## M7 · Visualización con matplotlib

- API orientada a objetos: `fig, ax = plt.subplots()` (evitar el estilo MATLAB `plt.plot`
  para gráficas complejas).
- Líneas, dispersión, histogramas, `imshow`/`pcolormesh`, subgráficas, etiquetas y leyendas.
- Guardar figuras para informes.

**Lecturas:** SPL "Matplotlib: plotting".

**Entregable:** las figuras del M8 salen de aquí.

## M8 · SciPy y métodos numéricos

Primero se implementa a mano y después se compara con SciPy.

- Raíces: bisección y Newton, frente a `scipy.optimize.root_scalar`/`root`.
- EDOs: Euler y RK4, frente a `scipy.integrate.solve_ivp`.
- Integración numérica: trapecios y Simpson, frente a `scipy.integrate.quad`.
- Interpolación y ajuste: `scipy.interpolate`, `scipy.optimize.curve_fit`.
- Optimización: `scipy.optimize.minimize`.
- Álgebra lineal dispersa (`scipy.sparse`) y FFT (`scipy.fft`).

**Lecturas:** SPL "SciPy: high-level scientific computing" y "Mathematical optimization".

**Entregable:** una mini-biblioteca `metodos_numericos/` con tests y gráficas de convergencia.

## M9 · Python avanzado

- Protocolo de iteración, generadores y `yield` (evaluación perezosa).
- Decoradores (escribir uno para medir tiempos y otro de caché) y `functools` (`lru_cache`, `partial`, `wraps`).
- Gestores de contexto propios (`__enter__`/`__exit__` y `contextlib`).
- `itertools` y `collections` (`Counter`, `defaultdict`, `deque`, `namedtuple`).
- `match` (*pattern matching* estructural).

**Lecturas:** TUT "Clases" (apartados de iteradores y generadores). SPL "Advanced Python constructs".

## M10 · Rendimiento

- Por qué Python "puro" es lento: intérprete, objetos y el GIL.
- Medir antes de optimizar: `timeit`, `cProfile` y `line_profiler`.
- Estrategias por orden: mejor algoritmo, vectorizar con NumPy, `numba` (JIT) y paralelismo
  (`multiprocessing`, `concurrent.futures`).
- Aprovechar tu C++: extensiones con `pybind11` (visión general y un ejemplo pequeño).

**Lecturas:** SPL "Optimizing code".

**Entregable:** optimizar un código lento del M8 y documentar la aceleración medida.

## M11 · Proyecto final

Proyecto de 2 semanas, elegido según el temario de Computación Avanzada. Ideas:

- Simulación de N cuerpos (integradores, conservación de energía, animación).
- Ecuación del calor o de ondas por diferencias finitas (matrices dispersas, estabilidad).
- Monte Carlo: modelo de Ising o integración en dimensión alta.

Requisitos: paquete estructurado, tests, gráficas, perfilado y un README que lo explique.

---

## Criterio para pasar de módulo

1. Todos los tests pasan.
2. Código revisado sin problemas de fondo (estilo pythónico, sin "C++ traducido").
3. Saber responder a una o dos preguntas conceptuales sobre el módulo sin mirar.

# Recursos

Los cuatro recursos del plan, con enlaces directos a cada capítulo y qué usar en cada módulo.
Todos son gratuitos.

> Verificado el 2026-09-23 contra las webs oficiales: tutorial de Python 3.14.7, NumPy 2.5 y
> Scientific Python Lectures 2025.2. Si un enlace deja de funcionar, busca el título del capítulo
> en la web del recurso.

## PDF para leer sin conexión

En [`recursos/`](recursos/) están las versiones actuales de las webs convertidas a PDF, con marcadores
por capítulo. Se generaron el 2026-09-23 directamente desde las páginas oficiales. La versión web
manda: si ves algo distinto, está más actualizada. Licencias y atribución en
[`recursos/LICENCIAS.md`](recursos/LICENCIAS.md).

| PDF | Contenido |
|---|---|
| [`tutorial-python-es.pdf`](recursos/tutorial-python-es.pdf) | Tutorial oficial de Python 3.14 en español (capítulos 1–16) |
| [`cs50p-notas.pdf`](recursos/cs50p-notas.pdf) | Apuntes de las 10 clases de CS50P (los problemas están en la web) |
| [`numpy-for-matlab-users.pdf`](recursos/numpy-for-matlab-users.pdf) | NumPy for MATLAB users (NumPy 2.5) |
| [`scientific-python-lectures-1-intro.pdf`](recursos/scientific-python-lectures-1-intro.pdf) | Scientific Python Lectures, capítulos 1–6 |
| [`scientific-python-lectures-2-avanzado.pdf`](recursos/scientific-python-lectures-2-avanzado.pdf) | Scientific Python Lectures, capítulos 7–11, 13 y 14 |

Descargas oficiales, por si las prefieres:
- Documentación completa de Python 3.14 en español: [EPUB](https://docs.python.org/es/3/archives/python-3.14-docs.epub)
  o [HTML en zip](https://docs.python.org/es/3/archives/python-3.14-docs-html.zip) (desde [la página de descargas](https://docs.python.org/es/3/download.html)).
- Guía de usuario de NumPy 2.5 completa: [PDF](https://numpy.org/doc/2.5/numpy-user.pdf).
- Scientific Python Lectures y CS50P no ofrecen PDF oficial actual. El PDF antiguo de
  scipy-lectures.org es de 2022 y está desactualizado.

## Resumen

| Recurso | Idioma | Para qué | Cuándo |
|---|---|---|---|
| [Tutorial oficial de Python](#1-tutorial-oficial-de-python) | Español | Aprender el lenguaje, de la fuente primaria | M0–M4, M9 |
| [CS50P (Harvard)](#2-cs50p-cs50s-introduction-to-programming-with-python) | Inglés | Problemas extra con corrector automático | M1–M5 (opcional) |
| [NumPy for MATLAB users](#3-numpy-for-matlab-users) | Inglés | Equivalencias MATLAB → NumPy | M6 |
| [Scientific Python Lectures](#4-scientific-python-lectures) | Inglés | NumPy, matplotlib, SciPy, optimización y rendimiento | M6–M10 |

---

## 1. Tutorial oficial de Python

**Enlace:** https://docs.python.org/es/3/tutorial/

Lo escriben los propios desarrolladores de Python y está traducido al español. Es denso pero
completo. Para alguien que ya programa, es la forma más rápida de aprender el lenguaje.
Algunos capítulos del final (10, 11 y 15) siguen parcialmente en inglés.

| Cap. | Título | Módulo | Notas |
|---|---|---|---|
| 1 | [Abriendo el apetito](https://docs.python.org/es/3/tutorial/appetite.html) | — | Opcional |
| 2 | [Usando el intérprete de Python](https://docs.python.org/es/3/tutorial/interpreter.html) | M0 | |
| 3 | [Una introducción informal a Python](https://docs.python.org/es/3/tutorial/introduction.html) | M1 | Números, texto y listas |
| 4 | [Más herramientas para control de flujo](https://docs.python.org/es/3/tutorial/controlflow.html) | M1, M2 | 4.1–4.6 en M1; 4.8–4.10 (funciones) en M2; 4.7 (`match`) en M9 |
| 5 | [Estructuras de datos](https://docs.python.org/es/3/tutorial/datastructures.html) | M1 | Listas, tuplas, conjuntos, diccionarios y comprensiones |
| 6 | [Módulos](https://docs.python.org/es/3/tutorial/modules.html) | M3 | |
| 7 | [Entrada y salida](https://docs.python.org/es/3/tutorial/inputoutput.html) | M1, M3 | 7.1.1 (f-strings) en M1; ficheros y `json` en M3 |
| 8 | [Errores y excepciones](https://docs.python.org/es/3/tutorial/errors.html) | M3 | |
| 9 | [Clases](https://docs.python.org/es/3/tutorial/classes.html) | M2, M4, M9 | 9.1–9.2 (nombres y ámbitos) en M2; 9.3–9.7 en M4; 9.8–9.10 (iteradores y generadores) en M9 |
| 10 | [Pequeño paseo por la biblioteca estándar](https://docs.python.org/es/3/tutorial/stdlib.html) | M3, M10 | 10.10 "Performance measurement" en M10 |
| 11 | [Paseo por la biblioteca estándar, parte II](https://docs.python.org/es/3/tutorial/stdlib2.html) | M9 | 11.7 "Tools for working with lists" |
| 12 | [Entornos virtuales y paquetes](https://docs.python.org/es/3/tutorial/venv.html) | M0 | |
| 15 | [Floating-Point Arithmetic: Issues and Limitations](https://docs.python.org/es/3/tutorial/floatingpoint.html) | M8 | Clave para cálculo numérico |

---

## 2. CS50P: CS50's Introduction to Programming with Python

**Enlace:** https://cs50.harvard.edu/python/

Curso de Harvard (David J. Malan). El curso es gratuito en OpenCourseWare y el certificado
verificado se paga en edX. Lo mejor que tiene para ti son los **problemas**: cada semana trae varios
ejercicios cortos con corrector automático.

**Cómo usarlo en este plan:** es opcional y complementario. **No veas las clases enteras**: están
pensadas para gente que nunca ha programado. Haz los problemas de cada semana y mira el vídeo solo
si un tema te resulta nuevo.

**Cómo se entregan los problemas** (según la página del Problem Set 0):
1. Rellenar el formulario de inscripción y autorizar la app de CS50 con tu cuenta de GitHub.
2. Programar en [cs50.dev](https://cs50.dev), un VS Code en la nube con todo preinstalado.
   También puedes resolverlos en local, pero para entregarlos se usa su entorno.
3. Los problemas se corrigen automáticamente. La fecha límite de esta edición es el **31-12-2026**.

| Semana | Tema | Problemas | Módulo |
|---|---|---|---|
| [0](https://cs50.harvard.edu/python/weeks/0/) | Functions, Variables | Indoor Voice, Playback Speed, Making Faces, Einstein, Tip Calculator | M1 |
| [1](https://cs50.harvard.edu/python/weeks/1/) | Conditionals | Deep Thought, Home Federal Savings Bank, File Extensions, Math Interpreter, Meal Time | M1 |
| [2](https://cs50.harvard.edu/python/weeks/2/) | Loops | camelCase, Coke Machine, Just setting up my twttr, Vanity Plates, Nutrition Facts | M1 |
| [3](https://cs50.harvard.edu/python/weeks/3/) | Exceptions | Fuel Gauge, Felipe's Taqueria, Grocery List, Outdated | M3 |
| [4](https://cs50.harvard.edu/python/weeks/4/) | Libraries | Emojize, Frank Ian and Glen's Letters, Adieu Adieu, Guessing Game, Little Professor, Bitcoin Price Index | M3 |
| [5](https://cs50.harvard.edu/python/weeks/5/) | Unit Tests | Testing my twttr, Back to the Bank, Re-requesting a Vanity Plate, Refueling | M5 |
| [6](https://cs50.harvard.edu/python/weeks/6/) | File I/O | Lines of Code, Pizza Py, Scourgify, CS50 P-Shirt | M3 |
| [7](https://cs50.harvard.edu/python/weeks/7/) | Regular Expressions | NUMB3RS, Watch on YouTube, Working 9 to 5, Regular um Expressions, Response Validation | Opcional |
| [8](https://cs50.harvard.edu/python/weeks/8/) | Object-Oriented Programming | Seasons of Love, Cookie Jar, CS50 Shirtificate | M4 |
| [9](https://cs50.harvard.edu/python/weeks/9/) | Et Cetera | — | M9 |

Si solo tienes tiempo para una selección, haz estos: **Vanity Plates** (semana 2), **Outdated**
(semana 3), **Back to the Bank** (semana 5), **Scourgify** (semana 6) y **Cookie Jar** (semana 8).

---

## 3. NumPy for MATLAB users

**Enlace:** https://numpy.org/doc/stable/user/numpy-for-matlab-users.html

Página de la documentación oficial de NumPy (versión 2.5). Tiene una tabla enorme de
equivalencias ("Rough equivalents") entre MATLAB y NumPy. Es lo primero que se lee en el **M6** y
la chuleta que tendrás abierta mientras programes con NumPy.

**Secciones:** Introduction · Some key differences · Rough equivalents (general y álgebra lineal) ·
Notes · 'array' or 'matrix'? · Customizing your environment · Links.

**Las diferencias que más te afectan** (resumen de "Some key differences"):

| | MATLAB | NumPy |
|---|---|---|
| Primer elemento | `a(1)` | `a[0]` |
| `*` | producto matricial | elemento a elemento (el producto matricial es `@`) |
| Slicing | copia (*copy-on-write*) | **vista**: modificar el slice modifica el original |
| Vectores | siempre 2-D (1×N o N×1) | existen arrays 1-D de verdad; las formas `(N,)`, `(1, N)` y `(N, 1)` son distintas |
| `&` y `\|` | lógicos | a nivel de bits (con arrays booleanos funcionan como lógicos) |
| Tipo por defecto | `double` 2-D | el tipo mínimo necesario para los datos (`np.array([1, 2])` es de enteros) |

Usa siempre `np.array` y nunca `np.matrix`: la propia página lo recomienda en "'array' or 'matrix'?".

---

## 4. Scientific Python Lectures

**Enlace:** https://lectures.scientific-python.org/

Apuntes comunitarios del ecosistema científico de Python. Es la referencia principal del M6 al M10.

### Getting started with Python for Science

| Cap. | Título | Módulo | Notas |
|---|---|---|---|
| 1 | [Python scientific computing ecosystem](https://lectures.scientific-python.org/intro/intro.html) | M0 | Visión general |
| 2 | [The Python language](https://lectures.scientific-python.org/intro/language/python_language.html) | M1–M4 | Alternativa o repaso rápido del tutorial oficial |
| 3 | [NumPy: creating and manipulating numerical data](https://lectures.scientific-python.org/intro/numpy/index.html) | **M6** | 3.1 [array object](https://lectures.scientific-python.org/intro/numpy/array_object.html) · 3.2 [operations](https://lectures.scientific-python.org/intro/numpy/operations.html) · 3.3 [elaborate arrays](https://lectures.scientific-python.org/intro/numpy/elaborate_arrays.html) · 3.4 [advanced operations](https://lectures.scientific-python.org/intro/numpy/advanced_operations.html) · 3.5 [exercises](https://lectures.scientific-python.org/intro/numpy/exercises.html) |
| 4 | [Matplotlib: plotting](https://lectures.scientific-python.org/intro/matplotlib/index.html) | **M7** | |
| 5 | [SciPy: high-level scientific computing](https://lectures.scientific-python.org/intro/scipy/index.html) | **M8** | |
| 6 | [Getting help and finding documentation](https://lectures.scientific-python.org/intro/help/help.html) | M0 | |

### Advanced topics

| Cap. | Título | Módulo |
|---|---|---|
| 7 | [Advanced Python Constructs](https://lectures.scientific-python.org/advanced/advanced_python/index.html) | **M9** |
| 8 | [Advanced NumPy](https://lectures.scientific-python.org/advanced/advanced_numpy/index.html) | M6 (vistas y *strides*), M10 |
| 9 | [Debugging code](https://lectures.scientific-python.org/advanced/debugging/index.html) | M5 |
| 10 | [Optimizing code](https://lectures.scientific-python.org/advanced/optimizing/index.html) | **M10** |
| 11 | [Scipy sparse arrays](https://lectures.scientific-python.org/advanced/scipy_sparse/introduction.html) | M8 |
| 12 | [Image manipulation and processing using NumPy and SciPy](https://lectures.scientific-python.org/advanced/image_processing/index.html) | Opcional |
| 13 | [Mathematical optimization: finding minima of functions](https://lectures.scientific-python.org/advanced/mathematical_optimization/index.html) | **M8** |
| 14 | [Interfacing with C](https://lectures.scientific-python.org/advanced/interfacing_with_c/interfacing_with_c.html) | M10 (aquí sacas partido a tu C++) |

### Packages and applications (opcionales, según la asignatura)

[Statistics](https://lectures.scientific-python.org/packages/statistics/index.html) ·
[SymPy](https://lectures.scientific-python.org/packages/sympy.html) ·
[scikit-image](https://lectures.scientific-python.org/packages/scikit-image/index.html) ·
[scikit-learn](https://lectures.scientific-python.org/packages/scikit-learn/index.html)

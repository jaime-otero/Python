# Progreso

## Estado actual

- **Módulo actual:** M0 · Entorno de trabajo
- **Siguiente paso:** instalar Python y VS Code, clonar el repo, crear el `venv` y ejecutar los tests de M1
  (deben fallar). Después, leer `apuntes/01_chuleta_cpp_matlab.md` y empezar `modulos/m01_fundamentos/`.
- **Pendiente:** conseguir la guía docente o el temario de Computación Avanzada para ajustar M8–M11.

## Módulos

- [ ] M0 · Entorno de trabajo
- [ ] M1 · Fundamentos y colecciones
- [ ] M2 · Funciones y modelo de objetos
- [ ] M3 · Errores, módulos y ficheros
- [ ] M4 · POO pythónica
- [ ] M5 · Herramientas profesionales
- [ ] M6 · NumPy
- [ ] M7 · matplotlib
- [ ] M8 · SciPy y métodos numéricos
- [ ] M9 · Python avanzado
- [ ] M10 · Rendimiento
- [ ] M11 · Proyecto final

## Puntos a vigilar

Hábitos de C++ detectados en `codigo_previo/` (detalle en `apuntes/02_de_tu_cpp_a_python.md`):

- Devuelve resultados por referencia (`double &x`) en lugar de devolverlos: en Python, tuplas.
- Copia y pega funciones entre programas: en Python, módulos e `import`.
- Bucles con índices y vectores `n×1`: en Python, NumPy vectorizado y arrays 1-D.
- Variables globales mutables y bloques casi repetidos que solo cambian un valor.
- Contadores `double` en bucles (`t += h`), errores con `cout` + `exit(1)` y recursión profunda.

## Registro de sesiones

### Sesión 1 · 2026-09-23
- Diagnóstico: sabe C++ y MATLAB; tiene JS/HTML oxidados. Motivación: Python es el lenguaje más usado
  y quiere cubrir por su cuenta la asignatura Computación Avanzada.
- Se crean el plan (`PLAN.md`), la chuleta C++/MATLAB → Python y los ejercicios de M1.
- Se verifican los cuatro recursos contra sus webs y se añaden `RECURSOS.md` (enlaces por capítulo
  y módulo) y los PDF en `recursos/`.
- Sube 23 prácticas de métodos numéricos en C++ del curso pasado. Se organizan en `codigo_previo/cpp/`,
  con catálogo y retos de depuración en `codigo_previo/README.md`, y se escribe el diagnóstico de
  hábitos (`apuntes/02_de_tu_cpp_a_python.md`). El plan se personaliza: M3, M4, M6, M8, M10 y M11
  usan sus prácticas, y M8 pasa de enseñar los métodos a portarlos y compararlos con SciPy.
- Pendiente: subir los ficheros de datos que usan las prácticas (`matriz.txt`, `posiciones.txt`).

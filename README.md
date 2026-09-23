# Aprendiendo Python (desde C++ y MATLAB)

Repositorio personal para aprender Python a nivel avanzado, con un plan guiado y
personalizado. Objetivo: dominar Python general y científico (NumPy, SciPy,
matplotlib) y llegar preparado a la asignatura **Computación Avanzada**.

## Estructura

| Archivo / carpeta | Qué es |
|---|---|
| [`PLAN.md`](PLAN.md) | El plan completo por módulos: objetivos, lecturas, trampas típicas y entregables |
| [`PROGRESO.md`](PROGRESO.md) | Dónde estás, qué está hecho y qué toca en la siguiente sesión |
| [`apuntes/`](apuntes/) | Chuletas y resúmenes (empieza por la de C++/MATLAB → Python) |
| [`modulos/`](modulos/) | Un directorio por módulo con teoría breve, ejercicios y tests |
| `CLAUDE.md` | Instrucciones para Claude como tutor (cómo llevar las sesiones) |

## Cómo se trabaja

1. Abre una sesión con Claude sobre este repositorio y di **"sigamos"**.
   Claude lee `PROGRESO.md` y retoma donde lo dejaste.
2. Cada módulo tiene un `ejercicios.py` con funciones vacías y un
   `test_ejercicios.py` que las comprueba. Tú escribes el código; los tests
   te dicen si funciona.
3. Cuando los tests pasen, haz commit y pide revisión: Claude lee tu código,
   te señala lo que no es "pythónico" y te hace alguna pregunta para comprobar
   que lo has entendido.
4. Al final de cada sesión se actualiza `PROGRESO.md`.

## Ejecutar los tests

```bash
python -m venv .venv                 # crea un entorno virtual (solo la primera vez)
source .venv/bin/activate            # Linux/macOS  |  Windows: .venv\Scripts\activate
pip install -r requirements.txt
python -m pytest modulos/m01_fundamentos -v
```

Al principio todos los tests fallan (`NotImplementedError`): es lo esperado.

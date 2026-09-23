# M1 · Fundamentos y colecciones

## Antes de empezar

1. Lee `apuntes/01_chuleta_cpp_matlab.md`.
2. Lecturas del tutorial oficial (https://docs.python.org/es/3/tutorial/):
   - "Una introducción informal a Python"
   - "Más herramientas para control de flujo" (hasta `match`, sin incluirlo)
   - "Estructuras de datos"
3. Opcional: los problemas de las lecciones 0–2 de CS50P (https://cs50.harvard.edu/python/).
   Los vídeos, solo si un tema te resulta nuevo.

## Ejercicios

Abre `ejercicios.py` y sustituye cada `raise NotImplementedError` por tu código.
No cambies los nombres ni los parámetros de las funciones: los tests dependen de ellos.

| # | Función | Practica |
|---|---|---|
| 1 | `suma_pares` | `for` sobre elementos, `%` |
| 2 | `rango_matlab` | `range` y su fin excluido |
| 3 | `invertir_palabras` | `str.split`, `str.join`, slicing |
| 4 | `contar_palabras` | `dict` |
| 5 | `media_y_desviacion` | devolver tuplas, `sum`, `len` |
| 6 | `aplanar` | listas de listas, comprensiones |
| 7 | `transponer` | `zip` o comprensiones anidadas |
| 8 | `crear_tablero` | referencias frente a copias (¡cuidado!) |
| 9 | `unicos_en_orden` | `set` y `list` juntos |

## Comprobar

```bash
python -m pytest modulos/m01_fundamentos -v          # todos
python -m pytest modulos/m01_fundamentos -k suma     # solo los que contienen "suma"
```

## Reglas del juego

- **Sin librerías** (nada de `import`) salvo que el enunciado lo diga: queremos practicar lo básico.
- Cuando un test pase, pregúntate si tu solución parece Python o C++ traducido (mira la tabla de estilo de la chuleta).
- Cuando acabes, haz commit y pide revisión.

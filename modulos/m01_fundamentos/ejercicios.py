"""M1 · Fundamentos y colecciones.

Sustituye cada `raise NotImplementedError` por tu implementación.
Ejecuta los tests con:  python -m pytest modulos/m01_fundamentos -v
"""


# 1 ---------------------------------------------------------------------------
def suma_pares(numeros):
    """Devuelve la suma de los números pares de la lista `numeros`.

    >>> suma_pares([1, 2, 3, 4])
    6
    >>> suma_pares([])
    0
    """
    raise NotImplementedError


# 2 ---------------------------------------------------------------------------
def rango_matlab(inicio, paso, fin):
    """Imita `inicio:paso:fin` de MATLAB con enteros y devuelve una lista.

    Al contrario que `range`, en MATLAB `fin` se INCLUYE si se alcanza.
    `paso` puede ser negativo. Si el rango está vacío, devuelve [].

    >>> rango_matlab(1, 1, 5)
    [1, 2, 3, 4, 5]
    >>> rango_matlab(0, 3, 10)
    [0, 3, 6, 9]
    >>> rango_matlab(5, -2, 1)
    [5, 3, 1]
    >>> rango_matlab(5, 1, 1)
    []
    """
    raise NotImplementedError


# 3 ---------------------------------------------------------------------------
def invertir_palabras(frase):
    """Devuelve la frase con el orden de las palabras invertido.

    Las palabras están separadas por espacios; ignora los espacios de sobra.

    >>> invertir_palabras("hola mundo cruel")
    'cruel mundo hola'
    >>> invertir_palabras("  mucho   espacio ")
    'espacio mucho'
    """
    raise NotImplementedError


# 4 ---------------------------------------------------------------------------
def contar_palabras(texto):
    """Devuelve un diccionario {palabra: número de apariciones}.

    Sin distinguir mayúsculas de minúsculas (las claves van en minúscula).
    No hace falta tratar los signos de puntuación.

    >>> contar_palabras("El perro y el gato")
    {'el': 2, 'perro': 1, 'y': 1, 'gato': 1}
    """
    raise NotImplementedError


# 5 ---------------------------------------------------------------------------
def media_y_desviacion(datos):
    """Devuelve la tupla (media, desviación típica poblacional) de `datos`.

    desviación = sqrt( sum((x - media)**2) / N )
    Pista: para la raíz cuadrada no necesitas importar nada; piensa en `**`.
    Si `datos` está vacío, lanza ValueError (busca cómo se lanza una excepción).

    >>> media_y_desviacion([2, 4, 4, 4, 5, 5, 7, 9])
    (5.0, 2.0)
    """
    raise NotImplementedError


# 6 ---------------------------------------------------------------------------
def aplanar(matriz):
    """Convierte una lista de listas en una sola lista, recorriendo POR FILAS.

    Ojo: en MATLAB, A(:) recorre por columnas. Aquí queremos por filas.

    >>> aplanar([[1, 2, 3], [4, 5, 6]])
    [1, 2, 3, 4, 5, 6]
    """
    raise NotImplementedError


# 7 ---------------------------------------------------------------------------
def transponer(matriz):
    """Devuelve la traspuesta de una matriz dada como lista de listas.

    Todas las filas tienen la misma longitud. El resultado es una lista de listas.

    >>> transponer([[1, 2, 3], [4, 5, 6]])
    [[1, 4], [2, 5], [3, 6]]
    """
    raise NotImplementedError


# 8 ---------------------------------------------------------------------------
def crear_tablero(filas, columnas, valor=0):
    """Devuelve una matriz filas x columnas (lista de listas) llena de `valor`.

    Cada fila debe ser un objeto INDEPENDIENTE: modificar tablero[0][0]
    no debe cambiar ninguna otra fila. (Lee la chuleta antes de hacerlo.)

    >>> crear_tablero(2, 3)
    [[0, 0, 0], [0, 0, 0]]
    """
    raise NotImplementedError


# 9 ---------------------------------------------------------------------------
def unicos_en_orden(elementos):
    """Elimina duplicados conservando el orden de la primera aparición.

    Debe ser eficiente con listas grandes: comprobar `x in lista` es O(n),
    mientras que `x in conjunto` es O(1) de media.

    >>> unicos_en_orden([3, 1, 3, 2, 1])
    [3, 1, 2]
    """
    raise NotImplementedError

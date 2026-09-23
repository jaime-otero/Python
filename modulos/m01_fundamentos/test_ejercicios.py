"""Tests del M1. No hace falta modificarlos: ejecútalos con
    python -m pytest modulos/m01_fundamentos -v
"""

import pytest

from ejercicios import (
    aplanar,
    contar_palabras,
    crear_tablero,
    invertir_palabras,
    media_y_desviacion,
    rango_matlab,
    suma_pares,
    transponer,
    unicos_en_orden,
)


def test_suma_pares():
    assert suma_pares([1, 2, 3, 4]) == 6
    assert suma_pares([]) == 0
    assert suma_pares([1, 3, 5]) == 0
    assert suma_pares([-2, -3, 10]) == 8


@pytest.mark.parametrize(
    "inicio, paso, fin, esperado",
    [
        (1, 1, 5, [1, 2, 3, 4, 5]),
        (0, 3, 10, [0, 3, 6, 9]),
        (0, 5, 10, [0, 5, 10]),
        (5, -2, 1, [5, 3, 1]),
        (5, -2, 0, [5, 3, 1]),
        (5, 1, 1, []),
        (3, 1, 3, [3]),
    ],
)
def test_rango_matlab(inicio, paso, fin, esperado):
    assert rango_matlab(inicio, paso, fin) == esperado


def test_invertir_palabras():
    assert invertir_palabras("hola mundo cruel") == "cruel mundo hola"
    assert invertir_palabras("  mucho   espacio ") == "espacio mucho"
    assert invertir_palabras("sola") == "sola"
    assert invertir_palabras("") == ""


def test_contar_palabras():
    assert contar_palabras("El perro y el gato") == {"el": 2, "perro": 1, "y": 1, "gato": 1}
    assert contar_palabras("") == {}
    assert contar_palabras("a A a") == {"a": 3}


def test_media_y_desviacion():
    media, desv = media_y_desviacion([2, 4, 4, 4, 5, 5, 7, 9])
    assert media == pytest.approx(5.0)
    assert desv == pytest.approx(2.0)
    assert media_y_desviacion([3]) == pytest.approx((3.0, 0.0))


def test_media_y_desviacion_devuelve_tupla():
    assert isinstance(media_y_desviacion([1, 2]), tuple)


def test_media_y_desviacion_vacia():
    with pytest.raises(ValueError):
        media_y_desviacion([])


def test_aplanar():
    assert aplanar([[1, 2, 3], [4, 5, 6]]) == [1, 2, 3, 4, 5, 6]
    assert aplanar([[1], [], [2, 3]]) == [1, 2, 3]
    assert aplanar([]) == []


def test_aplanar_no_modifica_la_entrada():
    m = [[1, 2], [3]]
    aplanar(m)
    assert m == [[1, 2], [3]]


def test_transponer():
    assert transponer([[1, 2, 3], [4, 5, 6]]) == [[1, 4], [2, 5], [3, 6]]
    assert transponer([[1, 2]]) == [[1], [2]]
    assert transponer([[7]]) == [[7]]


def test_transponer_devuelve_listas():
    t = transponer([[1, 2], [3, 4]])
    assert all(isinstance(fila, list) for fila in t)


def test_crear_tablero():
    assert crear_tablero(2, 3) == [[0, 0, 0], [0, 0, 0]]
    assert crear_tablero(1, 2, valor=".") == [[".", "."]]


def test_crear_tablero_filas_independientes():
    t = crear_tablero(3, 3)
    t[0][0] = 99
    assert t[1][0] == 0 and t[2][0] == 0, "Las filas comparten el mismo objeto"


def test_unicos_en_orden():
    assert unicos_en_orden([3, 1, 3, 2, 1]) == [3, 1, 2]
    assert unicos_en_orden([]) == []
    assert unicos_en_orden(["b", "a", "b"]) == ["b", "a"]


def test_unicos_en_orden_eficiente():
    import time

    datos = list(range(20_000)) * 2
    t0 = time.perf_counter()
    resultado = unicos_en_orden(datos)
    assert resultado == list(range(20_000))
    assert time.perf_counter() - t0 < 0.5, "Demasiado lento: ¿usas `in` sobre una lista?"

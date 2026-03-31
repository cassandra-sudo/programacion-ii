# Ejercicios — Tema 1: Especificación, Verificación y Validación

---

## Ejercicio 1 — Diferencia entre verificación y validación

**Verificación** responde a: *¿el programa hace lo que su especificación dice?*
Es una pregunta técnica e interna — el código contra su contrato.

**Validación** responde a: *¿el programa resuelve el problema real del usuario?*
Es una pregunta de negocio y contexto — el sistema contra el mundo real.

**Ejemplo de error de verificación:**
Una función `calcularSaldo()` está especificada para retornar un `double` con dos decimales de precisión. La implementación retorna un `int` y trunca los centavos. El código no cumple su propia especificación — eso es un error de verificación.

**Ejemplo de error de validación:**
El sistema calcula el saldo correctamente según su especificación. Pero la especificación nunca modeló las comisiones bancarias por retiro. El programa es técnicamente correcto pero no resuelve el problema real del banco — eso es un error de validación.

> La distinción clásica:
> **Verificación** = ¿Estamos construyendo el producto *correctamente*?
> **Validación** = ¿Estamos construyendo el producto *correcto*?

---

## Ejercicio 2 — Por qué las pruebas no demuestran ausencia de errores

Las pruebas las diseña el desarrollador o el QA, y están limitadas a los casos que alguien fue capaz de imaginar. No son demostraciones matemáticas de inexistencia.

Para demostrar que un programa *no tiene errores* habría que ejecutarlo con **todas las entradas posibles** — lo cual es infinito en la mayoría de los casos. Las pruebas solo cubren una muestra finita.

Dijkstra lo formuló así: *"las pruebas demuestran la presencia de bugs, no su ausencia"*.

Lo que sí puede hacer una prueba: encontrar errores. Lo que no puede: garantizar que no quedan más.

---

## Ejercicio 3 — Especificación de una función de ordenamiento

La especificación describe **qué garantiza el resultado**, no cómo se obtiene.
Esa distinción es la diferencia entre especificación descriptiva y operativa.

**Especificación descriptiva:**
```
ordenar(lista L) → lista L'
  PRE:  L es una lista de n números enteros (puede estar vacía)
  POST: L' contiene los mismos elementos que L
        L'[i] <= L'[i+1]  para todo i ∈ [0, n-2]
        |L'| == |L|
```

La postcondición no dice nada sobre cómo se ordenó — solo qué propiedades tiene el resultado.

**Nota:** la descripción *"tomo el mínimo, lo extraigo, repito"* que se intuye naturalmente es correcta como algoritmo (Selection Sort), pero es una especificación *operativa* — describe el proceso, no el contrato. Ambas son válidas; la descriptiva es más rigurosa.

---

## Ejercicio 4 — Función `maximo` con casos borde

### Razonamiento

El algoritmo surge de una observación simple: recorres la lista viendo un elemento a la vez. El primero es provisionalmente el mayor. Por cada siguiente elemento, si es mayor que el que tenías, lo reemplazas. Al final tienes el mayor de todos.

### Implementación

```cpp
#include <iostream>
#include <cassert>
#include <vector>
#include <stdexcept>

int maximo(const std::vector<int>& list) {
    if (list.empty()) throw std::invalid_argument("Lista vacía");

    int mayor = list[0];  // el primero es provisionalmente el mayor

    for (size_t i = 1; i < list.size(); ++i) {  // recorre desde el segundo
        if (list[i] > mayor) {  // si este es mayor que el que tenía
            mayor = list[i];    // actualizo
        }
        // si es menor o igual, no hago nada
    }

    return mayor;  // retorna el valor, no el índice
}

int main() {
    // Caso normal: máximo al final
    assert(maximo({1, 2, 3, 7, 8}) == 8);

    // Máximo al inicio
    assert(maximo({8, 7, 3, 2, 1}) == 8);

    // Un solo elemento
    assert(maximo({5}) == 5);

    // Todos iguales
    assert(maximo({3, 3, 3}) == 3);

    // Todos negativos
    assert(maximo({-5, -1, -3}) == -1);

    // Lista vacía: debe lanzar excepción
    try {
        maximo({});
        assert(false);  // si llega aquí, el test falló
    } catch (const std::invalid_argument&) {
        // correcto — la excepción fue lanzada
    }

    std::cout << "Todos los casos pasaron.\n";
    return 0;
}
```

### Por qué `-1` como centinela no funciona para lista vacía

Retornar `-1` para lista vacía es ambiguo: si la lista es `{-3, -1, -5}`, el máximo legítimo es `-1`. No puedes distinguir "lista vacía" de "el máximo es -1". La excepción elimina esa ambigüedad.

---

## Ejercicio 5 — Análisis estático con `cppcheck`

### Código con error intencional

```cpp
// error_acceso.cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};

    // Error: acceso fuera de límites
    // v tiene índices 0, 1, 2 — el índice 5 no existe
    std::cout << v[5] << "\n";

    return 0;
}
```

### Ejecutar cppcheck

```bash
cppcheck --enable=all error_acceso.cpp
```

### Output esperado

```
error_acceso.cpp:9:22: error: Array 'v[3]' accessed at index 5, which is out of bounds.
```

### Observaciones

`cppcheck` detecta el acceso fuera de límites en tiempo de análisis, sin ejecutar el programa. Esto es **análisis estático** — examina el código como texto, no su ejecución.

Lo que el compilador con `-Wall` *no* detecta en este caso, `cppcheck` sí lo encuentra. Son herramientas complementarias, no equivalentes.

En producción, un acceso fuera de límites en C++ no lanza una excepción amigable como en Python — produce **comportamiento indefinido**: puede crashear, puede corromper memoria silenciosamente, puede no hacer nada visible. Por eso el análisis estático es importante.

---

*Tema 1 completado.*

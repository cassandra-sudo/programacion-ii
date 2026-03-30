# Guía de Estudio — Programación II
### Licenciatura en Actuaría · Tercer Semestre

> **Para quién es esta guía:** Alguien que quiere entender de verdad, no memorizar para olvidar. El temario data de 1991, pero las ideas son atemporales. Lo que cambia es cómo se usan hoy, y eso también está aquí.

---

## Cómo leer esta guía

Cada tema sigue la misma estructura:

1. **¿Qué es y por qué importa?** — Contexto real antes que definición.
2. **La teoría** — Lo que necesitas saber conceptualmente.
3. **En código** — Implementación en C++17 comentada línea a línea.
4. **Insight 2026** — Dónde vive esto hoy en el mundo real.
5. **Ejercicios** — De comprensión a implementación.

No es una guía para devorar en orden lineal. Es una referencia que crece contigo.

---

## Parte 0 — Configuración del entorno (Debian 12 Bookworm)

### 0.1 Por qué C++ y no otro lenguaje

El temario no especifica lenguaje, pero la bibliografía y la naturaleza del curso apuntan a C o C++. En 2026, C++ sigue siendo el lenguaje de referencia para enseñar estructuras de datos porque:

- **Te obliga a pensar en memoria.** No hay recolector de basura automático que te oculte lo que está pasando.
- **Las estructuras que implementarás a mano** (listas ligadas, árboles) ya existen en la STL (Standard Template Library). Aprenderás las dos caras: cómo funcionan por dentro y cómo se usan en producción.
- **La demanda no muere.** Sistemas embebidos, motores de videojuegos, bases de datos, compiladores y software financiero de alta frecuencia están escritos en C++.

El estándar que usaremos es **C++17**. Es moderno, estable y está disponible en Bookworm sin configuración extra.

---

### 0.2 Instalación del compilador y herramientas

Abre una terminal y ejecuta:

```bash
sudo apt update && sudo apt upgrade -y
```

Instala el compilador, el debugger y las herramientas esenciales:

```bash
sudo apt install -y \
  build-essential \
  g++ \
  gdb \
  make \
  cmake \
  valgrind \
  git
```

**¿Qué instala cada uno?**

| Paquete | Para qué sirve |
|---|---|
| `build-essential` | Meta-paquete: incluye g++, gcc, make y cabeceras del sistema |
| `g++` | El compilador de C++ de GNU |
| `gdb` | Debugger. Cuando un árbol AVL no balancea, esto te salva |
| `make` | Para automatizar compilación de múltiples archivos |
| `cmake` | Sistema de build para proyectos más grandes (opcional pero útil) |
| `valgrind` | Detecta fugas de memoria (memory leaks). Indispensable con punteros |
| `git` | Control de versiones. Úsalo desde el primer día |

Verifica la instalación:

```bash
g++ --version
# Debe mostrar algo como: g++ (Debian 12.2.0-14) 12.2.0

gdb --version
# GNU gdb (Debian 15.2-1) 15.2
```

---

### 0.3 Editor: VSCode con C++

Tienes VSCode, úsalo bien.

**Extensiones necesarias** (instálalas desde el panel de extensiones o con `Ctrl+Shift+X`):

1. **C/C++** — Microsoft. Da IntelliSense, autocompletado y debugging integrado.
2. **C/C++ Extension Pack** — Incluye CMake Tools y otras utilidades.
3. **Code Runner** — Para ejecutar fragmentos pequeños con un clic (opcional pero conveniente).

**Configuración mínima del compilador en VSCode:**

Crea un archivo `.vscode/tasks.json` en tu carpeta de trabajo:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Compilar C++17",
      "type": "shell",
      "command": "g++",
      "args": [
        "-std=c++17",
        "-Wall",
        "-Wextra",
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

Con `Ctrl+Shift+B` compilas el archivo activo. El ejecutable queda en la misma carpeta.

**Alternativa sin VSCode — flujo desde terminal pura:**

Si en algún momento prefieres trabajar solo en terminal (es perfectamente válido y más limpio para aprender):

```bash
# Compilar
g++ -std=c++17 -Wall -g mi_programa.cpp -o mi_programa

# Ejecutar
./mi_programa

# Las flags que importan:
# -std=c++17  → usa el estándar C++17
# -Wall       → muestra todos los warnings (advertencias del compilador)
# -g          → incluye información de debug para gdb
```

---

### 0.4 Tu primer programa en C++17 — verificación del entorno

Crea un archivo `hola.cpp`:

```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    // Vector: la versión moderna del arreglo
    std::vector<std::string> temas = {
        "Especificación y verificación",
        "Tipos abstractos de datos",
        "Estructuras lineales",
        "Estructuras no lineales",
        "Búsqueda y ordenamiento"
    };

    std::cout << "Programación II — Temario\n";
    std::cout << "==========================\n";

    for (int i = 0; i < temas.size(); i++) {
        std::cout << "Tema " << (i + 1) << ": " << temas[i] << "\n";
    }

    return 0;
}
```

Compila y ejecuta:

```bash
g++ -std=c++17 -Wall hola.cpp -o hola
./hola
```

Si ves el temario impreso, el entorno funciona correctamente.

---

### 0.5 Neovim como alternativa (solo si te interesa)

Si quieres usar Neovim con soporte completo de C++ (LSP, autocompletado, diagnósticos en tiempo real), el camino es:

```bash
sudo apt install neovim
```

Luego instalar un gestor de plugins como **lazy.nvim** y configurar **clangd** como language server. Es una configuración de ~2 horas que vale la pena si planeas usar Neovim a largo plazo. Para este curso, VSCode o terminal pura son la ruta más directa. No te compliques el entorno cuando el objetivo es aprender el contenido.

---

### 0.6 Estructura de carpetas recomendada

```
programacion_ii/
├── tema1_especificacion/
│   └── ejercicio1.cpp
├── tema2_TAD/
│   └── pila_tad.cpp
├── tema3_estructuras/
│   ├── lista_ligada.cpp
│   ├── pila.cpp
│   └── cola.cpp
├── tema4_no_lineales/
│   ├── arbol_binario.cpp
│   └── arbol_avl.cpp
├── tema5_ordenamiento/
│   ├── quicksort.cpp
│   ├── mergesort.cpp
│   └── heapsort.cpp
└── README.md
```

Inicializa git desde el primer día:

```bash
cd programacion_ii
git init
git add .
git commit -m "inicio del curso"
```

---

## Tema 1 — Especificación, Verificación y Validación

*8 horas teóricas + 4 prácticas*

---

### 1.1 ¿Qué es y por qué importa?

Antes de escribir código, los ingenieros de software de los años 70-80 enfrentaron un problema que se llamó la **crisis del software**: los programas eran cada vez más grandes, y los errores costaban vidas y dinero. La NASA perdió cohetes. Los bancos perdieron dinero. Los hospitales tuvieron fallos.

La respuesta fue formalizar el proceso: ¿cómo sé que mi programa hace lo que debe hacer? Esa pregunta tiene tres partes:

- **Especificación:** Describir *qué* debe hacer el programa.
- **Verificación:** Demostrar *formalmente* que el programa cumple la especificación.
- **Validación:** Comprobar que el programa *realmente* resuelve el problema del usuario.

La distinción clásica es:
> **Verificación** = ¿Estamos construyendo el producto *correctamente*?
> **Validación** = ¿Estamos construyendo el producto *correcto*?

---

### 1.2 Tipos de especificaciones

#### Especificaciones operativas
Describen el comportamiento del sistema mediante ejemplos, casos de uso, o pseudocódigo. Son más fáciles de entender pero menos rigurosas.

**Ejemplo:** "La función `buscar(lista, x)` recorre la lista desde el inicio y retorna la posición de `x`, o -1 si no está."

#### Especificaciones descriptivas (formales)
Usan notación matemática o lógica para describir el comportamiento con precisión absoluta. No hay ambigüedad.

**Ejemplo (precondición/postcondición):**
```
buscar(lista L, elemento x):
  PRE:  L es una lista válida (puede estar vacía)
  POST: resultado = i  si L[i] == x  para algún i ∈ [0, n-1]
        resultado = -1 si x ∉ L
```

Las especificaciones descriptivas son la base de la **verificación formal** y de los contratos en programación moderna.

---

### 1.3 Verificación

Verificar un programa significa demostrar que cumple su especificación. Los enfoques principales son:

#### a) Análisis estático
Examinar el código sin ejecutarlo. El compilador con flags `-Wall -Wextra` hace una forma básica de esto. Herramientas modernas como `clang-tidy` o `cppcheck` van mucho más lejos.

```bash
# Instalar cppcheck
sudo apt install cppcheck

# Analizar un archivo
cppcheck --enable=all mi_programa.cpp
```

#### b) Ejecución simbólica
En vez de ejecutar el programa con valores concretos, se ejecuta con variables simbólicas para explorar todos los caminos posibles. Es la base de herramientas modernas de testing automático.

#### c) Pruebas (testing)
El método más usado en la práctica. No puede demostrar la ausencia de errores, pero sí encontrarlos.

```cpp
// Ejemplo de prueba simple para una función de búsqueda
#include <iostream>
#include <cassert>  // para assert()
#include <vector>

int buscar(const std::vector<int>& lista, int x) {
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i] == x) return i;
    }
    return -1;
}

int main() {
    std::vector<int> lista = {3, 7, 1, 9, 4};

    // assert() lanza un error si la condición es falsa
    assert(buscar(lista, 7) == 1);   // está en posición 1
    assert(buscar(lista, 4) == 4);   // está en posición 4
    assert(buscar(lista, 99) == -1); // no está

    std::cout << "Todas las pruebas pasaron.\n";
    return 0;
}
```

#### d) Depuración (debugging)
El proceso de encontrar y corregir errores. Con `gdb`:

```bash
# Compilar con información de debug
g++ -std=c++17 -g mi_programa.cpp -o mi_programa

# Iniciar gdb
gdb ./mi_programa

# Comandos básicos de gdb:
# run          → ejecutar el programa
# break 15     → poner punto de parada en línea 15
# next         → ejecutar línea actual y pasar a la siguiente
# print x      → imprimir el valor de la variable x
# backtrace    → ver la pila de llamadas
# quit         → salir
```

---

### 1.4 Validación

La validación verifica que el software resuelve el problema *real* del usuario. Históricamente se hace con:

- **Revisiones de código (code reviews):** Otro programador lee el código buscando errores lógicos.
- **Recorridos estructurados (walkthroughs):** El equipo sigue la ejecución del programa paso a paso en papel o en pizarrón, con datos de prueba concretos.
- **Pruebas de aceptación:** El usuario final prueba el sistema con casos reales.

---

### 1.5 Insight 2026

En 2026, la especificación formal ha encontrado una segunda vida en dos áreas:

1. **Contratos en código moderno.** C++20 introdujo *Contracts* (precondiciones y postcondiciones directamente en el código). El diseño por contrato (`Design by Contract`, popularizado por Bertrand Meyer en Eiffel) es ahora estándar en lenguajes como Rust, donde el compilador *garantiza* ciertas propiedades en tiempo de compilación.

2. **Verificación asistida por LLMs.** Herramientas como GitHub Copilot y los sistemas de AI ahora generan código, pero la verificación sigue siendo responsabilidad humana. Saber especificar correctamente qué quieres es la habilidad que distingue a quien sabe usar estas herramientas de quien no.

---

### 1.6 Ejercicios

**Comprensión:**
1. ¿Cuál es la diferencia entre un error de verificación y uno de validación? Da un ejemplo de cada uno.
2. ¿Por qué las pruebas no pueden demostrar que un programa no tiene errores?
3. Describe en lenguaje natural la especificación de una función que ordena una lista de números de menor a mayor.

**Implementación:**
4. Escribe la función `maximo(vector<int> v)` que retorna el mayor elemento. Luego escribe al menos 5 `assert()` que la validen, incluyendo casos borde (lista vacía, un solo elemento, todos iguales).
5. Usa `cppcheck` en un archivo con un posible error de acceso fuera de límites y observa qué detecta.

---

## Tema 2 — Tipos Abstractos de Datos (TAD)

*8 horas teóricas + 4 prácticas*

---

### 2.1 ¿Qué es y por qué importa?

Un **Tipo Abstracto de Dato (TAD)** — en inglés, *Abstract Data Type* (ADT) — es una de las ideas más importantes en ciencias de la computación.

La idea central: separar **qué hace** una estructura de datos de **cómo lo hace internamente**.

Piénsalo así: cuando usas un cajero automático, no necesitas saber cómo funciona el banco por dentro. Sabes que puedes *depositar*, *retirar* y *consultar saldo*. Esa interfaz es el TAD. La implementación bancaria detrás es el detalle.

Un TAD define:
1. **El tipo:** el nombre y la naturaleza del dato.
2. **Las operaciones:** qué se puede hacer con él.
3. **Las propiedades:** qué garantías ofrecen las operaciones.

Lo que **no** define: cómo están guardados los datos en memoria.

---

### 2.2 Ejemplo concreto: TAD Pila (Stack)

**Definición abstracta:**

```
TAD Pila<T>:
  Operaciones:
    push(x: T)    → agrega x al tope
    pop()         → elimina y retorna el tope
    top()         → retorna el tope sin eliminarlo
    isEmpty()     → retorna verdadero si la pila está vacía
    size()        → retorna el número de elementos

  Propiedades:
    - Orden LIFO: Last In, First Out
    - push seguido de pop retorna el mismo elemento
    - pop() en pila vacía es un error
```

Ahora, dos implementaciones completamente distintas del mismo TAD:

#### Implementación 1: con arreglo (array)

```cpp
#include <iostream>
#include <stdexcept>  // para std::underflow_error

template <typename T>
class PilaArreglo {
private:
    T datos[100];  // arreglo de tamaño fijo
    int tope;      // índice del elemento en el tope

public:
    PilaArreglo() : tope(-1) {}  // tope = -1 significa vacía

    void push(T elemento) {
        if (tope >= 99) throw std::overflow_error("Pila llena");
        datos[++tope] = elemento;
    }

    T pop() {
        if (isEmpty()) throw std::underflow_error("Pila vacía");
        return datos[tope--];
    }

    T top() const {
        if (isEmpty()) throw std::underflow_error("Pila vacía");
        return datos[tope];
    }

    bool isEmpty() const {
        return tope == -1;
    }

    int size() const {
        return tope + 1;
    }
};
```

#### Implementación 2: con lista ligada (nodos dinámicos)

```cpp
#include <iostream>
#include <stdexcept>

template <typename T>
class PilaLista {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T d) : dato(d), siguiente(nullptr) {}
    };

    Nodo* tope_ptr;  // puntero al tope
    int cantidad;

public:
    PilaLista() : tope_ptr(nullptr), cantidad(0) {}

    ~PilaLista() {  // destructor: limpia la memoria
        while (!isEmpty()) pop();
    }

    void push(T elemento) {
        Nodo* nuevo = new Nodo(elemento);  // reservar memoria
        nuevo->siguiente = tope_ptr;
        tope_ptr = nuevo;
        cantidad++;
    }

    T pop() {
        if (isEmpty()) throw std::underflow_error("Pila vacía");
        Nodo* temp = tope_ptr;
        T valor = temp->dato;
        tope_ptr = tope_ptr->siguiente;
        delete temp;   // liberar memoria
        cantidad--;
        return valor;
    }

    T top() const {
        if (isEmpty()) throw std::underflow_error("Pila vacía");
        return tope_ptr->dato;
    }

    bool isEmpty() const {
        return tope_ptr == nullptr;
    }

    int size() const {
        return cantidad;
    }
};
```

#### Usando ambas con la misma interfaz

```cpp
int main() {
    PilaArreglo<int> p1;
    PilaLista<int>   p2;

    // El código que usa la pila es idéntico
    // sin importar la implementación interna
    for (int pila : {1, 2, 3}) {
        p1.push(pila);
        p2.push(pila);
    }

    std::cout << "Arreglo: " << p1.pop() << "\n";  // 3
    std::cout << "Lista:   " << p2.pop() << "\n";  // 3

    return 0;
}
```

---

### 2.3 TADs y la STL de C++

La Standard Template Library de C++ es, en esencia, una biblioteca de TADs ya implementados y optimizados:

| TAD | Clase en STL | Header |
|---|---|---|
| Pila | `std::stack` | `<stack>` |
| Cola | `std::queue` | `<queue>` |
| Lista | `std::list` | `<list>` |
| Arreglo dinámico | `std::vector` | `<vector>` |
| Mapa (diccionario) | `std::map` | `<map>` |
| Árbol de búsqueda | `std::set` | `<set>` |

En producción usarías la STL. En este curso implementarás las estructuras a mano para entender cómo funcionan por dentro. Ambas habilidades son valiosas.

---

### 2.4 Insight 2026

Los TADs son el fundamento de las **interfaces** en programación orientada a objetos y de los **traits** en Rust. En Python, los *Abstract Base Classes* (`abc.ABCMeta`) son exactamente esto. En Go, las *interfaces* funcionan igual.

La idea de separar contrato de implementación es hoy más relevante que nunca en arquitecturas de microservicios, donde una API REST es literalmente un TAD: defines qué operaciones existen, qué entradas aceptan y qué salen, sin exponer cómo están implementadas.

---

### 2.5 Ejercicios

**Comprensión:**
1. Define el TAD `Cola` (Queue) con sus operaciones y propiedades. ¿En qué se diferencia de una Pila?
2. ¿Por qué es útil separar la especificación de la implementación? Da un ejemplo del mundo real.
3. ¿Qué ventajas tiene la implementación con lista ligada sobre la de arreglo fijo para una Pila?

**Implementación:**
4. Implementa el TAD `Cola` con dos implementaciones: arreglo circular y lista ligada.
5. Usa `std::stack` de la STL para resolver este problema: dada una cadena de texto con paréntesis `()`, `[]`, `{}`, verifica si están correctamente balanceados.

---

## Tema 3 — Estructuras de Datos Básicas (Lineales)

*20 horas teóricas + 10 prácticas*

Esta es la parte central del curso. Aquí construirás las estructuras que son la base de todo el software moderno.

---

### 3.1 Arreglos (Arrays)

El arreglo es la estructura más fundamental: una secuencia de elementos del mismo tipo almacenados en posiciones de memoria **contiguas**.

```
Memoria:   [10] [20] [30] [40] [50]
Posición:   0    1    2    3    4
Dirección: 100  104  108  112  116   (asumiendo 4 bytes por int)
```

**Arreglos en C++:**

```cpp
#include <iostream>

int main() {
    // Arreglo estático: tamaño fijo en tiempo de compilación
    int estatico[5] = {10, 20, 30, 40, 50};

    // Arreglo dinámico: tamaño en tiempo de ejecución
    int n = 5;
    int* dinamico = new int[n];
    for (int i = 0; i < n; i++) dinamico[i] = (i + 1) * 10;

    // Acceso O(1): directo por índice
    std::cout << estatico[2] << "\n";   // 30
    std::cout << dinamico[2] << "\n";   // 30

    delete[] dinamico;  // liberar memoria del arreglo dinámico

    // La alternativa moderna: std::vector
    // (arreglo dinámico con gestión automática de memoria)
    std::vector<int> v = {10, 20, 30, 40, 50};
    std::cout << v[2] << "\n";   // 30
    v.push_back(60);             // agregar al final
    std::cout << v.size() << "\n"; // 6

    return 0;
}
```

**Complejidad de operaciones en arreglo:**

| Operación | Complejidad | Por qué |
|---|---|---|
| Acceso por índice | O(1) | Cálculo directo de dirección |
| Búsqueda lineal | O(n) | Peor caso: recorrer todo |
| Búsqueda binaria (ordenado) | O(log n) | Divide y conquistarás |
| Inserción al final | O(1) amortizado | En vector dinámico |
| Inserción en medio | O(n) | Hay que mover elementos |
| Eliminación en medio | O(n) | Hay que cerrar el hueco |

---

### 3.2 Listas Ligadas (Linked Lists)

A diferencia del arreglo, los elementos de una lista ligada no están contiguos en memoria. Cada elemento (nodo) guarda el dato *y* un puntero al siguiente nodo.

```
[10|→] → [20|→] → [30|→] → [40|→] → [50|∅]
```

Esto cambia completamente el perfil de operaciones:

```cpp
#include <iostream>

struct Nodo {
    int dato;
    Nodo* siguiente;

    Nodo(int d) : dato(d), siguiente(nullptr) {}
};

class ListaLigada {
private:
    Nodo* cabeza;
    int cantidad;

public:
    ListaLigada() : cabeza(nullptr), cantidad(0) {}

    ~ListaLigada() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // Insertar al inicio: O(1)
    void insertarAlInicio(int dato) {
        Nodo* nuevo = new Nodo(dato);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;
    }

    // Insertar al final: O(n)
    void insertarAlFinal(int dato) {
        Nodo* nuevo = new Nodo(dato);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        cantidad++;
    }

    // Buscar: O(n)
    bool buscar(int dato) const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == dato) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    // Eliminar un elemento: O(n)
    bool eliminar(int dato) {
        if (cabeza == nullptr) return false;

        // Caso especial: eliminar la cabeza
        if (cabeza->dato == dato) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cantidad--;
            return true;
        }

        // Caso general: buscar el nodo anterior al que queremos eliminar
        Nodo* anterior = cabeza;
        while (anterior->siguiente != nullptr &&
               anterior->siguiente->dato != dato) {
            anterior = anterior->siguiente;
        }

        if (anterior->siguiente == nullptr) return false;  // no encontrado

        Nodo* aEliminar = anterior->siguiente;
        anterior->siguiente = aEliminar->siguiente;
        delete aEliminar;
        cantidad--;
        return true;
    }

    void imprimir() const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            std::cout << actual->dato;
            if (actual->siguiente != nullptr) std::cout << " → ";
            actual = actual->siguiente;
        }
        std::cout << "\n";
    }

    int size() const { return cantidad; }
};

int main() {
    ListaLigada lista;
    lista.insertarAlFinal(10);
    lista.insertarAlFinal(20);
    lista.insertarAlFinal(30);
    lista.insertarAlInicio(5);

    lista.imprimir();      // 5 → 10 → 20 → 30
    lista.eliminar(10);
    lista.imprimir();      // 5 → 20 → 30

    std::cout << lista.buscar(20) << "\n";  // 1 (true)
    std::cout << lista.buscar(99) << "\n";  // 0 (false)

    return 0;
}
```

---

### 3.3 Listas Doblemente Ligadas y Circulares

**Lista doblemente ligada:** cada nodo tiene puntero al siguiente *y* al anterior.

```
∅ ← [5|←→] ↔ [10|←→] ↔ [20|←→] ↔ [30|←→] → ∅
```

```cpp
struct NodoDoble {
    int dato;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(int d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};
```

Ventaja: eliminar un nodo es O(1) si tienes el puntero al nodo (no necesitas recorrer buscando el anterior).

**Lista circular:** el último nodo apunta de vuelta al primero.

```
[5|→] → [10|→] → [20|→] → [30|→]
 ↑_________________________________|
```

Útil para: buffers circulares, planificadores de tareas round-robin.

---

### 3.4 Pilas (Stacks)

Ya viste la implementación en el Tema 2. Aquí, los casos de uso:

**Aplicaciones clásicas de la Pila:**

1. **Llamadas a funciones.** Cada llamada empuja un *frame* en el stack del sistema. Por eso existe el término *stack overflow*.
2. **Deshacer operaciones** (Ctrl+Z): cada acción se apila, deshacer saca la última.
3. **Evaluación de expresiones matemáticas** con operadores y paréntesis.
4. **Algoritmos DFS** (búsqueda en profundidad en grafos).

```cpp
// Ejemplo: verificar paréntesis balanceados
#include <iostream>
#include <stack>
#include <string>

bool estaBalanceada(const std::string& expresion) {
    std::stack<char> pila;

    for (char c : expresion) {
        if (c == '(' || c == '[' || c == '{') {
            pila.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (pila.empty()) return false;

            char tope = pila.top();
            pila.pop();

            if ((c == ')' && tope != '(') ||
                (c == ']' && tope != '[') ||
                (c == '}' && tope != '{')) {
                return false;
            }
        }
    }

    return pila.empty();
}

int main() {
    std::cout << estaBalanceada("(a + b) * [c - {d}]") << "\n";  // 1
    std::cout << estaBalanceada("(a + [b)]") << "\n";             // 0
    std::cout << estaBalanceada("{a + b") << "\n";                // 0
    return 0;
}
```

---

### 3.5 Colas (Queues)

Orden **FIFO**: First In, First Out. El primero en entrar es el primero en salir.

```
Entrada → [30] [20] [10] → Salida
```

```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<int> cola;

    cola.push(10);   // enqueue
    cola.push(20);
    cola.push(30);

    std::cout << cola.front() << "\n";  // 10
    cola.pop();                          // dequeue
    std::cout << cola.front() << "\n";  // 20

    return 0;
}
```

**Aplicaciones reales de la Cola:**
- Sistemas de impresión: documentos en espera.
- Redes: paquetes esperando ser procesados.
- BFS (búsqueda en anchura en grafos).
- Sistemas de mensajería: Kafka, RabbitMQ son, conceptualmente, colas muy sofisticadas.

---

### 3.6 Complejidad: tiempo vs espacio

Este tema es crucial para el examen y para la vida profesional.

| Estructura | Acceso | Búsqueda | Inserción | Eliminación | Espacio |
|---|---|---|---|---|---|
| Arreglo | O(1) | O(n) | O(n) | O(n) | O(n) |
| Lista ligada | O(n) | O(n) | O(1)* | O(1)* | O(n) |
| Pila | O(n) | O(n) | O(1) | O(1) | O(n) |
| Cola | O(n) | O(n) | O(1) | O(1) | O(n) |

*Asumiendo que ya tienes el puntero al nodo.

**¿Cuándo usar cada una?**
- **Arreglo:** acceso aleatorio frecuente, tamaño conocido o con pocos cambios.
- **Lista ligada:** muchas inserciones/eliminaciones en posiciones arbitrarias.
- **Pila:** necesitas LIFO (historial, recursión).
- **Cola:** necesitas FIFO (turnos, procesamiento en orden).

---

### 3.7 Ejercicios

**Comprensión:**
1. ¿Por qué acceder a `arreglo[i]` es O(1) pero acceder al i-ésimo elemento de una lista ligada es O(n)?
2. Explica la diferencia entre una lista circular simple y una doblemente ligada. ¿Cuándo usarías cada una?
3. ¿Qué sucede en memoria cuando llamas a una función recursiva muchas veces? ¿Qué tiene que ver el stack?

**Implementación:**
4. Implementa una lista doblemente ligada con las operaciones: `insertarAlInicio`, `insertarAlFinal`, `eliminar(dato)`, `imprimir()` (en ambas direcciones).
5. Implementa una cola usando **dos pilas** (sí, es posible). Pista: una pila para enqueue, otra para dequeue.
6. Implementa un historial de navegación web simplificado: las operaciones son `visitar(url)`, `atras()`, `adelante()`.

---

## Tema 4 — Estructuras de Datos No Lineales

*12 horas teóricas + 6 prácticas*

---

### 4.1 ¿Qué es y por qué importa?

Las estructuras lineales representan secuencias: hay un primero, un segundo, un último. Pero muchos problemas tienen una estructura **jerárquica** o **relacional** que no encaja en una línea.

Un árbol genealógico, la estructura de carpetas de tu sistema de archivos, las decisiones en un juego de ajedrez, los nodos de una red — todos tienen estructura de **árbol** o **grafo**.

---

### 4.2 Árboles

Un **árbol** es una estructura donde cada elemento (nodo) puede tener múltiples "hijos", pero exactamente un "padre", excepto la raíz que no tiene padre.

**Terminología:**

```
         [A]          ← raíz (root)
        /   \
      [B]   [C]       ← nodos internos
      / \     \
    [D] [E]  [F]      ← hojas (sin hijos)
```

- **Raíz:** nodo sin padre.
- **Hoja:** nodo sin hijos.
- **Altura:** longitud del camino más largo desde la raíz hasta una hoja.
- **Nivel:** distancia desde la raíz (raíz = nivel 0).
- **Subárbol:** un nodo y todos sus descendientes.

---

### 4.3 Árboles Binarios

Un árbol donde cada nodo tiene **a lo sumo dos hijos**: izquierdo y derecho.

```cpp
#include <iostream>

struct NodoArbol {
    int dato;
    NodoArbol* izquierdo;
    NodoArbol* derecho;

    NodoArbol(int d) : dato(d), izquierdo(nullptr), derecho(nullptr) {}
};

class ArbolBinario {
private:
    NodoArbol* raiz;

    // Recorridos recursivos (internos)
    void inorden(NodoArbol* nodo) const {
        if (nodo == nullptr) return;
        inorden(nodo->izquierdo);    // izquierdo
        std::cout << nodo->dato << " ";  // raíz
        inorden(nodo->derecho);     // derecho
    }

    void preorden(NodoArbol* nodo) const {
        if (nodo == nullptr) return;
        std::cout << nodo->dato << " ";  // raíz primero
        preorden(nodo->izquierdo);
        preorden(nodo->derecho);
    }

    void postorden(NodoArbol* nodo) const {
        if (nodo == nullptr) return;
        postorden(nodo->izquierdo);
        postorden(nodo->derecho);
        std::cout << nodo->dato << " ";  // raíz al final
    }

    void destruir(NodoArbol* nodo) {
        if (nodo == nullptr) return;
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }

public:
    ArbolBinario() : raiz(nullptr) {}
    ~ArbolBinario() { destruir(raiz); }

    NodoArbol*& getRaiz() { return raiz; }

    void recorridoInorden()   const { inorden(raiz);    std::cout << "\n"; }
    void recorridoPreorden()  const { preorden(raiz);   std::cout << "\n"; }
    void recorridoPostorden() const { postorden(raiz);  std::cout << "\n"; }
};

int main() {
    ArbolBinario arbol;

    // Construir el árbol manualmente
    arbol.getRaiz() = new NodoArbol(1);
    arbol.getRaiz()->izquierdo = new NodoArbol(2);
    arbol.getRaiz()->derecho   = new NodoArbol(3);
    arbol.getRaiz()->izquierdo->izquierdo = new NodoArbol(4);
    arbol.getRaiz()->izquierdo->derecho   = new NodoArbol(5);

    /*
         [1]
        /   \
      [2]   [3]
      / \
    [4] [5]
    */

    std::cout << "Inorden:    "; arbol.recorridoInorden();    // 4 2 5 1 3
    std::cout << "Preorden:   "; arbol.recorridoPreorden();   // 1 2 4 5 3
    std::cout << "Postorden:  "; arbol.recorridoPostorden();  // 4 5 2 3 1

    return 0;
}
```

---

### 4.4 Árbol Binario de Búsqueda (BST)

Un árbol binario con una propiedad adicional:
- Todo nodo del subárbol **izquierdo** tiene valor **menor** que la raíz.
- Todo nodo del subárbol **derecho** tiene valor **mayor** que la raíz.

Esto permite búsqueda eficiente: O(log n) en el caso promedio.

```cpp
class ArbolBST {
private:
    NodoArbol* raiz;

    NodoArbol* insertar(NodoArbol* nodo, int dato) {
        if (nodo == nullptr) return new NodoArbol(dato);

        if (dato < nodo->dato)
            nodo->izquierdo = insertar(nodo->izquierdo, dato);
        else if (dato > nodo->dato)
            nodo->derecho = insertar(nodo->derecho, dato);
        // si dato == nodo->dato, no se inserta (sin duplicados)

        return nodo;
    }

    bool buscar(NodoArbol* nodo, int dato) const {
        if (nodo == nullptr) return false;
        if (nodo->dato == dato) return true;

        if (dato < nodo->dato)
            return buscar(nodo->izquierdo, dato);
        else
            return buscar(nodo->derecho, dato);
    }

    void inorden(NodoArbol* nodo) const {
        if (nodo == nullptr) return;
        inorden(nodo->izquierdo);
        std::cout << nodo->dato << " ";
        inorden(nodo->derecho);
    }

    void destruir(NodoArbol* nodo) {
        if (nodo == nullptr) return;
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }

public:
    ArbolBST() : raiz(nullptr) {}
    ~ArbolBST() { destruir(raiz); }

    void insertar(int dato) { raiz = insertar(raiz, dato); }
    bool buscar(int dato) const { return buscar(raiz, dato); }
    void imprimirOrdenado() const { inorden(raiz); std::cout << "\n"; }
};

int main() {
    ArbolBST bst;
    for (int x : {5, 3, 7, 1, 4, 6, 8}) {
        bst.insertar(x);
    }

    bst.imprimirOrdenado();    // 1 3 4 5 6 7 8 (¡ya ordenado!)
    std::cout << bst.buscar(4) << "\n";  // 1 (true)
    std::cout << bst.buscar(9) << "\n";  // 0 (false)

    return 0;
}
```

---

### 4.5 Representación de árboles arbitrarios como árboles binarios

¿Qué pasa si un árbol tiene nodos con más de 2 hijos? La técnica clásica es transformarlo en un árbol binario usando la regla **"hijo izquierdo, hermano derecho"**:

```
Árbol original:         Representación binaria:
      A                       A
    / | \                    /
   B  C  D                  B
         |                 / \
         E                C   D
                               \
                                E
```

El hijo izquierdo en la representación binaria es el **primer hijo** del nodo original. El hijo derecho es el **hermano siguiente**.

---

### 4.6 Memoria dinámica y recolección de basura

Cuando usas `new` en C++ para crear un nodo, reservas memoria en el **heap**. Si no usas `delete`, esa memoria nunca se libera. Eso es un **memory leak** (fuga de memoria).

```cpp
// MAL: memory leak
void mal() {
    int* p = new int(42);
    // p sale de scope pero la memoria NO se libera
}

// BIEN: liberar manualmente
void bien() {
    int* p = new int(42);
    delete p;
}

// MEJOR: usar smart pointers (C++11 en adelante)
#include <memory>
void mejor() {
    std::unique_ptr<int> p = std::make_unique<int>(42);
    // se libera automáticamente al salir del scope
}
```

En lenguajes como Java, Python o Go, el **recolector de basura** hace esto automáticamente. En C++, es tu responsabilidad. Usa `valgrind` para detectar leaks:

```bash
valgrind --leak-check=full ./mi_programa
```

---

### 4.7 Insight 2026

Los árboles están en todas partes:

- **Sistema de archivos de Linux:** `ext4`, `btrfs` — basados en árboles B.
- **Bases de datos:** `PostgreSQL`, `MySQL` usan B-Trees para los índices. Cuando haces una búsqueda que usa un índice, el motor navega un árbol.
- **Git:** el historial de commits es un árbol (con posibilidad de ser un DAG — directed acyclic graph).
- **HTML/CSS DOM:** el árbol de elementos de una página web.
- **Machine Learning:** los Decision Trees y Random Forests son literalmente árboles de decisión.
- **Compiladores:** el Abstract Syntax Tree (AST) es cómo un compilador entiende tu código.

---

### 4.8 Ejercicios

**Comprensión:**
1. Dado el árbol binario de búsqueda con inserciones en el orden: 10, 5, 15, 3, 7, 12, 20, dibuja el árbol resultante.
2. ¿Cuál es el resultado del recorrido inorden de ese árbol? ¿Qué propiedad notable tiene?
3. ¿Por qué la búsqueda en un BST degenerado (insertado en orden) es O(n) y no O(log n)?

**Implementación:**
4. Agrega a la clase `ArbolBST` el método `int altura()` que retorna la altura del árbol.
5. Implementa el método `eliminar(int dato)` en el BST. Este es el más complejo: considera los tres casos (nodo hoja, un hijo, dos hijos).
6. Implementa un recorrido por niveles (*breadth-first*) usando una `std::queue`.

---

## Tema 5 — Búsqueda y Ordenamiento

*16 horas teóricas + 8 prácticas*

Este es el tema más matemático del curso. Los algoritmos de ordenamiento son el ejemplo clásico de análisis de complejidad.

---

### 5.1 ¿Por qué importa el ordenamiento?

Un conjunto de datos ordenado es radicalmente más fácil de trabajar: búsqueda binaria en vez de lineal, detección de duplicados, merge de datasets, índices en bases de datos.

La pregunta es: ¿cuál es la forma más rápida de ordenar `n` elementos?

---

### 5.2 Análisis de complejidad — repaso

La notación **O grande** (Big O) describe cómo crece el tiempo de ejecución de un algoritmo en función del tamaño de la entrada.

| Notación | Nombre | Ejemplo |
|---|---|---|
| O(1) | Constante | Acceso a arreglo por índice |
| O(log n) | Logarítmica | Búsqueda binaria |
| O(n) | Lineal | Búsqueda lineal |
| O(n log n) | Lineal-logarítmica | Mergesort, Heapsort, Quicksort (promedio) |
| O(n²) | Cuadrática | Bubble sort, Insertion sort |
| O(2ⁿ) | Exponencial | Problemas NP-hard |

El límite teórico inferior para ordenar por comparaciones es **O(n log n)**. No existe algoritmo de comparación más rápido que esto en el caso general.

---

### 5.3 Quicksort

El más usado en la práctica. Divide el arreglo en dos partes alrededor de un **pivote**: elementos menores a la izquierda, mayores a la derecha. Luego ordena cada parte recursivamente.

**Complejidad:**
- Mejor caso: O(n log n)
- Caso promedio: O(n log n)
- Peor caso: O(n²) — cuando el pivote siempre es el mínimo o máximo

```cpp
#include <iostream>
#include <vector>

void quicksort(std::vector<int>& v, int izq, int der) {
    if (izq >= der) return;  // caso base: 0 o 1 elemento

    // Partición: elegir pivote y reorganizar
    int pivote = v[der];  // elegimos el último elemento como pivote
    int i = izq - 1;      // índice del último elemento menor que pivote

    for (int j = izq; j < der; j++) {
        if (v[j] <= pivote) {
            i++;
            std::swap(v[i], v[j]);  // mover elemento menor al lado izquierdo
        }
    }

    // Colocar el pivote en su posición correcta
    std::swap(v[i + 1], v[der]);
    int pos_pivote = i + 1;

    // Ordenar recursivamente las dos mitades
    quicksort(v, izq, pos_pivote - 1);
    quicksort(v, pos_pivote + 1, der);
}

int main() {
    std::vector<int> v = {64, 34, 25, 12, 22, 11, 90};
    quicksort(v, 0, v.size() - 1);

    for (int x : v) std::cout << x << " ";
    std::cout << "\n";  // 11 12 22 25 34 64 90

    return 0;
}
```

---

### 5.4 Mergesort

Divide el arreglo a la mitad, ordena cada mitad recursivamente, luego **mezcla** (merge) las dos mitades ordenadas.

**Complejidad:**
- Todos los casos: O(n log n) — garantizado
- Espacio adicional: O(n) — necesita arreglo auxiliar

```cpp
#include <iostream>
#include <vector>

void merge(std::vector<int>& v, int izq, int medio, int der) {
    // Copiar las dos mitades a arreglos temporales
    std::vector<int> izquierda(v.begin() + izq, v.begin() + medio + 1);
    std::vector<int> derecha(v.begin() + medio + 1, v.begin() + der + 1);

    int i = 0, j = 0, k = izq;

    // Mezclar comparando elementos de ambas mitades
    while (i < izquierda.size() && j < derecha.size()) {
        if (izquierda[i] <= derecha[j]) {
            v[k++] = izquierda[i++];
        } else {
            v[k++] = derecha[j++];
        }
    }

    // Copiar los elementos restantes de cada mitad
    while (i < izquierda.size()) v[k++] = izquierda[i++];
    while (j < derecha.size())  v[k++] = derecha[j++];
}

void mergesort(std::vector<int>& v, int izq, int der) {
    if (izq >= der) return;  // caso base

    int medio = izq + (der - izq) / 2;  // evita overflow vs (izq+der)/2
    mergesort(v, izq, medio);
    mergesort(v, medio + 1, der);
    merge(v, izq, medio, der);
}

int main() {
    std::vector<int> v = {38, 27, 43, 3, 9, 82, 10};
    mergesort(v, 0, v.size() - 1);

    for (int x : v) std::cout << x << " ";
    std::cout << "\n";  // 3 9 10 27 38 43 82

    return 0;
}
```

---

### 5.5 Heapsort

Usa una estructura llamada **heap** (montículo) — un árbol binario completo donde cada nodo es mayor (o menor) que sus hijos. El elemento en la raíz siempre es el máximo (en un max-heap).

**Complejidad:**
- Todos los casos: O(n log n)
- Espacio adicional: O(1) — ordena in-place

```cpp
#include <iostream>
#include <vector>
#include <algorithm>  // para std::make_heap, std::sort_heap

// Versión conceptual usando STL:
int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

    // Convertir el vector en un max-heap
    std::make_heap(v.begin(), v.end());
    // Internamente: [9, 6, 4, 1, 5, 1, 2, 3]

    // Ordenar usando el heap
    std::sort_heap(v.begin(), v.end());

    for (int x : v) std::cout << x << " ";
    std::cout << "\n";  // 1 1 2 3 4 5 6 9

    return 0;
}
```

---

### 5.6 Algoritmo de Shell

Una mejora de Insertion Sort que compara elementos separados por un **gap** que se reduce progresivamente.

**Complejidad:** entre O(n log n) y O(n²) dependiendo de la secuencia de gaps. En la práctica, mucho más rápido que Insertion Sort para n grandes.

```cpp
#include <iostream>
#include <vector>

void shellsort(std::vector<int>& v) {
    int n = v.size();

    // Empezar con gap grande, reducir a la mitad cada vez
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Insertion sort con este gap
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j = i;

            // Desplazar elementos que están gap posiciones adelante
            while (j >= gap && v[j - gap] > temp) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = temp;
        }
    }
}
```

---

### 5.7 Funciones de dispersión (Hash) y resolución de colisiones

Una **tabla hash** mapea claves a posiciones en un arreglo mediante una **función hash**: `h(clave) = posición`.

El problema: dos claves distintas pueden producir la misma posición → **colisión**.

```
h(x) = x % tamaño_tabla

h(10) = 10 % 7 = 3
h(17) = 17 % 7 = 3   ← ¡colisión!
```

**Métodos de resolución de colisiones:**

1. **Encadenamiento (chaining):** cada posición de la tabla guarda una lista ligada de todos los elementos con ese hash.

2. **Direccionamiento abierto (open addressing):** si la posición está ocupada, buscar la siguiente disponible.

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <string>

class TablaHash {
private:
    int capacidad;
    std::vector<std::list<std::pair<int, std::string>>> tabla;

    int hash(int clave) const {
        return clave % capacidad;
    }

public:
    TablaHash(int cap) : capacidad(cap), tabla(cap) {}

    void insertar(int clave, const std::string& valor) {
        int pos = hash(clave);
        // Actualizar si ya existe
        for (auto& par : tabla[pos]) {
            if (par.first == clave) {
                par.second = valor;
                return;
            }
        }
        tabla[pos].push_back({clave, valor});
    }

    std::string buscar(int clave) const {
        int pos = hash(clave);
        for (const auto& par : tabla[pos]) {
            if (par.first == clave) return par.second;
        }
        return "";  // no encontrado
    }
};

int main() {
    TablaHash th(7);
    th.insertar(10, "diez");
    th.insertar(17, "diecisiete");  // colisiona con 10
    th.insertar(3,  "tres");

    std::cout << th.buscar(10) << "\n";  // diez
    std::cout << th.buscar(17) << "\n";  // diecisiete

    return 0;
}
```

---

### 5.8 Búsqueda binaria

Si los datos están **ordenados**, la búsqueda binaria reduce el problema a la mitad en cada paso: O(log n).

```cpp
#include <iostream>
#include <vector>

// Versión iterativa
int busquedaBinaria(const std::vector<int>& v, int objetivo) {
    int izq = 0, der = v.size() - 1;

    while (izq <= der) {
        int medio = izq + (der - izq) / 2;

        if (v[medio] == objetivo) return medio;
        if (v[medio] < objetivo)  izq = medio + 1;
        else                      der = medio - 1;
    }

    return -1;  // no encontrado
}

int main() {
    std::vector<int> v = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};

    std::cout << busquedaBinaria(v, 23) << "\n";   // 5
    std::cout << busquedaBinaria(v, 100) << "\n";  // -1

    return 0;
}
```

---

### 5.9 Árboles AVL y B-Trees

#### Árboles AVL

Un BST puede degenerar en una lista ligada si los datos se insertan en orden. Un **árbol AVL** se mantiene **balanceado** automáticamente: la diferencia de altura entre el subárbol izquierdo y derecho de cualquier nodo es a lo sumo 1.

Para lograrlo, después de cada inserción o eliminación, el árbol realiza **rotaciones** para rebalancearse.

```
BST degenerado:         Árbol AVL equivalente:
1                              4
 \                           /   \
  2                         2     5
   \                       / \
    3                     1   3
     \
      4
       \
        5
```

**Tipos de rotación:**
- Rotación simple izquierda
- Rotación simple derecha
- Rotación doble izquierda-derecha
- Rotación doble derecha-izquierda

La búsqueda en un AVL es siempre **O(log n)**, garantizado.

#### Árboles B

Los árboles B son árboles **multi-llave** (cada nodo puede tener más de una clave y más de dos hijos) diseñados para minimizar los accesos a disco. Son la estructura detrás de casi todas las bases de datos y sistemas de archivos.

Un árbol B de orden `m` garantiza que cada nodo tiene entre `⌈m/2⌉` y `m` hijos.

---

### 5.10 Comparación de algoritmos de ordenamiento

| Algoritmo | Mejor caso | Promedio | Peor caso | Espacio | Estable |
|---|---|---|---|---|---|
| Quicksort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Mergesort | O(n log n) | O(n log n) | O(n log n) | O(n) | Sí |
| Heapsort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Shell Sort | O(n log n) | O(n^1.3) | O(n²) | O(1) | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Sí |
| Bucket Sort | O(n+k) | O(n+k) | O(n²) | O(n+k) | Sí |

*Estable = mantiene el orden relativo de elementos iguales.*

**¿Cuándo usar cuál?**
- **Quicksort:** uso general, datos en memoria, rendimiento promedio excelente.
- **Mergesort:** cuando necesitas estabilidad o datos externos (archivos grandes).
- **Heapsort:** cuando el espacio extra es crítico.
- **Insertion Sort:** listas casi ordenadas o muy pequeñas (n < 20).

---

### 5.11 Insight 2026

`std::sort` en la STL de C++ usa **introsort** — un híbrido de quicksort, heapsort e insertion sort que garantiza O(n log n) en todos los casos y O(n log n) en promedio.

**Ordenamiento externo** (tema 5.6 del temario) se refiere a ordenar datos que no caben en RAM. Mergesort es la base de esto: se ordena en bloques que caben en memoria, luego se mezclan. Hadoop y Spark hacen esto a escala de terabytes.

Las tablas hash están en todas partes en 2026: los diccionarios de Python, los objetos de JavaScript, `std::unordered_map` en C++, Redis, las tablas de enrutamiento en redes.

---

### 5.12 Ejercicios

**Comprensión:**
1. ¿Por qué Quicksort tiene peor caso O(n²)? ¿En qué situación ocurre?
2. ¿Qué significa que un algoritmo de ordenamiento sea **estable**? ¿Por qué importa?
3. Dado el arreglo `[7, 2, 9, 4, 1, 8, 3]`, muestra los pasos del mergesort hasta obtener el resultado.

**Implementación:**
4. Implementa Insertion Sort y mídelo con `std::chrono` para `n = 100`, `n = 1000`, `n = 10000`. ¿Confirmas el comportamiento O(n²)?
5. Implementa una tabla hash con direccionamiento abierto (linear probing) en vez de encadenamiento.
6. Implementa búsqueda binaria en su versión recursiva y verifica que produce el mismo resultado que la iterativa.

---

## Apéndice A — Cheat Sheet de Complejidades

```
O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(2ⁿ)

Para n = 1,000,000:
  O(1)      →  1 operación
  O(log n)  →  ~20 operaciones
  O(n)      →  1,000,000 operaciones
  O(n log n)→  ~20,000,000 operaciones
  O(n²)     →  1,000,000,000,000 operaciones  ← inaceptable
```

---

## Apéndice B — Comandos esenciales de compilación

```bash
# Compilar archivo simple
g++ -std=c++17 -Wall -g archivo.cpp -o ejecutable

# Ejecutar
./ejecutable

# Detectar memory leaks
valgrind --leak-check=full ./ejecutable

# Analizar estáticamente
cppcheck --enable=all archivo.cpp

# Depurar con gdb
gdb ./ejecutable
(gdb) run
(gdb) break 42       # parar en línea 42
(gdb) print variable # ver valor de variable
(gdb) backtrace      # ver pila de llamadas
(gdb) quit
```

---

## Apéndice C — La STL como referencia

```cpp
#include <vector>        // std::vector — arreglo dinámico
#include <list>          // std::list — lista doblemente ligada
#include <stack>         // std::stack — pila
#include <queue>         // std::queue — cola
#include <deque>         // std::deque — cola de doble extremo
#include <map>           // std::map — árbol BST de pares clave-valor
#include <set>           // std::set — árbol BST de claves únicas
#include <unordered_map> // std::unordered_map — tabla hash
#include <unordered_set> // std::unordered_set — conjunto con hash
#include <algorithm>     // std::sort, std::find, std::binary_search
```

Para cada estructura que implementas a mano en este curso, existe una versión en la STL. Cuando termines el curso, úsalas. Pero ahora, constrúyelas tú.

---

## Apéndice D — Glosario

| Término | Definición |
|---|---|
| Heap (montículo) | Árbol binario completo donde cada padre es mayor/menor que sus hijos |
| Heap (memoria) | Región de memoria para asignación dinámica (`new`/`delete`). No confundir con el anterior |
| Stack (pila) | Estructura LIFO |
| Stack (memoria) | Región de memoria para variables locales y llamadas a funciones |
| Nodo | Unidad básica de una lista ligada o árbol |
| Puntero | Variable que guarda una dirección de memoria |
| Complejidad amortizada | Costo promedio de una operación en una secuencia larga |
| In-place | Algoritmo que ordena sin usar espacio adicional significativo |
| Estable | Algoritmo que mantiene el orden relativo de elementos iguales |
| Colisión | Dos claves distintas que producen el mismo valor hash |

---

*Esta guía está pensada para acompañarte, no para ser devorada. Abre una terminal, escribe el código, rómpelo, entiende por qué se rompe. Ahí está el aprendizaje.*

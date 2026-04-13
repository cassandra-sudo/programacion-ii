# Estructuras de Datos en C++ — Enfoque TAD (Tipo Abstracto de Dato)

> Este documento es una guía estructurada para entender las estructuras de datos fundamentales desde su definición abstracta hasta su implementación en C++. Está pensado para quien ya maneja variables, tipos básicos y flujos de control.

---

## Conceptos previos: Sintaxis esencial

Antes de ver cada TAD, es necesario entender algunos bloques de construcción que aparecen en todas las implementaciones.

### Templates (`template <typename T>`)

Permiten escribir una clase o función que trabaja con **cualquier tipo de dato** sin repetir código.

```cpp
template <typename T>   // T es un "parámetro de tipo"
class Caja {
    T contenido;        // T se reemplaza por int, double, string, etc. al usar la clase
};

Caja<int>    c1;   // T = int
Caja<string> c2;   // T = string
```

### Structs anidados (nodos)

Un `struct` define un agrupamiento de datos. Cuando se anida dentro de una clase, es privado y solo la clase lo conoce.

```cpp
struct Node {
    T data;       // el valor que guarda
    Node* next;   // apuntador al siguiente nodo
    Node(T d) : data(d), next(nullptr) {}  // constructor del nodo
};
```

### Apuntadores

Un apuntador almacena la **dirección de memoria** de otro objeto.

```cpp
Node* ptr;          // ptr es un apuntador a Node (aún no apunta a nada)
ptr = new Node(5);  // reserva memoria y apunta a ella
ptr->data;          // accede al campo data del objeto apuntado
delete ptr;         // libera la memoria reservada con new
ptr = nullptr;      // buena práctica: evita apuntador "colgante"
```

| Sintaxis | Significado |
|---|---|
| `T* p` | p es un apuntador a T |
| `*p` | el valor en la dirección que guarda p |
| `p->campo` | equivale a `(*p).campo` |
| `new T(...)` | reserva memoria dinámica y devuelve un apuntador |
| `delete p` | libera esa memoria |
| `nullptr` | apuntador nulo (no apunta a nada) |

### Constructor y Destructor

```cpp
class MiClase {
public:
    MiClase() { /* se ejecuta al crear el objeto */ }
    ~MiClase() { /* se ejecuta al destruir el objeto — liberar memoria aquí */ }
};
```

El **destructor** (`~`) es crítico cuando se usa memoria dinámica: si no se libera, se produce una **fuga de memoria** (*memory leak*).

### Lista de inicialización

```cpp
Node(T d) : data(d), next(nullptr) {}
//           ^^^^^^   ^^^^^^^^^^^
//           inicializa miembros antes de entrar al cuerpo
```

Es más eficiente que asignar dentro del cuerpo. Se usa con frecuencia en constructores.

---

## ¿Qué es un TAD?

Un **Tipo Abstracto de Dato (TAD)** define:

1. **Tipo** — La naturaleza del dato: qué representa y cómo está organizado.
2. **Operaciones** — Qué acciones se pueden realizar sobre él.
3. **Propiedades** — Las garantías que cumplen esas operaciones (invariantes).

La clave es la **separación entre interfaz e implementación**: el usuario del TAD solo necesita conocer *qué hace*, no *cómo lo hace*.

---

## 1. Lista (Ligada Simple)

### Tipo

Una **lista ligada** es una secuencia de nodos donde cada nodo contiene un valor y un apuntador al siguiente. El acceso es **secuencial**: para llegar al elemento `i` hay que recorrer desde el principio.

```
[dato|next] → [dato|next] → [dato|next] → nullptr
   head
```

### Operaciones

| Operación | Descripción | Complejidad |
|---|---|---|
| `push_front(x)` | Inserta al inicio | O(1) |
| `push_back(x)` | Inserta al final | O(n) |
| `pop_front()` | Elimina el primero | O(1) |
| `front()` | Lee el primero | O(1) |
| `isEmpty()` | ¿Está vacía? | O(1) |
| `size()` | Número de elementos | O(1) o O(n) |

### Propiedades

- El orden de inserción se preserva.
- No hay acceso aleatorio por índice en O(1).
- La memoria crece y decrece de forma dinámica.

### Implementación

```cpp
template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    Node* head;
    int currentSize;

public:
    LinkedList() : head(nullptr), currentSize(0) {}

    ~LinkedList() {
        while (!isEmpty()) pop_front();
    }

    void push_front(T value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        currentSize++;
    }

    T pop_front() {
        if (isEmpty()) throw std::underflow_error("Lista vacía");
        Node* temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        currentSize--;
        return value;
    }

    T front() const {
        if (isEmpty()) throw std::underflow_error("Lista vacía");
        return head->data;
    }

    bool isEmpty() const { return head == nullptr; }
    int size() const { return currentSize; }
};
```

### Diagnóstico del código original (`implementacion2.cpp`)

El archivo compartido tiene **tres errores**. En él `currentSize` es el nombre del miembro, pero en `push`, `pop` y `size()` se usa `size` (que colisiona con el nombre del método). Las correcciones son:

```cpp
// ❌ Error en el original:
size++;         // 'size' es el nombre del método, no el miembro
size--;
int size() const { return size; }   // recursión infinita / ambigüedad

// ✅ Corrección:
currentSize++;
currentSize--;
int size() const { return currentSize; }
```

---

## 2. Pila (Stack)

### Tipo

Una pila organiza los datos bajo el principio **LIFO** (*Last In, First Out*): el último elemento en entrar es el primero en salir. Se puede imaginar como una pila de platos: solo se puede tomar o poner en la cima.

```
       ← top
  [ C ]
  [ B ]
  [ A ]
```

### Operaciones

| Operación | Descripción | Complejidad |
|---|---|---|
| `push(x)` | Inserta en la cima | O(1) |
| `pop()` | Elimina la cima y la devuelve | O(1) |
| `top()` | Lee la cima sin eliminarla | O(1) |
| `isEmpty()` | ¿Está vacía? | O(1) |
| `size()` | Número de elementos | O(1) |

### Propiedades

- Solo se puede acceder al elemento de la cima.
- `pop()` en una pila vacía es un error (underflow).
- Toda operación es O(1).

### Implementación

```cpp
template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    Node* topPtr;
    int currentSize;

public:
    Stack() : topPtr(nullptr), currentSize(0) {}

    ~Stack() {
        while (!isEmpty()) pop();
    }

    void push(T element) {
        Node* newNode = new Node(element);
        newNode->next = topPtr;
        topPtr = newNode;
        currentSize++;
    }

    T pop() {
        if (isEmpty()) throw std::underflow_error("Pila vacía");
        Node* temp = topPtr;
        T value = temp->data;
        topPtr = topPtr->next;
        delete temp;
        currentSize--;
        return value;
    }

    T top() const {
        if (isEmpty()) throw std::underflow_error("Pila vacía");
        return topPtr->data;
    }

    bool isEmpty() const { return topPtr == nullptr; }
    int size() const { return currentSize; }
};
```

### Uso práctico

```cpp
Stack<int> s;
s.push(10);
s.push(20);
s.push(30);
std::cout << s.top();  // 30
s.pop();
std::cout << s.top();  // 20
```

---

## 3. Cola (Queue)

### Tipo

Una cola organiza los datos bajo el principio **FIFO** (*First In, First Out*): el primero en entrar es el primero en salir. Como una fila en una caja registradora.

```
enqueue →  [ D ][ C ][ B ][ A ]  → dequeue
                               front
```

### Operaciones

| Operación | Descripción | Complejidad |
|---|---|---|
| `enqueue(x)` | Inserta al final | O(1) |
| `dequeue()` | Elimina el frente y lo devuelve | O(1) |
| `front()` | Lee el frente sin eliminarlo | O(1) |
| `isEmpty()` | ¿Está vacía? | O(1) |
| `size()` | Número de elementos | O(1) |

### Propiedades

- El orden de llegada determina el orden de salida.
- Se necesitan dos apuntadores: `front` y `back`.
- `dequeue()` en una cola vacía es un error.

### Implementación

```cpp
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    Node* frontPtr;
    Node* backPtr;
    int currentSize;

public:
    Queue() : frontPtr(nullptr), backPtr(nullptr), currentSize(0) {}

    ~Queue() {
        while (!isEmpty()) dequeue();
    }

    void enqueue(T element) {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            frontPtr = backPtr = newNode;
        } else {
            backPtr->next = newNode;
            backPtr = newNode;
        }
        currentSize++;
    }

    T dequeue() {
        if (isEmpty()) throw std::underflow_error("Cola vacía");
        Node* temp = frontPtr;
        T value = temp->data;
        frontPtr = frontPtr->next;
        if (frontPtr == nullptr) backPtr = nullptr;  // cola quedó vacía
        delete temp;
        currentSize--;
        return value;
    }

    T front() const {
        if (isEmpty()) throw std::underflow_error("Cola vacía");
        return frontPtr->data;
    }

    bool isEmpty() const { return frontPtr == nullptr; }
    int size() const { return currentSize; }
};
```

---

## 4. Arreglo Dinámico (`std::vector`)

### Tipo

Un arreglo dinámico almacena elementos de forma **contigua en memoria** (como un arreglo normal), pero puede crecer automáticamente cuando se llena. Ofrece acceso aleatorio en O(1) por índice.

```
índice:  [0] [1] [2] [3] [4] ...
datos:   [10][20][30][40][50]
         ↑ memoria contigua
```

### Operaciones

| Operación | Descripción | Complejidad |
|---|---|---|
| `push_back(x)` | Agrega al final | O(1) amortizado |
| `pop_back()` | Elimina el último | O(1) |
| `operator[i]` | Acceso por índice | O(1) |
| `at(i)` | Acceso con verificación de rango | O(1) |
| `size()` | Número de elementos | O(1) |
| `empty()` | ¿Está vacío? | O(1) |
| `insert(pos, x)` | Inserta en posición | O(n) |
| `erase(pos)` | Elimina en posición | O(n) |
| `clear()` | Elimina todo | O(n) |

### Propiedades

- Acceso aleatorio O(1) gracias a la memoria contigua.
- `push_back` es O(1) amortizado: cuando se llena, duplica su capacidad y copia.
- Insertar/eliminar en el medio requiere desplazar elementos: O(n).

### Uso de `std::vector`

```cpp
#include <vector>

std::vector<int> v;

v.push_back(10);
v.push_back(20);
v.push_back(30);

std::cout << v[1];      // 20  (sin verificación de rango)
std::cout << v.at(1);   // 20  (lanza excepción si fuera de rango)
std::cout << v.size();  // 3

// Iterar
for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
}

// Iterar con rango (más moderno)
for (int x : v) {
    std::cout << x << " ";
}

v.erase(v.begin() + 1);  // elimina el elemento en índice 1
v.clear();                // vacía el vector
```

### Capacidad vs Tamaño

```cpp
std::vector<int> v;
v.reserve(100);         // reserva espacio para 100 elementos (sin agregarlos)
std::cout << v.size();      // 0   (elementos actuales)
std::cout << v.capacity();  // 100 (espacio reservado)
```

---

## 5. Mapa / Diccionario (`std::map` y `std::unordered_map`)

### Tipo

Un mapa almacena pares **clave → valor**. Dada una clave única, recupera su valor asociado de forma eficiente. Es la representación en C++ de un diccionario.

```
"nombre" → "Ana"
"edad"   → 25
"ciudad" → "Guadalajara"
```

### Dos variantes principales

| | `std::map` | `std::unordered_map` |
|---|---|---|
| Implementación | Árbol rojo-negro | Tabla hash |
| Claves ordenadas | Sí (por defecto) | No |
| Búsqueda | O(log n) | O(1) promedio |
| Iteración | En orden | Sin orden garantizado |

### Operaciones

| Operación | Descripción |
|---|---|
| `m[clave] = valor` | Inserta o actualiza |
| `m.at(clave)` | Acceso con excepción si no existe |
| `m.find(clave)` | Devuelve iterador; `end()` si no existe |
| `m.count(clave)` | 1 si existe, 0 si no |
| `m.erase(clave)` | Elimina la entrada |
| `m.size()` | Número de pares |
| `m.empty()` | ¿Está vacío? |

### Propiedades

- Cada clave es única. Insertar con `[]` sobre una clave existente **sobreescribe** el valor.
- `m[clave]` crea la entrada con valor por defecto si la clave no existe — usar `find` para verificar sin crear.
- `std::map` mantiene las claves ordenadas; `std::unordered_map` es más rápido pero sin orden.

### Uso

```cpp
#include <map>
#include <unordered_map>

std::map<std::string, int> edades;

edades["Ana"]   = 25;
edades["Carlos"] = 30;
edades["Beatriz"] = 28;

// Acceso
std::cout << edades["Ana"];      // 25
std::cout << edades.at("Carlos"); // 30

// Verificar existencia antes de acceder
if (edades.find("Diana") != edades.end()) {
    std::cout << edades["Diana"];
} else {
    std::cout << "No existe";
}

// Iterar (en orden alfabético para std::map)
for (auto& par : edades) {
    std::cout << par.first << ": " << par.second << "\n";
}
```

---

## 6. Árbol Binario de Búsqueda (ABB)

### Tipo

Un árbol binario de búsqueda (ABB o BST) organiza los datos en una estructura jerárquica donde cada nodo tiene al más dos hijos. Para cualquier nodo con valor `v`:

- Todos los nodos en su **subárbol izquierdo** tienen valores **menores** que `v`.
- Todos los nodos en su **subárbol derecho** tienen valores **mayores** que `v`.

```
        [50]
       /    \
    [30]    [70]
    /  \    /  \
  [20][40][60][80]
```

### Operaciones

| Operación | Descripción | Complejidad promedio | Peor caso |
|---|---|---|---|
| `insert(x)` | Inserta un valor | O(log n) | O(n) |
| `search(x)` | Busca un valor | O(log n) | O(n) |
| `remove(x)` | Elimina un valor | O(log n) | O(n) |
| `inorder()` | Recorre en orden (izq-raíz-der) | O(n) | O(n) |

*El peor caso O(n) ocurre cuando el árbol queda degenerado (como una lista) si se insertan elementos ya ordenados.*

### Propiedades

- El recorrido **inorder** produce los elementos en orden ascendente.
- La eficiencia depende del **balance**: un árbol balanceado garantiza O(log n).
- Existen variantes auto-balanceadas: AVL, Árbol Rojo-Negro (`std::map` usa uno internamente).

### Implementación

```cpp
template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T d) : data(d), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* insert(Node* node, T value) {
        if (node == nullptr) return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        // si value == node->data, no se insertan duplicados
        return node;
    }

    bool search(Node* node, T value) const {
        if (node == nullptr) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    void inorder(Node* node) const {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(T value)       { root = insert(root, value); }
    bool search(T value) const { return search(root, value); }
    void inorder() const       { inorder(root); std::cout << "\n"; }
};
```

### Uso

```cpp
BST<int> tree;
tree.insert(50);
tree.insert(30);
tree.insert(70);
tree.insert(20);
tree.insert(40);

tree.inorder();           // 20 30 40 50 70
std::cout << tree.search(30);  // 1 (true)
std::cout << tree.search(99);  // 0 (false)
```

---

## 7. Lista Doblemente Ligada

### Tipo

En una lista doblemente ligada, cada nodo tiene **dos apuntadores**: uno al nodo siguiente y otro al nodo anterior. Esto permite recorrer la lista en ambas direcciones.

```
nullptr ← [prev|dato|next] ↔ [prev|dato|next] ↔ [prev|dato|next] → nullptr
           head                                    tail
```

### Diferencias con la lista simple

| | Lista Simple | Lista Doble |
|---|---|---|
| Apuntadores por nodo | 1 (`next`) | 2 (`prev` + `next`) |
| Recorrido | Solo hacia adelante | En ambas direcciones |
| Eliminar nodo (dado apuntador) | O(n) — hay que encontrar el anterior | O(1) |
| Insertar antes de un nodo | O(n) | O(1) |
| Memoria | Menos | Más (un apuntador extra) |

### Operaciones

| Operación | Descripción | Complejidad |
|---|---|---|
| `push_front(x)` | Inserta al inicio | O(1) |
| `push_back(x)` | Inserta al final | O(1) |
| `pop_front()` | Elimina el primero | O(1) |
| `pop_back()` | Elimina el último | O(1) |
| `front()` / `back()` | Lee primero / último | O(1) |

### Implementación

```cpp
template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T d) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node* headPtr;
    Node* tailPtr;
    int currentSize;

public:
    DoublyLinkedList() : headPtr(nullptr), tailPtr(nullptr), currentSize(0) {}

    ~DoublyLinkedList() {
        while (!isEmpty()) pop_front();
    }

    void push_back(T value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            headPtr = tailPtr = newNode;
        } else {
            newNode->prev = tailPtr;
            tailPtr->next = newNode;
            tailPtr = newNode;
        }
        currentSize++;
    }

    void push_front(T value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            headPtr = tailPtr = newNode;
        } else {
            newNode->next = headPtr;
            headPtr->prev = newNode;
            headPtr = newNode;
        }
        currentSize++;
    }

    T pop_back() {
        if (isEmpty()) throw std::underflow_error("Lista vacía");
        Node* temp = tailPtr;
        T value = temp->data;
        tailPtr = tailPtr->prev;
        if (tailPtr) tailPtr->next = nullptr;
        else headPtr = nullptr;  // la lista quedó vacía
        delete temp;
        currentSize--;
        return value;
    }

    T pop_front() {
        if (isEmpty()) throw std::underflow_error("Lista vacía");
        Node* temp = headPtr;
        T value = temp->data;
        headPtr = headPtr->next;
        if (headPtr) headPtr->prev = nullptr;
        else tailPtr = nullptr;
        delete temp;
        currentSize--;
        return value;
    }

    bool isEmpty() const { return headPtr == nullptr; }
    int size() const { return currentSize; }
};
```

---

## 8. Lista Circular

### Tipo

En una lista circular, el último nodo apunta de regreso al primero (y en la versión doble, el primero también apunta al último). No hay un `nullptr` al final: la lista forma un **ciclo cerrado**.

```
    ┌──────────────────────────┐
    ↓                          │
[dato|next] → [dato|next] → [dato|next]
    ↑
   head (o tail, según implementación)
```

### Cuándo es útil

- Turnos rotativos (Round Robin en sistemas operativos).
- Buffers circulares.
- Estructuras donde el "siguiente" del último es el primero de manera natural.

### Propiedades importantes

- Se detecta el final del recorrido cuando se vuelve al nodo inicial, no cuando se encuentra `nullptr`.
- Insertar/eliminar el nodo "cabeza" requiere actualizar el enlace del último nodo.

### Implementación (simple, con `tail`)

Una implementación eficiente usa un apuntador al **último** nodo (`tail`). Desde `tail` se accede al primero con `tail->next`.

```cpp
template <typename T>
class CircularList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    Node* tail;   // apunta al último; tail->next apunta al primero
    int currentSize;

public:
    CircularList() : tail(nullptr), currentSize(0) {}

    ~CircularList() {
        while (!isEmpty()) pop_front();
    }

    void push_back(T value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            newNode->next = newNode;  // apunta a sí mismo
            tail = newNode;
        } else {
            newNode->next = tail->next;  // nuevo apunta al primero
            tail->next = newNode;        // último apunta al nuevo
            tail = newNode;              // tail avanza al nuevo último
        }
        currentSize++;
    }

    T pop_front() {
        if (isEmpty()) throw std::underflow_error("Lista vacía");
        Node* front = tail->next;
        T value = front->data;
        if (front == tail) {
            tail = nullptr;  // era el único nodo
        } else {
            tail->next = front->next;
        }
        delete front;
        currentSize--;
        return value;
    }

    // Imprimir toda la lista (recorre una vuelta)
    void print() const {
        if (isEmpty()) return;
        Node* current = tail->next;  // empieza en el primero
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != tail->next);
        std::cout << "\n";
    }

    bool isEmpty() const { return tail == nullptr; }
    int size() const { return currentSize; }
};
```

---

## Resumen comparativo

| Estructura | Acceso | Inserción | Eliminación | Orden | Uso típico |
|---|---|---|---|---|---|
| Lista simple | O(n) | O(1) frente | O(1) frente | Inserción | General, base de pila/cola |
| Pila | O(1) solo cima | O(1) | O(1) | LIFO | Recursión, deshacer, parseo |
| Cola | O(1) solo frente | O(1) final | O(1) frente | FIFO | Scheduling, BFS, buffers |
| `std::vector` | O(1) | O(1)* final | O(n) medio | Índice | Arreglo flexible general |
| `std::map` | O(log n) | O(log n) | O(log n) | Por clave | Diccionarios, índices |
| ABB | O(log n) prom | O(log n) prom | O(log n) prom | Clave | Búsqueda eficiente |
| Lista doble | O(n) | O(1) extremos | O(1) dado nodo | Inserción | Editores, historial |
| Lista circular | O(n) | O(1) | O(1) frente | Cíclico | Round-robin, buffers |

*`push_back` en vector es O(1) amortizado.*

---

## Equivalencias en la STL de C++

C++ ofrece implementaciones listas para usar en `<...>`:

| TAD | STL | Header |
|---|---|---|
| Lista | `std::list` | `<list>` |
| Pila | `std::stack` | `<stack>` |
| Cola | `std::queue` | `<queue>` |
| Arreglo dinámico | `std::vector` | `<vector>` |
| Mapa ordenado | `std::map` | `<map>` |
| Mapa no ordenado | `std::unordered_map` | `<unordered_map>` |
| ABB / Árbol AVL | `std::set` / `std::map` | `<set>` / `<map>` |
| Lista doble | `std::list` | `<list>` |
| Cola doble (deque) | `std::deque` | `<deque>` |

Implementar estas estructuras desde cero es el mejor ejercicio para interiorizar su funcionamiento. Una vez comprendidas, la STL ofrece versiones robustas, optimizadas y listas para producción.

---

*Fin del documento — TAD y Estructuras de Datos en C++*

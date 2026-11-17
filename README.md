# PhysiCode
---

## Información del Proyecto
- **Equipo:** Syntax Overlords
- **Integrantes:**
  - Jesús Alfonso Guerrero García — V-30.960.664
  - Eldry Jesús Briceño Zerpa — V-31.704.456

---

## Descripción General

**PhysiCode** es un lenguaje de dominio específico (DSL) diseñado para entornos educativos y de ingeniería enfocado en el modelado, resolución y evaluación de ecuaciones físicas (cinemática, dinámica y termodinámica).

El lenguaje resuelve el problema común de errores en cálculos científicos derivados de inconsistencias dimensionales y conversiones manuales erróneas. PhysiCode permite vincular variables numéricas a unidades físicas explícitas tales como `[m]`, `[s]`, `[kg]`, `[N]`, `[m/s]`, `[m/s^2]` y `[J]`, realizando comprobaciones dimensionales en tiempo de compilación y ejecutando conversiones automáticas de unidades de forma transparente.

### Características Principales

- **Paradigma:** Imperativo, centrado en la evaluación secuencial de expresiones matemáticas, asignaciones y estructuras de control.
- **Tipado:** Estático y fuerte. Prohíbe operaciones físicamente incompatibles (como sumar una longitud con un tiempo) antes de la ejecución.
- **Nivel de abstracción:** Alto nivel y de dominio específico (DSL), con notación física intuitiva.

---

## Estructura del Proyecto

```text
PhysiCode/
├── .gitignore
├── CMakeLists.txt
├── README.md
├── include/
│   └── physicode_lexer.hpp    # Definición de tokens, interfaz y funciones del lexer
├── src/
│   ├── physicode_lexer.cpp    # Implementación de reglas regex y lógica del analizador léxico
│   └── main.cpp               # Punto de entrada del compilador y pruebas
└── examples/                  # Programas de ejemplo para probar el analizador
    ├── example1.txt           # Cinemática y conversión automática
    ├── example2.txt           # Dinámica, Segunda Ley de Newton y fórmula
    └── example3.txt           # Termodinámica, notación científica y ciclo
```

---

## Requisitos del Sistema

- Compilador compatible con **C++17** 
- **CMake** >= 3.20
- Biblioteca **DeSiGNAR** 

---

## Compilación

El proyecto utiliza **CMake** como sistema de construcción.

### Configurar la ruta de DeSiGNAR
Abre el archivo `CMakeLists.txt` ubicado en la raíz del proyecto y escribe la ruta hacia tu directorio de **DeSiGNAR** en la variable `DESIGNAR_DIR`:

```cmake
# ==============================================================================
# Configuración de la ruta de DeSiGNAR
# ==============================================================================
# Escribe aquí la ruta hacia la carpeta de la biblioteca DeSiGNAR:
set(DESIGNAR_DIR "/ruta/a/tu/DeSiGNAR")
```

### Compilar el proyecto
Desde la raíz del proyecto, ejecuta en la terminal:

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

Una vez finalizada la compilación, se generará el ejecutable `physicode` dentro de la carpeta `build/`.

> **Nota para recompilaciones:** Si realizas cambios en el código posteriormente, solo necesitas ejecutar `cmake --build .` dentro de `build/` sin repetir los pasos anteriores.

---

## Ejecución

El ejecutable `physicode` recibe como argumento la ruta a un archivo de código fuente para tokenizarlo y mostrar la tabla detallada de tokens reconocidos.

Estando dentro de la carpeta `build/`, puedes probar cualquiera de los archivos de ejemplo proporcionados:

```bash
# Ejemplo 1: Cinemática y conversión automática de unidades
./physicode ../examples/example1.txt

# Ejemplo 2: Dinámica, Segunda Ley de Newton y constante G
./physicode ../examples/example2.txt

# Ejemplo 3: Termodinámica, notación científica y ciclos de simulación
./physicode ../examples/example3.txt
```

También puedes analizar cualquier archivo personalizado indicando su ruta:

```bash
./physicode /ruta/a/tu/archivo.txt
```

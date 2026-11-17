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

## Analizador Léxico

La primera fase del compilador está implementada sobre la clase `Designar::Lexer` de la biblioteca **DeSiGNAR**. Su función es leer el código fuente de **PhysiCode**, validar cada lexema frente a las expresiones regulares del lenguaje y transformar la entrada en un flujo secuencial de tokens (`DynArray<Designar::Token>`) listo para el análisis sintáctico.

### Categorías de Tokens Reconocidos

| Categoría / Token | Descripción | Ejemplos |
| :--- | :--- | :--- |
| **Palabras Reservadas** | Declaración, control de flujo, E/S, conversión y magnitudes (`KW_VAR`, `KW_CONST`, `KW_FORMULA`, `KW_IF`, `KW_ELSE`, `KW_ELIF`, `KW_WHILE`, `KW_FOR`, `KW_INPUT`, `KW_SHOW`, `KW_PRINT`, `KW_TO`, `KW_MAGNITUDE`, `KW_UNIT`) | `var`, `const`, `formula`, `if`, `while`, `show`, `to` |
| **Constantes y Literales** | Constantes matemáticas/físicas y booleanos (`CONST_PI`, `CONST_EULER`, `CONST_G`, `TOKEN_BOOL`) | `PI`, `EULER`, `G`, `true`, `false` |
| **Tipos Primitivos** | Tipos de datos base (`TYPE_NUM`, `TYPE_BOOL`, `TYPE_STRING`) | `num`, `bool`, `string` |
| **`TOKEN_UNIT`** | Unidades físicas encerradas entre corchetes | `[m]`, `[km/h]`, `[m/s^2]`, `[N]` |
| **`TOKEN_NUMBER`** | Enteros, decimales y notación científica | `21`, `7.51`, `2.5e4`, `2e9` |
| **`TOKEN_STRING`** | Cadenas de texto delimitadas por comillas dobles | `"Calculo completado"` |
| **`TOKEN_ID`** | Identificadores de variables, fórmulas y magnitudes | `velocidad`, `masa_carro`, `Presion` |
| **`TOKEN_OP_ARIT`** | Operadores aritméticos y de potencia | `+`, `-`, `*`, `/`, `^` |
| **`TOKEN_OP_REL`** | Operadores relacionales de comparación | `==`, `!=`, `<=`, `>=`, `<`, `>` |
| **`TOKEN_OP_LOGIC`** | Operadores lógicos | `&&`, \|\|, `!` |
| **`TOKEN_ASIGN`** | Operador de asignación | `=` |
| **`TOKEN_DELIM`** | Delimitadores y signos de puntuación | `;`, `(`, `)`, `{`, `}`, `,` |
| **`COMENTARIO`** | Comentarios de línea y de bloque *(filtrados antes del parser)* | `// ...`, `/* ... */` |
| **`IGNORAR`** | Espacios en blanco, tabulaciones y saltos de línea *(filtrados antes del parser)* | `' '`, `\t`, `\n`, `\r` |

### Decisiones de Diseño y Prioridad Léxica

- **Compatibilidad con el motor de DeSiGNAR:** Las expresiones regulares se construyen mediante bloques explícitos de unión, concatenación y cerraduras compatibles con los autómatas finitos generados por **DeSiGNAR**.
- **Jerarquía de registro:** El orden en que se añaden las reglas dentro de `make_lexer()` resuelve ambigüedades léxicas:
  1. **`COMENTARIO` antes de `TOKEN_OP_ARIT`:** Evita que los inicios de comentario `//` o `/*` sean interpretados como el operador de división `/`.
  2. **Palabras reservadas y constantes antes de `TOKEN_ID`:** Asegura que lexemas como `var`, `formula` o `G` se clasifiquen con su token específico y no como identificadores genéricos.
  3. **Operadores compuestos antes de simples:** Los operadores de dos caracteres (`==`, `!=`, `<=`, `>=`, `&&`, `||`) tienen precedencia sobre `=` y `!`.
- **Depuración del flujo de salida:** Las funciones de tokenización descartan automáticamente los tokens `IGNORAR` y `COMENTARIO`, entregando únicamente los tokens sintácticamente relevantes.

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

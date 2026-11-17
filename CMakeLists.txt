cmake_minimum_required(VERSION 3.20)
project(PhysiCode VERSION 1.0.0 LANGUAGES CXX)

# Exigir estándar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Advertencias de compilación
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ==============================================================================
# Configuración de la ruta de DeSiGNAR
# ==============================================================================
# Escribe aquí la ruta hacia la carpeta de la biblioteca DeSiGNAR:
set(DESIGNAR_DIR "")

if("${DESIGNAR_DIR}" STREQUAL "")
    message(FATAL_ERROR 
        "\n"
        "===============================================================================\n"
        " ERROR: Debes especificar la ruta de la biblioteca DeSiGNAR en este archivo.\n"
        " Abre CMakeLists.txt y coloca la ruta en la variable DESIGNAR_DIR:\n"
        "   set(DESIGNAR_DIR \"/ruta/a/tu/DeSiGNAR\")\n"
        "===============================================================================\n"
    )
endif()

# Directorio de cabeceras y librería estática basados en la ruta especificada
set(DESIGNAR_INCLUDE_DIR "${DESIGNAR_DIR}/include")

# Ubicación de libDesignar.a (verifica en lib/ o en build/)
if(EXISTS "${DESIGNAR_DIR}/lib/libDesignar.a")
    set(DESIGNAR_LIBRARY "${DESIGNAR_DIR}/lib/libDesignar.a")
elseif(EXISTS "${DESIGNAR_DIR}/build/libDesignar.a")
    set(DESIGNAR_LIBRARY "${DESIGNAR_DIR}/build/libDesignar.a")
else()
    set(DESIGNAR_LIBRARY "${DESIGNAR_DIR}/lib/libDesignar.a")
endif()

message(STATUS "DeSiGNAR Directorio: ${DESIGNAR_DIR}")
message(STATUS "DeSiGNAR Include:    ${DESIGNAR_INCLUDE_DIR}")
message(STATUS "DeSiGNAR Library:    ${DESIGNAR_LIBRARY}")

# ==============================================================================
# Definición del Ejecutable
# ==============================================================================
# Recopilar los archivos fuentes de src/
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(physicode ${SOURCES})

# Directorios de inclusión (cabeceras locales y de DeSiGNAR)
target_include_directories(physicode PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${DESIGNAR_INCLUDE_DIR}"
)

# Enlazar biblioteca DeSiGNAR y soporte de hilos (Threads/pthread)
find_package(Threads REQUIRED)
target_link_libraries(physicode PRIVATE
    Threads::Threads
    "${DESIGNAR_LIBRARY}"
)

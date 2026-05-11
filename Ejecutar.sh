#!/bin/bash

# Nombre del archivo fuente y del ejecutable
ARCHIVO_FUENTE="Practica_3_SO.cpp"
EJECUTABLE="programa"

echo "Compilando el cliente C++: $ARCHIVO_FUENTE..."

# Compilación usando comillas para el nombre con espacios
g++ "$ARCHIVO_FUENTE" -o "$EJECUTABLE"

if [ $? -eq 0 ]; then
    echo "Compilación exitosa."
    echo "Asegúrate de tener el servidor corriendo antes de continuar."
    
    # Dar permisos de ejecución por si acaso
    chmod +x "$EJECUTABLE"
    
    echo "Ejecutando el cliente..."
    echo "-----------------------------------"
    ./"$EJECUTABLE"
else
    echo "Error: La compilación ha fallado."
fi
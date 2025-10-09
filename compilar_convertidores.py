#!/usr/bin/env python3

# Compilar los programas para convertir de .txt a .dat

import sys

from utils import cargar_env, limpiar_cache_python, compilar_src

def main():
    env = cargar_env()
    separador = env.get("SEPARADOR")
    if not separador:
        print("Separador no encontrado")
        return
    archivos = env.get("NOMBRES_CONVERTIDORES")
    if not archivos:
        print("Archivos no encontrados")
        return
    archivos = [archivo.strip() for archivo in archivos.split(separador) if archivo.strip()]
    for archivo in archivos:
        archivo.strip()
        compilar_src(env, archivo)
    limpiar_cache_python()

if __name__ == "__main__":
    main()

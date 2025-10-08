#!/usr/bin/env python3

# Script para darle formato estándar al código

from utils import cargar_env, ejecutar_comando, limpiar_cache_python, exist_file

def formatear_codigo(src):
    if not src or not exist_file(src):
        print(f"Archivo no encontrado: {src}")
        return
    comando = ["clang-format", "-i", src]
    if ejecutar_comando(comando):
        print(f"Archivo formateado: {src}")

def main():
    env = cargar_env()
    src = env.get("SRC")
    formatear_codigo(src)
    limpiar_cache_python()

if __name__ == "__main__":
    main()

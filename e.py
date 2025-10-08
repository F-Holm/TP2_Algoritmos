#!/usr/bin/env python3

# Ejecuta el programa compilado

import sys

from utils import cargar_env, ejecutar_comando, detectar_sistema, SistemaOperativo, base_name, exist_file, limpiar_cache_python

def ejecutar_ejecutable(env):
    src = env.get("SRC")
    if not src:
        print("No se encontró la variable SRC en el .env")
        return

    exe_file = base_name(src) + ".exe"

    if not exist_file(exe_file):
        print(f"No se encontró el ejecutable: {exe_file}")
        return

    so = detectar_sistema()
    if so == SistemaOperativo.WINDOWS:
        comando = [exe_file]
    elif so == SistemaOperativo.LINUX:
        comando = ["wine", exe_file]
    else:
        print(f"Sistema operativo no soportado: {sys.platform}")
        return

    ejecutar_comando(comando)

def main():
    env = cargar_env()
    ejecutar_ejecutable(env)
    limpiar_cache_python()

if __name__ == "__main__":
    main()

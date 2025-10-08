#!/usr/bin/env python3

import os
import subprocess

from l import ejecutar_comando, limpiar_cache_python

def cargar_env(ruta="scripts_conf.env"):
    env_vars = {}
    if not os.path.isfile(ruta):
        return env_vars
    with open(ruta, "r") as f:
        for linea in f:
            linea = linea.strip()
            if not linea or linea.startswith("#"):
                continue
            if "=" in linea:
                clave, valor = linea.split("=", 1)
                env_vars[clave.strip()] = valor.strip().strip('"').strip("'")
    return env_vars

def formatear_codigo(src):
    if not src or not os.path.isfile(src):
        print(f"Archivo no encontrado: {src}")
        return
    comando = ["clang-format", "-i", src]
    if ejecutar_comando(comando):
        pass # print(f"Archivo formateado: {src}")

def main():
    env = cargar_env()
    src = env.get("SRC")
    formatear_codigo(src)
    limpiar_cache_python()

if __name__ == "__main__":
    main()

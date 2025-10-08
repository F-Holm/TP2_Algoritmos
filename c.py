#!/usr/bin/env python3

import os
import sys
import subprocess

from utils import cargar_env, ejecutar_comando, limpiar_cache_python, exist_file

def detectar_compilador(env):
    if sys.platform.startswith("win"):
        comp_var = env.get("COMPILADOR_WINDOWS")
    else:
        comp_var = env.get("COMPILADOR_LINUX")
    if not comp_var:
        print("No se definió el compilador para este sistema operativo.")
        return None
    # Obtener el comando real del compilador
    compilador = env.get(comp_var)
    if not compilador:
        print(f"No se encontró la variable de compilador: {comp_var}")
        return None
    return compilador.split()

def compilar_src(env):
    src = env.get("SRC")
    if not src or not os.path.isfile(src):
        print(f"Archivo SRC no encontrado: {src}")
        return
    compilador = detectar_compilador(env)
    if not compilador:
        return

    base_name = os.path.splitext(os.path.basename(src))[0]
    output_file = base_name + ".exe"

    flags = []
    flags += env.get("INFO_FLAGS", "").split()
    flags += env.get("ESTANDAR", "").split()
    flags += env.get("EXTRA", "").split()

    modo = env.get("MODO", "D")
    if modo.upper() == "R":
        flags += env.get("RELEASE_FLAGS", "").split()
    else:
        flags += env.get("DEBUG_FLAGS", "").split()

    comando = compilador + [src, "-o", output_file] + flags
    if ejecutar_comando(comando):
        print(f"✅ Compilación completada: {output_file}")

def main():
    env = cargar_env()
    compilar_src(env)
    limpiar_cache_python()

if __name__ == "__main__":
    main()

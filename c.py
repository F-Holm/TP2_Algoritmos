#!/usr/bin/env python3

# Compilar el código

import sys

from utils import cargar_env, ejecutar_comando, limpiar_cache_python, exist_file, detectar_sistema, SistemaOperativo, base_name, formatear_codigo

def detectar_compilador(env):
    SO = detectar_sistema()
    if SO == SistemaOperativo.WINDOWS:
        comp_var = env.get("COMPILADOR_WINDOWS")
    elif SO == SistemaOperativo.LINUX:
        comp_var = env.get("COMPILADOR_LINUX")
    else:
        print(f"Sistema operativo no soportado: {sys.platform}")
        return None

    if not comp_var:
        print("No se definió el compilador para este sistema operativo.")
        return None

    compilador = env.get(comp_var)
    if not compilador:
        print(f"No se encontró la variable de compilador: {comp_var}")
        return None

    return compilador.split()


def compilar_src(env):
    src = env.get("SRC")
    if not src or not exist_file(src):
        print(f"Archivo SRC no encontrado: {src}")
        return
    formatear_codigo(src)
    compilador = detectar_compilador(env)
    if not compilador:
        return

    output_file = base_name(src) + ".exe"

    flags = []
    flags += env.get("INFO_FLAGS", "").split()
    flags += env.get("ESTANDAR", "").split()
    flags += env.get("EXTRA", "").split()

    modo = env.get("MODO")
    if not modo:
        print(f"Configuración 'MODO' no encontrada")
        return
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

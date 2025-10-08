#!/usr/bin/env python3

# Restaura al último commit todos los archivos que tengan una extensión que esté en REST_EXT

import subprocess

from utils import cargar_env, ejecutar_comando, limpiar_cache_python, exist_dir


def restaurar_archivos(env):
    rest_ext = env.get("REST_EXT")
    separador = env.get("SEPARADOR")
    
    if not rest_ext or not separador:
        return
    
    extensiones = [ext.strip() for ext in rest_ext.split(separador) if ext.strip()]
    if not extensiones:
        return

    if not exist_dir(".git"):
        return

    # Obtener archivos modificados
    try:
        result = subprocess.run(
            ["git", "ls-files", "-m"],
            capture_output=True,
            text=True,
            check=True
        )
        archivos_modificados = result.stdout.splitlines()
    except Exception:
        archivos_modificados = []

    restaurados = []

    for archivo in archivos_modificados:
        if any(archivo.endswith(f".{ext}") for ext in extensiones):
            cmd = ["git", "checkout", "--", archivo]
            subprocess.run(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            restaurados.append(archivo)

    if restaurados:
        print("✅ Archivos restaurados:")
        for f in restaurados:
            print(f"  {f}")
    else:
        print("No se encontraron archivos modificados con las extensiones indicadas.")

def main():
    env = cargar_env()
    restaurar_archivos(env)
    limpiar_cache_python()

if __name__ == "__main__":
    main()

#!/usr/bin/env python3

# Restaura al último commit todos los archivos que tengan una extensión que esté en REST_EXT

from utils import cargar_env, ejecutar_comando, limpiar_cache_python, exist_dir

def restaurar_archivos(env):
    rest_ext = env.get("REST_EXT")
    if not rest_ext:
        print("No se definieron extensiones para restaurar en REST_EXT")
        return

    extensiones = [ext.strip().lstrip(".") for ext in rest_ext.split(",") if ext.strip()]
    if not extensiones:
        print("No se encontraron extensiones válidas para restaurar")
        return

    if not exist_dir(".git"):
        print("⚠️ No es un repositorio Git")
        return

    for ext in extensiones:
        patron = f"*.{ext}"
        comando = ["git", "checkout", "--", patron]
        if ejecutar_comando(comando):
            print(f"✅ Restaurados archivos con extensión: .{ext}")

def main():
    env = cargar_env()
    restaurar_archivos(env)
    limpiar_cache_python()

if __name__ == "__main__":
    main()

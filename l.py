#!/usr/bin/env python3

# Script de limpieza del proyecto.

from utils import ejecutar_comando, limpiar_cache_python, exist_dir

def git_clean() -> None:
    if not exist_dir(".git"):
        print("⚠️ No es un repositorio Git. Saltando limpieza con git...")
        return

    comando = ["git", "clean", "-Xfd"]
    if ejecutar_comando(comando):
        pass # print("✅ Limpieza de Git completada.")

def main() -> None:
    git_clean()
    limpiar_cache_python()

if __name__ == "__main__":
    main()

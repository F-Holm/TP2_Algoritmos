#!/usr/bin/env python3

# Script de limpieza del proyecto.

import os
import subprocess
import sys
import shutil
from pathlib import Path


def ejecutar_comando(comando: list[str]) -> bool:
    try:
        # print(f"→ Ejecutando: {' '.join(comando)}")
        subprocess.run(comando, check=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"❌ Error al ejecutar {' '.join(comando)}: {e}")
    except FileNotFoundError:
        print(f"⚠️ Comando no encontrado: {comando[0]}")
    return False

def eliminar_directorio(ruta: str) -> bool:
    if os.path.isdir(ruta):
        try:
            shutil.rmtree(ruta)
            # print(f"🗑️  Eliminado: {ruta}")
            return True
        except Exception as e:
            pass # print(f"❌ No se pudo eliminar {ruta}: {e}")
    return False

def git_clean() -> None:
    if not os.path.isdir(".git"):
        # print("⚠️ No es un repositorio Git. Saltando limpieza con git...")
        return

    comando = ["git", "clean", "-Xfd"]
    if ejecutar_comando(comando):
        pass # print("✅ Limpieza de Git completada.")


def limpiar_cache_python() -> None:
    eliminar_directorio("./__pycache__/")

def limpiar() -> None:
    git_clean()
    limpiar_cache_python()

def main() -> None:
    limpiar()

if __name__ == "__main__":
    main()
